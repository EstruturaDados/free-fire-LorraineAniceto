#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIOS 5
#define MAX_MOCHILA 100
#define MAX_COMPONENTES 20

// =====================
// MÓDULO 1: TERRITÓRIOS
// =====================
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

void cadastrarTerritorios(struct Territorio t[], int n){
    for(int i=0;i<n;i++){
        printf("\n--- Cadastro do Territorio %d ---\n", i+1);
        printf("Nome: "); scanf(" %29s", t[i].nome);
        printf("Cor do exercito: "); scanf(" %9s", t[i].cor);
        printf("Quantidade de tropas: "); scanf("%d", &t[i].tropas);
    }
}

void mostrarTerritorios(struct Territorio t[], int n){
    printf("\n===== Territorios =====\n");
    for(int i=0;i<n;i++)
        printf("%d) %s | %s | %d tropas\n", i+1, t[i].nome, t[i].cor, t[i].tropas);
}

// =====================
// MÓDULO 2: MOCHILA
// =====================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// --- Vetor ---
Item mochilaVetor[MAX_MOCHILA];
int qtdVetor=0, comparacoesSeq=0, comparacoesBin=0;

void inserirItemVetor(){
    if(qtdVetor>=MAX_MOCHILA){ printf("Mochila cheia!\n"); return;}
    Item it;
    printf("Nome: "); scanf(" %29[^\n]", it.nome);
    printf("Tipo: "); scanf(" %19[^\n]", it.tipo);
    printf("Quantidade: "); scanf("%d", &it.quantidade);
    mochilaVetor[qtdVetor++]=it;
}

void listarItensVetor(){
    printf("\n--- Mochila (Vetor) ---\n");
    for(int i=0;i<qtdVetor;i++)
        printf("%s | %s | %d\n", mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
}

int buscarSequencialVetor(char nome[]){
    comparacoesSeq=0;
    for(int i=0;i<qtdVetor;i++){
        comparacoesSeq++;
        if(strcmp(mochilaVetor[i].nome,nome)==0) return i;
    }
    return -1;
}

void ordenarVetor(){ // Bubble sort
    Item tmp;
    for(int i=0;i<qtdVetor-1;i++)
        for(int j=0;j<qtdVetor-1-i;j++)
            if(strcmp(mochilaVetor[j].nome,mochilaVetor[j+1].nome)>0){
                tmp=mochilaVetor[j];
                mochilaVetor[j]=mochilaVetor[j+1];
                mochilaVetor[j+1]=tmp;
            }
}

int buscarBinariaVetor(char nome[]){
    int ini=0, fim=qtdVetor-1, meio;
    comparacoesBin=0;
    while(ini<=fim){
        meio=(ini+fim)/2;
        comparacoesBin++;
        int cmp=strcmp(nome,mochilaVetor[meio].nome);
        if(cmp==0) return meio;
        else if(cmp<0) fim=meio-1;
        else ini=meio+1;
    }
    return -1;
}

// --- Lista Encadeada ---
typedef struct No{
    Item dados;
    struct No* proximo;
} No;

void inserirItemLista(No **inicio){
    No* novo=(No*)malloc(sizeof(No));
    printf("Nome: "); scanf(" %29[^\n]", novo->dados.nome);
    printf("Tipo: "); scanf(" %19[^\n]", novo->dados.tipo);
    printf("Quantidade: "); scanf("%d", &novo->dados.quantidade);
    novo->proximo=*inicio;
    *inicio=novo;
}

void listarItensLista(No *inicio){
    printf("\n--- Mochila (Lista) ---\n");
    No* aux=inicio;
    while(aux){
        printf("%s | %s | %d\n", aux->dados.nome, aux->dados.tipo, aux->dados.quantidade);
        aux=aux->proximo;
    }
}

// =====================
// MÓDULO 3: TORRE DE FUGA
// =====================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

int compTorre=0;

void bubbleSortNome(Componente v[], int n){
    compTorre=0;
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-1-i;j++){
            compTorre++;
            if(strcmp(v[j].nome,v[j+1].nome)>0){
                Componente tmp=v[j]; v[j]=v[j+1]; v[j+1]=tmp;
            }
        }
}

void insertionSortTipo(Componente v[], int n){
    compTorre=0;
    for(int i=1;i<n;i++){
        Componente key=v[i]; int j=i-1;
        while(j>=0 && (compTorre++, strcmp(v[j].tipo,key.tipo)>0)){
            v[j+1]=v[j]; j--;
        }
        v[j+1]=key;
    }
}

void selectionSortPrioridade(Componente v[], int n){
    compTorre=0;
    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++){
            compTorre++;
            if(v[j].prioridade<v[min].prioridade) min=j;
        }
        if(min!=i){ Componente tmp=v[i]; v[i]=v[min]; v[min]=tmp;}
    }
}

int buscaBinariaPorNome(Componente v[], int n, char chave[]){
    int ini=0,fim=n-1; compTorre=0;
    while(ini<=fim){
        int meio=(ini+fim)/2;
        compTorre++;
        int cmp=strcmp(chave,v[meio].nome);
        if(cmp==0) return meio;
        else if(cmp<0) fim=meio-1;
        else ini=meio+1;
    }
    return -1;
}

