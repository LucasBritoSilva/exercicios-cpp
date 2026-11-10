/*
 * Busca um valor em uma lista ordenada crescente.
 * Entrada: quantidade, valores ordenados e valor procurado.
 * Saída: informa se o valor foi encontrado.
 * Compilar: g++ -std=c++11 -Wall -Wextra busca-ordenada.cpp -o busca-ordenada
 */
#include <iostream>
using namespace std;

struct No {
    int valor;
    No* proximo;
};

bool busca(No* inicio, int valor) {
    No* atual = inicio;
    while (atual != nullptr && atual->valor < valor)
        atual = atual->proximo;
    return atual != nullptr && atual->valor == valor;
}

int main() {
    int n, valor, procurado;
    No* inicio = nullptr;
    No* fim = nullptr;

    cout << "Quantidade e valores em ordem crescente: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> valor;
        No* novo = new No{valor, nullptr};
        if (inicio == nullptr) inicio = novo;
        else fim->proximo = novo;
        fim = novo;
    }

    cout << "Valor procurado: ";
    cin >> procurado;
    cout << (busca(inicio, procurado) ? "Encontrado." : "Nao encontrado.") << endl;

    while (inicio != nullptr) {
        No* removido = inicio;
        inicio = inicio->proximo;
        delete removido;
    }
    return 0;
}