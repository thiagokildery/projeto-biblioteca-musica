#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct no {
    char *valor;         // Nome do disco
    float nota;          // Nota de avaliação
    struct no *proximo;
} No;

void inserir_disco(No **fila, char *disco, float nota) {
    No *aux, *novo = malloc(sizeof(No));
    if (novo) {
        novo->valor = malloc(strlen(disco) + 1);
        if (novo->valor) {
            strcpy(novo->valor, disco);
        }
        novo->nota = nota;  // Armazena a nota de avaliação
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

    // Caso a lista esteja vazia
    if (*fila == NULL) {
        printf("\nLista de discos vazia!\n");
        return NULL;
    }

    // Se o disco a ser removido for o primeiro
    if (strcmp(aux->valor, disco) == 0) {
        remover = *fila;
        *fila = aux->proximo;
    } else {
        // Percorre a lista para encontrar o disco
        while (aux->proximo != NULL && strcmp(aux->proximo->valor, disco) != 0) {
            aux = aux->proximo;
        }

        // Se encontrar o disco
        if (aux->proximo != NULL) {
            remover = aux->proximo;
            aux->proximo = aux->proximo->proximo;
        }
    }

    // Caso o disco não tenha sido encontrado
    if (remover) {
        printf("\nRemovido: %s | Nota: %.2f\n", remover->valor, remover->nota);
        free(remover->valor); // Libera a memória do nome do disco
        free(remover);        // Libera o nó
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

// Função para exibir o menu
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

// Função para obter uma nota válida (entre 0.0 e 5.0)
float obter_nota() {
    float nota;
    do {
        printf("Digite a nota de avaliação para o disco (0.0 a 5.0): ");
        scanf("%f", &nota);
        getchar(); // Limpa o buffer do teclado

        if (nota < 0.0 || nota > 5.0) {
            printf("Nota inválida! A nota deve estar entre 0.0 e 5.0.\n");
        }
    } while (nota < 0.0 || nota > 5.0);
    return nota;
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");  // Configuração do locale para o português
    No *fila = NULL; // Inicializa a fila
    No *r = NULL;    // Para armazenar o nó removido
    char valor[100]; // Buffer para armazenar o nome do disco
    int opcao;

    do {
        mostrar_menu(); // Exibe o menu
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
        case 1: {
            printf("Digite o nome do disco: ");
            fgets(valor, sizeof(valor), stdin);
            valor[strcspn(valor, "\n")] = '\0';

            float nota = obter_nota();  // Chama a função que valida a nota
            inserir_disco(&fila, valor, nota);
            break;
        }
        case 2: {
            char disco_remover[100];
            printf("Digite o nome do disco a ser removido: ");
            fgets(disco_remover, sizeof(disco_remover), stdin);
            disco_remover[strcspn(disco_remover, "\n")] = '\0'; // Remove o \n

            r = remover_disco(&fila, disco_remover);
            if (r) {
                free(r->valor); // Libera a memória do nome do disco
                free(r);        // Libera o nó
            }
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

    // Libera a memória de todos os nós restantes
    while (fila) {
        r = remover_disco(&fila, fila->valor);
        free(r->valor);
        free(r);
    }

    return 0;
}
