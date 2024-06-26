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
// Códigos de status de quarto
#define OCUPADO 1
#define DESOCUPADO 0
// Meses do ano
#define JANEIRO 1
#define FEVEREIRO 2
#define MARCO 3
#define ABRIL 4
#define MAIO 5
#define JUNHO 6
#define JULHO 7
#define AGOSTO 8
#define SETEMBRO 9
#define OUTUBRO 10
#define NOVEMBRO 11
#define DEZEMBRO 12

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
    int qntdHospedes;
    int qntdDiarias;
    int codigoCliente;
    int numQuarto;
    int isTerminada;
};
struct Quarto {
    int numero;
    int qntdHospedes;
    int valorDiaria;
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
        // fflush(stdin);
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
        if (resp < 1 || resp > 9){
            printf("Resposta inválida! Digite novamente.\n");
        }
        printf("1 - Cadastrar um cliente\n");
        printf("2 - Cadastrar um funcionario\n");
        printf("3 - Cadastrar uma estadia\n");
        printf("4 - Cadastrar um quarto\n");
        printf("5 - Dar baixa em uma estadia\n");
        printf("6 - Pesquisar cliente\n");
        printf("7 - Pesquisar funcionario\n");
        printf("8 - Mostrar estadias de um cliente\n");
        printf("9 - Sair\n");
        scanf("%d", &resp);
    } while (resp < 1 || resp > 9);
    return resp;
}

void cadastrarCliente(int * qntdClientes, struct Cliente * clientes){
    int codigo = *qntdClientes;
    char nome[100];
    char endereco[100];
    long telefone = 1;
    clearScreen();
    printf("Digite o nome do cliente: \n");
    scanf(" %[^\n]s", &nome); replaceSpace(&nome);
    printf("Digite o endereco do cliente: \n");
    scanf(" %[^\n]s", &endereco); replaceSpace(&endereco);
    do {
        if (telefone <= 0){
            printf("O numero de telefone deve ser maior que 0\n");
        }
        printf("Digite o telefone do cliente: \n");
        scanf("%ld", &telefone);
    } while (telefone <= 0);
    FILE * file;
    file = fopen("clientes.txt", "a");
    if (file == NULL){
        printf("Nao foi possivel adicionar o cliente.\n");
        return;
    }

    fprintf(file, "%d\t%s\t%s\t%ld\n", codigo, nome, endereco, telefone);
    fclose(file);
    struct Cliente c;
    c.codigo = codigo;
    c.telefone = telefone;
    strcpy(c.nome, nome);
    strcpy(c.endereco, endereco);
    clientes[codigo] = c;
    *qntdClientes = *qntdClientes + 1;
}

void cadastrarFuncionario(int * qntdFuncionarios, struct Funcionario * funcionarios){
    int codigo = *qntdFuncionarios;
    char nome[100];
    long telefone = 1;
    float salario = 1;
    int cargo = 1;
    clearScreen();
    printf("Digite o nome do funcionario: \n");
    scanf(" %[^\n]s", &nome); replaceSpace(&nome);
    do {
        if (telefone <= 0){
            printf("O numero de telefone deve ser maior que 0\n");
        }
        printf("Digite o telefone do funcionario: \n");
        scanf("%ld", &telefone);
    } while (telefone <= 0);
    do {
        if (salario <= 0){
            printf("O salario deve ser maior que 0!\n");
        }
        printf("Digite o salario do cliente: R$");
        scanf("%f", &salario);
    } while(salario <= 0);
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
    FILE * file;
    file = fopen("funcionarios.txt", "a");
    if (file == NULL){
        printf("Nao foi possivel adicionar o funcionario.\n");
        return;
    }

    fprintf(file, "%d\t%s\t%ld\t%.2f\t%d\n", codigo, nome, telefone, salario, cargo);
    fclose(file);
    struct Funcionario f;
    f.codigo = codigo;
    f.telefone = telefone;
    f.salario = salario;
    f.cargo = cargo;
    strcpy(f.nome, nome);
    funcionarios[codigo] = f;
    *qntdFuncionarios = *qntdFuncionarios + 1;
}

