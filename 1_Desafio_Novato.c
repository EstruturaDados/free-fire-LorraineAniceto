#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10  // Capacidade máxima da mochila

// =====================
// Estrutura Item
// =====================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// =====================
// Protótipos das funções
// =====================
void inserirItem(Item mochila[], int *contador);
void removerItem(Item mochila[], int *contador);
void listarItens(Item mochila[], int contador);
void buscarItem(Item mochila[], int contador);

// =====================
// Função principal
// =====================
int main() {
    Item mochila[MAX_ITENS];
    int contador = 0; // Contador de itens na mochila
    int opcao;

    do {
        printf("\n=== Sistema de Inventário ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch(opcao) {
            case 1:
                inserirItem(mochila, &contador);
                break;
            case 2:
                removerItem(mochila, &contador);
                break;
            case 3:
                listarItens(mochila, contador);
                break;
            case 4:
                buscarItem(mochila, contador);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);

    return 0;
}

// =====================
// Função para inserir item
// =====================
void inserirItem(Item mochila[], int *contador) {
    if (*contador >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novoItem;
    printf("Digite o nome do item: ");
    fgets(novoItem.nome, sizeof(novoItem.nome), stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = '\0'; // Remove o \n do final

    printf("Digite o tipo do item (arma, munição, cura, ferramenta): ");
    fgets(novoItem.tipo, sizeof(novoItem.tipo), stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    getchar(); // Limpar buffer

    mochila[*contador] = novoItem;
    (*contador)++;

    printf("Item inserido com sucesso!\n");
    listarItens(mochila, *contador);
}

// =====================
// Função para remover item
// =====================
void removerItem(Item mochila[], int *contador) {
    if (*contador == 0) {
        printf("Mochila vazia! Nada para remover.\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < *contador; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = 1;
            // Move todos os itens à frente uma posição para trás
            for (int j = i; j < *contador - 1; j++) {
                mochila[j] = mochila[j+1];
            }
            (*contador)--;
            printf("Item removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Item não encontrado na mochila.\n");
    }

    listarItens(mochila, *contador);
}

// =====================
// Função para listar itens
// =====================
void listarItens(Item mochila[], int contador) {
    if (contador == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("\nItens na mochila:\n");
    for (int i = 0; i < contador; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n", i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// =====================
// Função para buscar item (busca sequencial)
// =====================
void buscarItem(Item mochila[], int contador) {
    if (contador == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do item a buscar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < contador; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("Item encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("Item não encontrado.\n");
}

