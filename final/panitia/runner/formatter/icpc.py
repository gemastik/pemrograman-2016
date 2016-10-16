'''
Created on Jul 4, 2015

@author: dolphinigle
'''

from collections import defaultdict

class KattisFormatter(object):
  def __init__(self, dirname):
    self.test_case_count = defaultdict(lambda: 1)
    self.dirname = dirname

  def Add(self, content, tc_name=''):
    tc_cnt = self.test_case_count[tc_name]
    self.test_case_count[tc_name] += 1
    full_tc_name = '{2}/{0}{1}.in'.format((tc_name + '_') if tc_name else '',
                                          tc_cnt,
                                          self.dirname)
    f = open(full_tc_name, 'w')
    f.write(content)
    print 'Test case {0} written'.format(full_tc_name)
    f.close()

  def AddLines(self, lines, tc_name):
    return self.Add('\n'.join(lines) + '\n', tc_name)
