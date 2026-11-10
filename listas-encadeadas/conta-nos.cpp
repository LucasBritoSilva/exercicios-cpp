/*
 * Conta os nós de uma lista simplesmente encadeada.
 * Entrada: quantidade de valores e os valores.
 * Saída: quantidade de nós.
 * Compilar: g++ -std=c++11 -Wall -Wextra conta-nos.cpp -o conta-nos
 */
#include <iostream>
using namespace std;

struct No {
    int valor;
    No* proximo;
};

int contar(No* inicio) {
    int quantidade = 0;
    for (No* atual = inicio; atual != nullptr; atual = atual->proximo)
        quantidade++;
    return quantidade;
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

    cout << "Quantidade de nos: " << contar(inicio) << endl;
    while (inicio != nullptr) {
        No* removido = inicio;
        inicio = inicio->proximo;
        delete removido;
    }
    return 0;
}