#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Registro {
    int dado;
} Registro;

typedef struct No {
    Registro Reg;
    struct No *pEsq, *pDir;
} No;

void PrimeiroCenario(No *pRaiz);
int EhArvoreAvl(No* pRaiz);
void SegundoCenario();
int Inserir(No** ppRaiz,int a);
int Remover(No** ppRaiz, int a);
int Altura(No* pRaiz);
int FB (No* pRaiz);
void RSE(No** ppRaiz);
void RSD(No** ppRaiz);
int BalancearEsquerda(No** ppRaiz);
int BalancearDireita(No** ppRaiz);
int Balanceamento(No** ppRaiz);
No* procuraMenor (No* pAtual);
void listar (No *pRaiz);
void limpar(No *pRaiz);

int main(){
    No *pRaiz = NULL;

    int escolha;

    do{
        printf("Digite a opção desejada: \n1 - Primeiro cenário \n2 - Segundo Cenário \n3 - Sair \n");
        scanf("%d", &escolha);

        switch(escolha){
            case 1:
                PrimeiroCenario(pRaiz);
                break;
            case 2:
                SegundoCenario();
                break;
            case 3:
                exit(1);
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    }while(escolha!=3);

}

void PrimeiroCenario(No *pRaiz){
    int numeroNodos, random, i;
    srand(time(0));

    printf("Digite a quantidade de nodos: \n");
    scanf("%d", &numeroNodos);

    for(i=0;i<numeroNodos;i++){
        random = rand()%1000;
        Inserir(&pRaiz, random);
    }

    listar(pRaiz);
    printf("\n");

    if(EhArvoreAvl(pRaiz)) {
        printf("\nA arvore eh AVL\n");
    }
    else {
        printf("\nNao eh arvore AVL\n");
    }

    limpar(pRaiz);
}

int EhArvoreAvl(No* pRaiz){
    int fb;
    if (pRaiz == NULL){
        return 1;
    }
    if (!EhArvoreAvl(pRaiz->pEsq)){
        return 0;
    }
    if (!EhArvoreAvl(pRaiz->pDir)){
        return 0;
    }

    fb = FB (pRaiz);

    if ( ( fb > 1 ) || ( fb < -1) ){
        return 0;
    }
    else{
        return 1;
    }
}

void SegundoCenario(){
    No *pRaiz = NULL;

    printf("Primeiro caso: Inserindo 15\n");
    Inserir(&pRaiz, 20);
    Inserir(&pRaiz, 4);
    printf("--ANTES DE INSERIR O 15--\n");
    listar(pRaiz);
    printf("\n");
    Inserir(&pRaiz, 15);
    printf("--DEPOIS DE INSERIR O 15--\n");
    listar(pRaiz);
    printf("\n\n");
    limpar(pRaiz);
    pRaiz = NULL;

    printf("Segundo caso: Inserindo 15\n");
    Inserir(&pRaiz, 20);
    Inserir(&pRaiz, 4);
    Inserir(&pRaiz, 26);
    Inserir(&pRaiz, 3);
    Inserir(&pRaiz, 9);
    printf("--ANTES DE INSERIR O 15--\n");
    listar(pRaiz);
    printf("\n");
    Inserir(&pRaiz, 15);
    printf("--DEPOIS DE INSERIR O 15--\n");
    listar(pRaiz);
    printf("\n\n");
    limpar(pRaiz);
    pRaiz = NULL;

    printf("Terceiro caso: Inserindo 15\n");
    Inserir(&pRaiz, 20);
    Inserir(&pRaiz, 4);
    Inserir(&pRaiz, 26);
    Inserir(&pRaiz, 3);
    Inserir(&pRaiz, 9);
    Inserir(&pRaiz, 2);
    Inserir(&pRaiz, 7);
    Inserir(&pRaiz, 11);
    Inserir(&pRaiz, 21);
    Inserir(&pRaiz, 30);
    printf("--ANTES DE INSERIR O 15--\n");
    listar(pRaiz);
    printf("\n");
    Inserir(&pRaiz, 15);
    printf("--DEPOIS DE INSERIR O 15--\n");
    listar(pRaiz);
    printf("\n\n");
    limpar(pRaiz);
    pRaiz = NULL;

    printf("Primeiro caso: Inserindo 8\n");
    Inserir(&pRaiz, 20);
    Inserir(&pRaiz, 4);
    printf("--ANTES DE INSERIR O 8--\n");
    listar(pRaiz);
    printf("\n");
    Inserir(&pRaiz, 8);
    printf("--DEPOIS DE INSERIR O 8--\n");
    listar(pRaiz);
    printf("\n\n");
    limpar(pRaiz);
    pRaiz = NULL;

    printf("Segundo caso: Inserindo 8\n");
    Inserir(&pRaiz, 20);
    Inserir(&pRaiz, 4);
    Inserir(&pRaiz, 26);
    Inserir(&pRaiz, 3);
    Inserir(&pRaiz, 9);
    printf("--ANTES DE INSERIR O 8--\n");
    listar(pRaiz);
    printf("\n");
    Inserir(&pRaiz, 8);
    printf("--DEPOIS DE INSERIR O 8--\n");
    listar(pRaiz);
    printf("\n\n");
    limpar(pRaiz);
    pRaiz = NULL;

    printf("Terceiro caso: Inserindo 8\n");
    Inserir(&pRaiz, 20);
    Inserir(&pRaiz, 4);
    Inserir(&pRaiz, 26);
    Inserir(&pRaiz, 3);
    Inserir(&pRaiz, 9);
    Inserir(&pRaiz, 21);
    Inserir(&pRaiz, 30);
    Inserir(&pRaiz, 2);
    Inserir(&pRaiz, 7);
    Inserir(&pRaiz, 11);
    printf("--ANTES DE INSERIR O 8--\n");
    listar(pRaiz);
    printf("\n");
    Inserir(&pRaiz, 8);
    printf("--DEPOIS DE INSERIR O 8--\n");
    listar(pRaiz);
    printf("\n\n");
    limpar(pRaiz);
    pRaiz = NULL;

    printf("Primeiro caso: Removendo 1\n");
    Inserir(&pRaiz, 2);
    Inserir(&pRaiz, 1);
    Inserir(&pRaiz, 4);
    Inserir(&pRaiz, 3);
    Inserir(&pRaiz, 5);
    printf("--ANTES DE REMOVER O 1--\n");
    listar(pRaiz);
    printf("\n");
    Remover(&pRaiz, 1);
    printf("--DEPOIS DE REMOVER O 1--\n");
    listar(pRaiz);
    printf("\n\n");
    limpar(pRaiz);
    pRaiz = NULL;

    printf("Segundo caso: Removendo 1\n");
    Inserir(&pRaiz, 6);
    Inserir(&pRaiz, 2);
    Inserir(&pRaiz, 9);
    Inserir(&pRaiz, 1);
    Inserir(&pRaiz, 8);    
    Inserir(&pRaiz, 4);
    Inserir(&pRaiz, 11);
    Inserir(&pRaiz, 3);
    Inserir(&pRaiz, 7);
    Inserir(&pRaiz, 5);
    Inserir(&pRaiz, 12);
    Inserir(&pRaiz, 10);
    Inserir(&pRaiz, 13);
    printf("--ANTES DE REMOVER O 1--\n");
    listar(pRaiz);
    printf("\n");
    Remover(&pRaiz, 1);
    printf("--DEPOIS DE REMOVER O 1--\n");
    listar(pRaiz);
    printf("\n\n");
    limpar(pRaiz);
    pRaiz = NULL;

    printf("Terceiro caso: Removendo 1\n");
    Inserir(&pRaiz, 5);
    Inserir(&pRaiz, 2);
    Inserir(&pRaiz, 8);
    Inserir(&pRaiz, 1);
    Inserir(&pRaiz, 3);    
    Inserir(&pRaiz, 7);
    Inserir(&pRaiz, 10);
    Inserir(&pRaiz, 4);
    Inserir(&pRaiz, 6);
    Inserir(&pRaiz, 11);
    Inserir(&pRaiz, 9);
    Inserir(&pRaiz, 12);
    printf("--ANTES DE REMOVER O 1--\n");
    listar(pRaiz);
    printf("\n");
    Remover(&pRaiz, 1);
    printf("--DEPOIS DE REMOVER O 1--\n");
    listar(pRaiz);
    printf("\n\n");
    limpar(pRaiz);
    pRaiz = NULL;
}

int Inserir(No** ppRaiz,int a){
    if (*ppRaiz == NULL){
        *ppRaiz = (No*)malloc(sizeof(No));
        (*ppRaiz)->Reg.dado = a;
        (*ppRaiz)->pEsq = NULL;
        (*ppRaiz)->pDir = NULL;
        return 1;
    }

    else if ( (*ppRaiz)->Reg.dado > a){
        if ( Inserir(&(*ppRaiz)->pEsq,a) ){
            if (Balanceamento(ppRaiz)){
                return 0;
            }
            else{
                return 1;
            }
        }
    }

    else if ( (*ppRaiz)->Reg.dado < a ){
        if ( Inserir(&(*ppRaiz)->pDir,a) ){
            if (Balanceamento(ppRaiz)){
                return 0;
            }
            else{
                return 1;
            }
        }
        else{
            return 0;
        }
    }

    else{
        return 0;
    }

    return 0;
}

int Remover(No** ppRaiz, int a){
    if(*ppRaiz == NULL){
        printf("O valor não existe\n");
        return 0;
    }

    int resposta;
    
    if(a < (*ppRaiz)->Reg.dado){
        if((resposta=Remover(&(*ppRaiz)->pEsq, a)) == 1){
            Balanceamento(ppRaiz);
        }
    }

    if(a > (*ppRaiz)->Reg.dado){
        if((resposta=Remover(&(*ppRaiz)->pDir, a)) == 1){
            Balanceamento(ppRaiz);
        }
    }

    if((*ppRaiz)->Reg.dado == a){
        if((*ppRaiz)->pEsq == NULL || (*ppRaiz)->pDir == NULL){
            No *removido = (*ppRaiz);
            if((*ppRaiz)->pEsq != NULL){
                (*ppRaiz) = (*ppRaiz)->pEsq;
            }
            else{
                (*ppRaiz) = (*ppRaiz)->pDir;
            }

            free(removido);
        }
        else{
            No *temporario = procuraMenor((*ppRaiz)->pDir);
            (*ppRaiz)->Reg.dado = temporario->Reg.dado;
            Remover(&(*ppRaiz)->pDir, (*ppRaiz)->Reg.dado);
            Balanceamento(ppRaiz);
        }

        return 1;
    }

    return resposta;
}

int Altura(No* pRaiz){
    int iEsq,iDir;

    if (pRaiz == NULL){
        return 0;
    }

    iEsq = Altura(pRaiz->pEsq);
    iDir = Altura(pRaiz->pDir);

    if( iEsq > iDir ){
        return iEsq + 1;
    }
    else{
        return iDir + 1;
    }
}

int FB (No* pRaiz){
    if (pRaiz == NULL){
        return 0;
    }

    return Altura(pRaiz->pEsq) - Altura(pRaiz->pDir);
}

void RSE(No** ppRaiz){
    No *pAux;
    pAux = (*ppRaiz)->pDir;
    (*ppRaiz)->pDir = pAux->pEsq;
    pAux->pEsq = (*ppRaiz);
    (*ppRaiz) = pAux;
}

void RSD(No** ppRaiz){
    No *pAux;
    pAux = (*ppRaiz)->pEsq;
    (*ppRaiz)->pEsq = pAux->pDir;
    pAux->pDir = (*ppRaiz);
    (*ppRaiz) = pAux;
}

int BalancearEsquerda(No** ppRaiz){
    int fbe = FB ( (*ppRaiz)->pEsq );

    if( fbe >= 0 ){
        RSD(ppRaiz);
        return 1;
    }

    else if (fbe < 0 ){
        RSE( &((*ppRaiz)->pEsq) );
        RSD( ppRaiz ); 
        return 1;
    }

    return 0;
}

int BalancearDireita(No** ppRaiz){
    int fbd = FB( (*ppRaiz)->pDir);

    if( fbd <= 0 ){
        RSE (ppRaiz);
        return 1;
    }

    else if (fbd > 0 ){ 
        RSD( &((*ppRaiz)->pDir) );
        RSE( ppRaiz );
        return 1;
    }

    return 0;
}

int Balanceamento(No** ppRaiz){
    int fb = FB(*ppRaiz);
    if( fb > 1){
        return BalancearEsquerda(ppRaiz);
    }
    else if(fb < -1 ){
        return BalancearDireita(ppRaiz);
    }
    else{
        return 0;
    }
}

No* procuraMenor (No* pAtual) {
    No *nodo1 = pAtual;
    No *nodo2 = pAtual->pEsq;
    while (nodo2 != NULL) {
        nodo1 = nodo2;
        nodo2 = nodo2->pEsq;
    }

    return nodo1;
}

void listar (No *pRaiz){
    if (pRaiz != NULL) {
        printf("%d(", pRaiz->Reg.dado);
        listar(pRaiz->pEsq);
        listar(pRaiz->pDir);
        printf(")");
    }
}

void limpar(No *pRaiz){
    if (pRaiz != NULL) {
        limpar(pRaiz->pEsq);
        limpar(pRaiz->pDir);
        free(pRaiz);
    }
}