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
    int codigo = qntdClientes;
    char * nome;
    char * endereco;
    long telefone = 0;
    while (fscanf(file, "%d|%s|%s|%ld", &codigo, &nome, &endereco, &telefone) != NULL){
        printf("%d - %s - %s - %ld\n", codigo, nome, endereco, telefone);
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

int main(){
    // loadClientes();
    pausar();
    int resp = 0;
    do {
        resp = mainMenu();
        switch (resp) {
            case 1:
                cadastrarCliente(file, &qntdClientes, &clientes);
            break;
            default:
                printf("Nada aqui.\n");
        }
    } while (resp < 8);
    return 0;
}
