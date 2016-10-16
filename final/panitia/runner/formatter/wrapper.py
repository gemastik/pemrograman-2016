'''
Created on Jul 4, 2015

@author: dolphinigle
'''

class Printer(object):
  def __init__(self, formatter):
    self.formatter = formatter
    self.tc_name = None
    self.ntc = 0

  def Begin(self, tc_name=''):
    assert not self.tc_name, 'Still writing test case {0}'.format(self.tc_name)
    assert tc_name is not None
    self.ntc += 1
    if self.ntc >= 1000:
      raise BaseException('Too many test cases')
    self.lines = []
    self.tc_name = tc_name

  def Close(self):
    self.formatter.AddLines(self.lines, self.tc_name)
    self.tc_name = None

  def Print(self, *args):
    self.lines.append(' '.join(map(str, args)))
