#!/usr/bin/env python3


"""Redirect tasks to judge."""


import colorful
import invoke
import os
import pandas as pd
import re
import sys
import tempfile
import yaml

from datetime import datetime, timedelta
from invoke import task
from invoke.context import Context
from invoke.collection import Collection
from yaml import CLoader as Loader


__author__      = 'Vitor Santa Rosa Gomes'
__copyright__   = 'Copyright 2018, Vitor Santa Rosa Gomes'
__credits__     = ['Vitor Santa Rosa Gomes']
__license__     = 'MIT'
__version__     = '1.0'
__maintainer__  = 'Vitor Santa Rosa Gomes'
__email__       = 'vitorssrg@usp.br'
__status__      = 'Development'


__workdir__ = os.getcwd()
__taskdir__ = __taskdir__ \
              if '__taskdir__' in globals() \
              else os.path.dirname(__file__)

GLOBAL_CTX  = GLOBAL_CTX \
              if 'GLOGAL_CTX' in globals() \
              else Context()

with open(os.path.join(os.path.dirname(__file__), './judge.yml')) as configfile: 
    SETTINGS    = yaml.load(configfile)

    DEFAULTS    = SETTINGS['DEFAULTS']
    ALIASES     = {alias: key
                   for key, aliases in SETTINGS['ALIASES'].items()
                   for alias in aliases}


#region colors
colorful.use_8_ansi_colors()

class Empty(object):
    def __init__(self, *args, **kwargs):
        pass

    def __call__(self, *args, **kwargs):
        return self

    def __getattribute__(self, key):
        try:
            return object.__getattribute__(self, key)
        except AttributeError:
            return self

    def __getitem__(self, key):
        return self

    def __repr__(self):
        return ''

class Color(object):
    """
        https://en.wikipedia.org/wiki/ANSI_escape_code
        https://pypi.org/project/colorama/#recognised-ansi-sequences
    """

    back        = f'\r'

    up          = f'\033[{1}A'
    down        = f'\033[{1}B'
    right       = f'\033[{1}C'
    left        = f'\033[{1}D'

    clear       = f'\033[{2}J'
    clear_down  = f'\033[{0}J'
    clear_up    = f'\033[{1}J'
    clear_line  = f'\033[{2}K'
    clear_right = f'\033[{0}K'
    clear_left  = f'\033[{1}K'

    def __init__(self, *args, **kwargs):
        pass

    def __call__(self, *args, **kwargs):
        return self

    def __getattr__(self, key):
        try:
            return object.__getattr__(self, key)
        except AttributeError:
            pass

        try:
            return getattr(colorful, key)
        except AttributeError:
            return self

    def __getitem__(self, key):
        return eval(f'self.{key}', globals(), locals())

    def __repr__(self):
        return ''


    @staticmethod
    def up(n=1):
        return f'\033[{n}A'

    @staticmethod
    def down(n=1):  
        return f'\033[{n}B'

    @staticmethod
    def right(n=1):
        return f'\033[{n}C'

    @staticmethod
    def left(n=1):
        return f'\033[{n}D'


def style(msg, file=sys.stdout, colored=None):
    if colored is None:
        colored = file.isatty()

    if colored:
        color = Color()
    else:
        color = Empty()

    return msg.format_map(color)

def cprint(*args, sep=' ', end='\n', 
           file=sys.stdout, flush=False, colored=None):

    args = [style(arg, file=file, colored=colored) 
            if isinstance(arg, str) 
            else arg
            for arg in args]

    print(*args, sep=sep, end=end, file=file, flush=flush)
#endregion

#region yaml
def str_factory(cname, rname):
    cls = type(cname, (str,), {})

    yaml.add_constructor(rname, 
                         lambda loader, node: cls(loader.construct_scalar(node)))

    return cls

Literal  = str_factory('Literal', '!literal')
UnitTest = str_factory('UnitTest', '!unit_test')
File     = str_factory('File', '!file')
Command  = str_factory('Command', '!command')

# class Literal(str):
#     def __new__(cls, data):
#         return super(Literal, cls).__new__(cls, data)

#     @staticmethod
#     def constructor(loader, node):
#         value = loader.construct_scalar(node)
#         return Literal(value)

# yaml.add_constructor('!literal', Literal.constructor)
#endregion

