/*
 * Fila de atendimento da emergência de um hospital
 * ---------------------------------------------------------------------------
 * Objetivo : gerenciar a fila de atendimento com uma fila encadeada que guarda
 *            ponteiros para o início (frente) e para o fim (cauda), de modo que
 *            a inserção seja O(1). Cada nó contém nome, CPF, idade e nível de
 *            prioridade do paciente (1 = baixa, 2 = média, 3 = alta). A
 *            prioridade é apenas um dado do paciente: a ordem de atendimento
 *            continua sendo a de chegada (FIFO), como pede o enunciado.
 * Entrada  : a quantidade de pacientes (mínimo 4) e, para cada um: nome
 *            completo (pode ter espaços), CPF (apenas texto — use dados
 *            fictícios), idade e prioridade (1, 2 ou 3).
 * Saída    : a fila após o cadastro, os dados dos dois pacientes atendidos e
 *            o estado final da fila.
 * Exemplo  : Pacientes: Ana (prioridade 3), Bruno (1), Carla (2), Davi (3)
 *            Atendidos: Ana e Bruno
 *            Fila final: Carla, Davi
 * Compilar : g++ -std=c++11 -Wall -Wextra fila-hospital.cpp -o fila-hospital
 * Executar : ./fila-hospital   (Windows: fila-hospital.exe)
 */
#include <iostream>
#include <string>
using namespace std;

const int MIN_PACIENTES = 4;                 // o enunciado pede ao menos quatro pacientes
const int ATENDIMENTOS = 2;                  // quantidade de remoções realizadas

struct Paciente {
    string nome;
    string cpf;
    int idade;
    int prioridade;
};

struct No {
    Paciente dados;
    No* proximo;
};

struct Fila {
    No* inicio;                              // frente: próximo paciente a ser atendido
    No* fim;                                 // cauda: último paciente que chegou
};

// (a) Cria uma fila vazia.
void criarFilaVazia(Fila& fila) {
    fila.inicio = nullptr;
    fila.fim = nullptr;
}

// (b) Aloca um novo nó com os dados do paciente.
No* criarPaciente(string nome, string cpf, int idade, int prioridade) {
    No* novo = new No;
    novo->dados.nome = nome;
    novo->dados.cpf = cpf;
    novo->dados.idade = idade;
    novo->dados.prioridade = prioridade;
    novo->proximo = nullptr;
    return novo;
}

// (c) Insere o paciente no fim da fila. Complexidade: O(1).
void enfileirar(Fila& fila, No* novo) {
    if (fila.inicio == nullptr) fila.inicio = novo;
    else fila.fim->proximo = novo;
    fila.fim = novo;
}

string textoPrioridade(int prioridade) {
    if (prioridade == 1) return "1 (baixa)";
    if (prioridade == 2) return "2 (media)";
    return "3 (alta)";
}

void mostrarPaciente(const Paciente& paciente) {
    cout << "Nome: " << paciente.nome << endl;
    cout << "CPF: " << paciente.cpf << endl;
    cout << "Idade: " << paciente.idade << endl;
    cout << "Prioridade: " << textoPrioridade(paciente.prioridade) << endl;
}

// (d) Remove o paciente da frente, mostra seus dados e libera o nó.
void desenfileirar(Fila& fila) {
    if (fila.inicio == nullptr) {
        cout << "A fila esta vazia. Nao ha pacientes para atender." << endl;
        return;
    }

    No* removido = fila.inicio;
    fila.inicio = removido->proximo;
    if (fila.inicio == nullptr) fila.fim = nullptr;

    cout << "Paciente atendido:" << endl;
    mostrarPaciente(removido->dados);
    delete removido;
}

// (e) Percorre e mostra todos os pacientes, sem removê-los.
void exibirFila(const Fila& fila) {
    if (fila.inicio == nullptr) {
        cout << "A fila esta vazia." << endl;
        return;
    }

    int posicao = 1;
    for (No* atual = fila.inicio; atual != nullptr; atual = atual->proximo) {
        cout << endl;
        cout << "Posicao " << posicao << ":" << endl;
        mostrarPaciente(atual->dados);
        posicao++;
    }
}

void liberar(Fila& fila) {
    while (fila.inicio != nullptr) {
        No* removido = fila.inicio;
        fila.inicio = fila.inicio->proximo;
        delete removido;
    }
    fila.fim = nullptr;
}

// Lê um inteiro entre minimo e maximo, repetindo a leitura se o valor for inválido.
int lerInteiro(int minimo, int maximo) {
    int valor;
    while (!(cin >> valor) || valor < minimo || valor > maximo) {
        cin.clear();                         // limpa o estado de erro (ex.: digitou letras)
        cin.ignore(1000, '\n');              // descarta o restante da linha
        cout << "Valor invalido. Digite um numero de " << minimo << " a " << maximo << ": ";
    }
    return valor;
}

int main() {
    Fila fila;
    int quantidade;
    criarFilaVazia(fila);

    cout << "Quantidade de pacientes (minimo " << MIN_PACIENTES << "): ";
    quantidade = lerInteiro(MIN_PACIENTES, 1000);

    for (int i = 0; i < quantidade; i++) {
        string nome, cpf;
        int idade, prioridade;

        cout << endl << "Paciente " << i + 1 << endl;
        cout << "Nome completo: ";
        getline(cin >> ws, nome);            // "cin >> ws" descarta o Enter que sobrou da leitura anterior
        cout << "CPF (apenas texto, ex.: 000.000.000-00): ";
        cin >> cpf;
        cout << "Idade: ";
        idade = lerInteiro(0, 150);
        cout << "Prioridade (1 = baixa, 2 = media, 3 = alta): ";
        prioridade = lerInteiro(1, 3);

        enfileirar(fila, criarPaciente(nome, cpf, idade, prioridade));
    }

    cout << endl << "========== FILA APOS O CADASTRO ==========" << endl;
    exibirFila(fila);

    cout << endl << "========== ATENDIMENTOS ==========" << endl;
    for (int i = 0; i < ATENDIMENTOS; i++) {
        cout << endl;
        desenfileirar(fila);
    }

    cout << endl << "========== ESTADO FINAL DA FILA ==========" << endl;
    exibirFila(fila);

    liberar(fila);
    return 0;
}
