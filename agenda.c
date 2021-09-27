#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Auxiliares
#define COUNTER (sizeof(int))
#define OPTION (sizeof(int))
#define AUX_POINTERPOINTER (sizeof(void **))

//Informações da Pessoa
#define NAME (sizeof(char) * 10)
#define AGE (sizeof(int))
#define NUMBER (sizeof(int))

//Finais da fila
#define FIRST_PERSON (sizeof(int))
#define LAST_PERSON (sizeof(int) + sizeof(void **))

//Antes e depois do nome
#define NEXT_PERSON (sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void **))
#define PREVIOUS_PERSON (sizeof(char) * 10 + sizeof(int) + sizeof(int))


void adicionar(void *pBuffer, void *pAux);
void remover(void *pBuffer, void *linkedList, void *pRun);
void listar(void *pBuffer, void *pAux);
void buscar(void *pBuffer, void *pAux, void *pRun);
void sair(void *pAux);

int main(){
    void *pAux = NULL;
    pAux = malloc(COUNTER + AUX_POINTERPOINTER + AUX_POINTERPOINTER);

    *(int *)(pAux) = 0;

    void *pBuffer = NULL;
    pBuffer = malloc(OPTION + AUX_POINTERPOINTER);

    void *pRun = NULL;

    if (!pBuffer || !pAux){
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    do{
        printf("\n\n--MENU-- \n1 - Adicionar \n2 - Remover \n3 - Listar \n4 - Buscar \n5 - Sair \n");
        scanf("%d", (int *)(pBuffer));
        getchar();

        switch (*(int *)(pBuffer)){
            case 1:
                adicionar(pBuffer, pAux);
                break;
            case 2:
                remover(pBuffer, pAux, pRun);
                break;
            case 3:
                listar(pBuffer, pAux);
                break;
            case 4:
                buscar(pBuffer, pAux, pRun);
                break;
            case 5:
                sair(pAux);
                free(pBuffer);
                free(pAux);
                exit(0);
                break;
            default:
                printf("Opção inexistente.\n");
                break;
        }
    } while (*(int *)(pBuffer) != 5);
}

void adicionar(void *pBuffer, void *pAux){
    int *counter = (int *)(pAux);

    void *pPersonInfo = NULL;
    pPersonInfo = malloc(NAME + AGE + NUMBER + AUX_POINTERPOINTER + AUX_POINTERPOINTER);

    void *pPersonInfoAux = NULL;

    if (!pPersonInfo){
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    printf("Digite o nome: ");
    scanf("%s", (char *)pPersonInfo);
    getchar();

    printf("Digite a idade: ");
    scanf("%d", &*(int *)(pPersonInfo + NAME));
    getchar();
   
    printf("Digite o telefone: ");
    scanf("%d", &*(int *)(pPersonInfo + NAME + AGE));
    getchar();

    *(void **)(pPersonInfo + NEXT_PERSON) = NULL;   
    *(void **)(pPersonInfo + PREVIOUS_PERSON) = NULL;

    if (*counter == 0){
        *(void **)(pAux + LAST_PERSON) = pPersonInfo;
        *(void **)(pAux + FIRST_PERSON) = pPersonInfo;
        
        *counter += 1;

        return;
    }

    pBuffer = *(void **)(pAux + FIRST_PERSON);

    while(pBuffer != NULL){
        if(strcmp((char *)pPersonInfo, (char *)pBuffer) < 0){
            *(void **)(pPersonInfo + PREVIOUS_PERSON) = *(void **)(pBuffer + PREVIOUS_PERSON);
            *(void **)(pPersonInfo + NEXT_PERSON) = pBuffer;

            if(*counter > 1 && *(void **)(pBuffer + PREVIOUS_PERSON) != NULL){
                pPersonInfoAux = *(void **)(pBuffer + PREVIOUS_PERSON);
                *(void **)(pPersonInfoAux + NEXT_PERSON) = pPersonInfo;
            }

            *(void **)(pBuffer + PREVIOUS_PERSON) = pPersonInfo;

            if(*(void **)(pPersonInfo + PREVIOUS_PERSON) == NULL){
                *(void **)(pAux + FIRST_PERSON) = pPersonInfo;
            }

            *counter += 1;

            return;
        }

        if(*(void **)(pBuffer + NEXT_PERSON) == NULL){
            pPersonInfoAux = pBuffer;
        }

        pBuffer = *(void **)(pBuffer + NEXT_PERSON);
    }

    *(void **)(pPersonInfo + PREVIOUS_PERSON) = pPersonInfoAux;
    *(void **)(pPersonInfoAux + NEXT_PERSON) = pPersonInfo;
    *(void **)(pAux + LAST_PERSON) = pPersonInfo;

    *counter += 1;

    return;

}

void remover(void *pBuffer, void *pAux, void *pRun){
    int *counter = (int *)(pAux);

    if (*counter == 0){
        printf("A agenda está vazia.\n");
    }
    else{ //se nao
        printf("O primeiro nome da lista foi removido!\n\n");
        pRun = *(void **)(pAux + FIRST_PERSON);
        *(void **)(pAux + FIRST_PERSON) = *(void **)(pRun + NEXT_PERSON);
        free(pRun);
        *(void **)(pBuffer + PREVIOUS_PERSON) = NULL;

        *counter -= 1;

    }
}

void listar(void *pBuffer, void *pAux){
    void *pPersonInfo = NULL;
    pPersonInfo = *(void **)(pAux + FIRST_PERSON);

    int *counter = (int *)(pAux);

    if(*counter == 0){
        printf("A agenda está vazia.\n");
    }
    else{
        while(pPersonInfo != NULL){//percorre toda lista
            printf("Nome: %s - ", (char *)pPersonInfo);
            printf("Idade: %d - ", *(int *)(pPersonInfo + NAME));
            printf("Numero: %d\n\n", *(int *)(pPersonInfo + NAME + AGE));

            pPersonInfo = *(void **)(pPersonInfo + NEXT_PERSON);
        }
    }
}

void buscar(void *pBuffer, void *pAux, void *pRun){
    int *counter = (int *)(pAux);

    pRun = *(void **)(pAux + FIRST_PERSON);

    if(*counter == 0){
        printf("Lista vazia.\n");
        return;
    } 
    else{
        void *auxSearch = malloc(sizeof(char) * 10);

        printf("Digite o nome que queira buscar: \n");
        scanf("%s", (char *)auxSearch);
        getchar();

        while(pRun != NULL){
            if(strcmp(pRun ,(char *)auxSearch) == 0){
                printf("Nome: %s\n", (char *)pRun);
                printf("Idade: %d\n", *(int *)(pRun + NAME));
                printf("Numero: %d\n\n", *(int *)(pRun + NAME + AGE));

                free(auxSearch);
                
                return;
            }
            
            pRun = *(void **)(pRun + NEXT_PERSON);
        }
    }

    return;

}

void sair(void *pAux){
    void *pFree = *(void **)(pAux + FIRST_PERSON);
    int *counter = (int *)(pAux);

    if ((int *)(pAux) == 0){
        printf("A lista está vazia.");
    }
    else{
        while (*(void **)(pAux + FIRST_PERSON) != NULL) {
            pFree = *(void **)(pAux + FIRST_PERSON);
            *(void **)(pAux + FIRST_PERSON) = *(void **)(pFree + NEXT_PERSON);
            free(pFree);

            *counter -= 1;
        }
    }
}