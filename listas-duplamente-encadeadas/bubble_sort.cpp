/*
 * Ordenar uma lista duplamente encadeada com Bubble Sort
 * ---------------------------------------------------------------------------
 * Objetivo : ordena os valores em ordem crescente por comparações
 *            e trocas entre nós adjacentes, sem mover os nós.
 * Entrada  : nenhuma entrada pelo teclado; a lista inicial recebe
 *            quatro inteiros fixos (4, 2, 8, 1).
 * Saída    : mostra "Antes:" com a ordem original e "Depois:"
 *            com os valores ordenados de forma crescente.
 * Exemplo  : Entrada:  (nenhuma; a lista é inicializada no código)
 *            Saída:    Antes: 4 2 8 1 
 *                      Depois: 1 2 4 8 
 * Compilar : g++ -std=c++11 -Wall -Wextra 08_bubble_sort.cpp -o 08_bubble_sort
 * Executar : ./08_bubble_sort   (Windows: 08_bubble_sort.exe)
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
void bubbleSort(No* inicio) {
    if (inicio == nullptr) return;
    bool trocou;
    No* limite = nullptr;
    do {
        trocou = false;
        No* atual = inicio;
        while (atual->proximo != limite) {
            if (atual->valor > atual->proximo->valor) {
                int temp = atual->valor;
                atual->valor = atual->proximo->valor;
                atual->proximo->valor = temp;
                trocou = true;
            }
            atual = atual->proximo;
        }
        limite = atual;
    } while (trocou);
}

int main() {
    No* inicio = nullptr;
    inserirFim(inicio, 4);
    inserirFim(inicio, 2);
    inserirFim(inicio, 8);
    inserirFim(inicio, 1);
    cout << "Antes: "; mostrar(inicio);
    bubbleSort(inicio);
    cout << "Depois: "; mostrar(inicio);
    liberar(inicio);
    return 0;
}
