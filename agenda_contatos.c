#include <stdio.h>
#include <string.h>

#define MAX_CONTATOS 100
#define TAM_NOME 80
#define TAM_TELEFONE 30
#define TAM_EMAIL 80
#define TAM_CIDADE 60
#define ARQUIVO "contatos.txt"

typedef struct {
    char nome[TAM_NOME], telefone[TAM_TELEFONE], email[TAM_EMAIL], cidade[TAM_CIDADE];
} Contato;

void limpar_enter(char texto[]) {
    int tam = strlen(texto);
    if (tam > 0 && texto[tam - 1] == '\n') texto[tam - 1] = '\0';
}

void ler_texto(char mensagem[], char texto[], int tamanho) {
    printf("%s", mensagem);
    fgets(texto, tamanho, stdin);
    limpar_enter(texto);
}

void pausar() {
    char enter[5];
    printf("\nPressione ENTER para continuar...");
    fgets(enter, 5, stdin);
}

void salvar_contatos(Contato contatos[], int qtd) {
    FILE *arquivo = fopen(ARQUIVO, "w");
    int i;

    if (arquivo == NULL) {
        printf("\nNao foi possivel salvar os contatos.\n");
        return;
    }

    for (i = 0; i < qtd; i++)
        fprintf(arquivo, "%s;%s;%s;%s\n", contatos[i].nome, contatos[i].telefone,
                contatos[i].email, contatos[i].cidade);

    fclose(arquivo);
}

int carregar_contatos(Contato contatos[]) {
    FILE *arquivo = fopen(ARQUIVO, "r");
    int qtd = 0;

    if (arquivo == NULL) return 0;

    while (qtd < MAX_CONTATOS &&
           fscanf(arquivo, "%79[^;];%29[^;];%79[^;];%59[^\n]\n",
                  contatos[qtd].nome, contatos[qtd].telefone,
                  contatos[qtd].email, contatos[qtd].cidade) == 4)
        qtd++;

    fclose(arquivo);
    return qtd;
}

void mostrar_contato(Contato contato, int numero) {
    printf("\nContato %i\n", numero);
    printf("Nome: %s\nTelefone: %s\nE-mail: %s\nCidade: %s\n",
           contato.nome, contato.telefone, contato.email, contato.cidade);
}

void incluir_contato(Contato contatos[], int *qtd) {
    if (*qtd >= MAX_CONTATOS) {
        printf("\nAgenda cheia.\n");
        return;
    }

    printf("\n=== Incluir contato ===\n");
    ler_texto("Nome: ", contatos[*qtd].nome, TAM_NOME);
    ler_texto("Telefone: ", contatos[*qtd].telefone, TAM_TELEFONE);
    ler_texto("E-mail: ", contatos[*qtd].email, TAM_EMAIL);
    ler_texto("Cidade: ", contatos[*qtd].cidade, TAM_CIDADE);

    if (strlen(contatos[*qtd].nome) == 0 || strlen(contatos[*qtd].telefone) == 0) {
        printf("\nNome e telefone sao obrigatorios.\n");
        return;
    }

    (*qtd)++;
    salvar_contatos(contatos, *qtd);
    printf("\nContato cadastrado com sucesso.\n");
}

void listar_contatos(Contato contatos[], int qtd) {
    int i;
    printf("\n=== Lista de contatos ===\n");

    if (qtd == 0) {
        printf("Nenhum contato cadastrado.\n");
        return;
    }

    for (i = 0; i < qtd; i++) mostrar_contato(contatos[i], i + 1);
}

void consultar_contato(Contato contatos[], int qtd) {
    char busca[TAM_NOME];
    int i, encontrou = 0;

    printf("\n=== Consultar contato ===\n");
    ler_texto("Digite o nome ou parte do nome: ", busca, TAM_NOME);

    for (i = 0; i < qtd; i++) {
        if (strstr(contatos[i].nome, busca) != NULL) {
            mostrar_contato(contatos[i], i + 1);
            encontrou = 1;
        }
    }

    if (!encontrou) printf("\nContato nao encontrado.\n");
}

void excluir_contato(Contato contatos[], int *qtd) {
    char busca[TAM_NOME];
    int i, j;

    printf("\n=== Excluir contato ===\n");
    ler_texto("Digite o nome exato do contato: ", busca, TAM_NOME);

    for (i = 0; i < *qtd; i++) {
        if (strcmp(contatos[i].nome, busca) == 0) {
            for (j = i; j < *qtd - 1; j++) contatos[j] = contatos[j + 1];
            (*qtd)--;
            salvar_contatos(contatos, *qtd);
            printf("\nContato excluido com sucesso.\n");
            return;
        }
    }

    printf("\nContato nao encontrado.\n");
}

void mostrar_menu() {
    printf("\n==============================\n");
    printf("      AGENDA DE CONTATOS\n");
    printf("==============================\n");
    printf("1 - Incluir contato\n2 - Listar contatos\n");
    printf("3 - Consultar contato pelo nome\n4 - Excluir contato\n5 - Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    Contato contatos[MAX_CONTATOS];
    int qtd = carregar_contatos(contatos), opcao = 0;
    char linha[20];

    while (opcao != 5) {
        mostrar_menu();
        fgets(linha, 20, stdin);
        sscanf(linha, "%i", &opcao);

        switch (opcao) {
            case 1: incluir_contato(contatos, &qtd); pausar(); break;
            case 2: listar_contatos(contatos, qtd); pausar(); break;
            case 3: consultar_contato(contatos, qtd); pausar(); break;
            case 4: excluir_contato(contatos, &qtd); pausar(); break;
            case 5: printf("\nPrograma encerrado.\n"); break;
            default: printf("\nOpcao invalida.\n"); pausar();
        }
    }

    return 0;
}
