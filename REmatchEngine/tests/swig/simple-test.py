import os.path
import sys

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.abspath(dir_path + '/' + '../../build/Release/bin/SWIG'))

import rematch as re

regex = ".*!y{b+}!x{a+}.*"
document = "bbbbaaaabbbbbaaa"

rgx = re.RegEx(regex)
match = rgx.findIter(document)

while match:
  for var in match.variables():
    print("!{}:".format(var), match.span("x"), end='\t')
  print("")
  print(match.doc())
  match = rgx.findIter(document)