int verificarNumQuarto(int n,int qntdQuartos, struct Quarto * quartos){
    for (int i = 0; i < qntdQuartos; i++){
        if (quartos[i].numero == n){
            return 0;
        }
    }
    return 1;
}
void cadastrarQuarto(int * qntdQuartos, struct Quarto * quartos){
    clearScreen();
    int num = 1; int disp = 1;
    int qntdHospedes = 1;
    float valorDiaria = 1;
    do {
        if (num <= 0 || !disp){
            printf("O numero digitado nao e valido\n");
        }
        printf("Digite o numero do quarto: ");
        scanf("%d", &num);
        disp = verificarNumQuarto(num, *qntdQuartos, quartos);
    } while (!disp || num <= 0);
    do {
        if (qntdHospedes <= 0){
            printf("A quantidade de hospedes suportada deve ser maior que 0!\n");
        }
        printf("Digite a quantidade de hospedes suportada: ");
        scanf("%d", &qntdHospedes);
    } while (qntdHospedes <= 0);
    do {
        if (valorDiaria <= 0){
            printf("O valor da diaria deve ser maior que 0!\n");
        }
        printf("Digite o valor da diaria: R$");
        scanf("%f", &valorDiaria);
    } while (valorDiaria <= 0);
    FILE * file;
    file = fopen("quartos.txt", "a");
    if (file == NULL){
        printf("Ocorreu um erro ao adicionar o quarto!\n");
        return;
    }
    fprintf(file, "%d\t%d\t%.2f\n", num, qntdHospedes, valorDiaria);
    struct Quarto q;
    q.numero = num;
    q.qntdHospedes = qntdHospedes;
    q.valorDiaria = valorDiaria;
    quartos[*qntdQuartos] = q;
    *qntdQuartos = *qntdQuartos + 1;
    fclose(file);
}

void pesquisarFuncionario(int * qntdFuncionarios, struct Funcionario * funcionarios){
    clearScreen();
    printf("Deseja pesquisar o funcionario por: \n");
    printf("\t [1] - Codigo\n");
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
        printf("\tCodigo do funcionario: %d\n", codigo);
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
                printf("\tCodigo do funcionario: %d\n", i);
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
    printf("\t [1] - Codigo\n");
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
        printf("-----------------\n");
        printf("Resultado da pesquisa:\n");
        printf("\tCodigo do cliente: %d\n", codigo);
        printf("\tNome: %s\n", clientes[codigo].nome);
        printf("\tTelefone: %ld\n", clientes[codigo].telefone);
        printf("\tEndereco: %s\n", clientes[codigo].endereco);
        printf("-----------------\n");
    } else {
        // pesquisa por nome
        char n[100];
        printf("Digite o nome: ");
        scanf(" %[^\n]s", n);
        for (int i = 0; i < *qntdClientes; i++){
            if (strstr(clientes[i].nome, n)){
                printf("-----------------\n");
                printf("Resultado da pesquisa:\n");
                printf("\tCodigo do cliente: %d\n", i);
                printf("\tNome: %s\n", clientes[i].nome);
                printf("\tTelefone: %ld\n", clientes[i].telefone);
                printf("\tEndereco: %s\n", clientes[i].endereco);
            }
        }
        printf("-----------------\n");
    }
}

int getMAXdiaMes(int m) {
    if (
        m == JANEIRO ||
        m == MARCO ||
        m == MAIO ||
        m == JULHO ||
        m == AGOSTO ||
        m == OUTUBRO ||
        m == DEZEMBRO
    ){
        return 31;
    } else if (m == FEVEREIRO) {
        return 28;
    }
    return 30;
}

void pedirData(int * d, int * m, int * a, char * tipoDeData){
    int confirmar = 0;
    while (confirmar != 1){
        do {
            if (*a < 2000){
                printf("O menor ano possivel eh 2000\n");
            }
            printf("Digite o ano da data de %s: ", tipoDeData);
            scanf("%d", a);
        } while (*a < 2000);
        do {
            if (*m < JANEIRO || *m > DEZEMBRO){
                printf("Digite um numero de mes valido! (entre 1 e 12)");
            }
            printf("Digite o mes (entre 1 e 12) da data de %s: ", tipoDeData);
            scanf("%d", m);
        } while (*m < JANEIRO || *m > DEZEMBRO);
        do {
            if (*d < 1 || *d > getMAXdiaMes(*m)){
                printf("Digite um dia valido desse mes!\n");
            }
            printf("Digite o dia da data de %s: ", tipoDeData);
            scanf("%d", d);
        } while (*d < 1 || *d > getMAXdiaMes(*m));
        printf("Confirme a data de entrada: %d/%d/%d\n", *d, *m , *a);
        printf("1 - Sim | Outro valor - Corrigir\n");
        scanf("%d", &confirmar);
    }
}

