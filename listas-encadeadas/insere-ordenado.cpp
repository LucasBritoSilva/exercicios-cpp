/*
 * Insere um valor em uma lista mantendo a ordem crescente.
 * Entrada: quantidade, valores e novo valor.
 * Saída: lista ordenada após a inserção.
 * Compilar: g++ -std=c++11 -Wall -Wextra insere-ordenado.cpp -o insere-ordenado
 */
#include <iostream>
using namespace std;

struct No {
    int valor;
    No* proximo;
};

No* inserir(No* inicio, int valor) {
    No* novo = new No{valor, nullptr};
    if (inicio == nullptr || valor <= inicio->valor) {
        novo->proximo = inicio;
        return novo;
    }

    No* atual = inicio;
    while (atual->proximo != nullptr && atual->proximo->valor < valor)
        atual = atual->proximo;

    novo->proximo = atual->proximo;
    atual->proximo = novo;
    return inicio;
}

int main() {
    int n, valor;
    No* inicio = nullptr;

    cout << "Quantidade de valores: ";
    cin >> n;
    cout << "Digite os valores: ";
    for (int i = 0; i < n; i++) {
        cin >> valor;
        inicio = inserir(inicio, valor);
    }

    cout << "Valor para inserir: ";
    cin >> valor;
    inicio = inserir(inicio, valor);

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