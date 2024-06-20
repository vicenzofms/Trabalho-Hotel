#include <stdio.h>
#include <stdlib.h>

// Define qual comando de pausa usar
#ifdef WIN32
#define PAUSE 1
#else
#define PAUSE 0
#endif
// numeros maximos
#define MAX_CLIENTES 100
#define MAX_QUARTOS 100
#define MAX_ESTADIAS 1000
#define MAX_FUNCIONARIOS 50
// Códigos de status de quarto
#define OCUPADO 1
#define DESOCUPADO 0
// Códigos de cargo
#define RECEPCIONISTA 1
#define AUXILIAR_LIMPEZA 2
#define GARCOM 3
#define GERENTE 4

struct Cliente {
    int codigo;
    char nome[100];
    char endereco[100];
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

FILE *file;
struct Cliente clientes[MAX_CLIENTES];
struct Funcionario funcionarios[MAX_FUNCIONARIOS];
struct Estadia estadias[MAX_ESTADIAS];
struct Quarto quartos[MAX_QUARTOS];

// função para limpar o console
void clearScreen(){
    printf("\e[1;1H\e[2J");
}

// função para pausar o console
void pausar(){
    if (PAUSE == 1){
        system("pause");
    } else {
        system("read -p \"Pressione qualquer tecla para continuar...\"");
    }
}
void replacespace(char * str){
    for(int i = 0; i <= strlen(str); i++){
      if(str[i] == ' '){
         str[i] = '_';
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

void loadClientes(){
    file = fopen("clientes.txt", "r");
    int codigo = 0;
    char nome[100];
    char endereco[100];
    long telefone = 0;
    while (fscanf(file, "%d|%s|%s|%ld", &codigo, &nome, &endereco, &telefone) != NULL){
        printf("%d - %s - %s - %ld\n", codigo, nome, endereco, telefone);
    }
    fclose(file);
}
void cadastrarCliente(){
    int codigo = 0;
    char nome[100];
    char endereco[100];
    long telefone = 0;
    clearScreen();
    printf("Digite o nome do cliente: \n");
    scanf(" %[^\n]s", &nome); replacespace(&nome);
    printf("Digite o endereco do cliente: \n");
    scanf(" %[^\n]s", &endereco); replacespace(&endereco);
    printf("Digite o telefone do cliente: \n");
    scanf("%ld", &telefone);
    
    file = fopen("clientes.txt", "a");
    if (file == NULL){
        printf("Nao foi possivel adicionar o cliente.\n");
        system("pause");
        return;
    }

    fprintf(file, "%d|%s|%s|%ld\n", codigo, nome, endereco, telefone);
    fclose(file);
    struct Cliente cliente = {codigo, nome, endereco, telefone};
    clientes[codigo] = cliente;
    pausar();
}

int main(){
    loadClientes();
    int resp = 0;
    do {
        resp = mainMenu();
        switch (resp) {
            case 1:
                cadastrarCliente();
            break;
            default:
                printf("Nada aqui.\n");
        }
    } while (resp < 8);
    return 0;
}
