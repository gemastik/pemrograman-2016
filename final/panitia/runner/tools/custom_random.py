'''
Created on Jul 5, 2015

@author: dolphinigle
'''
import random


def RandomCombination(pool, pick):
  # randomly pick "pick" element from 0...pool-1.
  if pick > pool/2:
    combin = set(RandomCombination(pool, pool-pick))
    res = []
    for i in range(pool):
      if i not in combin:
        res.append(i)
    return res

  chosen = set()
  while len(chosen) < pick:
    chosen.add(random.randint(0, pool-1))
  return sorted(list(chosen))

def RandomPartition(pool, pick, min_value=0):
  # Randomly partition n into  pick non-negative integers. ORDER MATTERS.
  assert pool >= min_value * pick
  comb = RandomCombination(pool+pick-1 - min_value * pick, pick-1)
  seq = []
  comb = [-1] + comb + [pool+pick-1 - min_value * pick]
  for i, j in zip(comb, comb[1:]):
    seq.append(j-i-1 + min_value)
  return seq


def RandomStr(alphabet, length):
  return ''.join([random.choice(alphabet) for _ in range(length)])


def Sequence(alphabet, length):
  return [random.choice(alphabet) for _ in range(length)]
  


def RandomMergeSequence(seq1, seq2):
  result = [None] * (len(seq1) + len(seq2))
  locations = RandomCombination(len(result), len(seq1))
  i = 0
  p1 = 0
  p2 = 0
  for j in range(len(result)):
    if i < len(locations) and locations[i] == j:
      i += 1
      result[j] = seq1[p1]
      p1 += 1
    else:
      result[j] = seq2[p2]
      p2 += 1
  return result


