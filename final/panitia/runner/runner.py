'''
Created on Jul 6, 2015

@author: dolphinigle
'''

from formatter import wrapper, icpc
import random

import numpy.random

from tools import scaler, custom_random


def Gen(n_range):
  random.seed(754321)
  printer = wrapper.Printer(icpc.KattisFormatter('../../../../out/sg2015/uniform'))
  m = 10**7

  def Print(colors, shirts, tc_name):
    assert(len(shirts) == len(colors)+1)
    for c in colors:
      assert 1 <= c <= len(colors)
    for i in shirts:
      assert 0 <= i <= m
    assert sum(shirts) >= len(colors)

    printer.Begin(tc_name)
    printer.Print(len(colors))
    printer.Print(' '.join(map(str, colors)))
    printer.Print(' '.join(map(str, shirts)))
    printer.Close()

  # Random
  for _ in range(10):
    n = random.randint(*n_range)
    max_m = random.randint(1, m)
    Print([random.randint(1, n) for _ in range(n)],
          [random.randint(0, max_m) for _ in range(n+1)],
          'random')

  # All match
  n = n_range[-1]
  Print(range(1, n+1),
        [1] * n + [0],
        'best')
  Print([1] * n,
        [n] + [0] * n,
        'best')
  Print([1] * n,
        [m] + [0] * n,
        'best')

  # "Worst"
  Print([n] * n,
        [m] * (n+1),
        'worst')
  Print([n] * n,
        [m] * (n-1) + [0] + [m],
        'worst')
  Print([n] * n,
        [m] * (n-1) + [1] + [m],
        'worst')

  "Special cases"
  Print(range(1, n+1),
        [m] * n + [0],
        'special')
  Print(range(1, n+1),
        [m] * n + [m],
        'special')
  Print([n] * n,
        [m] * n + [0],
        'special')
  Print([n] * n,
        [m] * n + [m],
        'special')

  "Proportional"
  for _ in range(2):
    shirts = [random.randint(1, m) for _ in range(n+1)]
    probabilities = [float(x) / sum(shirts[:-1]) for x in shirts[:-1]]
    guys = map(lambda x: x+1, list(numpy.random.choice(n, n, p=probabilities)))
    Print(guys, shirts, 'proportional')

  # Limited number of shirts in warehouse
  shirtcnts = [n, 2*n, 10*n, 100*n, 1000*n, 2000*n]
  for shirtcnt in shirtcnts:
    distrib = custom_random.RandomPartition(shirtcnt, n+1)
    Print([random.randint(1, n) for _ in range(n)],
          distrib,
          'limited_shirts')

  # No match
  Print(range(1, n+1),
        [0] * n + [m],
        'none')
  Print(range(1, n+1),
        [0] * n + [n],
        'none')

if __name__ == '__main__':
  Gen((2, 50))
