/*
 * Soma os nós simétricos de uma lista com quantidade par de nós.
 * Entrada: quantidade par e os valores da lista.
 * Saída: lista com as somas, na ordem da primeira metade.
 * Compilar: g++ -std=c++11 -Wall -Wextra soma-valores-simetricos.cpp -o soma-valores-simetricos
 */
#include <iostream>
using namespace std;

struct No {
    int valor;
    No* proximo;
};

No* somaSimetricos(No* inicio, int n) {
    if (inicio == nullptr || n == 0) return nullptr;

    int metade = n / 2;
    No* fimPrimeira = inicio;
    for (int i = 1; i < metade; i++)
        fimPrimeira = fimPrimeira->proximo;

    No* segunda = fimPrimeira->proximo;
    fimPrimeira->proximo = nullptr;

    No* anterior = nullptr;
    No* atual = segunda;
    while (atual != nullptr) {
        No* proximo = atual->proximo;
        atual->proximo = anterior;
        anterior = atual;
        atual = proximo;
    }

    No* p = inicio;
    No* q = anterior;
    while (p != nullptr && q != nullptr) {
        p->valor += q->valor;
        p = p->proximo;
        q = q->proximo;
    }

    // Libera os nós da segunda metade, que não fazem parte do resultado.
    while (anterior != nullptr) {
        No* removido = anterior;
        anterior = anterior->proximo;
        delete removido;
    }
    return inicio;
}

int main() {
    int n, valor;
    No* inicio = nullptr;
    No* fim = nullptr;

    cout << "Digite uma quantidade par de valores: ";
    cin >> n;
    if (n < 0 || n % 2 != 0) {
        cout << "Quantidade invalida." << endl;
        return 1;
    }

    cout << "Digite os valores: ";
    for (int i = 0; i < n; i++) {
        cin >> valor;
        No* novo = new No{valor, nullptr};
        if (inicio == nullptr) inicio = novo;
        else fim->proximo = novo;
        fim = novo;
    }

    inicio = somaSimetricos(inicio, n);
    for (No* p = inicio; p != nullptr; p = p->proximo)
        cout << p->valor << " ";
    cout << endl;

    while (inicio != nullptr) {
        No* removido = inicio;
        inicio = inicio->proximo;
        delete removido;
    }
    return 0;
}