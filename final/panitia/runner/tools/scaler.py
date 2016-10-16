'''
Created on Jul 4, 2015

@author: dolphinigle
'''

def ScaleInt(value, orig_range, new_range):
  min_orig, max_orig = orig_range
  new_min, new_max = new_range
  assert min_orig <= value <= max_orig
  newval = (value - min_orig) * (new_max - new_min)
  newval = float(newval) / float(max_orig - min_orig)
  newval = int(round(newval))
  newval += new_range[0]
  if newval < new_min:
    newval = new_min
  if newval > new_max:
    newval = new_max
  return newval

def ScaleSequenceInt(values, orig_range, new_range):
  return [ScaleInt(value, orig_range, new_range) for value in values]
