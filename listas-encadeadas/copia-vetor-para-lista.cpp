/*
 * Acrescenta os valores de um vetor ao final de uma lista.
 * Entrada: tamanho e valores do vetor.
 * Saída: lista resultante.
 * Compilar: g++ -std=c++11 -Wall -Wextra copia-vetor-para-lista.cpp -o copia-vetor-para-lista
 */
#include <iostream>
using namespace std;

struct No {
    int valor;
    No* proximo;
};

No* copiaVetor(No* inicio, int vetor[], int n) {
    No* fim = inicio;
    while (fim != nullptr && fim->proximo != nullptr)
        fim = fim->proximo;

    for (int i = 0; i < n; i++) {
        No* novo = new No{vetor[i], nullptr};
        if (inicio == nullptr) inicio = novo;
        else fim->proximo = novo;
        fim = novo;
    }
    return inicio;
}

int main() {
    int n;
    cout << "Quantidade de valores: ";
    cin >> n;

    int* vetor = new int[n];
    cout << "Digite os valores: ";
    for (int i = 0; i < n; i++) cin >> vetor[i];

    No* inicio = copiaVetor(nullptr, vetor, n);
    for (No* p = inicio; p != nullptr; p = p->proximo)
        cout << p->valor << " ";
    cout << endl;

    while (inicio != nullptr) {
        No* removido = inicio;
        inicio = inicio->proximo;
        delete removido;
    }
    delete[] vetor;
    return 0;
}