int verificarDisponibilidadeQuarto(int dataEntrada, int dataSaida, int qntdEstadias, struct Estadia * estadias, int numQuarto){
    for (int i = 0; i < qntdEstadias; i++){
        if (estadias[i].numQuarto != numQuarto || estadias[i].isTerminada){continue;}
        int diasDosMesesEst = 0; int diasDosMesesSaidaEst = 0;
        for (int j = estadias[i].dataEntrada[1]-1; j >= 1; j--){
            diasDosMesesEst += getMAXdiaMes(j);
        }
        for (int j = estadias[i].dataSaida[1]-1; j >= 1; j--){
            diasDosMesesSaidaEst += getMAXdiaMes(j);
        }
        int dataEntradaEst = (estadias[i].dataEntrada[2]*365 + diasDosMesesEst + estadias[i].dataEntrada[0]);
        int dataSaidaEst = (estadias[i].dataSaida[2]*365 + diasDosMesesSaidaEst + estadias[i].dataSaida[0]);
        if (
            ((dataEntrada > dataEntradaEst && dataEntrada < dataSaidaEst) ||
             (dataSaida > dataEntradaEst && dataSaida < dataSaidaEst)) ||
            (dataEntrada < dataEntradaEst && dataSaida > dataSaidaEst)
        ){
            return 0;
        }
    }
    return 1;
}

int acharQuartoLivre(int d, int m, int a, int dS, int mS, int aS, int qntdEstadias, struct Estadia * estadias, int qntdQuartos ,struct Quarto * quartos, int qntdHospedes){
    int diasDosMeses = 0; int diasDosMesesSaida = 0;
    for (int i = m-1; i >= 1; i--){
        diasDosMeses += getMAXdiaMes(i);
    }
    for (int i = mS-1; i >= 1; i--){
        diasDosMesesSaida += getMAXdiaMes(i);
    }
    int dataEntrada = (a*365 + diasDosMeses + d);
    int dataSaida = (a*365 + diasDosMesesSaida + dS);
    for (int i = 0; i < qntdQuartos; i++){
        if (quartos[i].qntdHospedes >= qntdHospedes){
            int isDisponivel = verificarDisponibilidadeQuarto(dataEntrada, dataSaida, qntdEstadias, estadias, quartos[i].numero);
            if (isDisponivel){
                return quartos[i].numero;
            }
        }
    }
    return -1;
}

