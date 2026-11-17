/*
 * Conteúdo de uma pilha após uma sequência de operações
 * ---------------------------------------------------------------------------
 * Objetivo : simular, com uma pilha encadeada inicialmente vazia, a sequência
 *            empilha(5), empilha(3), desempilha(), empilha(2), empilha(8),
 *            desempilha(), desempilha(), empilha(9), empilha(1), desempilha(),
 *            empilha(7), empilha(6), desempilha(), desempilha(), empilha(4),
 *            desempilha(), desempilha() e mostrar a pilha após cada passo.
 *            Também permite empilhar e desempilhar valores manualmente.
 * Entrada  : um menu (1 = executar a sequência do exercício, 2 = empilhar,
 *            3 = desempilhar, 4 = mostrar a pilha, 5 = sair).
 * Saída    : o conteúdo da pilha (do topo para a base) após cada operação.
 * Exemplo  : Opção 1 -> ... desempilha() = 9  Pilha (topo -> base): 5
 *                       Conteudo final da pilha: 5
 * Compilar : g++ -std=c++11 -Wall -Wextra conteudo-pilha.cpp -o conteudo-pilha
 * Executar : ./conteudo-pilha   (Windows: conteudo-pilha.exe)
 */
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

const int DESEMPILHA = -1;   // na sequência do exercício, marca uma chamada a desempilha()

struct No {
    int valor;
    No* proximo;
};

struct Pilha {
    No* topo;
};

void criarPilhaVazia(Pilha& pilha) {
    pilha.topo = nullptr;
}

bool pilhaVazia(const Pilha& pilha) {
    return pilha.topo == nullptr;
}

// Complexidade: O(1).
void empilha(Pilha& pilha, int valor) {
    No* novo = new No{valor, pilha.topo};
    pilha.topo = novo;
}

// Remove o nó do topo e devolve seu valor em "valor". Retorna false se a pilha estiver vazia.
bool desempilha(Pilha& pilha, int& valor) {
    if (pilhaVazia(pilha)) return false;
    No* removido = pilha.topo;
    valor = removido->valor;
    pilha.topo = removido->proximo;
    delete removido;
    return true;
}

void mostrar(const Pilha& pilha) {
    cout << "Pilha (topo -> base): ";
    if (pilhaVazia(pilha)) cout << "vazia";
    for (No* atual = pilha.topo; atual != nullptr; atual = atual->proximo)
        cout << atual->valor << " ";
    cout << endl;
}

void liberar(Pilha& pilha) {
    int valor;
    while (desempilha(pilha, valor)) {}
}

void executarSequencia(Pilha& pilha) {
    int sequencia[] = {5, 3, DESEMPILHA, 2, 8, DESEMPILHA, DESEMPILHA, 9, 1, DESEMPILHA,
                       7, 6, DESEMPILHA, DESEMPILHA, 4, DESEMPILHA, DESEMPILHA};
    int total = sizeof(sequencia) / sizeof(sequencia[0]);

    liberar(pilha);                          // o exercício começa com a pilha vazia
    for (int i = 0; i < total; i++) {
        string operacao;
        int valor;
        if (sequencia[i] == DESEMPILHA) {
            if (desempilha(pilha, valor)) operacao = "desempilha() = " + to_string(valor);
            else operacao = "desempilha() (vazia)";
        } else {
            empilha(pilha, sequencia[i]);
            operacao = "empilha(" + to_string(sequencia[i]) + ")";
        }
        cout << left << setw(22) << operacao;
        mostrar(pilha);
    }

    cout << "Conteudo final da pilha: ";
    if (pilhaVazia(pilha)) cout << "vazia";
    for (No* atual = pilha.topo; atual != nullptr; atual = atual->proximo)
        cout << atual->valor << " ";
    cout << endl;
}

int main() {
    Pilha pilha;
    int opcao, valor;
    criarPilhaVazia(pilha);

    do {
        cout << endl;
        cout << "========== PILHA ==========" << endl;
        cout << "1 - Executar a sequencia do exercicio" << endl;
        cout << "2 - Empilhar um valor" << endl;
        cout << "3 - Desempilhar" << endl;
        cout << "4 - Mostrar a pilha" << endl;
        cout << "5 - Sair" << endl;
        cout << "Escolha uma opcao (1 a 5): ";
        while (!(cin >> opcao) || opcao < 1 || opcao > 5) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Opcao invalida. Digite um numero de 1 a 5: ";
        }

        if (opcao == 1) {
            executarSequencia(pilha);
        } else if (opcao == 2) {
            cout << "Valor para empilhar: ";
            while (!(cin >> valor)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Valor invalido. Digite um numero inteiro: ";
            }
            empilha(pilha, valor);
            mostrar(pilha);
        } else if (opcao == 3) {
            if (desempilha(pilha, valor)) cout << "Valor desempilhado: " << valor << endl;
            else cout << "A pilha esta vazia." << endl;
            mostrar(pilha);
        } else if (opcao == 4) {
            mostrar(pilha);
        }
    } while (opcao != 5);

    liberar(pilha);
    return 0;
}
