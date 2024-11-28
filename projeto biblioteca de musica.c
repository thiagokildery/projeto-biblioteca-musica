#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura para armazenar informações dos discos
typedef struct no {
    char *valor;        // Nome do disco
    float nota;         // Nota de avaliação
    struct no *proximo; // Ponteiro para o próximo nó
} No;

// Função para inserir um disco na fila
void inserir_disco(No **fila, char *disco, float nota) {
    No *novo = malloc(sizeof(No));
    if (!novo) {
        printf("\nErro ao alocar memória para o disco!\n");
        return;
    }

    // Aloca espaço para o nome do disco e inicializa os valores
    novo->valor = malloc(strlen(disco) + 1);
    if (novo->valor) {
        strcpy(novo->valor, disco);
    }
    novo->nota = nota;
    novo->proximo = NULL;

    // Adiciona o nó ao final da lista
    if (*fila == NULL) {
        *fila = novo;
    } else {
        No *aux = *fila;
        while (aux->proximo) {
            aux = aux->proximo;
        }
        aux->proximo = novo;
    }
}

// Função para carregar dados do arquivo
void carregar_dados(No **fila, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        return; // Arquivo não encontrado, apenas retorna
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char disco[100];
        float nota;

        // Extrai dados formatados da linha
        if (sscanf(linha, "%[^|]|%f", disco, &nota) == 2) {
            inserir_disco(fila, disco, nota);
        }
    }
    fclose(arquivo); // Fecha o arquivo
}

// Função para salvar os dados no arquivo
void salvar_dados(No *fila, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar!\n");
        return;
    }

    // Escreve cada nó no arquivo
    while (fila) {
        fprintf(arquivo, "%s|%.2f\n", fila->valor, fila->nota);
        fila = fila->proximo;
    }
    fclose(arquivo);
}

// Função para remover um disco da lista
No* remover_disco(No **fila, const char *disco) {
    if (*fila == NULL) { // Caso a lista esteja vazia
        printf("\nLista de discos vazia!\n");
        return NULL;
    }

    No *aux = *fila, *remover = NULL;

    // Se o disco a ser removido for o primeiro da lista
    if (strcmp(aux->valor, disco) == 0) {
        remover = aux;
        *fila = aux->proximo; // Atualiza o início da lista
    } else {
        // Percorre a lista para encontrar o disco
        while (aux->proximo != NULL && strcmp(aux->proximo->valor, disco) != 0) {
            aux = aux->proximo;
        }

        // Verifica se encontrou o disco
        if (aux->proximo != NULL) {
            remover = aux->proximo;
            aux->proximo = remover->proximo; // Remove o nó
        }
    }

    // Caso o disco tenha sido encontrado e removido
    if (remover) {
        printf("\nRemovido: %s | Nota: %.2f\n", remover->valor, remover->nota);
        free(remover->valor); // Libera o nome do disco
        free(remover);        // Libera o nó
    } else {
        printf("\nDisco não encontrado!\n");
    }

    return remover; // Retorna o nó removido ou NULL
}

// Função para exibir a lista de discos
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

        if (nota < 0.0 || nota > 5.0) {
            printf("Nota inválida! A nota deve estar entre 0.0 e 5.0.\n");
        }
    } while (nota < 0.0 || nota > 5.0);
    return nota;
}

// Função principal
int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    No *fila = NULL; // Inicializa a fila
    int opcao;
    char valor[100];
    const char *nome_arquivo = "discos.txt";

    // Carrega dados do arquivo
    carregar_dados(&fila, nome_arquivo);

    do {
        mostrar_menu(); // Exibe o menu
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
        case 1:
            printf("Digite o nome do disco: ");
            fgets(valor, sizeof(valor), stdin);
            valor[strcspn(valor, "\n")] = '\0'; // Remove o \n do final

            float nota = obter_nota();
            inserir_disco(&fila, valor, nota);
            break;

        case 2:
            printf("Digite o nome do disco a ser removido: ");
            fgets(valor, sizeof(valor), stdin);
            valor[strcspn(valor, "\n")] = '\0';

            remover_disco(&fila, valor);
            break;

        case 3:
            mostrar_lista(fila);
            break;

        default:
            if (opcao != 0) {
                printf("Opção inválida!\n");
            }
        }
    } while (opcao != 0);

    // Salva os dados e libera a memória
    salvar_dados(fila, nome_arquivo);

    // Libera a memória restante
    while (fila) {
        No *remover = fila;
        fila = fila->proximo;
        free(remover->valor);
        free(remover);
    }

    return 0;
}