void cadastrarEstadia(int * qntdEstadias, int qntdClientes, struct Estadia * estadias, int qntdQuartos, struct Quarto * quartos){
    int codCliente = 0;
    int qntdHospedes = 1;
    int d = 1, m = 1, a = 2000; // dia / mes / ano
    int dS = 1, mS = 1, aS = 2000; // dia / mes / ano
    do {
        if (codCliente < 0 || codCliente >= qntdClientes){
            printf("Esse codigo de cliente nao eh valido!\n");
        }
        printf("Digite o codigo do cliente: ");
        scanf("%d", &codCliente);
    } while (codCliente < 0 || codCliente >= qntdClientes);
    do {
        if (qntdHospedes <= 0){
            printf("A quantidade de hospedes deve ser maior que 0!\n");
        }
        printf("Digite a quantidade de hospedes: ");
        scanf("%d", &qntdHospedes);
    } while (qntdHospedes <= 0);
    pedirData(&d, &m, &a, "entrada");
    pedirData(&dS, &mS, &aS, "saida");
    struct Estadia e;
    e.qntdHospedes = qntdHospedes;
    e.codigoCliente = codCliente;
    // calculo das diarias
    a -= 2000; aS -= 2000;
    int diasDosMeses = 0; int diasDosMesesSaida = 0;
    for (int i = m-1; i >= 1; i--){
        diasDosMeses += getMAXdiaMes(i);
    }
    for (int i = mS-1; i >= 1; i--){
        diasDosMesesSaida += getMAXdiaMes(i);
    }
    e.qntdDiarias = (aS*365 + diasDosMesesSaida + dS)-(a*365 + diasDosMeses + d);
    e.dataEntrada[0] = d;
    e.dataEntrada[1] = m;
    e.dataEntrada[2] = a;
    e.dataSaida[0] = dS;
    e.dataSaida[1] = mS;
    e.dataSaida[2] = aS;
    e.codigo = *qntdEstadias;
    e.numQuarto = acharQuartoLivre(d,m,a,dS,mS,aS, *qntdEstadias, estadias, qntdQuartos, quartos, qntdHospedes);
    e.isTerminada = 0;
    if (e.numQuarto == -1){
        printf("Nao foi possivel achar um quarto livre com essas datas\n");
        pausar();
        return;
    }
    FILE * file;
    file = fopen("estadias.txt", "a");
    if (file == NULL){
        printf("Nao foi possivel realizar o cadastro da estadia\n");
        return;
    }
    fprintf(file, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t0\n", e.codigo, e.codigoCliente, e.numQuarto, e.qntdDiarias, e.qntdHospedes, e.dataEntrada[0], e.dataEntrada[1], e.dataEntrada[2], e.dataSaida[0], e.dataSaida[1], e.dataSaida[2]);
    estadias[e.codigo] = e;
    *qntdEstadias = *qntdEstadias + 1;
    printf("Estadia cadastrada! Quarto encontrado: %d\n", e.numQuarto);
    fclose(file);
}

void darBaixaEmEstadia(int qntdEstadias, struct Estadia * estadias, int qntdQuartos,struct Quarto * quartos){
    int codigo = 0;
    int confirm = 0;
    do {
        if (codigo < 0 || codigo >= qntdEstadias){
            printf("Digite um codigo valido!\n");
        }
        printf("Digite o codigo da estadia em que deseja dar baixa: \n");
        scanf("%d", &codigo);
    } while (codigo < 0 || codigo >= qntdEstadias);
    float valorDiarias = 0;
    for (int i = 0; i < qntdQuartos; i++){
        if (quartos[i].numero == estadias[codigo].numQuarto){
            valorDiarias = estadias[codigo].qntdDiarias * quartos[i].valorDiaria;
            break;
        }
    }
    printf("O valor a ser pago eh: R$%.2f\n", valorDiarias);
    printf("Tem certeza que deseja dar baixa na estadia de codigo: %d\n", codigo);
    printf("1 - Sim | Outro Valor - Nao\n");
    scanf("%d", &confirm);
    if (confirm != 1){
        return;
    }
    estadias[codigo].isTerminada = 1;
    FILE * file;
    file = fopen("estadias.txt", "w");
    if (file == NULL){
        printf("Ocorreu um erro! Tente novamente!");
        return;
    }
    for (int i = 0; i < qntdEstadias; i++){
        fprintf(file, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", estadias[i].codigo, estadias[i].codigoCliente, estadias[i].numQuarto, estadias[i].qntdDiarias, estadias[i].qntdHospedes, estadias[i].dataEntrada[0], estadias[i].dataEntrada[1], estadias[i].dataEntrada[2], estadias[i].dataSaida[0], estadias[i].dataSaida[1], estadias[i].dataSaida[2], estadias[i].isTerminada);
    }
    fclose(file);
}

void mostrarEstadiasCliente(int qntdEstadias, struct Estadia * estadias, int qntdClientes){
    int codCliente = 0;
    do {
        if (codCliente < 0 || codCliente >= qntdClientes){
            printf("Digite um codigo de cliente valido!\n");
        }
        printf("Digite o codigo do cliente: ");
        scanf("%d", &codCliente);
    } while (codCliente < 0 || codCliente >= qntdClientes);
    for (int i = 0; i < qntdEstadias; i++){
        if (estadias[i].codigoCliente != codCliente){
            continue;
        }
        printf("-----------------\n");
        printf("Codigo da Estadia: %d\n", estadias[i].codigo);
        printf("Qntd. Hospedes: %d\n", estadias[i].qntdHospedes);
        printf("Qntd. Diarias: %d\n", estadias[i].qntdDiarias);
        printf("Numero do Quarto: %d\n", estadias[i].numQuarto);
        printf("Data de Entrada: %d/%d/%d\n", estadias[i].dataEntrada[0], estadias[i].dataEntrada[1], estadias[i].dataEntrada[2]);
        printf("Data de Saida: %d/%d/%d\n", estadias[i].dataSaida[0], estadias[i].dataSaida[1], estadias[i].dataSaida[2]);
    }
    printf("-----------------\n");

}
