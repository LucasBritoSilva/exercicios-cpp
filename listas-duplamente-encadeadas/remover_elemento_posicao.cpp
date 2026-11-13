/*
 * Remover o elemento de uma posição específica da lista
 * ---------------------------------------------------------------------------
 * Objetivo : localiza e remove o nó da terceira posição (contagem
 *            iniciada em 1), corrigindo os vínculos dos vizinhos.
 * Entrada  : nenhuma entrada pelo teclado; utiliza os inteiros fixos
 *            (4, 2, 8, 1) e a posição 3, definidos no código.
 * Saída    : exibe "Antes:" e "Depois:", demonstrando a retirada
 *            do valor 8, que ocupava a terceira posição.
 * Exemplo  : Entrada:  (nenhuma; a lista é inicializada no código)
 *            Saída:    Antes: 4 2 8 1 
 *                      Depois: 4 2 1 
 * Compilar : g++ -std=c++11 -Wall -Wextra 03_remover_elemento_posicao.cpp -o 03_remover_elemento_posicao
 * Executar : ./03_remover_elemento_posicao   (Windows: 03_remover_elemento_posicao.exe)
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

// Posicoes comecam em 1. Complexidade: O(n).
void removerPosicao(No*& inicio, int posicao) {
    if (posicao < 1) return;
    No* atual = inicio;
    for (int i = 1; i < posicao && atual != nullptr; i++)
        atual = atual->proximo;
    if (atual == nullptr) return;
    if (atual->anterior != nullptr)
        atual->anterior->proximo = atual->proximo;
    else
        inicio = atual->proximo;
    if (atual->proximo != nullptr)
        atual->proximo->anterior = atual->anterior;
    delete atual;
}

int main() {
    No* inicio = nullptr;
    inserirFim(inicio, 4);
    inserirFim(inicio, 2);
    inserirFim(inicio, 8);
    inserirFim(inicio, 1);
    cout << "Antes: "; mostrar(inicio);
    removerPosicao(inicio, 3);
    cout << "Depois: "; mostrar(inicio);
    liberar(inicio);
    return 0;
}