#region utils
def dig(d, keys):
    if keys[0] not in d:
        return None
    if len(keys) == 1:
        return d[keys[0]]
    return dig(d[keys[0]], keys[1:])

def escape(s):
    return repr(s)[1:-1].replace('"', '\\"')

def parse_time(s):
    regex = re.compile(r'\b(((?P<hours>\d+)\:)?(?P<minutes>\d+)\:)?'
                         r'(?P<seconds>\d+)'
                         r'(\.(?P<milliseconds>\d+))?\b')
    groups = regex.match(s)

    if not groups:
        regex = re.compile(r'\b((?P<seconds>\d+)s'
                              r'|(?P<minutes>\d+)m'
                              r'|(?P<hours>\d+)h)\b')
        groups = regex.match(s)

    if not groups:
        return
    groups = groups.groupdict()
    
    return timedelta(**{key: int(value) 
                        for key, value in groups.items() 
                        if value is not None}).total_seconds()

def format_time(s):
    return f'{s:5.2f}'

def parse_memory(b):
    predecs = list(map(lambda i: i.lower(), ['B', 'kB',  'MB',  'GB',  'TB' ]))
    prebins = list(map(lambda i: i.lower(), ['B', 'KiB', 'MiB', 'GiB', 'TiB']))

    search = re.compile(r'\b(\d+(?:\.\d+)?)(\w+)?\b').search(b)

    if not search:
        return

    if search.group(2) is None:
        return float(search.group(1))

    exp = predecs.index(search.group(2).lower())

    if exp > 0:
        return float(search.group(1))*10**(3*exp)

    exp = prebins.index(search.group(2).lower())

    if exp > 0:
        return float(search.group(1))*2**(10*exp)

def format_memory(b):
    predecs = ['B', 'kB',  'MB',  'GB',  'TB' ]

    for i in range(len(predecs)):
        if b <= 10**3:
            return f'{b:6.2f}{predecs[i]}'

        b /= 10**3

    return f'{b*10**3:.2f}{predecs[-1]}'
#endregion

#region helpers
#TODO: options
def parse(file, platform=None):
    if not hasattr(parse, 'cache'):
        parse.cache = dict()

    if file in parse.cache:
        return parse.cache[file]

    file     = os.path.expanduser(file)

    workdir  = __workdir__
    taskdir  = __taskdir__
    judgedir = os.path.dirname(__file__)

    filerel  = os.path.relpath(file, workdir)
    fileabs  = os.path.normpath(os.path.join(workdir, file))
    filename = os.path.basename(file)
    filebase, \
    fileext  = os.path.splitext(file)
    filetype = ALIASES[fileext.lower()]

    dirabs   = os.path.dirname(fileabs)
    dirname  = os.path.basename(dirabs)
    dirrel   = os.path.relpath(dirabs, workdir)

    if os.path.isfile(fileabs):
        with open(file) as inputfile:
            filetext = inputfile.read()

        metadelm = dig(DEFAULTS, [platform, filetype, 'p']) \
                   or dig(DEFAULTS, [platform, 'd', 'p']) \
                   or dig(DEFAULTS, ['d', filetype, 'p']) \
                   or dig(DEFAULTS, ['d', 'd', 'p'])

        fileyml  = '\n'.join(line
                             for match in re.findall(metadelm, filetext)
                             for line in match.split('\n'))

        filemeta = yaml.load(fileyml)

    for metaitem in filemeta:
        if not isinstance(metaitem, dict):
            continue

        if 'language' in metaitem:
            filetype  = ALIASES[metaitem['language'].lower()]

    parse.cache[file] = locals()
    return parse.cache[file]

def sandbox(ctx, cmd, pipe_in='', memory_limit=None, time_limit=None):
    with tempfile.NamedTemporaryFile('w+') as timefile:
        box  = ''

        box += f'/usr/bin/time -o {timefile.name} -f "%e %M %x" sh -c "'

        if memory_limit is not None:
            memory_limit = int(2*parse_memory(memory_limit)/10**3)+1

            box += f'ulimit -v {memory_limit}; '
            box += f'ulimit -m {memory_limit}; '
        if time_limit is not None:
            time_limit = int(2*parse_time(time_limit))+1

            box += f'ulimit -t {time_limit}; '
            box += f'timeout -k {time_limit} {time_limit} '

        box += escape(f'sh -c "{escape(cmd)}" 2>&1') + '"'

        res = ctx.run(box, warn=True, hide=True)

        output  = res.stdout
        elapsed, mpeek, status = timefile.read().strip().split()[-3:]

        elapsed = parse_time(elapsed)
        mpeek   = parse_memory(f'{mpeek}kB')
        status  = int(status)

    return output, elapsed, mpeek, status
