#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct no {
    char *valor;
    float nota;
    struct no *proximo;
} No;

void inserir_disco(No **fila, char *disco, float nota); // Protótipo da função

void carregar_dados(No **fila, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char disco[100];
        float nota;
        if (sscanf(linha, "%[^|]|%f", disco, &nota) == 2) {
            inserir_disco(fila, disco, nota);
        }
    }
    fclose(arquivo);
}

void salvar_dados(No *fila, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    while (fila) {
        fprintf(arquivo, "%s|%.2f\n", fila->valor, fila->nota);
        fila = fila->proximo;
    }
    fclose(arquivo);
}

void inserir_disco(No **fila, char *disco, float nota) {
    No *aux, *novo = malloc(sizeof(No));
    if (novo) {
        novo->valor = malloc(strlen(disco) + 1);
        if (novo->valor) {
            strcpy(novo->valor, disco);
        }
        novo->nota = nota;
        novo->proximo = NULL;

        if (*fila == NULL) {
            *fila = novo;
        } else {
            aux = *fila;
            while (aux->proximo) {
                aux = aux->proximo;
            }
            aux->proximo = novo;
        }
    } else {
        printf("\nErro ao alocar memória para o disco!\n");
    }
}

No* remover_disco(No **fila, const char *disco) {
    No *aux = *fila, *remover = NULL;

    if (*fila == NULL) {
        printf("\nLista de discos vazia!\n");
        return NULL;
    }

    if (strcmp(aux->valor, disco) == 0) {
        remover = *fila;
        *fila = aux->proximo;
    } else {
        while (aux->proximo != NULL && strcmp(aux->proximo->valor, disco) != 0) {
            aux = aux->proximo;
        }

        if (aux->proximo != NULL) {
            remover = aux->proximo;
            aux->proximo = aux->proximo->proximo;
        }
    }

    if (remover) {
        printf("\nRemovido: %s | Nota: %.2f\n", remover->valor, remover->nota);
        free(remover->valor);
        free(remover);
    } else {
        printf("\nDisco não encontrado!\n");
    }

    return remover;
}

void mostrar_lista(No *fila) {
    printf("\nLista de discos:\n");
    while (fila) {
        printf("Disco: %s | Nota: %.2f\n", fila->valor, fila->nota);
        fila = fila->proximo;
    }
    printf("\n");
}

void mostrar_menu() {
    printf("====================================\n");
    printf("\tSistema de Discos\n");
    printf("====================================\n");
    printf("1 - Inserir disco\n");
    printf("2 - Remover disco\n");
    printf("3 - Mostrar lista\n");
    printf("0 - Sair\n");
    printf("====================================\n");
    printf("Escolha uma opção: ");
}

float obter_nota() {
    float nota;
    do {
        printf("Digite a nota de avaliação para o disco (0.0 a 5.0): ");
        scanf("%f", &nota);
        getchar();

        if (nota < 0.0 || nota > 5.0) {
            printf("Nota inválida! A nota deve estar entre 0.0 e 5.0.\n");
        }
    } while (nota < 0.0 || nota > 5.0);
    return nota;
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    No *fila = NULL;
    char valor[100];
    int opcao;
    const char *nome_arquivo = "discos.txt";

    carregar_dados(&fila, nome_arquivo);

    do {
        mostrar_menu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
        case 1: {
            printf("Digite o nome do disco: ");
            fgets(valor, sizeof(valor), stdin);
            valor[strcspn(valor, "\n")] = '\0';

            float nota = obter_nota();
            inserir_disco(&fila, valor, nota);
            break;
        }
        case 2: {
            char disco_remover[100];
            printf("Digite o nome do disco a ser removido: ");
            fgets(disco_remover, sizeof(disco_remover), stdin);
            disco_remover[strcspn(disco_remover, "\n")] = '\0';

            remover_disco(&fila, disco_remover);
            break;
        }
        case 3:
            mostrar_lista(fila);
            break;
        default:
            if (opcao != 0) {
                printf("Opção inválida!\n");
            }
        }
    } while (opcao != 0);

    salvar_dados(fila, nome_arquivo);

    while (fila) {
        remover_disco(&fila, fila->valor);
    }

    return 0;
}
