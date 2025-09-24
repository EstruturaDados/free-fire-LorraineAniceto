#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// =====================
// Estrutura Componente
// =====================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Contador global de comparações
int comparacoes = 0;

// =====================
// Funções de Ordenação
// =====================

// Bubble Sort por nome
void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j+1].nome) > 0) {
                Componente tmp = v[j];
                v[j] = v[j+1];
                v[j+1] = tmp;
            }
        }
    }
}

// Insertion Sort por tipo
void insertionSortTipo(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente key = v[i];
        int j = i-1;
        while (j >= 0 && (comparacoes++, strcmp(v[j].tipo, key.tipo) > 0)) {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = key;
    }
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[min].prioridade)
                min = j;
        }
        if (min != i) {
            Componente tmp = v[i];
            v[i] = v[min];
            v[min] = tmp;
        }
    }
}

// =====================
// Busca Binária por nome
// =====================
int buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int ini = 0, fim = n-1;
    comparacoes = 0;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comparacoes++;
        int cmp = strcmp(chave, v[meio].nome);

        if (cmp == 0) return meio;
        else if (cmp < 0) fim = meio - 1;
        else ini = meio + 1;
    }
    return -1;
}

// =====================
// Mostrar Componentes
// =====================
void mostrarComponentes(Componente v[], int n) {
    printf("\n--- Componentes ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d) Nome: %s | Tipo: %s | Prioridade: %d\n",
               i+1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

// =====================
// Medir tempo de execução
// =====================
void medirTempo(void (*algoritmo)(Componente[], int), Componente v[], int n) {
    clock_t inicio = clock();
    algoritmo(v, n);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoes, tempo);
}

// =====================
// Programa Principal
// =====================
int main() {
    Componente torre[MAX_COMPONENTES];
    int qtd = 0;
    int opcao;
    char buffer[30];

    do {
        printf("\n===== Torre de Fuga =====\n");
        printf("1 - Cadastrar componente\n");
        printf("2 - Mostrar componentes\n");
        printf("3 - Bubble Sort (nome)\n");
        printf("4 - Insertion Sort (tipo)\n");
        printf("5 - Selection Sort (prioridade)\n");
        printf("6 - Busca Binaria (por nome)\n");
        printf("0 - Sair\nOpcao: ");
        scanf("%d", &opcao); getchar();

        if (opcao == 1) {
            if (qtd >= MAX_COMPONENTES) {
                printf("Limite atingido!\n");
                continue;
            }
            printf("Nome: "); fgets(torre[qtd].nome, 30, stdin);
            torre[qtd].nome[strcspn(torre[qtd].nome, "\n")] = 0;

            printf("Tipo: "); fgets(torre[qtd].tipo, 20, stdin);
            torre[qtd].tipo[strcspn(torre[qtd].tipo, "\n")] = 0;

            printf("Prioridade (1-10): "); scanf("%d", &torre[qtd].prioridade); getchar();

            qtd++;
        }
        else if (opcao == 2) mostrarComponentes(torre, qtd);
        else if (opcao == 3) medirTempo(bubbleSortNome, torre, qtd);
        else if (opcao == 4) medirTempo(insertionSortTipo, torre, qtd);
        else if (opcao == 5) medirTempo(selectionSortPrioridade, torre, qtd);
        else if (opcao == 6) {
            printf("Digite o nome do componente-chave: ");
            fgets(buffer, 30, stdin);
            buffer[strcspn(buffer, "\n")] = 0;

            int idx = buscaBinariaPorNome(torre, qtd, buffer);
            if (idx >= 0) printf("Encontrado na posicao %d (%d comparacoes).\n", idx, comparacoes);
            else printf("Nao encontrado (%d comparacoes).\n", comparacoes);
        }

    } while (opcao != 0);

    return 0;
}
