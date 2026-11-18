#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct Paso {
    int pagina, victima;
    bool fallo;
    vector<int> ram;
};

struct Resultado {
    int fallos = 0, aciertos = 0;
    vector<Paso> pasos;
};

Resultado simular(const vector<int>& referencias, int n, const string& algoritmo) {
    vector<int> ram(n, -1), ultimoUso(n, -1);
    queue<int> colaFIFO;
    Resultado r;

    for (int t = 0; t < (int)referencias.size(); ++t) {
        int pagina = referencias[t], victima = -1;
        auto it = find(ram.begin(), ram.end(), pagina);
        bool fallo = (it == ram.end());

        if (!fallo) {
            int pos = (int)(it - ram.begin());
            ultimoUso[pos] = t;
            ++r.aciertos;
        } else {
            ++r.fallos;
            int pos;
            auto libre = find(ram.begin(), ram.end(), -1);
            if (libre != ram.end()) {
                pos = (int)(libre - ram.begin());
            } else if (algoritmo == "FIFO") {
                pos = colaFIFO.front();
                colaFIFO.pop();
            } else {
                pos = (int)(min_element(ultimoUso.begin(), ultimoUso.end())
                            - ultimoUso.begin());
            }
            victima = ram[pos];
            ram[pos] = pagina;
            ultimoUso[pos] = t;
            if (algoritmo == "FIFO") colaFIFO.push(pos);
        }
        r.pasos.push_back({pagina, victima, fallo, ram});
    }
    return r;
}

void mostrar(const string& algoritmo, const Resultado& r) {
    cout << "\nALGORITMO " << algoritmo << "\n";
    cout << "Paso  Pagina  Marcos RAM   Estado     Reemplaza\n";
    cout << "------------------------------------------------\n";
    for (int i = 0; i < (int)r.pasos.size(); ++i) {
        const Paso& p = r.pasos[i];
        cout << setw(4) << i + 1 << "  " << setw(6) << p.pagina << "  [";
        for (int j = 0; j < (int)p.ram.size(); ++j) {
            if (j) cout << " ";
            if (p.ram[j] == -1) cout << "-";
            else cout << p.ram[j];
        }
        cout << "]  " << left << setw(10) << (p.fallo ? "FALLO" : "ACIERTO")
             << right;
        if (p.victima == -1) cout << "-";
        else cout << "P" << p.victima;
        cout << "\n";
    }
    cout << "Fallos de pagina: " << r.fallos << "\n";
    cout << "Aciertos: " << r.aciertos << "\n";
    cout << "Tasa de fallos: " << fixed << setprecision(2)
         << 100.0 * r.fallos / r.pasos.size() << "%\n";
}

int main() {
    const vector<int> referencias = {1, 2, 3, 1, 4, 1, 2};
    const int marcos = 3;
    cout << "SIMULADOR DE MEMORIA VIRTUAL - C++17\n";
    cout << "Referencias: 1, 2, 3, 1, 4, 1, 2\n";
    cout << "Marcos de RAM: " << marcos << "\n";
    for (const string algoritmo : {"FIFO", "LRU"}) {
        Resultado resultado = simular(referencias, marcos, algoritmo);
        mostrar(algoritmo, resultado);
    }
    return 0;
}
