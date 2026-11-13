/*
 * Ordenar uma lista duplamente encadeada com Insertion Sort
 * ---------------------------------------------------------------------------
 * Objetivo : insere cada valor na posição correta da parte já
 *            ordenada, deslocando valores pelos nós anteriores.
 * Entrada  : nenhuma entrada pelo teclado; a lista é criada com
 *            quatro inteiros fixos (4, 2, 8, 1).
 * Saída    : mostra "Antes:" com a lista inicial e "Depois:"
 *            com a mesma lista em ordem crescente.
 * Exemplo  : Entrada:  (nenhuma; a lista é inicializada no código)
 *            Saída:    Antes: 4 2 8 1 
 *                      Depois: 1 2 4 8 
 * Compilar : g++ -std=c++11 -Wall -Wextra 10_insertion_sort.cpp -o 10_insertion_sort
 * Executar : ./10_insertion_sort   (Windows: 10_insertion_sort.exe)
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

// Complexidade: O(n^2) no pior caso.
void insertionSort(No* inicio) {
    if (inicio == nullptr) return;
    for (No* atual = inicio->proximo; atual != nullptr; atual = atual->proximo) {
        int chave = atual->valor;
        No* anterior = atual->anterior;
        while (anterior != nullptr && anterior->valor > chave) {
            anterior->proximo->valor = anterior->valor;
            anterior = anterior->anterior;
        }
        if (anterior != nullptr) anterior->proximo->valor = chave;
        else inicio->valor = chave;
    }
}

int main() {
    No* inicio = nullptr;
    inserirFim(inicio, 4);
    inserirFim(inicio, 2);
    inserirFim(inicio, 8);
    inserirFim(inicio, 1);
    cout << "Antes: "; mostrar(inicio);
    insertionSort(inicio);
    cout << "Depois: "; mostrar(inicio);
    liberar(inicio);
    return 0;
}
