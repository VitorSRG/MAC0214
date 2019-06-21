#!/usr/bin/env python3
 
"""
 -  domain:     GoogleCode Jam 2019
 -  contest:    Round 1C
 -  problem:    B
 -  title:      Power Arrangers
 -  link:       https://codingcompetitions.withgoogle.com/codejam/round/00000000000516b9/0000000000134e91
 -  hash:       GKS19_1B_B

 -  author:     Vitor SRG
 -  version:    1.0 04/05/2019

 -  tags:       tests interactive query recursive factorial

 -  language:   C++17
"""


def factorial(n):
    if n <= 1:
        return 1
    return n*factorial(n-1)

def main():
    # file = open('test.out', 'w')
    t, f = [int(s) for s in input().split(" ")]
    # print(t, f, file=file, flush=True)

    for ti in range(1, t+1):
        candidates = list(range(119))
        missing = ''

        for i in range(5):
            buckets = [[] if chr(j+ord('A')) not in missing else -1
                       for j in range(5)]

            for j in candidates:
                print(j*5+(i+1), flush=True)
                letter = ord(input()) - ord('A')
                # print(j, letter, sep=':', file=file, end=' ', flush=True)
                buckets[letter].append(j)
            # print(file=file, flush=True)

            buckets_amin = list(map(lambda item: len(item) if item != -1 
                                                           else -1, buckets)) \
                           .index(factorial(5-1-i)-1)
            # print(factorial(5-1-i)-1, file=file, flush=True)

            candidates = buckets[buckets_amin]
            missing += chr(ord('A')+buckets_amin)
            # print(missing, file=file, flush=True)

        print(missing)
        verdict = input()
        if verdict != 'Y':
            exit(0)

    exit(0)


def unit_test():
    exit(0)


"""
 -  test:
    command:    !command |-
                python {workdir}/interactive_runner.py 
                python {workdir}/testing_tool.py 0 -- {absdir}/{filebase}.bin

 -  test:
    command:    !command |-
                python {workdir}/interactive_runner.py 
                python {workdir}/testing_tool.py 1 -- {absdir}/{filebase}.bin
"""

if __name__ == '__main__':
    main()
