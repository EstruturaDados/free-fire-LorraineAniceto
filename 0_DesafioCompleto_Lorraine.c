#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10
#define MAX_COMPONENTES 20

// =====================
// Estruturas
// =====================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No *proximo;
} No;

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// =====================
// Protótipos Funções - Mochila Vetor
// =====================
void inserirItemVetor(Item vetor[], int *contador);
void removerItemVetor(Item vetor[], int *contador);
void listarVetor(Item vetor[], int contador);
int buscarSequencialVetor(Item vetor[], int contador, char nome[], int *comparacoes);
void ordenarVetor(Item vetor[], int contador);
int buscarBinariaVetor(Item vetor[], int contador, char nome[], int *comparacoes);

// =====================
// Protótipos Funções - Lista Encadeada
// =====================
void inserirItemLista(No **cabeca);
void removerItemLista(No **cabeca);
void listarLista(No *cabeca);
No* buscarSequencialLista(No *cabeca, char nome[], int *comparacoes);

// =====================
// Protótipos Funções - Torre de Fuga
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
    int opcao, subopcao;
    do {
        printf("\n=== Sistema de Jogos - Modulos Unificados ===\n");
        printf("1. Mochila Inicial (Vetor)\n");
        printf("2. Comparacao de Estruturas (Vetor vs Lista Encadeada)\n");
        printf("3. Torre de Fuga (Componentes)\n");
        printf("0. Sair\n");
        printf("Escolha o modulo: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            // =====================
            // Módulo 1: Mochila Inicial
            // =====================
            case 1: {
                Item mochila[MAX_ITENS];
                int contador = 0, escolha;
                do {
                    printf("\n--- Mochila Inicial ---\n");
                    printf("1. Inserir item\n2. Remover item\n3. Listar itens\n4. Buscar item\n0. Voltar\nEscolha: ");
                    scanf("%d", &escolha);
                    getchar();
                    int comparacoes = 0;
                    char nomeBusca[30];
                    int pos;
                    switch(escolha) {
                        case 1: inserirItemVetor(mochila, &contador); break;
                        case 2: removerItemVetor(mochila, &contador); break;
                        case 3: listarVetor(mochila, contador); break;
                        case 4:
                            printf("Nome do item: "); fgets(nomeBusca, sizeof(nomeBusca), stdin);
                            nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                            pos = buscarSequencialVetor(mochila, contador, nomeBusca, &comparacoes);
                            if(pos != -1) printf("Item encontrado: %s | %s | %d\n", mochila[pos].nome, mochila[pos].tipo, mochila[pos].quantidade);
                            else printf("Item nao encontrado.\n");
                            printf("Comparacoes: %d\n", comparacoes);
                            break;
                        case 0: break;
                        default: printf("Opcao invalida!\n");
                    }
                } while(escolha != 0);
                break;
            }

            // =====================
            // Módulo 2: Comparação de Estruturas
            // =====================
            case 2: {
                Item vetor[MAX_ITENS];
                int contadorVetor = 0;
                No *lista = NULL;
                do {
                    printf("\n--- Comparacao Estruturas ---\n");
                    printf("Escolha a estrutura:\n1. Vetor\n2. Lista Encadeada\n0. Voltar\nOpcao: ");
                    scanf("%d", &subopcao);
                    getchar();
                    if(subopcao == 0) break;
                    int escolha2;
                    do {
                        printf("\n1. Inserir item\n2. Remover item\n3. Listar itens\n4. Buscar item\n5. Ordenar vetor (apenas vetor)\n0. Voltar\nEscolha: ");
                        scanf("%d", &escolha2);
                        getchar();
                        int comparacoes = 0;
                        char nomeBusca[30];
                        int pos;
                        switch(escolha2) {
                            case 1: if(subopcao==1) inserirItemVetor(vetor,&contadorVetor); else inserirItemLista(&lista); break;
                            case 2: if(subopcao==1) removerItemVetor(vetor,&contadorVetor); else removerItemLista(&lista); break;
                            case 3: if(subopcao==1) listarVetor(vetor,contadorVetor); else listarLista(lista); break;
                            case 4:
                                printf("Nome do item: "); fgets(nomeBusca,sizeof(nomeBusca),stdin);
                                nomeBusca[strcspn(nomeBusca,"\n")]='\0';
                                if(subopcao==1){
                                    pos = buscarSequencialVetor(vetor,contadorVetor,nomeBusca,&comparacoes);
                                    if(pos!=-1) printf("Item encontrado: %s | %s | %d\n", vetor[pos].nome, vetor[pos].tipo, vetor[pos].quantidade);
                                    else printf("Item nao encontrado.\n");
                                    printf("Comparacoes sequenciais: %d\n",comparacoes);
                                    ordenarVetor(vetor,contadorVetor);
                                    pos = buscarBinariaVetor(vetor,contadorVetor,nomeBusca,&comparacoes);
                                    if(pos!=-1) printf("Busca binaria encontrou: %s | %s | %d\n", vetor[pos].nome, vetor[pos].tipo, vetor[pos].quantidade);
                                    else printf("Busca binaria nao encontrou o item.\n");
                                    printf("Comparacoes binaria: %d\n", comparacoes);
                                } else {
                                    No* achado = buscarSequencialLista(lista,nomeBusca,&comparacoes);
                                    if(achado!=NULL) printf("Item encontrado: %s | %s | %d\n", achado->dados.nome, achado->dados.tipo, achado->dados.quantidade);
                                    else printf("Item nao encontrado.\n");
                                    printf("Comparacoes sequenciais: %d\n", comparacoes);
                                }
                                break;
                            case 5: if(subopcao==1){ordenarVetor(vetor,contadorVetor); printf("Vetor ordenado.\n");} else printf("Ordenacao apenas para vetor.\n"); break;
                            case 0: break;
                            default: printf("Opcao invalida!\n");
                        }
                    } while(escolha2!=0);
                } while(subopcao!=0);
                // Liberar memória da lista
                No *tmp;
                while(lista!=NULL){ tmp=lista; lista=lista->proximo; free(tmp);}
                break;
            }

            // =====================
            // Módulo 3: Torre de Fuga
            // =====================
            case 3: {
                Componente comps[MAX_COMPONENTES];
                int n;
                printf("Quantos componentes (max 20)? "); scanf("%d",&n); getchar();
                if(n>MAX_COMPONENTES) n=MAX_COMPONENTES;
                for(int i=0;i<n;i++){
                    printf("\nComponente %d:\n", i+1);
                    printf("Nome: "); fgets(comps[i].nome,sizeof(comps[i].nome),stdin); comps[i].nome[strcspn(comps[i].nome,"\n")]=0;
                    printf("Tipo: "); fgets(comps[i].tipo,sizeof(comps[i].tipo),stdin); comps[i].tipo[strcspn(comps[i].tipo,"\n")]=0;
                    printf("Prioridade: "); scanf("%d",&comps[i].prioridade); getchar();
                }
                do{
                    printf("\n--- Torre de Fuga ---\n");
                    printf("1. Ordenar por nome (Bubble)\n2. Ordenar por tipo (Insertion)\n3. Ordenar por prioridade (Selection)\n4. Buscar componente-chave (Binaria)\n0. Voltar\nEscolha: ");
                    fgets(opcao,sizeof(opcao),stdin);
                    int comparacoes=0;
                    clock_t inicio,fim; double tempo;
                    switch(opcao[0]){
                        case '1':
                            inicio=clock();
                            bubbleSortNome(comps,n,&comparacoes);
                            fim=clock();
                            tempo=((double)(fim-inicio))/CLOCKS_PER_SEC;
                            printf("\nComponentes por nome:\n"); mostrarComponentes(comps,n);
                            printf("Comparacoes: %d | Tempo: %.6f s\n",comparacoes,tempo);
                            break;
                        case '2':
                            inicio=clock(); insertionSortTipo(comps,n,&comparacoes); fim=clock();
                            tempo=((double)(fim-inicio))/CLOCKS_PER_SEC;
                            printf("\nComponentes por tipo:\n"); mostrarComponentes(comps,n);
                            printf("Comparacoes: %d | Tempo: %.6f s\n",comparacoes,tempo);
                            break;
                        case '3':
                            inicio=clock(); selectionSortPrioridade(comps,n,&comparacoes); fim=clock();
                            tempo=((double)(fim-inicio))/CLOCKS_PER_SEC;
                            printf("\nComponentes por prioridade:\n"); mostrarComponentes(comps,n);
                            printf("Comparacoes: %d | Tempo: %.6f s\n",comparacoes,tempo);
                            break;
                        case '4':
                            {
                                char chave[30]; printf("Nome do componente-chave: "); fgets(chave,sizeof(chave),stdin); chave[strcspn(chave,"\n")]=0;
                                comparacoes=0;
                                int pos = buscaBinariaPorNome(comps,n,chave,&comparacoes);
                                if(pos!=-1) printf("Componente encontrado: %s | %s | %d\n", comps[pos].nome,comps[pos].tipo,comps[pos].prioridade);
                                else printf("Componente nao encontrado.\n");
                                printf("Comparacoes: %d\n",comparacoes);
                            }
                            break;
                        case '0': break;
                        default: printf("Opcao invalida!\n");
                    }
                }while(opcao[0]!='0');
                break;
            }

            case 0: printf("Saindo do programa...\n"); break;
            default: printf("Opcao invalida!\n");
        }

    } while(opcao!=0);

    return 0;
}

