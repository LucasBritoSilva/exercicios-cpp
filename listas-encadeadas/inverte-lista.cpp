/*
 * Inverte a ordem dos nós de uma lista.
 * Entrada: quantidade de valores e os valores.
 * Saída: lista invertida.
 * Compilar: g++ -std=c++11 -Wall -Wextra inverte-lista.cpp -o inverte-lista
 */
#include <iostream>
using namespace std;

struct No {
    int valor;
    No* proximo;
};

No* inverter(No* inicio) {
    No* anterior = nullptr;
    No* atual = inicio;

    while (atual != nullptr) {
        No* proximo = atual->proximo;
        atual->proximo = anterior;
        anterior = atual;
        atual = proximo;
    }
    return anterior;
}

int main() {
    int n, valor;
    No* inicio = nullptr;
    No* fim = nullptr;

    cout << "Quantidade de valores: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> valor;
        No* novo = new No{valor, nullptr};
        if (inicio == nullptr) inicio = novo;
        else fim->proximo = novo;
        fim = novo;
    }

    inicio = inverter(inicio);
    for (No* p = inicio; p != nullptr; p = p->proximo)
        cout << p->valor << " ";
    cout << endl;

    while (inicio != nullptr) {
        No* removido = inicio;
        inicio = inicio->proximo;
        delete removido;
    }
    return 0;
}