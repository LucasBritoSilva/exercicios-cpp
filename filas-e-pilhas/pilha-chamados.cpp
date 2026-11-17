/*
 * Pilha de chamados de suporte técnico
 * ---------------------------------------------------------------------------
 * Objetivo : gerenciar chamados de suporte com uma pilha encadeada: o chamado
 *            mais recente é atendido primeiro. Cada chamado tem código, nome
 *            do solicitante, departamento, descrição do problema, nível de
 *            complexidade (1 = simples, 2 = moderado, 3 = complexo) e a data e
 *            hora de abertura (estrutura DataHora). Não é permitido empilhar
 *            dois chamados com o mesmo código.
 * Entrada  : (nesta ordem)
 *            1) a quantidade de chamados (mínimo 6) e, para cada um: código,
 *               solicitante, departamento, descrição (até o Enter),
 *               complexidade, dia, mês, ano, hora e minuto;
 *            2) um chamado com código repetido, para testar a validação;
 *            3) um código existente e um código inexistente para buscar.
 * Saída    : as mensagens de abertura (ou de recusa), o resultado das duas
 *            buscas, o relatório de três atendimentos e os chamados pendentes.
 * Exemplo  : Chamados 101 a 106 abertos (106 é o último).
 *            Chamado com código 103 -> "ERRO: ja existe um chamado com o codigo 103"
 *            Busca 104 -> dados do chamado | Busca 999 -> nao localizado
 *            Atendidos: 106, 105, 104 | Pendentes: 103, 102, 101
 * Compilar : g++ -std=c++11 -Wall -Wextra pilha-chamados.cpp -o pilha-chamados
 * Executar : ./pilha-chamados   (Windows: pilha-chamados.exe)
 */
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

const int MIN_CHAMADOS = 6;                  // o enunciado pede ao menos seis chamados
const int ATENDIMENTOS = 3;                  // quantidade de chamados atendidos

struct DataHora {
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
};

struct Chamado {
    int codigo;
    string solicitante;
    string departamento;
    string descricao;
    int complexidade;
    DataHora abertura;
};

struct No {
    Chamado dados;
    No* proximo;
};

struct Pilha {
    No* topo;
};

// (a) Cria uma pilha vazia.
void criarPilhaVazia(Pilha& pilha) {
    pilha.topo = nullptr;
}

// (b) Aloca um novo nó com os dados do chamado.
No* criarChamado(int codigo, string solicitante, string departamento, string descricao,
                 int complexidade, DataHora abertura) {
    No* novo = new No;
    novo->dados.codigo = codigo;
    novo->dados.solicitante = solicitante;
    novo->dados.departamento = departamento;
    novo->dados.descricao = descricao;
    novo->dados.complexidade = complexidade;
    novo->dados.abertura = abertura;
    novo->proximo = nullptr;
    return novo;
}

// Procura um chamado pelo código, sem modificar a pilha. Retorna nullptr se não existir.
No* procurar(const Pilha& pilha, int codigo) {
    for (No* atual = pilha.topo; atual != nullptr; atual = atual->proximo)
        if (atual->dados.codigo == codigo) return atual;
    return nullptr;
}

// (c) Insere o chamado no topo. Recusa (e libera o nó) se o código já existir.
bool empilhar(Pilha& pilha, No* novo) {
    if (procurar(pilha, novo->dados.codigo) != nullptr) {
        cout << "ERRO: ja existe um chamado com o codigo " << novo->dados.codigo
             << ". O chamado nao foi aberto." << endl;
        delete novo;
        return false;
    }
    novo->proximo = pilha.topo;
    pilha.topo = novo;
    cout << "Chamado " << novo->dados.codigo << " aberto." << endl;
    return true;
}

string textoComplexidade(int complexidade) {
    if (complexidade == 1) return "1 (simples)";
    if (complexidade == 2) return "2 (moderado)";
    return "3 (complexo)";
}

void mostrarDataHora(const DataHora& data) {
    cout << setfill('0')
         << setw(2) << data.dia << "/" << setw(2) << data.mes << "/" << setw(4) << data.ano << " "
         << setw(2) << data.hora << ":" << setw(2) << data.minuto
         << setfill(' ');
}

void mostrarChamado(const Chamado& chamado) {
    cout << "Codigo: " << chamado.codigo << endl;
    cout << "Solicitante: " << chamado.solicitante << endl;
    cout << "Departamento: " << chamado.departamento << endl;
    cout << "Descricao: " << chamado.descricao << endl;
    cout << "Complexidade: " << textoComplexidade(chamado.complexidade) << endl;
    cout << "Abertura: ";
    mostrarDataHora(chamado.abertura);
    cout << endl;
}

