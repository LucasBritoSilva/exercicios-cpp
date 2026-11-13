/*
 * Criar uma cópia independente de uma lista duplamente encadeada
 * ---------------------------------------------------------------------------
 * Objetivo : cria novos nós com os mesmos valores, preservando a
 *            ordem e os vínculos sem reutilizar nós da origem.
 * Entrada  : nenhuma entrada pelo teclado; o programa monta uma
 *            lista com quatro inteiros fixos (4, 2, 8, 1).
 * Saída    : mostra "Antes:" para a origem, "Copia:" para a cópia
 *            e "Depois:" para a origem, que permanece igual.
 * Exemplo  : Entrada:  (nenhuma; a lista é inicializada no código)
 *            Saída:    Antes: 4 2 8 1 
 *                      Copia: 4 2 8 1 
 *                      Depois: 4 2 8 1 
 * Compilar : g++ -std=c++11 -Wall -Wextra 07_copiar_lista.cpp -o 07_copiar_lista
 * Executar : ./07_copiar_lista   (Windows: 07_copiar_lista.exe)
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

// Complexidade: O(n), criando nos independentes.
No* copiarLista(No* inicio) {
    No* copia = nullptr;
    No* ultimo = nullptr;
    for (No* atual = inicio; atual != nullptr; atual = atual->proximo) {
        No* novo = new No{atual->valor, ultimo, nullptr};
        if (ultimo != nullptr) ultimo->proximo = novo;
        else copia = novo;
        ultimo = novo;
    }
    return copia;
}

int main() {
    No* inicio = nullptr;
    inserirFim(inicio, 4);
    inserirFim(inicio, 2);
    inserirFim(inicio, 8);
    inserirFim(inicio, 1);
    cout << "Antes: "; mostrar(inicio);
    No* copia = copiarLista(inicio); cout << "Copia: "; mostrar(copia); liberar(copia);
    cout << "Depois: "; mostrar(inicio);
    liberar(inicio);
    return 0;
}
