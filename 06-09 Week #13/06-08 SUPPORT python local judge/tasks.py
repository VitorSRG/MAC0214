#!/usr/bin/env python3


"""Redirect tasks to judge."""


import invoke
import os
import re
import sys

from invoke import run, task
from invoke.context import Context

from local_judge.judge import *


__workdir__ = os.getcwd()
__taskdir__ = __taskdir__ \
              if '__taskdir__' in globals() \
              else os.path.dirname(__file__)

GLOBAL_CTX  = GLOBAL_CTX \
              if 'GLOGAL_CTX' in globals() \
              else Context()


#region task libraries
def load(file):
    file = os.path.normpath(os.path.join(os.path.dirname(__file__), 
                                         os.path.expanduser(file)))

    if not os.path.isfile(file):
        return

    exec(compile(open(file).read(), file, 'exec'), 
         {**globals(), 
          '__file__': file, 
          '__taskdir__': __taskdir__,
          '__name__': 'tasks_library'}, 
         locals())
    globals().update({**locals()})

load('/tasks.py')
load('~/tasks.py')
# load('./local_judge/judge.py')
#endregion



if __name__ == 'tasks':
    pass

if __name__ == '__main__':
    pass