// (d) Remove o chamado do topo, mostra o relatório de atendimento e libera o nó.
void atender(Pilha& pilha) {
    if (pilha.topo == nullptr) {
        cout << "Nao ha chamados pendentes." << endl;
        return;
    }

    No* removido = pilha.topo;
    pilha.topo = removido->proximo;

    cout << "------- RELATORIO DE ATENDIMENTO -------" << endl;
    mostrarChamado(removido->dados);
    cout << "Situacao: atendido" << endl;
    cout << "----------------------------------------" << endl;
    delete removido;
}

// (e) Busca um chamado pelo código e mostra o resultado.
void buscarChamado(const Pilha& pilha, int codigo) {
    No* encontrado = procurar(pilha, codigo);
    if (encontrado == nullptr) {
        cout << "Chamado " << codigo << " nao localizado." << endl;
        return;
    }
    cout << "Chamado encontrado:" << endl;
    mostrarChamado(encontrado->dados);
}

// (f) Mostra um resumo dos chamados, do topo ao fundo.
void exibirPendentes(const Pilha& pilha) {
    if (pilha.topo == nullptr) {
        cout << "Nao ha chamados pendentes." << endl;
        return;
    }
    for (No* atual = pilha.topo; atual != nullptr; atual = atual->proximo)
        cout << "Codigo: " << atual->dados.codigo
             << " | Solicitante: " << atual->dados.solicitante
             << " | Complexidade: " << textoComplexidade(atual->dados.complexidade) << endl;
}

void liberar(Pilha& pilha) {
    while (pilha.topo != nullptr) {
        No* removido = pilha.topo;
        pilha.topo = pilha.topo->proximo;
        delete removido;
    }
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

// Lê todos os dados de um chamado e devolve o nó criado por criarChamado.
No* lerChamado() {
    int codigo, complexidade;
    string solicitante, departamento, descricao;
    DataHora abertura;

    cout << "Codigo do chamado: ";
    codigo = lerInteiro(1, 999999);
    cout << "Nome do solicitante: ";
    getline(cin >> ws, solicitante);         // "cin >> ws" descarta o Enter que sobrou da leitura anterior
    cout << "Departamento: ";
    getline(cin >> ws, departamento);
    cout << "Descricao do problema: ";
    getline(cin >> ws, descricao);           // a descrição termina no Enter
    cout << "Complexidade (1 = simples, 2 = moderado, 3 = complexo): ";
    complexidade = lerInteiro(1, 3);
    cout << "Dia de abertura: ";
    abertura.dia = lerInteiro(1, 31);
    cout << "Mes de abertura: ";
    abertura.mes = lerInteiro(1, 12);
    cout << "Ano de abertura: ";
    abertura.ano = lerInteiro(1, 9999);
    cout << "Hora de abertura (0 a 23): ";
    abertura.hora = lerInteiro(0, 23);
    cout << "Minuto de abertura (0 a 59): ";
    abertura.minuto = lerInteiro(0, 59);

    return criarChamado(codigo, solicitante, departamento, descricao, complexidade, abertura);
}

int main() {
    Pilha pilha;
    int quantidade, abertos = 0, codigo;
    criarPilhaVazia(pilha);

    cout << "Quantidade de chamados (minimo " << MIN_CHAMADOS << "): ";
    quantidade = lerInteiro(MIN_CHAMADOS, 1000);

    while (abertos < quantidade) {
        cout << endl << "Chamado " << abertos + 1 << endl;
        if (empilhar(pilha, lerChamado())) abertos++;
    }

    cout << endl << "========== TESTE DE CODIGO DUPLICADO ==========" << endl;
    cout << "Digite um chamado usando um codigo que ja existe:" << endl;
    empilhar(pilha, lerChamado());

    cout << endl << "========== BUSCAS ==========" << endl;
    cout << "Codigo de um chamado existente: ";
    codigo = lerInteiro(1, 999999);
    buscarChamado(pilha, codigo);
    cout << endl << "Codigo de um chamado inexistente: ";
    codigo = lerInteiro(1, 999999);
    buscarChamado(pilha, codigo);

    cout << endl << "========== ATENDIMENTOS ==========" << endl;
    for (int i = 0; i < ATENDIMENTOS; i++) {
        cout << endl;
        atender(pilha);
    }

    cout << endl << "========== CHAMADOS PENDENTES ==========" << endl;
    exibirPendentes(pilha);

    liberar(pilha);
    return 0;
}
