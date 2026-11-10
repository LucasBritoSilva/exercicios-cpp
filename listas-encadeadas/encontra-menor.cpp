/*
 * Encontra o menor valor de uma lista simplesmente encadeada.
 * Entrada: quantidade de nós e seus valores.
 * Saída: valor mínimo da lista.
 * Compilar: g++ -std=c++11 -Wall -Wextra encontra-menor.cpp -o encontra-menor
 */
#include <iostream>
using namespace std;

struct No {
    int valor;
    No* proximo;
};

No* encontraMenor(No* inicio) {
    if (inicio == nullptr) return nullptr;

    No* menor = inicio;
    for (No* atual = inicio->proximo; atual != nullptr; atual = atual->proximo)
        if (atual->valor < menor->valor) menor = atual;

    return menor;
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

    No* menor = encontraMenor(inicio);
    if (menor == nullptr) cout << "Lista vazia." << endl;
    else cout << "Menor valor: " << menor->valor << endl;

    while (inicio != nullptr) {
        No* removido = inicio;
        inicio = inicio->proximo;
        delete removido;
    }
    return 0;
}