#endregion

#region tasks
#TODO: verbose mode

@task
def new(ctx, file, platform=None):
    filedata = parse(file, platform=platform)

    cmd = dig(DEFAULTS, [filedata['platform'], filedata['filetype'], 'n']) \
          or dig(DEFAULTS, [filedata['platform'], 'd', 'n']) \
          or dig(DEFAULTS, ['d', filedata['filetype'], 'n']) \
          or dig(DEFAULTS, ['d', 'd', 'n'])

    if cmd is None:
        return True

    cmd = cmd.format_map(filedata)

    status = sandbox(ctx, cmd)[-1]

    return status == 0

@task
def build(ctx, file, platform=None):
    filedata = parse(file, platform=platform)

    cmd = dig(DEFAULTS, [filedata['platform'], filedata['filetype'], 'b']) \
          or dig(DEFAULTS, [filedata['platform'], 'd', 'b']) \
          or dig(DEFAULTS, ['d', filedata['filetype'], 'b']) \
          or dig(DEFAULTS, ['d', 'd', 'b'])

    if cmd is None:
        return True

    cmd = cmd.format_map(filedata)

    cprint('{bold}BUILD{back}{reset}', end='', flush=True)
    output, elapsed, mpeek, status = sandbox(ctx, cmd)
    color = 'green' if status == 0 else 'red'

    cprint(f'{{{color}}}{{bold}}{"BUILD":8s}{{reset}}', 
           f'{format_time(elapsed):8s}', 
           f'{format_memory(mpeek):8s}')

    if status == 0:
        return True

    cprint(f'{{bold}}{cmd}{{reset}}')
    print(output)

    return False

@task
def run(ctx, file, platform=None):
    filedata = parse(file, platform=platform)

    cmd = dig(DEFAULTS, [filedata['platform'], filedata['filetype'], 'r']) \
          or dig(DEFAULTS, [filedata['platform'], 'd', 'r']) \
          or dig(DEFAULTS, ['d', filedata['filetype'], 'r']) \
          or dig(DEFAULTS, ['d', 'd', 'r'])

    if cmd is None:
        return True

    cmd = cmd.format_map(filedata)

    status = sandbox(ctx, cmd)[-1]

    return status == 0

