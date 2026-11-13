/*
 * Remover todos os nós de uma lista duplamente encadeada
 * ---------------------------------------------------------------------------
 * Objetivo : apaga cada nó da lista e deixa o ponteiro inicial nulo,
 *            liberando a memória dos quatro elementos de demonstração.
 * Entrada  : nenhuma entrada pelo teclado; o programa cria uma lista
 *            de quatro inteiros (4, 2, 8, 1) diretamente no código.
 * Saída    : exibe a lista antes da remoção e a lista vazia depois,
 *            identificadas pelas mensagens "Antes:" e "Depois:".
 * Exemplo  : Entrada:  (nenhuma; a lista é inicializada no código)
 *            Saída:    Antes: 4 2 8 1 
 *                      Depois: 
 * Compilar : g++ -std=c++11 -Wall -Wextra 01_remover_todos_os_nos.cpp -o 01_remover_todos_os_nos
 * Executar : ./01_remover_todos_os_nos   (Windows: 01_remover_todos_os_nos.exe)
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

// Complexidade: O(n), pois cada no e removido uma vez.
void removerTodos(No*& inicio) {
    liberar(inicio);
}

int main() {
    No* inicio = nullptr;
    inserirFim(inicio, 4);
    inserirFim(inicio, 2);
    inserirFim(inicio, 8);
    inserirFim(inicio, 1);
    cout << "Antes: "; mostrar(inicio);
    removerTodos(inicio);
    cout << "Depois: "; mostrar(inicio);
    liberar(inicio);
    return 0;
}