// =====================
// Implementações Funções - Mochila Vetor
// =====================
void inserirItemVetor(Item vetor[], int *contador){
    if(*contador>=MAX_ITENS){ printf("Mochila cheia!\n"); return; }
    Item novo;
    printf("Nome: "); fgets(novo.nome,sizeof(novo.nome),stdin); novo.nome[strcspn(novo.nome,"\n")]=0;
    printf("Tipo: "); fgets(novo.tipo,sizeof(novo.tipo),stdin); novo.tipo[strcspn(novo.tipo,"\n")]=0;
    printf("Quantidade: "); scanf("%d",&novo.quantidade); getchar();
    vetor[*contador]=novo; (*contador)++;
    printf("Item inserido.\n");
}

void removerItemVetor(Item vetor[], int *contador){
    if(*contador==0){ printf("Mochila vazia.\n"); return; }
    char nome[30]; printf("Nome do item: "); fgets(nome,sizeof(nome),stdin); nome[strcspn(nome,"\n")]=0;
    int encontrado=0;
    for(int i=0;i<*contador;i++){
        if(strcmp(vetor[i].nome,nome)==0){
            encontrado=1;
            for(int j=i;j<*contador-1;j++) vetor[j]=vetor[j+1];
            (*contador)--;
            printf("Item removido.\n");
            break;
        }
    }
    if(!encontrado) printf("Item nao encontrado.\n");
}

