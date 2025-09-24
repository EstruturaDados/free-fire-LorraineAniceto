#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// =====================
// Estrutura Item
// =====================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// =====================
// Estrutura Nó para lista encadeada
// =====================
typedef struct No {
    Item dados;
    struct No *proximo;
} No;

// =====================
// Protótipos - Vetor
// =====================
void inserirItemVetor(Item vetor[], int *contador);
void removerItemVetor(Item vetor[], int *contador);
void listarVetor(Item vetor[], int contador);
void ordenarVetor(Item vetor[], int contador);
int buscarSequencialVetor(Item vetor[], int contador, char nome[], int *comparacoes);
int buscarBinariaVetor(Item vetor[], int contador, char nome[], int *comparacoes);

// =====================
// Protótipos - Lista Encadeada
// =====================
void inserirItemLista(No **cabeca);
void removerItemLista(No **cabeca);
void listarLista(No *cabeca);
No* buscarSequencialLista(No *cabeca, char nome[], int *comparacoes);

// =====================
// Função principal
// =====================
int main() {
    Item mochilaVetor[MAX_ITENS];
    int contadorVetor = 0;

    No *lista = NULL; // Cabeça da lista encadeada

    int escolha, estrutura;

    do {
        printf("\n=== Sistema de Mochila ===\n");
        printf("Escolha a estrutura:\n1. Vetor\n2. Lista Encadeada\n0. Sair\nOpcao: ");
        scanf("%d", &estrutura);
        getchar(); // Limpar buffer

        if(estrutura == 0) break;

        do {
            printf("\nEscolha a operacao:\n");
            printf("1. Inserir item\n2. Remover item\n3. Listar itens\n4. Buscar item\n5. Ordenar vetor (apenas vetor)\n0. Voltar\nOpcao: ");
            scanf("%d", &escolha);
            getchar(); // Limpar buffer

            int comparacoes = 0;
            char nomeBusca[30];
            int pos;

            switch(escolha) {
                case 1:
                    if (estrutura == 1) inserirItemVetor(mochilaVetor, &contadorVetor);
                    else inserirItemLista(&lista);
                    break;
                case 2:
                    if (estrutura == 1) removerItemVetor(mochilaVetor, &contadorVetor);
                    else removerItemLista(&lista);
                    break;
                case 3:
                    if (estrutura == 1) listarVetor(mochilaVetor, contadorVetor);
                    else listarLista(lista);
                    break;
                case 4:
                    printf("Digite o nome do item a buscar: ");
                    fgets(nomeBusca, sizeof(nomeBusca), stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                    if (estrutura == 1) {
                        pos = buscarSequencialVetor(mochilaVetor, contadorVetor, nomeBusca, &comparacoes);
                        if(pos != -1) {
                            printf("Item encontrado: %s | %s | %d\n", mochilaVetor[pos].nome, mochilaVetor[pos].tipo, mochilaVetor[pos].quantidade);
                        } else {
                            printf("Item nao encontrado.\n");
                        }
                        printf("Comparacoes sequenciais: %d\n", comparacoes);

                        ordenarVetor(mochilaVetor, contadorVetor);
                        pos = buscarBinariaVetor(mochilaVetor, contadorVetor, nomeBusca, &comparacoes);
                        if(pos != -1) {
                            printf("Busca binaria encontrou: %s | %s | %d\n", mochilaVetor[pos].nome, mochilaVetor[pos].tipo, mochilaVetor[pos].quantidade);
                        } else {
                            printf("Busca binaria nao encontrou o item.\n");
                        }
                        printf("Comparacoes binaria: %d\n", comparacoes);
                    } else {
                        No *achado = buscarSequencialLista(lista, nomeBusca, &comparacoes);
                        if(achado != NULL) {
                            printf("Item encontrado: %s | %s | %d\n", achado->dados.nome, achado->dados.tipo, achado->dados.quantidade);
                        } else {
                            printf("Item nao encontrado.\n");
                        }
                        printf("Comparacoes sequenciais: %d\n", comparacoes);
                    }
                    break;
                case 5:
                    if (estrutura == 1) {
                        ordenarVetor(mochilaVetor, contadorVetor);
                        printf("Vetor ordenado por nome.\n");
                    } else {
                        printf("Ordenacao apenas para vetor.\n");
                    }
                    break;
                case 0:
                    break;
                default:
                    printf("Opcao invalida.\n");
            }

        } while(escolha != 0);

    } while(estrutura != 0);

    // Liberar memória da lista
    No *tmp;
    while(lista != NULL) {
        tmp = lista;
        lista = lista->proximo;
        free(tmp);
    }

    return 0;
}

// =====================
// Funções Vetor
// =====================
void inserirItemVetor(Item vetor[], int *contador) {
    if(*contador >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("Nome: "); fgets(novo.nome, sizeof(novo.nome), stdin); novo.nome[strcspn(novo.nome, "\n")] = '\0';
    printf("Tipo: "); fgets(novo.tipo, sizeof(novo.tipo), stdin); novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    printf("Quantidade: "); scanf("%d", &novo.quantidade); getchar();

    vetor[*contador] = novo;
    (*contador)++;
    printf("Item inserido no vetor.\n");
}

void removerItemVetor(Item vetor[], int *contador) {
    if(*contador == 0) { printf("Vetor vazio.\n"); return; }

    char nome[30];
    printf("Nome do item a remover: "); fgets(nome, sizeof(nome), stdin); nome[strcspn(nome, "\n")] = '\0';

    int encontrado = 0;
    for(int i=0; i<*contador; i++) {
        if(strcmp(vetor[i].nome, nome) == 0) {
            encontrado = 1;
            for(int j=i; j<*contador-1; j++) vetor[j] = vetor[j+1];
            (*contador)--;
            printf("Item removido do vetor.\n");
            break;
        }
    }
    if(!encontrado) printf("Item nao encontrado.\n");
}

void listarVetor(Item vetor[], int contador) {
    if(contador == 0) { printf("Vetor vazio.\n"); return; }
    printf("Itens no vetor:\n");
    for(int i=0;i<contador;i++) {
        printf("%d. %s | %s | %d\n", i+1, vetor[i].nome, vetor[i].tipo, vetor[i].quantidade);
    }
}

void ordenarVetor(Item vetor[], int contador) {
    Item tmp;
    for(int i=0;i<contador-1;i++) {
        for(int j=0;j<contador-i-1;j++) {
            if(strcmp(vetor[j].nome, vetor[j+1].nome) > 0) {
                tmp = vetor[j]; vetor[j] = vetor[j+1]; vetor[j+1] = tmp;
            }
        }
    }
}

int buscarSequencialVetor(Item vetor[], int contador, char nome[], int *comparacoes) {
    for(int i=0;i<contador;i++) {
        (*comparacoes)++;
        if(strcmp(vetor[i].nome, nome) == 0) return i;
    }
    return -1;
}

int buscarBinariaVetor(Item vetor[], int contador, char nome[], int *comparacoes) {
    int inicio=0, fim=contador-1;
    while(inicio<=fim) {
        (*comparacoes)++;
        int meio = (inicio+fim)/2;
        int cmp = strcmp(vetor[meio].nome, nome);
        if(cmp==0) return meio;
        else if(cmp<0) inicio = meio+1;
        else fim = meio-1;
    }
    return -1;
}

// =====================
// Funções Lista Encadeada
// =====================
void inserirItemLista(No **cabeca) {
    No *novo = (No*)malloc(sizeof(No));
    printf("Nome: "); fgets(novo->dados.nome, sizeof(novo->dados.nome), stdin); novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';
    printf("Tipo: "); fgets(novo->dados.tipo, sizeof(novo->dados.tipo), stdin); novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';
    printf("Quantidade: "); scanf("%d", &novo->dados.quantidade); getchar();
    novo->proximo = *cabeca;
    *cabeca = novo;
    printf("Item inserido na lista encadeada.\n");
}

void removerItemLista(No **cabeca) {
    if(*cabeca == NULL) { printf("Lista vazia.\n"); return; }

    char nome[30];
    printf("Nome do item a remover: "); fgets(nome, sizeof(nome), stdin); nome[strcspn(nome, "\n")] = '\0';

    No *atual = *cabeca, *anterior = NULL;
    while(atual != NULL) {
        if(strcmp(atual->dados.nome, nome) == 0) {
            if(anterior == NULL) *cabeca = atual->proximo;
            else anterior->proximo = atual->proximo;
            free(atual);
            printf("Item removido da lista.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item nao encontrado.\n");
}

void listarLista(No *cabeca) {
    if(cabeca == NULL) { printf("Lista vazia.\n"); return; }
    printf("Itens na lista:\n");
    No *atual = cabeca;
    int i=1;
    while(atual != NULL) {
        printf("%d. %s | %s | %d\n", i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

No* buscarSequencialLista(No *cabeca, char nome[], int *comparacoes) {
    No *atual = cabeca;
    while(atual != NULL) {
        (*comparacoes)++;
        if(strcmp(atual->dados.nome, nome) == 0) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

