/*
 * Copia os valores de uma lista para um vector.
 * Entrada: quantidade de nós e seus valores.
 * Saída: valores copiados para o vector.
 * Compilar: g++ -std=c++11 -Wall -Wextra copia-lista-para-vetor.cpp -o copia-lista-para-vetor
 */
#include <iostream>
#include <vector>
using namespace std;

struct No {
    int valor;
    No* proximo;
};

vector<int> copiaVetor(No* inicio) {
    vector<int> resultado;
    for (No* atual = inicio; atual != nullptr; atual = atual->proximo)
        resultado.push_back(atual->valor);
    return resultado;
}

int main() {
    int n, valor;
    No* inicio = nullptr;
    No* fim = nullptr;

    cout << "Quantidade de valores: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> valor;
        No* novo = new No{valor, nullptr};
        if (inicio == nullptr) inicio = novo;
        else fim->proximo = novo;
        fim = novo;
    }

    vector<int> resultado = copiaVetor(inicio);
    cout << "Vector: ";
    for (int x : resultado) cout << x << " ";
    cout << endl;

    while (inicio != nullptr) {
        No* removido = inicio;
        inicio = inicio->proximo;
        delete removido;
    }
    return 0;
}