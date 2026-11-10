/*
 * Intercala duas listas ordenadas, reutilizando e consumindo seus nós.
 * Entrada: tamanhos e valores ordenados das duas listas.
 * Saída: lista resultante em ordem crescente.
 * Compilar: g++ -std=c++11 -Wall -Wextra intercala-listas-ordenadas.cpp -o intercala-listas-ordenadas
 */
#include <iostream>
using namespace std;

struct No {
    int valor;
    No* proximo;
};

No* lerLista(int n) {
    No* inicio = nullptr;
    No* fim = nullptr;
    for (int i = 0, valor; i < n; i++) {
        cin >> valor;
        No* novo = new No{valor, nullptr};
        if (inicio == nullptr) inicio = novo;
        else fim->proximo = novo;
        fim = novo;
    }
    return inicio;
}

No* intercala(No* a, No* b) {
    No* inicio = nullptr;
    No* fim = nullptr;

    while (a != nullptr && b != nullptr) {
        No* escolhido;
        if (a->valor <= b->valor) {
            escolhido = a;
            a = a->proximo;
        } else {
            escolhido = b;
            b = b->proximo;
        }

        if (inicio == nullptr) inicio = escolhido;
        else fim->proximo = escolhido;
        fim = escolhido;
    }

    No* restante = (a != nullptr) ? a : b;
    if (inicio == nullptr) inicio = restante;
    else fim->proximo = restante;
    return inicio;
}

int main() {
    int n, m;
    cout << "Tamanho e valores ordenados da primeira lista: ";
    cin >> n;
    No* a = lerLista(n);

    cout << "Tamanho e valores ordenados da segunda lista: ";
    cin >> m;
    No* b = lerLista(m);

    No* resultado = intercala(a, b);
    for (No* p = resultado; p != nullptr; p = p->proximo)
        cout << p->valor << " ";
    cout << endl;

    while (resultado != nullptr) {
        No* removido = resultado;
        resultado = resultado->proximo;
        delete removido;
    }
    return 0;
}