void listarVetor(Item vetor[], int contador){
    if(contador==0){ printf("Mochila vazia.\n"); return; }
    for(int i=0;i<contador;i++) printf("%d. %s | %s | %d\n",i+1,vetor[i].nome,vetor[i].tipo,vetor[i].quantidade);
}

int buscarSequencialVetor(Item vetor[], int contador, char nome[], int *comparacoes){
    for(int i=0;i<contador;i++){ (*comparacoes)++; if(strcmp(vetor[i].nome,nome)==0) return i; }
    return -1;
}

void ordenarVetor(Item vetor[], int contador){
    for(int i=0;i<contador-1;i++){
        for(int j=0;j<contador-i-1;j++){
            if(strcmp(vetor[j].nome,vetor[j+1].nome)>0){
                Item tmp=vetor[j]; vetor[j]=vetor[j+1]; vetor[j+1]=tmp;
            }
        }
    }
}

int buscarBinariaVetor(Item vetor[], int contador, char nome[], int *comparacoes){
    int inicio=0,fim=contador-1;
    while(inicio<=fim){
        int meio=(inicio+fim)/2;
        (*comparacoes)++;
        int cmp=strcmp(vetor[meio].nome,nome);
        if(cmp==0) return meio; else if(cmp<0) inicio=meio+1; else fim=meio-1;
    }
    return -1;
}

