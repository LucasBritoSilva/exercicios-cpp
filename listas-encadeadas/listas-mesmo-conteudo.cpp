/*
 * Verifica se duas listas têm os mesmos valores na mesma ordem.
 * Entrada: tamanhos e valores das duas listas.
 * Saída: informa se os conteúdos são iguais.
 * Compilar: g++ -std=c++11 -Wall -Wextra listas-mesmo-conteudo.cpp -o listas-mesmo-conteudo
 */
#include <iostream>
using namespace std;

struct No {
    int valor;
    No* proximo;
};

No* lerLista(int n) {
    No* inicio = nullptr;
    No* fim = nullptr;
    for (int i = 0, valor; i < n; i++) {
        cin >> valor;
        No* novo = new No{valor, nullptr};
        if (inicio == nullptr) inicio = novo;
        else fim->proximo = novo;
        fim = novo;
    }
    return inicio;
}

bool iguais(No* a, No* b) {
    while (a != nullptr && b != nullptr) {
        if (a->valor != b->valor) return false;
        a = a->proximo;
        b = b->proximo;
    }
    return a == nullptr && b == nullptr;
}

void liberar(No* p) {
    while (p != nullptr) {
        No* removido = p;
        p = p->proximo;
        delete removido;
    }
}

int main() {
    int n, m;
    cout << "Tamanho e valores da primeira lista: ";
    cin >> n;
    No* a = lerLista(n);

    cout << "Tamanho e valores da segunda lista: ";
    cin >> m;
    No* b = lerLista(m);

    cout << (iguais(a, b) ? "Listas iguais." : "Listas diferentes.") << endl;
    liberar(a);
    liberar(b);
    return 0;
}