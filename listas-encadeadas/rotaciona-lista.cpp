/*
 * Move o primeiro nó de uma lista para o final.
 * Entrada: quantidade de valores e os valores.
 * Saída: lista rotacionada uma posição à esquerda.
 * Compilar: g++ -std=c++11 -Wall -Wextra rotaciona-lista.cpp -o rotaciona-lista
 */
#include <iostream>
using namespace std;

struct No {
    int valor;
    No* proximo;
};

No* rotaciona(No* inicio) {
    if (inicio == nullptr || inicio->proximo == nullptr) return inicio;

    No* primeiro = inicio;
    No* fim = inicio;
    while (fim->proximo != nullptr) fim = fim->proximo;

    inicio = inicio->proximo;
    fim->proximo = primeiro;
    primeiro->proximo = nullptr;
    return inicio;
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

    inicio = rotaciona(inicio);
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