#include <stdio.h>
#include <string.h>

#define MAX 100
#define TAM_NOME 80
#define TAM_TELEFONE 30
#define TAM_EMAIL 80
#define TAM_CIDADE 60

typedef struct {
    char nome[TAM_NOME];
    char telefone[TAM_TELEFONE];
    char email[TAM_EMAIL];
    char cidade[TAM_CIDADE];
} Contato;

Contato contatos[MAX];
int quantidade = 0;

void salvar() {
    FILE *arquivo;
    int i;

    arquivo = fopen("contatos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar arquivo.\n");
        return;
    }

    for (i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%s;%s;%s;%s\n", contatos[i].nome, contatos[i].telefone,
                contatos[i].email, contatos[i].cidade);
    }

    fclose(arquivo);
}

void carregar() {
    FILE *arquivo;

    arquivo = fopen("contatos.txt", "r");
    if (arquivo == NULL) return;

    while (quantidade < MAX &&
           fscanf(arquivo, "%79[^;];%29[^;];%79[^;];%59[^\n]\n",
                  contatos[quantidade].nome,
                  contatos[quantidade].telefone,
                  contatos[quantidade].email,
                  contatos[quantidade].cidade) == 4) {
        quantidade++;
    }

    fclose(arquivo);
}

void incluir() {
    if (quantidade == MAX) {
        printf("Agenda cheia.\n");
        return;
    }

    printf("\nNome: ");
    scanf(" %79[^\n]", contatos[quantidade].nome);

    printf("Telefone: ");
    scanf(" %29[^\n]", contatos[quantidade].telefone);

    printf("E-mail: ");
    scanf(" %79[^\n]", contatos[quantidade].email);

    printf("Cidade: ");
    scanf(" %59[^\n]", contatos[quantidade].cidade);

    quantidade++;
    salvar();
    printf("Contato cadastrado.\n");
}

void mostrar(int i) {
    printf("\nContato %i\n", i + 1);
    printf("Nome: %s\n", contatos[i].nome);
    printf("Telefone: %s\n", contatos[i].telefone);
    printf("E-mail: %s\n", contatos[i].email);
    printf("Cidade: %s\n", contatos[i].cidade);
}

void listar() {
    int i;

    if (quantidade == 0) {
        printf("Nenhum contato cadastrado.\n");
        return;
    }

    for (i = 0; i < quantidade; i++) {
        mostrar(i);
    }
}

void consultar() {
    char busca[TAM_NOME];
    int i, achou;

    achou = 0;
    printf("\nDigite o nome ou parte do nome: ");
    scanf(" %79[^\n]", busca);

    for (i = 0; i < quantidade; i++) {
        if (strstr(contatos[i].nome, busca) != NULL) {
            mostrar(i);
            achou = 1;
        }
    }

    if (achou == 0) {
        printf("Contato nao encontrado.\n");
    }
}

void excluir() {
    char busca[TAM_NOME];
    int i, j, achou;

    achou = 0;
    printf("\nDigite o nome exato: ");
    scanf(" %79[^\n]", busca);

    for (i = 0; i < quantidade; i++) {
        if (strcmp(contatos[i].nome, busca) == 0) {
            for (j = i; j < quantidade - 1; j++) {
                contatos[j] = contatos[j + 1];
            }

            quantidade--;
            salvar();
            achou = 1;
            printf("Contato excluido.\n");
            break;
        }
    }

    if (achou == 0) {
        printf("Contato nao encontrado.\n");
    }
}

void menu() {
    printf("\n===== AGENDA DE CONTATOS =====\n");
    printf("1 - Incluir contato\n");
    printf("2 - Listar contatos\n");
    printf("3 - Consultar contato pelo nome\n");
    printf("4 - Excluir contato\n");
    printf("5 - Sair\n");
    printf("Opcao: ");
}

int main() {
    int opcao;

    carregar();
    opcao = 0;

    while (opcao != 5) {
        menu();
        scanf("%i", &opcao);

        switch (opcao) {
            case 1:
                incluir();
                break;
            case 2:
                listar();
                break;
            case 3:
                consultar();
                break;
            case 4:
                excluir();
                break;
            case 5:
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    }

    return 0;
}
