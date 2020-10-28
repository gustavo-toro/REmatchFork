import os.path
import sys

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.abspath(dir_path + '/' + '../../build/bin/SWIG'))

import rematch as re

regex = ".*!y{b+}!x{a+}.*"
document = "bbbbaaaabbbbbaaa"

rgx = re.RegEx(regex)
match = rgx.findIter(document)

while match:
  for var in match.variables():
    print("!{}:".format(var), match.span(var), end='\t')
  print("")
  match = rgx.findIter(document)


def findIter(pattern, doc):
  rgx = RegEx(pattern);
  findIter = rgx.findIter()
  while True:
    yield rgx.findIter(doc);



findIter(".*x{a}.*", "aa")
findIter("x{a}", "aa")