void mostrarComponentes(Componente v[], int n){
    printf("\n--- Componentes ---\n");
    for(int i=0;i<n;i++)
        printf("%d) Nome: %s | Tipo: %s | Prioridade: %d\n", i+1,v[i].nome,v[i].tipo,v[i].prioridade);
}

void medirTempo(void (*algoritmo)(Componente[], int), Componente v[], int n){
    clock_t inicio=clock();
    algoritmo(v,n);
    clock_t fim=clock();
    double tempo=(double)(fim-inicio)/CLOCKS_PER_SEC;
    printf("Comparacoes: %d | Tempo: %.6f s\n", compTorre, tempo);
}

// =====================
// MENU PRINCIPAL
// =====================
int main(){
    struct Territorio territorios[MAX_TERRITORIOS];
    No* listaMochila=NULL;
    Componente torre[MAX_COMPONENTES];
    int qtdComponentes=0;
    int opcao;

    do{
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Territorios\n2 - Mochila\n3 - Torre de Fuga\n0 - Sair\nOpcao: ");
        scanf("%d",&opcao); getchar();

        if(opcao==1){
            int opT;
            do{
                printf("\n--- Modulo Territorios ---\n");
                printf("1-Cadastrar 2-Mostrar 0-Voltar\nOpcao: ");
                scanf("%d",&opT); getchar();
                if(opT==1) cadastrarTerritorios(territorios,MAX_TERRITORIOS);
                else if(opT==2) mostrarTerritorios(territorios,MAX_TERRITORIOS);
            }while(opT!=0);
        }
        else if(opcao==2){
            int opM;
            do{
                printf("\n--- Modulo Mochila ---\n");
                printf("1-Inserir Vetor 2-Listar Vetor 3-Busca Seq 4-Ordenar 5-Busca Binaria\n");
                printf("6-Inserir Lista 7-Listar Lista\n0-Voltar\nOpcao: ");
                scanf("%d",&opM); getchar();
                if(opM==1) inserirItemVetor();
                else if(opM==2) listarItensVetor();
                else if(opM==3){
                    char nome[30]; printf("Nome: "); scanf(" %29[^\n]",nome);
                    int idx=buscarSequencialVetor(nome);
                    if(idx>=0) printf("Encontrado em %d comparacoes.\n",comparacoesSeq);
                    else printf("Nao encontrado (%d comparacoes).\n",comparacoesSeq);
                }
                else if(opM==4) ordenarVetor();
                else if(opM==5){
                    char nome[30]; printf("Nome: "); scanf(" %29[^\n]",nome);
                    int idx=buscarBinariaVetor(nome);
                    if(idx>=0) printf("Encontrado em %d comparacoes.\n",comparacoesBin);
                    else printf("Nao encontrado (%d comparacoes).\n",comparacoesBin);
                }
                else if(opM==6) inserirItemLista(&listaMochila);
                else if(opM==7) listarItensLista(listaMochila);
            }while(opM!=0);
        }
        else if(opcao==3){
            int opTorre;
            do{
                printf("\n--- Modulo Torre de Fuga ---\n");
                printf("1-Cadastrar Componente\n2-Mostrar Componentes\n");
                printf("3-Bubble Sort (nome)\n4-Insertion Sort (tipo)\n5-Selection Sort (prioridade)\n");
                printf("6-Busca Binaria (por nome)\n0-Voltar\nOpcao: ");
                scanf("%d",&opTorre); getchar();

                if(opTorre==1){
                    if(qtdComponentes>=MAX_COMPONENTES){ printf("Limite atingido!\n"); continue;}
                    printf("Nome: "); fgets(torre[qtdComponentes].nome,30,stdin);
                    torre[qtdComponentes].nome[strcspn(torre[qtdComponentes].nome,"\n")]=0;
                    printf("Tipo: "); fgets(torre[qtdComponentes].tipo,20,stdin);
                    torre[qtdComponentes].tipo[strcspn(torre[qtdComponentes].tipo,"\n")]=0;
                    printf("Prioridade (1-10): "); scanf("%d",&torre[qtdComponentes].prioridade); getchar();
                    qtdComponentes++;
                }
                else if(opTorre==2) mostrarComponentes(torre,qtdComponentes);
                else if(opTorre==3) medirTempo(bubbleSortNome,torre,qtdComponentes);
                else if(opTorre==4) medirTempo(insertionSortTipo,torre,qtdComponentes);
                else if(opTorre==5) medirTempo(selectionSortPrioridade,torre,qtdComponentes);
                else if(opTorre==6){
                    char chave[30]; printf("Nome do componente-chave: "); fgets(chave,30,stdin);
                    chave[strcspn(chave,"\n")]=0;
                    int idx=buscaBinariaPorNome(torre,qtdComponentes,chave);
                    if(idx>=0) printf("Encontrado na posicao %d (%d comparacoes).\n",idx,compTorre);
                    else printf("Nao encontrado (%d comparacoes).\n",compTorre);
                }
            }while(opTorre!=0);
        }

    }while(opcao!=0);

    printf("Programa finalizado.\n");
    return 0;
}



