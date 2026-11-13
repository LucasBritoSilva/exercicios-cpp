/*
 * Somar os valores de uma lista duplamente encadeada
 * ---------------------------------------------------------------------------
 * Objetivo : percorre todos os nós e acumula seus valores inteiros
 *            em uma variável long long, sem modificar a lista.
 * Entrada  : nenhuma entrada pelo teclado; o programa utiliza
 *            quatro inteiros fixos (4, 2, 8, 1).
 * Saída    : mostra a lista em "Antes:", o total em "Soma:" e
 *            a lista preservada em "Depois:".
 * Exemplo  : Entrada:  (nenhuma; a lista é inicializada no código)
 *            Saída:    Antes: 4 2 8 1 
 *                      Soma: 15
 *                      Depois: 4 2 8 1 
 * Compilar : g++ -std=c++11 -Wall -Wextra 05_somar_elementos.cpp -o 05_somar_elementos
 * Executar : ./05_somar_elementos   (Windows: 05_somar_elementos.exe)
 */
#include <iostream>
using namespace std;

struct No {
    int valor;
    No* anterior;
    No* proximo;
};

void inserirFim(No*& inicio, int valor) {
    No* novo = new No{valor, nullptr, nullptr};
    if (inicio == nullptr) {
        inicio = novo;
        return;
    }
    No* atual = inicio;
    while (atual->proximo != nullptr) atual = atual->proximo;
    atual->proximo = novo;
    novo->anterior = atual;
}

void mostrar(No* inicio) {
    for (No* atual = inicio; atual != nullptr; atual = atual->proximo)
        cout << atual->valor << " ";
    cout << "\n";
}

void liberar(No*& inicio) {
    while (inicio != nullptr) {
        No* proximo = inicio->proximo;
        delete inicio;
        inicio = proximo;
    }
}

// Complexidade: O(n).
long long somarElementos(No* inicio) {
    long long soma = 0;
    for (No* atual = inicio; atual != nullptr; atual = atual->proximo)
        soma += atual->valor;
    return soma;
}

int main() {
    No* inicio = nullptr;
    inserirFim(inicio, 4);
    inserirFim(inicio, 2);
    inserirFim(inicio, 8);
    inserirFim(inicio, 1);
    cout << "Antes: "; mostrar(inicio);
    cout << "Soma: " << somarElementos(inicio) << "\n";
    cout << "Depois: "; mostrar(inicio);
    liberar(inicio);
    return 0;
}
