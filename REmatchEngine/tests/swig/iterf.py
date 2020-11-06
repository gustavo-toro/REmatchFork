def f(a):
  a += "b"
  while True:
    a += "c"
    yield a

if __name__ == "__main__":
  gen = f("aa")
  print(next(gen), next(gen), sep='\n')