#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// =====================
// Estruturas
// =====================

// Território
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Componente da torre
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// =====================
// Funções Torre de Fuga
// =====================

int comparacoes = 0;

void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-1-i; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j+1].nome) > 0) {
                Componente tmp = v[j];
                v[j] = v[j+1];
                v[j+1] = tmp;
            }
        }
}

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

int buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int ini = 0, fim = n-1;
    comparacoes = 0;
    while (ini <= fim) {
        int meio = (ini+fim)/2;
        comparacoes++;
        int cmp = strcmp(chave, v[meio].nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) fim = meio - 1;
        else ini = meio + 1;
    }
    return -1;
}

void mostrarComponentes(Componente v[], int n) {
    printf("\n--- Componentes ---\n");
    for (int i = 0; i < n; i++)
        printf("%d) Nome: %s | Tipo: %s | Prioridade: %d\n",
               i+1, v[i].nome, v[i].tipo, v[i].prioridade);
}

void medirTempo(void (*algoritmo)(Componente[], int), Componente v[], int n) {
    clock_t inicio = clock();
    algoritmo(v, n);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoes, tempo);
}

// =====================
// Funções Território
// =====================

void cadastrarTerritorios(struct Territorio t[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);
        printf("Nome: "); scanf(" %29s", t[i].nome);
        printf("Cor do exército: "); scanf(" %9s", t[i].cor);
        printf("Quantidade de tropas: "); scanf("%d", &t[i].tropas);
    }
}

void mostrarTerritorios(struct Territorio t[], int n) {
    printf("\n===== Territórios Cadastrados =====\n");
    for (int i = 0; i < n; i++)
        printf("\nTerritório %d\nNome: %s\nCor do exército: %s\nTropas: %d\n",
               i+1, t[i].nome, t[i].cor, t[i].tropas);
}

// =====================
// Main
// =====================

int main() {
    struct Territorio territorios[5];
    Componente torre[MAX_COMPONENTES];
    int qtdComponentes = 0;
    int opcao;

    do {
        printf("\n===== Menu Principal =====\n");
        printf("1 - Gerenciar Territorios\n");
        printf("2 - Gerenciar Torre de Fuga\n");
        printf("0 - Sair\nOpcao: ");
        scanf("%d", &opcao); getchar();

        if (opcao == 1) {
            cadastrarTerritorios(territorios, 5);
            mostrarTerritorios(territorios, 5);
        }
        else if (opcao == 2) {
            int opTorre;
            do {
                printf("\n--- Torre de Fuga ---\n");
                printf("1 - Cadastrar componente\n");
                printf("2 - Mostrar componentes\n");
                printf("3 - Bubble Sort (nome)\n");
                printf("4 - Insertion Sort (tipo)\n");
                printf("5 - Selection Sort (prioridade)\n");
                printf("6 - Busca Binaria (por nome)\n");
                printf("0 - Voltar\nOpcao: ");
                scanf("%d", &opTorre); getchar();

                if (opTorre == 1) {
                    if (qtdComponentes >= MAX_COMPONENTES) {
                        printf("Limite atingido!\n");
                        continue;
                    }
                    printf("Nome: "); fgets(torre[qtdComponentes].nome, 30, stdin);
                    torre[qtdComponentes].nome[strcspn(torre[qtdComponentes].nome, "\n")] = 0;

                    printf("Tipo: "); fgets(torre[qtdComponentes].tipo, 20, stdin);
                    torre[qtdComponentes].tipo[strcspn(torre[qtdComponentes].tipo, "\n")] = 0;

                    printf("Prioridade (1-10): "); scanf("%d", &torre[qtdComponentes].prioridade); getchar();

                    qtdComponentes++;
                }
                else if (opTorre == 2) mostrarComponentes(torre, qtdComponentes);
                else if (opTorre == 3) medirTempo(bubbleSortNome, torre, qtdComponentes);
                else if (opTorre == 4) medirTempo(insertionSortTipo, torre, qtdComponentes);
                else if (opTorre == 5) medirTempo(selectionSortPrioridade, torre, qtdComponentes);
                else if (opTorre == 6) {
                    char chave[30];
                    printf("Digite o nome do componente-chave: ");
                    fgets(chave, 30, stdin);
                    chave[strcspn(chave, "\n")] = 0;

                    int idx = buscaBinariaPorNome(torre, qtdComponentes, chave);
                    if (idx >= 0) printf("Encontrado na posicao %d (%d comparacoes).\n", idx, comparacoes);
                    else printf("Nao encontrado (%d comparacoes).\n", comparacoes);
                }
            } while (opTorre != 0);
        }

    } while (opcao != 0);

    return 0;
}


