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

// =====================
// Protótipos de funções
// =====================
void bubbleSortNome(Componente comps[], int n, int *comparacoes);
void insertionSortTipo(Componente comps[], int n, int *comparacoes);
void selectionSortPrioridade(Componente comps[], int n, int *comparacoes);
int buscaBinariaPorNome(Componente comps[], int n, char chave[], int *comparacoes);
void mostrarComponentes(Componente comps[], int n);

// =====================
// Função principal
// =====================
int main() {
    Componente comps[MAX_COMPONENTES];
    int n = 0;
    char opcao[10];
    char chave[30];
    int comparacoes = 0;
    clock_t inicio, fim;
    double tempo;

    printf("Quantos componentes deseja cadastrar? (max 20): ");
    scanf("%d", &n);
    getchar(); // Limpar buffer

    if(n > MAX_COMPONENTES) n = MAX_COMPONENTES;

    // Entrada de dados
    for(int i = 0; i < n; i++) {
        printf("\nComponente %d:\n", i+1);
        printf("Nome: ");
        fgets(comps[i].nome, sizeof(comps[i].nome), stdin);
        comps[i].nome[strcspn(comps[i].nome, "\n")] = '\0';

        printf("Tipo: ");
        fgets(comps[i].tipo, sizeof(comps[i].tipo), stdin);
        comps[i].tipo[strcspn(comps[i].tipo, "\n")] = '\0';

        printf("Prioridade (1-10): ");
        scanf("%d", &comps[i].prioridade);
        getchar();
    }

    do {
        printf("\n=== Menu de Ordenacao e Busca ===\n");
        printf("1. Ordenar por nome (Bubble Sort)\n");
        printf("2. Ordenar por tipo (Insertion Sort)\n");
        printf("3. Ordenar por prioridade (Selection Sort)\n");
        printf("4. Buscar componente-chave por nome (Busca Binaria)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        fgets(opcao, sizeof(opcao), stdin);

        switch(opcao[0]) {
            case '1':
                comparacoes = 0;
                inicio = clock();
                bubbleSortNome(comps, n, &comparacoes);
                fim = clock();
                tempo = ((double)(fim - inicio))/CLOCKS_PER_SEC;
                printf("\nComponentes ordenados por nome:\n");
                mostrarComponentes(comps, n);
                printf("Comparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                break;

            case '2':
                comparacoes = 0;
                inicio = clock();
                insertionSortTipo(comps, n, &comparacoes);
                fim = clock();
                tempo = ((double)(fim - inicio))/CLOCKS_PER_SEC;
                printf("\nComponentes ordenados por tipo:\n");
                mostrarComponentes(comps, n);
                printf("Comparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                break;

            case '3':
                comparacoes = 0;
                inicio = clock();
                selectionSortPrioridade(comps, n, &comparacoes);
                fim = clock();
                tempo = ((double)(fim - inicio))/CLOCKS_PER_SEC;
                printf("\nComponentes ordenados por prioridade:\n");
                mostrarComponentes(comps, n);
                printf("Comparacoes: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                break;

            case '4':
                printf("Digite o nome do componente-chave: ");
                fgets(chave, sizeof(chave), stdin);
                chave[strcspn(chave, "\n")] = '\0';
                comparacoes = 0;
                int pos = buscaBinariaPorNome(comps, n, chave, &comparacoes);
                if(pos != -1) {
                    printf("Componente encontrado!\n");
                    printf("Nome: %s | Tipo: %s | Prioridade: %d\n", comps[pos].nome, comps[pos].tipo, comps[pos].prioridade);
                } else {
                    printf("Componente nao encontrado!\n");
                }
                printf("Comparacoes realizadas: %d\n", comparacoes);
                break;

            case '0':
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao[0] != '0');

    return 0;
}

// =====================
// Funções de ordenacao
// =====================

// Bubble Sort por nome
void bubbleSortNome(Componente comps[], int n, int *comparacoes) {
    Componente temp;
    for(int i=0;i<n-1;i++) {
        for(int j=0;j<n-i-1;j++) {
            (*comparacoes)++;
            if(strcmp(comps[j].nome, comps[j+1].nome) > 0) {
                temp = comps[j];
                comps[j] = comps[j+1];
                comps[j+1] = temp;
            }
        }
    }
}

// Insertion Sort por tipo
void insertionSortTipo(Componente comps[], int n, int *comparacoes) {
    for(int i=1;i<n;i++) {
        Componente chave = comps[i];
        int j = i-1;
        while(j>=0 && ( (*comparacoes)++, strcmp(comps[j].tipo, chave.tipo) > 0 )) {
            comps[j+1] = comps[j];
            j--;
        }
        comps[j+1] = chave;
    }
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente comps[], int n, int *comparacoes) {
    for(int i=0;i<n-1;i++) {
        int min_idx = i;
        for(int j=i+1;j<n;j++) {
            (*comparacoes)++;
            if(comps[j].prioridade < comps[min_idx].prioridade) {
                min_idx = j;
            }
        }
        Componente temp = comps[i];
        comps[i] = comps[min_idx];
        comps[min_idx] = temp;
    }
}

// Busca binaria por nome (vetor deve estar ordenado por nome)
int buscaBinariaPorNome(Componente comps[], int n, char chave[], int *comparacoes) {
    int inicio = 0, fim = n-1;
    while(inicio <= fim) {
        int meio = (inicio + fim)/2;
        (*comparacoes)++;
        int cmp = strcmp(comps[meio].nome, chave);
        if(cmp == 0) return meio;
        else if(cmp < 0) inicio = meio+1;
        else fim = meio-1;
    }
    return -1;
}

// =====================
// Mostrar componentes
// =====================
void mostrarComponentes(Componente comps[], int n) {
    for(int i=0;i<n;i++) {
        printf("%d. Nome: %s | Tipo: %s | Prioridade: %d\n", i+1, comps[i].nome, comps[i].tipo, comps[i].prioridade);
    }
}
