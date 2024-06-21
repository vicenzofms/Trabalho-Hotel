#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/// Define qual comando de pausa usar
#ifdef WIN32
#define PAUSE 1
#else
#define PAUSE 0
#endif

struct Cliente {
    int codigo;
    char * nome;
    char * endereco;
    long telefone;
};
struct Funcionario {
    int codigo;
    char * nome;
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

void cadastrarCliente(FILE *file, int * qntdClientes, struct Cliente * clientes[]){
    int codigo = *qntdClientes;
    char * nome;
    char * endereco;
    long telefone = 0;
    clearScreen();
    printf("Digite o nome do cliente: \n");
    scanf(" %[^\n]s", &nome); replaceSpace(&nome);
    printf("Digite o endereco do cliente: \n");
    scanf(" %[^\n]s", &endereco); replaceSpace(&endereco);
    printf("Digite o telefone do cliente: \n");
    scanf("%ld", &telefone);

    file = fopen("clientes.txt", "a");
    if (file == NULL){
        printf("Nao foi possivel adicionar o cliente.\n");
        pausar();
        return;
    }

    fprintf(file, "%d|%s|%s|%ld\n", codigo, nome, endereco, telefone);
    fclose(file);
    struct Cliente cliente = {codigo, nome, endereco, telefone};
    *clientes[codigo] = cliente;
    *qntdClientes++;
    pausar();
}
