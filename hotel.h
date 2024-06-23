#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
/// Define qual comando de pausa usar
#ifdef WIN32
#define PAUSE 1
#else
#define PAUSE 0
#endif
// Códigos de cargo
#define RECEPCIONISTA 1
#define AUXILIAR_LIMPEZA 2
#define GARCOM 3
#define GERENTE 4

struct Cliente {
    int codigo;
    char nome[100];
    char endereco[150];
    long telefone;
};
struct Funcionario {
    int codigo;
    char nome[100];
    long telefone;
    int cargo; // USAR CÓDIGO DE CARGO
    float salario;
};
struct Estadia {
    int codigo;
    int dataEntrada[3];
    int dataSaida[3];
    int qntdDiarias;
    int codigoCliente;
    int numQuarto;
};
struct Quarto {
    int numero;
    int qntdHospedes;
    int valorDiaria;
    int status; // USAR CODIGO DE STATUS
};

// função para limpar o console
void clearScreen(){
    printf("\e[1;1H\e[2J");
}

// função para pausar o console
void pausar(){
    if (PAUSE == 1){
        system("pause");
    } else {
        system( "read -n 1 -s -p \"Press any key to continue...\"; echo" );
        // system("read -p \"Pressione qualquer tecla para continuar...\"");
        // printf("Pressione ENTER para continuar...\n");
        // getchar();
    }
}

// função que substitui todos os caracteres de espaço por um underscore
void replaceSpace(char * str){
    for(int i = 0; i <= strlen(str); i++){
      if(str[i] == ' '){
         str[i] = '_';
      }
   }
}
// função que substitui todos os caracteres de underscore por um espaço
void replaceUnderscore(char * str){
    for(int i = 0; i <= strlen(str); i++){
      if(str[i] == '_'){
         str[i] = ' ';
      }
   }
}

// função que devolve uma string com o nome do cargo
char * getCargo(int index){
    switch (index) {
        case RECEPCIONISTA:
            return "Recepcionista";
        break;
        case AUXILIAR_LIMPEZA:
            return "Auxiliar de Limpeza";
        break;
        case GERENTE:
            return "Gerente";
        break;
        case GARCOM:
            return "Garcom";
        break;
        default:
            return "Funcionario";
            break;
    }
}
int mainMenu(){
    int resp = 1;
    do {
        clearScreen();
        if (resp < 1 || resp > 8){
            printf("Resposta inválida! Digite novamente.\n");
        }
        printf("1 - Cadastrar um cliente\n");
        printf("2 - Cadastrar um funcionario\n");
        printf("3 - Cadastrar uma estadia\n");
        printf("4 - Dar baixa em uma estadia\n");
        printf("5 - Pesquisar cliente\n");
        printf("6 - Pesquisar funcionario\n");
        printf("7 - Mostrar estadias de um cliente\n");
        printf("8 - Sair\n");
        scanf("%d", &resp);
    } while (resp < 1 || resp > 8);
    return resp;
}

void cadastrarCliente(FILE *file, int * qntdClientes, struct Cliente clientes[]){
    int codigo = *qntdClientes;
    char nome[100];
    char endereco[100];
    long telefone = 0;
    clearScreen();
    printf("Digite o nome do cliente: \n");
    scanf(" %[^\n]s", &nome); replaceSpace(&nome);
    printf("Digite o endereco do cliente: \n");
    scanf(" %[^\n]s", &endereco); replaceSpace(&endereco);
    printf("Digite o telefone do cliente: \n");
    scanf("%ld", &telefone);
    file = fopen("clientes.txt", "a");
    printf("Aberto!");
    if (file == NULL){
        printf("Nao foi possivel adicionar o cliente.\n");
        pausar();
        return;
    }

    fprintf(file, "%d\t%s\t%s\t%ld\n", codigo, nome, endereco, telefone);
    fclose(file);
    // struct Cliente cliente = {codigo, nome, endereco, telefone};
    // clientes[codigo] = cliente;
    *qntdClientes++;
}