// =====================
// Lista Encadeada
// =====================
void inserirItemLista(No **cabeca){
    No *novo=(No*)malloc(sizeof(No));
    printf("Nome: "); fgets(novo->dados.nome,sizeof(novo->dados.nome),stdin); novo->dados.nome[strcspn(novo->dados.nome,"\n")]=0;
    printf("Tipo: "); fgets(novo->dados.tipo,sizeof(novo->dados.tipo),stdin); novo->dados.tipo[strcspn(novo->dados.tipo,"\n")]=0;
    printf("Quantidade: "); scanf("%d",&novo->dados.quantidade); getchar();
    novo->proximo=*cabeca; *cabeca=novo;
    printf("Item inserido na lista.\n");
}

void removerItemLista(No **cabeca){
    if(*cabeca==NULL){ printf("Lista vazia.\n"); return; }
    char nome[30]; printf("Nome do item: "); fgets(nome,sizeof(nome),stdin); nome[strcspn(nome,"\n")]=0;
    No *atual=*cabeca,*anterior=NULL;
    while(atual!=NULL){
        if(strcmp(atual->dados.nome,nome)==0){
            if(anterior==NULL) *cabeca=atual->proximo; else anterior->proximo=atual->proximo;
            free(atual); printf("Item removido.\n"); return;
        }
        anterior=atual; atual=atual->proximo;
    }
    printf("Item nao encontrado.\n");
}

void listarLista(No *cabeca){
    if(cabeca==NULL){ printf("Lista vazia.\n"); return; }
    No *atual=cabeca; int i=1;
    while(atual!=NULL){ printf("%d. %s | %s | %d\n",i++,atual->dados.nome,atual->dados.tipo,atual->dados.quantidade); atual=atual->proximo; }
}

No* buscarSequencialLista(No *cabeca, char nome[], int *comparacoes){
    No *atual=cabeca;
    while(atual!=NULL){ (*comparacoes)++; if(strcmp(atual->dados.nome,nome)==0) return atual; atual=atual->proximo; }
    return NULL;
}

// =====================
// Torre de Fuga - Funções
// =====================
void bubbleSortNome(Componente comps[], int n, int *comparacoes){
    Componente temp;
    for(int i=0;i<n-1;i++) for(int j=0;j<n-i-1;j++){ (*comparacoes)++; if(strcmp(comps[j].nome,comps[j+1].nome)>0){ temp=comps[j]; comps[j]=comps[j+1]; comps[j+1]=temp; } }
}

void insertionSortTipo(Componente comps[], int n, int *comparacoes){
    for(int i=1;i<n;i++){
        Componente chave=comps[i]; int j=i-1;
        while(j>=0 && ((*comparacoes)++,strcmp(comps[j].tipo,chave.tipo)>0)){ comps[j+1]=comps[j]; j--; }
        comps[j+1]=chave;
    }
}

void selectionSortPrioridade(Componente comps[], int n, int *comparacoes){
    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++){ (*comparacoes)++; if(comps[j].prioridade<comps[min].prioridade) min=j; }
        Componente temp=comps[i]; comps[i]=comps[min]; comps[min]=temp;
    }
}

int buscaBinariaPorNome(Componente comps[], int n, char chave[], int *comparacoes){
    int inicio=0,fim=n-1;
    while(inicio<=fim){
        int meio=(inicio+fim)/2;
        (*comparacoes)++;
        int cmp=strcmp(comps[meio].nome,chave);
        if(cmp==0) return meio; else if(cmp<0) inicio=meio+1; else fim=meio-1;
    }
    return -1;
}

void mostrarComponentes(Componente comps[], int n){
    for(int i=0;i<n;i++) printf("%d. %s | %s | %d\n",i+1,comps[i].nome,comps[i].tipo,comps[i].prioridade);
}