@task
def test(ctx, file, platform=None):
    filedata = parse(file, platform=platform)
    all_pass = True

    def verdict_memory(mpeek, mlimit):
        if mlimit is None:
            return '', format_memory(mpeek)
        elif mpeek <= parse_memory(mlimit):
            return '{green}', format_memory(mpeek)
        else:
            return '{red}', format_memory(mpeek)
               
    def verdict_time(elapsed, tlimit):
        if tlimit is None:
            return '', format_time(elapsed)
        elif elapsed <= parse_time(tlimit):
            return '{green}', format_time(elapsed)
        else:
            return '{red}', format_time(elapsed)

    def verdict_status(exited, expected):
        if expected is None:
            return '', f'{exited: 3d}'
        elif exited == int(expected):
            return '{green}', f'{exited: 3d}'
        else:
            return '{red}', f'{exited: 3d}'

    def verdict_output(output, expected):
        if expected is None:
            return '', ''
        elif output == expected:
            return '{green}', 'OK'
        elif re.sub(r'[\s\n]+', ' ', output) == re.sub(r'[\s\n]+', ' ', expected):
            return '{yellow}', 'SP'
        else:
            return '{red}', 'NO'

    def colordiff(ctx, width, output, expected):
        with tempfile.NamedTemporaryFile('w+') as outputfile:
            with tempfile.NamedTemporaryFile('w+') as expectedfile:
                outputfile.write(output)
                outputfile.flush()
                expectedfile.write(expected)
                expectedfile.flush()

                pipe = '| colordiff' if sys.stdout.isatty() else ''

                return sandbox(ctx, f'diff -y --width={width} '
                                    f'{outputfile.name} '
                                    f'{expectedfile.name}'
                                    f'{pipe}')[0]

    test_count   = 0

    time_limit   = None
    memory_limit = None
    exit_expect  = 0

    try:
        width    = int(ctx.run('tput cols', 
                               warn=True, hide=True, pty=True).stdout)
    except:
        width    = 150

    width = min(width, 150)


    table_format = ['{:>2.2s}', 
                    '{:>8.8s}', 
                    '{:>6.6s}', 
                    '{:>4.4s}',
                    '{:>3.3s}',
                    '{:<30.30s}',
                    '{:<30.30s}',
                    '{:<30.30s}',]

    table_title  = ['n',
                    'memory',
                    'time',
                    'stat',
                    'out',
                    'input',
                    'output',
                    'expected',]

    if width < 130: table_format[6] = '{:<25.25s}'
    if width < 130: table_format[7] = '{:<25.25s}'
    if width < 120: table_format[5] = '{:<25.25s}'
    if width < 110: table_format[6] = '{:<20.20s}'
    if width < 110: table_format[7] = '{:<20.20s}'
    if width < 100: table_format[6] = '\b{:<0.0s}'
    if width < 100: table_format[7] = '{:<25.25s}'
    if width <  90: table_format[5] = '{:<20.20s}'
    if width <  90: table_format[7] = '{:<20.20s}'
    if width <  80: table_format[5] = '{:<15.15s}'
    if width <  80: table_format[7] = '{:<15.15s}'
    if width <  70: table_format[5] = '{:<25.25s}'
    if width <  70: table_format[7] = '\b{:<0.0s}'
    if width <  60: table_format[5] = '{:<15.15s}'
    if width <  50: table_format[5] = '\b{:<0.0s}'

    cols = width - 32

    table_format[5:] = [f'{{:<{cols//3}.{cols//3}s}}',
                        f'{{:<{cols//3}.{cols//3}s}}',
                        f'{{:<{cols//3}.{cols//3}s}}']

    if width < 100:
        table_format[5:] = [f'{{:<{cols//2}.{cols//2}s}}',
                            '\b{:<0.0s}',
                            f'{{:<{cols//2}.{cols//2}s}}']

    if width <  70:
        table_format[5:] = [f'{{:<{cols}.{cols}s}}',
                            '\b{:<0.0s}',
                            '\b{:<0.0s}']

    if width <  50:
        table_format[5:] = ['\b{:<0.0s}',
                            '\b{:<0.0s}',
                            '\b{:<0.0s}']


    cprint(*[f'{{bold}}{fmt.format(val)}{{reset}}'
             for fmt, val in zip(table_format, table_title)])


    for metaitem in filedata['filemeta']:
        if not isinstance(metaitem, dict):
            continue

        if 'time' in metaitem and 'test' not in metaitem:
            time_limit   = metaitem['time']

        if 'memory' in metaitem and 'test' not in metaitem:
            memory_limit = metaitem['memory']

        if 'test' in metaitem:
            test_count  += 1

            metaitem.setdefault('memory', memory_limit)
            metaitem.setdefault('time', time_limit)
            metaitem.setdefault('status', exit_expect)

            if 'command' in metaitem and isinstance(metaitem['command'], UnitTest):
                cmd = dig(DEFAULTS, [filedata['platform'], filedata['filetype'], 'u']) \
                      or dig(DEFAULTS, ['d', filedata['filetype'], 'u']) \
                      or dig(DEFAULTS, ['d', 'd', 'u'])
            elif 'command' in metaitem and metaitem['command'] is not None:
                cmd = metaitem['command']
            else:
                cmd = dig(DEFAULTS, [filedata['platform'], filedata['filetype'], 'r']) \
                      or dig(DEFAULTS, [filedata['platform'], 'd', 'r']) \
                      or dig(DEFAULTS, ['d', filedata['filetype'], 'r']) \
                      or dig(DEFAULTS, ['d', 'd', 'r'])

            cmd = cmd.format_map(filedata)
            

            if 'input' not in metaitem:
                input = ''
            elif isinstance(metaitem['input'], File):
                with open(metaitem["input"].format_map(filedata)) as inputfile:
                    input = inputfile.read()
                cmd = f'cat "{metaitem["input"].format_map(filedata)}" | {cmd}'
            elif isinstance(metaitem['input'], Command):
                input = sandbox(ctx, metaitem["input"].format_map(filedata))[0]
                cmd = f'{metaitem["input"].format_map(filedata)} | {cmd}'
            else:
                input = metaitem["input"].format_map(filedata)
                cmd = f'printf "{escape(metaitem["input"].format_map(filedata))}" | {cmd}'
    
    
            if 'output' not in metaitem:
                expected = None
            elif isinstance(metaitem['output'], File):
                with open(metaitem["output"].format_map(filedata)) as inputfile:
                    expected = inputfile.read()
            elif isinstance(metaitem['output'], Command):
                expected = sandbox(ctx, metaitem["output"].format_map(filedata))[0]
            else:
                expected = metaitem["output"].format_map(filedata)


            output, elapsed, \
            mpeek, status = sandbox(ctx, cmd, 
                                    memory_limit=metaitem['memory'],
                                    time_limit=metaitem['time'])


            columns = [('', str(test_count)),
                       verdict_memory(mpeek, metaitem['memory']),
                       verdict_time(elapsed, metaitem['time']),
                       verdict_status(status, metaitem['status']),
                       verdict_output(output, expected),
                       ('', re.sub(r'(?<!\\)\\n', '\u21b5 ', escape(input))),
                       ('', re.sub(r'(?<!\\)\\n', '\u21b5 ', escape(output))),
                       ('', re.sub(r'(?<!\\)\\n', '\u21b5 ', escape(expected or ''))),]

            cprint(*[f'{sty}{fmt.format(val)}{{reset}}'
                    for fmt, (sty, val) in zip(table_format, columns)])

            if (metaitem['status'] is not None 
                and status != int(metaitem['status'])) \
               or (expected is not None and output != expected):
                cprint(f'{{bold}}{cmd}{{reset}}')

                all_pass = False

                print(colordiff(ctx, width, output, expected))

    return all_pass