void cadastrarFuncionario(FILE *file, int * qntdFuncionarios, struct Funcionario funcionarios[]){
    int codigo = *qntdFuncionarios;
    char nome[100];
    long telefone = 0;
    float salario = 0;
    int cargo = 1;
    clearScreen();
    printf("%s\n", funcionarios[0].nome);
    printf("Digite o nome do funcionario: \n");
    scanf(" %[^\n]s", &nome); replaceSpace(&nome);
    printf("Digite o telefone do cliente: \n");
    scanf("%ld", &telefone);
    printf("Digite o salario do cliente: \n");
    scanf("%f", &salario);
    do {
        if (cargo < 1 || cargo > 4){
            printf("Valor invalido! Digite novamente.\n");
        }
        printf("Digite o numero referente ao cargo:\n");
        printf("\t[1] - Recepcionista\n");
        printf("\t[2] - Auxiliar de Limpeza\n");
        printf("\t[3] - Garcom\n");
        printf("\t[4] - Gerente\n");
        scanf("%d", &cargo);
    } while (cargo < 1 || cargo > 4);
    file = fopen("funcionarios.txt", "a");
    if (file == NULL){
        printf("Nao foi possivel adicionar o funcionario.\n");
        pausar();
        return;
    }

    fprintf(file, "%d\t%s\t%ld\t%.2f\t%d\n", codigo, nome, telefone, salario, cargo);
    fclose(file);
    // struct Funcionario funcionario = {codigo, nome, telefone, cargo, salario};
    // funcionarios[codigo] = funcionario;
    *qntdFuncionarios++;
}

void pesquisarFuncionario(int * qntdFuncionarios, struct Funcionario * funcionarios){
    clearScreen();
    printf("Deseja pesquisar o funcionario por: \n");
    printf("\t [1] - Código\n");
    printf("\t [2] - Nome\n");
    int opt = 1;
    do {
        if (opt < 1 || opt > 2){
            printf("Valor invalido! Digite novamente.\n");
        }
        printf("-> ");
        scanf("%d", &opt);
    } while (opt < 1 || opt > 2);
    if (opt == 1){
        int codigo = 0;
        do {
            if (codigo < 0 || codigo >= *qntdFuncionarios){
                printf("Codigo nao existente. Digite novamente.\n");
            }
            printf("Digite o código: ");
            scanf("%d", &codigo);
        } while (codigo < 0 || codigo >= *qntdFuncionarios);
        printf("-----------------\n");
        printf("Resultado da pesquisa:\n");
        // nome nao esta funcionando
        printf("\tNome: %s\n", funcionarios[codigo].nome);
        printf("\tTelefone: %ld\n", funcionarios[codigo].telefone);
        printf("\tSalario: %.2f\n", funcionarios[codigo].salario);
        printf("\tCargo: %s\n", getCargo(funcionarios[codigo].cargo));
        printf("-----------------\n");
    } else {
        // pesquisa por nome
        char n[100];
        printf("Digite o nome: ");
        scanf(" %[^\n]s", n);
        for (int i = 0; i < *qntdFuncionarios; i++){
            if (strstr(funcionarios[i].nome, n)){
                printf("-----------------\n");
                printf("Resultado da pesquisa:\n");
                printf("\tNome: %s\n", funcionarios[i].nome);
                printf("\tTelefone: %ld\n", funcionarios[i].telefone);
                printf("\tSalario: %.2f\n", funcionarios[i].salario);
                printf("\tCargo: %s\n", getCargo(funcionarios[i].cargo));
            }
        }
        printf("-----------------\n");
    }
}

int pesquisarCliente(int * qntdClientes, struct Cliente * clientes){
    clearScreen();
    printf("Deseja pesquisar o cliente por: \n");
    printf("\t [1] - Código\n");
    printf("\t [2] - Nome\n");
    int opt = 1;
    int codigo = 0;
    do {
        if (opt < 1 || opt > 2){
            printf("Valor invalido! Digite novamente.\n");
        }
        printf("-> ");
        scanf("%d", &opt);
    } while (opt < 1 || opt > 2);
    if (opt == 1){
        do {
            if (codigo < 0 || codigo >= *qntdClientes){
                printf("Codigo nao existente. Digite novamente.\n");
            }
            printf("Digite o código: ");
            scanf("%d", &codigo);
        } while (codigo < 0 || codigo >= *qntdClientes);
        printf("Resultado da pesquisa:\n");
        printf("\tNome: %s\n", clientes[codigo].nome);
        printf("\tTelefone: %ld\n", clientes[codigo].telefone);
        printf("\tEndereco: %s\n", clientes[codigo].endereco);
    } else {
        // pesquisa por nome
        char n[100];
        printf("Digite o nome: ");
        scanf(" %[^\n]s", n);
        for (int i = 0; i < *qntdClientes; i++){
            if (strstr(clientes[i].nome, n)){
                printf("-----------------\n");
                printf("Resultado da pesquisa:\n");
                printf("\tNome: %s\n", clientes[i].nome);
                printf("\tTelefone: %ld\n", clientes[i].telefone);
                printf("\tEndereco: %s\n", clientes[i].endereco);
            }
        }
        printf("-----------------\n");
    }
}
