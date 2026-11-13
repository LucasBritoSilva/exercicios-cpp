/*
 * Remover o segundo elemento de uma lista duplamente encadeada
 * ---------------------------------------------------------------------------
 * Objetivo : exclui o segundo nó, reconectando o primeiro ao terceiro
 *            nó e liberando a memória do elemento removido.
 * Entrada  : nenhuma entrada pelo teclado; a lista é inicializada
 *            no código com quatro inteiros (4, 2, 8, 1).
 * Saída    : mostra "Antes:" com a lista inicial e "Depois:" com
 *            a lista sem o segundo elemento, de valor 2.
 * Exemplo  : Entrada:  (nenhuma; a lista é inicializada no código)
 *            Saída:    Antes: 4 2 8 1 
 *                      Depois: 4 8 1 
 * Compilar : g++ -std=c++11 -Wall -Wextra 04_remover_segundo_elemento.cpp -o 04_remover_segundo_elemento
 * Executar : ./04_remover_segundo_elemento   (Windows: 04_remover_segundo_elemento.exe)
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

// Complexidade: O(1), sem percorrer a lista.
void removerSegundo(No*& inicio) {
    if (inicio == nullptr || inicio->proximo == nullptr) return;
    No* segundo = inicio->proximo;
    inicio->proximo = segundo->proximo;
    if (segundo->proximo != nullptr)
        segundo->proximo->anterior = inicio;
    delete segundo;
}

int main() {
    No* inicio = nullptr;
    inserirFim(inicio, 4);
    inserirFim(inicio, 2);
    inserirFim(inicio, 8);
    inserirFim(inicio, 1);
    cout << "Antes: "; mostrar(inicio);
    removerSegundo(inicio);
    cout << "Depois: "; mostrar(inicio);
    liberar(inicio);
    return 0;
}
