/*
 * Remover o último elemento de uma lista duplamente encadeada
 * ---------------------------------------------------------------------------
 * Objetivo : percorre a lista até o último nó, desconecta esse nó e
 *            libera sua memória, preservando os anteriores.
 * Entrada  : nenhuma entrada pelo teclado; a lista inicial contém
 *            quatro inteiros fixos (4, 2, 8, 1).
 * Saída    : mostra "Antes:" com os quatro valores e "Depois:"
 *            com os três valores que permaneceram na lista.
 * Exemplo  : Entrada:  (nenhuma; a lista é inicializada no código)
 *            Saída:    Antes: 4 2 8 1 
 *                      Depois: 4 2 8 
 * Compilar : g++ -std=c++11 -Wall -Wextra 02_remover_ultimo_elemento.cpp -o 02_remover_ultimo_elemento
 * Executar : ./02_remover_ultimo_elemento   (Windows: 02_remover_ultimo_elemento.exe)
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

// Complexidade: O(n), pois percorre ate o ultimo no.
void removerUltimo(No*& inicio) {
    if (inicio == nullptr) return;
    No* atual = inicio;
    while (atual->proximo != nullptr) atual = atual->proximo;
    if (atual->anterior != nullptr)
        atual->anterior->proximo = nullptr;
    else
        inicio = nullptr;
    delete atual;
}

int main() {
    No* inicio = nullptr;
    inserirFim(inicio, 4);
    inserirFim(inicio, 2);
    inserirFim(inicio, 8);
    inserirFim(inicio, 1);
    cout << "Antes: "; mostrar(inicio);
    removerUltimo(inicio);
    cout << "Depois: "; mostrar(inicio);
    liberar(inicio);
    return 0;
}
