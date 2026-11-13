/*
 * Ordenar uma lista duplamente encadeada com Selection Sort
 * ---------------------------------------------------------------------------
 * Objetivo : procura o menor valor a cada passagem e troca os
 *            valores dos nós para ordenar a lista em ordem crescente.
 * Entrada  : nenhuma entrada pelo teclado; o programa usa os
 *            quatro inteiros fixos (4, 2, 8, 1).
 * Saída    : mostra "Antes:" com a sequência inicial e "Depois:"
 *            com os valores organizados em ordem crescente.
 * Exemplo  : Entrada:  (nenhuma; a lista é inicializada no código)
 *            Saída:    Antes: 4 2 8 1 
 *                      Depois: 1 2 4 8 
 * Compilar : g++ -std=c++11 -Wall -Wextra 09_selection_sort.cpp -o 09_selection_sort
 * Executar : ./09_selection_sort   (Windows: 09_selection_sort.exe)
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

// Complexidade: O(n^2).
void selectionSort(No* inicio) {
    for (No* atual = inicio; atual != nullptr; atual = atual->proximo) {
        No* menor = atual;
        for (No* busca = atual->proximo; busca != nullptr; busca = busca->proximo)
            if (busca->valor < menor->valor) menor = busca;
        int temp = atual->valor;
        atual->valor = menor->valor;
        menor->valor = temp;
    }
}

int main() {
    No* inicio = nullptr;
    inserirFim(inicio, 4);
    inserirFim(inicio, 2);
    inserirFim(inicio, 8);
    inserirFim(inicio, 1);
    cout << "Antes: "; mostrar(inicio);
    selectionSort(inicio);
    cout << "Depois: "; mostrar(inicio);
    liberar(inicio);
    return 0;
}
