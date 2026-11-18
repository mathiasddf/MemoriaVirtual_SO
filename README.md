# Memoria virtual — simulador FIFO y LRU en C++17

Simulador de reemplazo de páginas para el curso de Sistemas Operativos. Emplea 3 marcos y la secuencia `1, 2, 3, 1, 4, 1, 2`. Imprime la traza completa de FIFO y LRU con páginas, marcos, fallos, aciertos, víctimas y tasas.

## Compilación

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic main.cpp -o simulador
./simulador
```

En Windows PowerShell (MinGW): `g++ -std=c++17 main.cpp -o simulador.exe` y luego `./simulador.exe`.

## Pruebas

```bash
g++ -std=c++17 -O2 -Wall -Wextra -pedantic tests.cpp -o tests
./tests
```

## Resultados comprobados

- FIFO: 6 fallos, 1 acierto, 85.71 % de fallos.
- LRU: 5 fallos, 2 aciertos, 71.43 % de fallos.

La implementación completa está en `main.cpp` y se reproduce íntegramente en las diapositivas de Canva. El programa es una **simulación académica de políticas de reemplazo**, no manipula la memoria virtual real del sistema operativo.
