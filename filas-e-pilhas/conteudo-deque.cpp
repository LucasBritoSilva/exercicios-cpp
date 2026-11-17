/*
 * Conteúdo de um deque após uma sequência de operações
 * ---------------------------------------------------------------------------
 * Objetivo : simular, com um deque duplamente encadeado inicialmente vazio, a
 *            sequência insereComeco(3), insereFim(8), insereFim(9),
 *            insereComeco(5), removeComeco(), removeFim(), insereComeco(6),
 *            insereFim(7), removeComeco(), removeFim(), removeFim() e mostrar
 *            o deque após cada passo. Também permite fazer as operações
 *            manualmente.
 * Entrada  : um menu (1 = executar a sequência do exercício, 2 = inserir no
 *            começo, 3 = inserir no fim, 4 = remover do começo, 5 = remover do
 *            fim, 6 = mostrar o deque, 7 = sair).
 * Saída    : o conteúdo do deque (do começo para o fim) após cada operação.
 * Exemplo  : Opção 1 -> ... removeFim() = 8  Deque (comeco -> fim): 3
 *                       Conteudo final do deque: 3
 * Compilar : g++ -std=c++11 -Wall -Wextra conteudo-deque.cpp -o conteudo-deque
 * Executar : ./conteudo-deque   (Windows: conteudo-deque.exe)
 */
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

// Tipos de operação usados na sequência do exercício.
const int INSERE_COMECO = 1;
const int INSERE_FIM = 2;
const int REMOVE_COMECO = 3;
const int REMOVE_FIM = 4;

struct No {
    int valor;
    No* anterior;
    No* proximo;
};

struct Deque {
    No* inicio;
    No* fim;
};

struct Operacao {
    int tipo;
    int valor;     // usado apenas nas inserções
};

void criarDequeVazio(Deque& deque) {
    deque.inicio = nullptr;
    deque.fim = nullptr;
}

bool dequeVazio(const Deque& deque) {
    return deque.inicio == nullptr;
}

// Complexidade das quatro operações: O(1).
void insereComeco(Deque& deque, int valor) {
    No* novo = new No{valor, nullptr, deque.inicio};
    if (dequeVazio(deque)) deque.fim = novo;
    else deque.inicio->anterior = novo;
    deque.inicio = novo;
}

void insereFim(Deque& deque, int valor) {
    No* novo = new No{valor, deque.fim, nullptr};
    if (dequeVazio(deque)) deque.inicio = novo;
    else deque.fim->proximo = novo;
    deque.fim = novo;
}

bool removeComeco(Deque& deque, int& valor) {
    if (dequeVazio(deque)) return false;
    No* removido = deque.inicio;
    valor = removido->valor;
    deque.inicio = removido->proximo;
    if (deque.inicio == nullptr) deque.fim = nullptr;
    else deque.inicio->anterior = nullptr;
    delete removido;
    return true;
}

bool removeFim(Deque& deque, int& valor) {
    if (dequeVazio(deque)) return false;
    No* removido = deque.fim;
    valor = removido->valor;
    deque.fim = removido->anterior;
    if (deque.fim == nullptr) deque.inicio = nullptr;
    else deque.fim->proximo = nullptr;
    delete removido;
    return true;
}

void mostrar(const Deque& deque) {
    cout << "Deque (comeco -> fim): ";
    if (dequeVazio(deque)) cout << "vazio";
    for (No* atual = deque.inicio; atual != nullptr; atual = atual->proximo)
        cout << atual->valor << " ";
    cout << endl;
}

void liberar(Deque& deque) {
    int valor;
    while (removeComeco(deque, valor)) {}
}

void executarSequencia(Deque& deque) {
    Operacao sequencia[] = {
        {INSERE_COMECO, 3}, {INSERE_FIM, 8}, {INSERE_FIM, 9}, {INSERE_COMECO, 5},
        {REMOVE_COMECO, 0}, {REMOVE_FIM, 0}, {INSERE_COMECO, 6}, {INSERE_FIM, 7},
        {REMOVE_COMECO, 0}, {REMOVE_FIM, 0}, {REMOVE_FIM, 0}
    };
    int total = sizeof(sequencia) / sizeof(sequencia[0]);

    liberar(deque);                          // o exercício começa com o deque vazio
    for (int i = 0; i < total; i++) {
        string operacao;
        int valor;
        if (sequencia[i].tipo == INSERE_COMECO) {
            insereComeco(deque, sequencia[i].valor);
            operacao = "insereComeco(" + to_string(sequencia[i].valor) + ")";
        } else if (sequencia[i].tipo == INSERE_FIM) {
            insereFim(deque, sequencia[i].valor);
            operacao = "insereFim(" + to_string(sequencia[i].valor) + ")";
        } else if (sequencia[i].tipo == REMOVE_COMECO) {
            if (removeComeco(deque, valor)) operacao = "removeComeco() = " + to_string(valor);
            else operacao = "removeComeco() (vazio)";
        } else {
            if (removeFim(deque, valor)) operacao = "removeFim() = " + to_string(valor);
            else operacao = "removeFim() (vazio)";
        }
        cout << left << setw(22) << operacao;
        mostrar(deque);
    }

    cout << "Conteudo final do deque: ";
    if (dequeVazio(deque)) cout << "vazio";
    for (No* atual = deque.inicio; atual != nullptr; atual = atual->proximo)
        cout << atual->valor << " ";
    cout << endl;
}

int lerValor() {
    int valor;
    cout << "Valor para inserir: ";
    while (!(cin >> valor)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Valor invalido. Digite um numero inteiro: ";
    }
    return valor;
}

int main() {
    Deque deque;
    int opcao, valor;
    criarDequeVazio(deque);

    do {
        cout << endl;
        cout << "========== DEQUE ==========" << endl;
        cout << "1 - Executar a sequencia do exercicio" << endl;
        cout << "2 - Inserir no comeco" << endl;
        cout << "3 - Inserir no fim" << endl;
        cout << "4 - Remover do comeco" << endl;
        cout << "5 - Remover do fim" << endl;
        cout << "6 - Mostrar o deque" << endl;
        cout << "7 - Sair" << endl;
        cout << "Escolha uma opcao (1 a 7): ";
        while (!(cin >> opcao) || opcao < 1 || opcao > 7) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Opcao invalida. Digite um numero de 1 a 7: ";
        }

        if (opcao == 1) {
            executarSequencia(deque);
        } else if (opcao == 2) {
            insereComeco(deque, lerValor());
            mostrar(deque);
        } else if (opcao == 3) {
            insereFim(deque, lerValor());
            mostrar(deque);
        } else if (opcao == 4 || opcao == 5) {
            bool removeu;
            if (opcao == 4) removeu = removeComeco(deque, valor);
            else removeu = removeFim(deque, valor);
            if (removeu) cout << "Valor removido: " << valor << endl;
            else cout << "O deque esta vazio." << endl;
            mostrar(deque);
        } else if (opcao == 6) {
            mostrar(deque);
        }
    } while (opcao != 7);

    liberar(deque);
    return 0;
}
