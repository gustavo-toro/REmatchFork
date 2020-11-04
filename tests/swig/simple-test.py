import rematchpy as re

regex = ".*!x{.<3,>}!y{.<1,2>}.*"
document = "aabcad"

rgx = re.Regex(regex)
it = rgx.finditer(document)

for match in it:
  for var in match.variables():
    print("!{}:".format(var), match.span(var), end='\t')
  print("")