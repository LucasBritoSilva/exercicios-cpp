/*
 * Contar os nós de uma lista duplamente encadeada
 * ---------------------------------------------------------------------------
 * Objetivo : percorre os nós e incrementa um contador para obter
 *            quantos elementos existem, sem alterar os nós.
 * Entrada  : nenhuma entrada pelo teclado; a lista contém os
 *            quatro inteiros fixos (4, 2, 8, 1).
 * Saída    : exibe "Antes:", "Quantidade:" com o total de nós
 *            e "Depois:" com os valores não alterados.
 * Exemplo  : Entrada:  (nenhuma; a lista é inicializada no código)
 *            Saída:    Antes: 4 2 8 1 
 *                      Quantidade: 4
 *                      Depois: 4 2 8 1 
 * Compilar : g++ -std=c++11 -Wall -Wextra 06_contar_elementos.cpp -o 06_contar_elementos
 * Executar : ./06_contar_elementos   (Windows: 06_contar_elementos.exe)
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
int contarElementos(No* inicio) {
    int quantidade = 0;
    for (No* atual = inicio; atual != nullptr; atual = atual->proximo)
        quantidade++;
    return quantidade;
}

int main() {
    No* inicio = nullptr;
    inserirFim(inicio, 4);
    inserirFim(inicio, 2);
    inserirFim(inicio, 8);
    inserirFim(inicio, 1);
    cout << "Antes: "; mostrar(inicio);
    cout << "Quantidade: " << contarElementos(inicio) << "\n";
    cout << "Depois: "; mostrar(inicio);
    liberar(inicio);
    return 0;
}
