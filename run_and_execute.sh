#!/bin/bash
cmake -H. -Bbuild/Release
cmake --build build/Release
build/Release/bin/rematch test.txt -e '!x{b}'
# 1) Crear tests con catch2 (último commit refactoring)
# 2) Ver delta eficiencia con distintas distance = 1 primero 
# 3) Ver como actúa con proteomas (cuánto más sube)
# 4) En enero se ve lo de los epsilons.
# 5) Con el encoding de utf-8 se caería, pero por lo menos no lo vamos a tocar ahora mismo.

