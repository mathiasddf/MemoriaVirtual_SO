#define main main_original
#include "main.cpp"
#undef main
#include <cassert>
int main() {
    vector<int> r = {1, 2, 3, 1, 4, 1, 2};
    Resultado f = simular(r, 3, "FIFO");
    Resultado l = simular(r, 3, "LRU");
    assert(f.fallos == 6 && f.aciertos == 1);
    assert(l.fallos == 5 && l.aciertos == 2);
    assert(f.pasos[4].victima == 1);
    assert(l.pasos[4].victima == 2);
    assert(simular({1, 1, 1}, 1, "FIFO").fallos == 1);
    assert(simular({1, 1, 1}, 1, "LRU").fallos == 1);
    cout << "Todas las pruebas C++ pasaron.\n";
}
