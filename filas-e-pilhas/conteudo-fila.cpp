/*
 * Conteúdo de uma fila após uma sequência de operações
 * ---------------------------------------------------------------------------
 * Objetivo : simular, com uma fila encadeada inicialmente vazia, a sequência
 *            enfileira(5), enfileira(3), desenfileira(), enfileira(2),
 *            enfileira(8), desenfileira(), desenfileira(), enfileira(9),
 *            enfileira(1), desenfileira(), enfileira(7), enfileira(6),
 *            desenfileira(), desenfileira(), enfileira(4), desenfileira(),
 *            desenfileira() e mostrar a fila após cada passo. Também permite
 *            enfileirar e desenfileirar valores manualmente.
 * Entrada  : um menu (1 = executar a sequência do exercício, 2 = enfileirar,
 *            3 = desenfileirar, 4 = mostrar a fila, 5 = sair).
 * Saída    : o conteúdo da fila (do início para o fim) após cada operação.
 * Exemplo  : Opção 1 -> ... desenfileira() = 6  Fila (inicio -> fim): 4
 *                       Conteudo final da fila: 4
 * Compilar : g++ -std=c++11 -Wall -Wextra conteudo-fila.cpp -o conteudo-fila
 * Executar : ./conteudo-fila   (Windows: conteudo-fila.exe)
 */
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

const int DESENFILEIRA = -1;   // na sequência do exercício, marca uma chamada a desenfileira()

struct No {
    int valor;
    No* proximo;
};

struct Fila {
    No* inicio;
    No* fim;
};

void criarFilaVazia(Fila& fila) {
    fila.inicio = nullptr;
    fila.fim = nullptr;
}

bool filaVazia(const Fila& fila) {
    return fila.inicio == nullptr;
}

// Insere no fim. Complexidade: O(1).
void enfileira(Fila& fila, int valor) {
    No* novo = new No{valor, nullptr};
    if (filaVazia(fila)) fila.inicio = novo;
    else fila.fim->proximo = novo;
    fila.fim = novo;
}

// Remove o nó do início e devolve seu valor em "valor". Retorna false se a fila estiver vazia.
bool desenfileira(Fila& fila, int& valor) {
    if (filaVazia(fila)) return false;
    No* removido = fila.inicio;
    valor = removido->valor;
    fila.inicio = removido->proximo;
    if (fila.inicio == nullptr) fila.fim = nullptr;
    delete removido;
    return true;
}

void mostrar(const Fila& fila) {
    cout << "Fila (inicio -> fim): ";
    if (filaVazia(fila)) cout << "vazia";
    for (No* atual = fila.inicio; atual != nullptr; atual = atual->proximo)
        cout << atual->valor << " ";
    cout << endl;
}

void liberar(Fila& fila) {
    int valor;
    while (desenfileira(fila, valor)) {}
}

void executarSequencia(Fila& fila) {
    int sequencia[] = {5, 3, DESENFILEIRA, 2, 8, DESENFILEIRA, DESENFILEIRA, 9, 1, DESENFILEIRA,
                       7, 6, DESENFILEIRA, DESENFILEIRA, 4, DESENFILEIRA, DESENFILEIRA};
    int total = sizeof(sequencia) / sizeof(sequencia[0]);

    liberar(fila);                           // o exercício começa com a fila vazia
    for (int i = 0; i < total; i++) {
        string operacao;
        int valor;
        if (sequencia[i] == DESENFILEIRA) {
            if (desenfileira(fila, valor)) operacao = "desenfileira() = " + to_string(valor);
            else operacao = "desenfileira() (vazia)";
        } else {
            enfileira(fila, sequencia[i]);
            operacao = "enfileira(" + to_string(sequencia[i]) + ")";
        }
        cout << left << setw(24) << operacao;
        mostrar(fila);
    }

    cout << "Conteudo final da fila: ";
    if (filaVazia(fila)) cout << "vazia";
    for (No* atual = fila.inicio; atual != nullptr; atual = atual->proximo)
        cout << atual->valor << " ";
    cout << endl;
}

int main() {
    Fila fila;
    int opcao, valor;
    criarFilaVazia(fila);

    do {
        cout << endl;
        cout << "========== FILA ==========" << endl;
        cout << "1 - Executar a sequencia do exercicio" << endl;
        cout << "2 - Enfileirar um valor" << endl;
        cout << "3 - Desenfileirar" << endl;
        cout << "4 - Mostrar a fila" << endl;
        cout << "5 - Sair" << endl;
        cout << "Escolha uma opcao (1 a 5): ";
        while (!(cin >> opcao) || opcao < 1 || opcao > 5) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Opcao invalida. Digite um numero de 1 a 5: ";
        }

        if (opcao == 1) {
            executarSequencia(fila);
        } else if (opcao == 2) {
            cout << "Valor para enfileirar: ";
            while (!(cin >> valor)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Valor invalido. Digite um numero inteiro: ";
            }
            enfileira(fila, valor);
            mostrar(fila);
        } else if (opcao == 3) {
            if (desenfileira(fila, valor)) cout << "Valor desenfileirado: " << valor << endl;
            else cout << "A fila esta vazia." << endl;
            mostrar(fila);
        } else if (opcao == 4) {
            mostrar(fila);
        }
    } while (opcao != 5);

    liberar(fila);
    return 0;
}
