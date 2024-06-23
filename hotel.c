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

struct Cliente clientes[MAX_CLIENTES];
struct Funcionario funcionarios[MAX_FUNCIONARIOS];
struct Estadia estadias[MAX_ESTADIAS];
struct Quarto quartos[MAX_QUARTOS];

int qntdClientes = 0;
int qntdFuncionarios = 0;
int qntdEstadias = 0;

void loadClientes(){
    FILE * file;
    file = fopen("clientes.txt", "r");
    if (file == NULL){
        return;
    }
    while (1){
        char linha[1000];
        fgets(linha, 1000, file);
        if (feof(file)){ // verifica se acabou o arquivo
            break;
        }
        int cod = 0;
        char n[100];
        char end[150];
        long tel = 0;
        sscanf(linha, "%d\t%s\t%s\t%ld", &cod, &n, &end, &tel);
        struct Cliente c;
        c.codigo = cod;
        c.telefone = tel;
        replaceUnderscore(&n);
        replaceUnderscore(&end);
        strcpy(c.nome, n);
        strcpy(c.endereco, end);
        clientes[cod] = c;
        qntdClientes++;
    }
    fclose(file);
}
void loadFuncionarios(){
    FILE * file;
    file = fopen("funcionarios.txt", "r");
    if (file == NULL){
        return;
    }
    while (1){
        char linha[1000];
        fgets(linha, 1000, file);
        if (feof(file)){ // verifica se acabou o arquivo
            break;
        }
        int cod = 0;
        char n[100];
        long tel = 0;
        float sal = 0;
        int cargo = 0;
        sscanf(linha, "%d\t%s\t%ld\t%f\t%d", &cod, &n, &tel, &sal, &cargo);
        struct Funcionario f;
        f.codigo = cod;
        f.telefone = tel;
        f.salario = sal;
        f.cargo = cargo;
        replaceUnderscore(&n);
        strcpy(f.nome, n);
        funcionarios[cod] = f;
        qntdFuncionarios++;
    }
    fclose(file);
}

int main(){
    clearScreen();
    loadClientes();
    loadFuncionarios();
    int resp = 0;
    FILE * file;
    do {
        pausar();
        resp = mainMenu();
        switch (resp) {
            case 1:
                cadastrarCliente(file, &qntdClientes, &clientes);
            break;
            case 2:
                cadastrarFuncionario(file, &qntdFuncionarios, &funcionarios);
            break;
            case 5: {
                pesquisarCliente(&qntdClientes, &clientes);
            break;}
            case 6:
                pesquisarFuncionario(&qntdFuncionarios, &funcionarios);
            break;
            default:
                printf("Saindo...");
        }
    } while (resp < 8);
    return 0;
}