@task(default=True)
def judge(ctx, file, platform=None):
    filedata = parse(file, platform=platform)

    if build(ctx, file, platform):
        if test(ctx, file, platform):
            clean(ctx, file, platform)

        return True

    return False

@task
def clean(ctx, file, platform=None):
    filedata = parse(file, platform=platform)

    cmd = dig(DEFAULTS, [filedata['platform'], filedata['filetype'], 'c']) \
          or dig(DEFAULTS, [filedata['platform'], 'd', 'c']) \
          or dig(DEFAULTS, ['d', filedata['filetype'], 'c']) \
          or dig(DEFAULTS, ['d', 'd', 'c'])

    if cmd is None:
        return True

    cmd = cmd.format_map(filedata)

    status = sandbox(ctx, cmd)[-1]

    return status == 0
#endregion

#region other tasks
@task
def timeinfo(ctx):
    data = [
        ['max n' , 'worst class'   , 'class type'  , 'example'               ],
        ['11'    , 'O(n!), O(n^6)' , 'exponential' , 'permutations'          ],
        ['18'    , 'O(2^n n^2)'    , ''            , 'DP TSP'                ],
        ['22'    , 'O(2^n n)'      , ''            , 'DP with bitmask'       ],
        ['100'   , 'O(n^4)'        , 'quartic'     , 'DP with 3 dimentions'  ],
        ['400'   , 'O(n^3)'        , 'cubic'       , 'Floyd Warshall'        ],
        ['2K'    , 'O(n^2 lg n)'   , ''            , '2-nested loops + tree' ],
        ['10K'   , 'O(n^2)'        , 'quadratic'   , 'Insertion sort'        ],
        ['1M'    , 'O(n lg n)'     , 'linearithmic', 'Merge sort, segtree'   ],
        ['100M'  , 'O(n)'          , 'linear'      , 'Merge sort, segtree'   ],
        [''      , 'O(lg n)'       , 'logarithmic' , 'binary search'         ],
        [''      , 'O(1)'          , 'constant'    , 'hash lookup'           ],
    ]

    df = pd.DataFrame(data[1:], columns=data[0])

    print(df)

@task
def memoryinfo(ctx):
    #TODO
    pass

@task
def help(ctx):
    #TODO
    print('help')
#endregion


def main(*args, **kwargs):
    help(GLOBAL_CTX)


if __name__ == 'tasks':
    pass

if __name__ == 'tasks_library':
    pass

if __name__ == '__main__':
    main()
