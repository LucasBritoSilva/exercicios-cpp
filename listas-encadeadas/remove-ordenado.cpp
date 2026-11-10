/*
 * Remove a primeira ocorrência de um valor em uma lista ordenada.
 * Entrada: quantidade, valores ordenados e valor a remover.
 * Saída: lista após a remoção.
 * Compilar: g++ -std=c++11 -Wall -Wextra remove-ordenado.cpp -o remove-ordenado
 */
#include <iostream>
using namespace std;

struct No {
    int valor;
    No* proximo;
};

No* remover(No* inicio, int valor) {
    if (inicio == nullptr) return nullptr;

    if (inicio->valor == valor) {
        No* removido = inicio;
        inicio = inicio->proximo;
        delete removido;
        return inicio;
    }

    No* anterior = inicio;
    No* atual = inicio->proximo;
    while (atual != nullptr && atual->valor < valor) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual != nullptr && atual->valor == valor) {
        anterior->proximo = atual->proximo;
        delete atual;
    }
    return inicio;
}

int main() {
    int n, valor;
    No* inicio = nullptr;

    cout << "Quantidade de valores: ";
    cin >> n;
    cout << "Digite os valores ordenados: ";
    for (int i = 0; i < n; i++) {
        cin >> valor;
        No* novo = new No{valor, nullptr};
        if (inicio == nullptr) inicio = novo;
        else {
            No* fim = inicio;
            while (fim->proximo != nullptr) fim = fim->proximo;
            fim->proximo = novo;
        }
    }

    cout << "Valor para remover: ";
    cin >> valor;
    inicio = remover(inicio, valor);

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