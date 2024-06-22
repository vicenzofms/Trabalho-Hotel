#include <stdio.h>
#include <stdlib.h>
#include "hotel.h"
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

FILE *file;
struct Cliente clientes[MAX_CLIENTES];
struct Funcionario funcionarios[MAX_FUNCIONARIOS];
struct Estadia estadias[MAX_ESTADIAS];
struct Quarto quartos[MAX_QUARTOS];

int qntdClientes = 0;
int qntdFuncionarios = 0;
int qntdEstadias = 0;

void loadClientes(){
    file = fopen("clientes.txt", "r");
    if (file == NULL){
        return;
    }
    int codigo = 0;
    char nome[100];
    char endereco[100];
    long telefone = 0;
    while (1){
        fscanf(file, "%d\t%s\t%s\t%ld", &codigo, &nome, &endereco, &telefone);
        if (feof(file)){ // verifica se acabou o arquivo
            break;
        }
        replaceUnderscore(&nome);
        replaceUnderscore(&endereco);
        struct Cliente cliente =  {
            codigo,
            nome,
            endereco,
            telefone
        };
        clientes[codigo] = cliente;
        qntdClientes++;
    }
    fclose(file);
}
void loadFuncionarios(){
    file = fopen("funcionarios.txt", "r");
    if (file == NULL){
        return;
    }
    int codigo = 0;
    char nome[100];
    long telefone = 0;
    float salario = 0;
    int cargo = 0;
    while (1){
        fscanf(file, "%d\t%s\t%ld\t%f\t%d", &codigo, &nome, &telefone, &salario, &cargo);
        if (feof(file)){ // verifica se acabou o arquivo
            break;
        }
        replaceUnderscore(&nome);
        struct Funcionario funcionario =  {
            codigo,
            nome,
            telefone,
            salario,
            cargo
        };
        funcionarios[codigo] = funcionario;
        qntdFuncionarios++;
    }
    fclose(file);
}

int main(){
    loadClientes();
    loadFuncionarios();
    int resp = 0;
    do {
        resp = mainMenu();
        printf("Nome: %s\n", clientes[qntdClientes].nome);
        switch (resp) {
            case 1:
                cadastrarCliente(file, &qntdClientes, &clientes);
            break;
            case 2:
                cadastrarFuncionario(file, &qntdFuncionarios, &funcionarios);
            break;
            default:
                printf("Saindo...");
        }
    } while (resp < 8);
    return 0;
}
