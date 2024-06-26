#include <stdio.h>
#include <stdlib.h>
#include "hotel.h"
// numeros maximos
#define MAX_CLIENTES 1000
#define MAX_QUARTOS 100
#define MAX_ESTADIAS 1000
#define MAX_FUNCIONARIOS 50

struct Cliente clientes[MAX_CLIENTES]; 
struct Funcionario funcionarios[MAX_FUNCIONARIOS];
struct Estadia estadias[MAX_ESTADIAS];
struct Quarto quartos[MAX_QUARTOS];

int qntdClientes = 0;
int qntdFuncionarios = 0;
int qntdEstadias = 0;
int qntdQuartos = 0;

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

void loadQuartos(){
    FILE * file;
    file = fopen("quartos.txt", "r");
    if (file == NULL){
        return;
    }
    while (1){
        char linha[1000];
        fgets(linha, 1000, file);
        if (feof(file)){ // verifica se acabou o arquivo
            break;
        }
        int numero = 0;
        int qntdHospedes = 0;
        float valorDiaria = 0;
        sscanf(linha, "%d\t%d\t%f", &numero, &qntdHospedes, &valorDiaria);
        struct Quarto q;
        q.numero = numero;
        q.qntdHospedes = qntdHospedes;
        q.valorDiaria = valorDiaria;
        quartos[qntdQuartos] = q;
        qntdQuartos++;
    }
    fclose(file);
}

void loadEstadias(){
    FILE * file;
    file = fopen("estadias.txt", "r");
    if (file == NULL){
        return;
    }
    while (1){
        char linha [1000];
        fgets(linha, 1000, file);
        if (feof(file)){
            break;
        }
        struct Estadia e;
        sscanf(linha, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d", &e.codigo, &e.codigoCliente, &e.numQuarto, &e.qntdDiarias, &e.qntdHospedes, &e.dataEntrada[0], &e.dataEntrada[1], &e.dataEntrada[2], &e.dataSaida[0], &e.dataSaida[1], &e.dataSaida[2], &e.isTerminada);
        estadias[qntdEstadias] = e;
        qntdEstadias++;
    }
    fclose(file);
}

int main(){
    clearScreen();
    loadQuartos();
    loadClientes();
    loadFuncionarios();
    loadEstadias();
    int resp = 0;
    FILE * file;
    do {
        pausar();
        resp = mainMenu();
        switch (resp) {
            case 1:
                cadastrarCliente(&qntdClientes, &clientes);
            break;
            case 2:
                cadastrarFuncionario(&qntdFuncionarios, &funcionarios);
            break;
            case 3:
                cadastrarEstadia(&qntdEstadias, qntdClientes, &estadias, qntdQuartos, &quartos);
            break;
            case 4:
                cadastrarQuarto(&qntdQuartos, &quartos);
            break;
            case 5:
                darBaixaEmEstadia(qntdEstadias, &estadias, qntdQuartos, &quartos);
            break;
            case 6: 
                pesquisarCliente(&qntdClientes, &clientes);
            break;
            case 7:
                pesquisarFuncionario(&qntdFuncionarios, &funcionarios);
            break;
            case 8:
                mostrarEstadiasCliente(qntdEstadias, &estadias, qntdClientes);
            break;
            default:
                printf("Saindo...");
        }
    } while (resp < 9);
    return 0;
}
