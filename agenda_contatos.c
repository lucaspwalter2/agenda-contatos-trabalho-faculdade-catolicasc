#include <stdio.h>
#include <string.h>

#define MAX_CONTATOS 100
#define TAM_NOME 80
#define TAM_TELEFONE 30
#define TAM_EMAIL 80
#define TAM_CIDADE 60
#define ARQUIVO_DADOS "contatos.txt"

typedef struct {
    char nome[TAM_NOME];
    char telefone[TAM_TELEFONE];
    char email[TAM_EMAIL];
    char cidade[TAM_CIDADE];
} Contato;

void limpar_enter(char texto[]) {
    int tamanho;

    tamanho = strlen(texto);
    if (tamanho > 0 && texto[tamanho - 1] == '\n') {
        texto[tamanho - 1] = '\0';
    }
}

void ler_texto(char mensagem[], char texto[], int tamanho) {
    printf("%c", mensagem);
    fgets(texto, tamanho, stdin);
    limpar_enter(texto);
}

void pausar() {
    char enter[5];

    printf("\nPressione ENTER para continuar...");
    fgets(enter, 5, stdin);
}

void salvar_contatos(Contato contatos[], int quantidade) {
    FILE *arquivo;
    int i;

    arquivo = fopen(ARQUIVO_DADOS, "w");
    if (arquivo == NULL) {
        printf("\nNao foi possivel salvar os contatos.\n");
        return;
    }

    for (i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%c;%c;%c;%c\n",
                contatos[i].nome,
                contatos[i].telefone,
                contatos[i].email,
                contatos[i].cidade);
    }

    fclose(arquivo);
}

int carregar_contatos(Contato contatos[]) {
    FILE *arquivo;
    int quantidade;

    quantidade = 0;
    arquivo = fopen(ARQUIVO_DADOS, "r");

    if (arquivo == NULL) {
        return 0;
    }

    while (quantidade < MAX_CONTATOS &&
           fscanf(arquivo, "%79[^;];%29[^;];%79[^;];%59[^\n]\n",
                  contatos[quantidade].nome,
                  contatos[quantidade].telefone,
                  contatos[quantidade].email,
                  contatos[quantidade].cidade) == 4) {
        quantidade++;
    }

    fclose(arquivo);
    return quantidade;
}

void incluir_contato(Contato contatos[], int *quantidade) {
    if (*quantidade >= MAX_CONTATOS) {
        printf("\nAgenda cheia.\n");
        return;
    }

    printf("\n=== Incluir contato ===\n");
    ler_texto("Nome: ", contatos[*quantidade].nome, TAM_NOME);
    ler_texto("Telefone: ", contatos[*quantidade].telefone, TAM_TELEFONE);
    ler_texto("E-mail: ", contatos[*quantidade].email, TAM_EMAIL);
    ler_texto("Cidade: ", contatos[*quantidade].cidade, TAM_CIDADE);

    if (strlen(contatos[*quantidade].nome) == 0 ||
        strlen(contatos[*quantidade].telefone) == 0) {
        printf("\nNome e telefone sao obrigatorios. Contato nao cadastrado.\n");
        return;
    }

    (*quantidade)++;
    salvar_contatos(contatos, *quantidade);
    printf("\nContato cadastrado com sucesso.\n");
}

void mostrar_contato(Contato contato, int numero) {
    printf("\nContato %i\n", numero);
    printf("Nome: %c\n", contato.nome);
    printf("Telefone: %c\n", contato.telefone);
    printf("E-mail: %c\n", contato.email);
    printf("Cidade: %c\n", contato.cidade);
}

void listar_contatos(Contato contatos[], int quantidade) {
    int i;

    printf("\n=== Lista de contatos ===\n");

    if (quantidade == 0) {
        printf("Nenhum contato cadastrado.\n");
        return;
    }

    for (i = 0; i < quantidade; i++) {
        mostrar_contato(contatos[i], i + 1);
    }
}

void consultar_contato(Contato contatos[], int quantidade) {
    char busca[TAM_NOME];
    int i;
    int encontrou;

    encontrou = 0;
    printf("\n=== Consultar contato ===\n");
    ler_texto("Digite o nome ou parte do nome: ", busca, TAM_NOME);

    for (i = 0; i < quantidade; i++) {
        if (strstr(contatos[i].nome, busca) != NULL) {
            mostrar_contato(contatos[i], i + 1);
            encontrou = 1;
        }
    }

    if (encontrou == 0) {
        printf("\nContato nao encontrado.\n");
    }
}

void excluir_contato(Contato contatos[], int *quantidade) {
    char busca[TAM_NOME];
    int i;
    int j;
    int encontrou;

    encontrou = 0;

    printf("\n=== Excluir contato ===\n");
    ler_texto("Digite o nome exato do contato: ", busca, TAM_NOME);

    for (i = 0; i < *quantidade; i++) {
        if (strcmp(contatos[i].nome, busca) == 0) {
            for (j = i; j < *quantidade - 1; j++) {
                contatos[j] = contatos[j + 1];
            }

            (*quantidade)--;
            salvar_contatos(contatos, *quantidade);
            printf("\nContato excluido com sucesso.\n");
            encontrou = 1;
            break;
        }
    }

    if (encontrou == 0) {
        printf("\nContato nao encontrado.\n");
    }
}

void mostrar_menu() {
    printf("\n==============================\n");
    printf("      AGENDA DE CONTATOS\n");
    printf("==============================\n");
    printf("1 - Incluir contato\n");
    printf("2 - Listar contatos\n");
    printf("3 - Consultar contato pelo nome\n");
    printf("4 - Excluir contato\n");
    printf("5 - Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    Contato contatos[MAX_CONTATOS];
    int quantidade;
    int opcao;
    char linha[20];

    quantidade = carregar_contatos(contatos);
    opcao = 0;

    while (opcao != 5) {
        mostrar_menu();
        fgets(linha, 20, stdin);
        sscanf(linha, "%i", &opcao);

        switch (opcao) {
            case 1:
                incluir_contato(contatos, &quantidade);
                pausar();
                break;
            case 2:
                listar_contatos(contatos, quantidade);
                pausar();
                break;
            case 3:
                consultar_contato(contatos, quantidade);
                pausar();
                break;
            case 4:
                excluir_contato(contatos, &quantidade);
                pausar();
                break;
            case 5:
                printf("\nPrograma encerrado.\n");
                break;
            default:
                printf("\nOpcao invalida.\n");
                pausar();
                break;
        }
    }

    return 0;
}
