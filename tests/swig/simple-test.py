import os.path
import sys

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.abspath(dir_path + '/' + '../../build/Release/bin/SWIG'))

import rematch as re

regex = ".*!x{.<3,>}!y{.<1,2>}.*"
document = "aabcad"

rgx = re.RegEx(regex)
iterator = rgx.findIter(document)

match = iterator.next()

while match:
  for var in match.variables():
    print("!{}:".format(var), match.span(var), end='\t')
  print("")
  match = iterator.next()
