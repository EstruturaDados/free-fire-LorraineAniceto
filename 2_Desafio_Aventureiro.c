#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

Item mochilaVetor[MAX];
int qtdVetor = 0;
int comparacoesSeq = 0, comparacoesBin = 0;
// ======== Funções Vetor ========
void inserirItemVetor() {
    if (qtdVetor >= MAX) { printf("Mochila cheia!\n"); return; }
    Item it;
    printf("Nome: "); scanf(" %29[^\n]", it.nome);
    printf("Tipo: "); scanf(" %19[^\n]", it.tipo);
    printf("Quantidade: "); scanf("%d", &it.quantidade);
    mochilaVetor[qtdVetor++] = it;
}

void listarItensVetor() {
    for (int i = 0; i < qtdVetor; i++)
        printf("%s | %s | %d\n", mochilaVetor[i].nome,
                                 mochilaVetor[i].tipo,
                                 mochilaVetor[i].quantidade);
}

int buscarSequencialVetor(char nome[]) {
    comparacoesSeq = 0;
    for (int i = 0; i < qtdVetor; i++) {
        comparacoesSeq++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) return i;
    }
    return -1;
}

void ordenarVetor() { // Bubble Sort
    Item tmp;
    for (int i = 0; i < qtdVetor-1; i++)
        for (int j = 0; j < qtdVetor-1-i; j++)
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j+1].nome) > 0) {
                tmp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j+1];
                mochilaVetor[j+1] = tmp;
            }
}

int buscarBinariaVetor(char nome[]) {
    int ini=0, fim=qtdVetor-1, meio;
    comparacoesBin = 0;
    while (ini <= fim) {
        meio = (ini+fim)/2;
        comparacoesBin++;
        int cmp = strcmp(nome, mochilaVetor[meio].nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) fim = meio - 1;
        else ini = meio + 1;
    }
    return -1;
}

// ======== Funções Lista (exemplo de inserção) ========
void inserirItemLista(No **inicio) {
    No* novo = (No*)malloc(sizeof(No));
    printf("Nome: "); scanf(" %29[^\n]", novo->dados.nome);
    printf("Tipo: "); scanf(" %19[^\n]", novo->dados.tipo);
    printf("Quantidade: "); scanf("%d", &novo->dados.quantidade);
    novo->proximo = *inicio;
    *inicio = novo;
}

// ... outras funções para lista: remover, buscar, listar ...

int main() {
    int op;
    No* lista = NULL;

    do {
        printf("\n1 - Vetor\n2 - Lista\n0 - Sair\nEscolha: ");
        scanf("%d", &op);

        if (op == 1) {
            int opv;
            do {
                printf("\n--- Mochila Vetor ---\n");
                printf("1-Inserir 2-Listar 3-Busca Seq 4-Ordenar 5-Busca Bin 0-Voltar\n");
                scanf("%d", &opv);
                if (opv == 1) inserirItemVetor();
                else if (opv == 2) listarItensVetor();
                else if (opv == 3) {
                    char nome[30]; printf("Nome: "); scanf(" %29[^\n]", nome);
                    int idx = buscarSequencialVetor(nome);
                    if (idx >= 0) printf("Encontrado em %d comparacoes.\n", comparacoesSeq);
                    else printf("Nao encontrado (%d comparacoes).\n", comparacoesSeq);
                }
                else if (opv == 4) ordenarVetor();
                else if (opv == 5) {
                    char nome[30]; printf("Nome: "); scanf(" %29[^\n]", nome);
                    int idx = buscarBinariaVetor(nome);
                    if (idx >= 0) printf("Encontrado em %d comparacoes.\n", comparacoesBin);
                    else printf("Nao encontrado (%d comparacoes).\n", comparacoesBin);
                }
            } while (opv != 0);
        }

        // Caso op == 2 => chamar funções da lista encadeada

    } while (op != 0);

    return 0;
}
