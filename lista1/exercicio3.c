#include <stdio.h> //padrão
#include <string.h> //manipulação de strings
#include <stdlib.h> //alocação dinamica

void *incluir(void *pBuffer);
void *apagar(void *pBuffer);
void buscar(void *pBuffer);
void listar(void *pBuffer);

int main(){
    void *pBuffer = malloc(sizeof(int));

    if(pBuffer == NULL){
        printf("Erro ao alocar.\n");
        exit(1);
    }
    
    *(int*)pBuffer = 0;

    int escolha;

    do{
        printf("\n--MENU-- \n1) Incluir \n2) Apagar \n3) Buscar \n4) Listar \n5) Sair \n");
        scanf("%d", &escolha);

        switch (escolha){
        case 1:
            pBuffer = incluir(pBuffer);
            break;
        case 2:
            pBuffer = apagar(pBuffer);
            break;
        case 3:
            buscar(pBuffer);
            break;
        case 4:
            listar(pBuffer);
            break;
        case 5:
            free(pBuffer);
            exit(1);
            break;
        }
    } while(escolha != 5);

}

void *incluir(void *pBuffer){
    pBuffer = (void *)realloc(pBuffer, sizeof(int)*1 + (sizeof(char)*10 + sizeof(int)*2) * (*((int*)(pBuffer)) + 1));

    if(!pBuffer){
        printf("Erro ao alocar.\n");
        exit(1);
    }

    printf("Nome: ");
    scanf("%s", (char *)pBuffer + sizeof(int) + (sizeof(char)*10 + sizeof(int)*2) * (*(int*)(pBuffer)));
    getchar();
    printf("Idade: ");
    scanf("%d", (int *)(pBuffer + sizeof(int) + sizeof(char)*10 + (sizeof(char)*10 + sizeof(int)*2) * ((*(int*)(pBuffer)))));
    getchar();
    printf("Telefone: ");
    scanf("%d", (int *)(pBuffer + sizeof(int)*2 + sizeof(char)*10 + (sizeof(char)*10 + sizeof(int)*2) * ((*(int*)(pBuffer)))));
    getchar();

    *(int*)(pBuffer) += 1;

    return pBuffer;
}

void *apagar(void *pBuffer){
    if(*(int*)(pBuffer) > 0){
        char *nome = (char*)malloc(sizeof(char)*10);
        printf("\nDigite o nome que deseja apagar: ");
        getchar();
        scanf("%[^\n]", nome);

        int *busca = (int*)malloc(sizeof(int));
        *busca = 0;

        for (int i = 0; i < *(int*)(pBuffer); i++){
            if (strcmp((char *)(pBuffer + sizeof(int) + (sizeof(char)*10 + sizeof(int)*2) * i), nome) == 0){
                
                if ((i) != *(int*)(pBuffer)){
                    for (int j = (i + 1); j < *(int *)(pBuffer); j++){
                        strcpy((char *)(pBuffer + sizeof(int) + (sizeof(char)*10 + sizeof(int)*2) * (i)), (char *)(pBuffer + sizeof(int) + (sizeof(char)*10 + sizeof(int)*2) * j));
                        
                        *(int *)(pBuffer + sizeof(int) + sizeof(char)*10 + (sizeof(char) * 10 + sizeof(int)*2) * (i))=*(int *)(pBuffer + sizeof(int) + sizeof(char)*10 + (sizeof(char) * 10 + sizeof(int)*2) * j); 

                        *(int *)(pBuffer + sizeof(int) + sizeof(char)*10 + (sizeof(char) * 10 + sizeof(int)*2) * (i))=*(int *)(pBuffer + sizeof(int)*2 + sizeof(char)*10 + (sizeof(char) * 10 + sizeof(int)*2) * j); 
                        i++;
                    }
                    
                }

                pBuffer = (void *)realloc(pBuffer, sizeof(int)*1 + (sizeof(char)*10 + sizeof(int)*2) * (*((int*)(pBuffer)) - 1));
                *busca = 1;
                *(int*)(pBuffer) -= 1;
                
            }
            
        }

        if(*busca == 0){
            printf("Nome não encontrado.\n");
        }

        free(nome);
        free(busca);
        
    }
    else{
        printf("A lista está vazia.\n");
    }

    return pBuffer;
    
}

void buscar(void *pBuffer){
    char *nome = (char*)malloc(sizeof(char)*10);
    printf("\nDigite o nome que deseja buscar: ");
    getchar();
    scanf("%[^\n]", nome);

    int *busca = (int*)malloc(sizeof(int));
    *busca = 0;

    for (int i = 0; i < *(int*)(pBuffer); i++){
        if((strcmp((char *)(pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int)*2) * i), nome) == 0)){
            printf("Nome: %s ", (char *)(pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int)*2) * i)); 
            printf("Idade: %d ", *(int *)(pBuffer + sizeof(int) + sizeof(char)*10 + (sizeof(char) * 10 + sizeof(int)*2) * i)); 
            printf("Telefone: %d \n", *(int *)(pBuffer + sizeof(int)*2 + sizeof(char)*10 + (sizeof(char) * 10 + sizeof(int)*2) * i)); 
            *busca = 1;
        }
    }
    
    if(*busca != 1){
        printf("Nome não encontrado.\n");
    }

    free(nome);
    free(busca);
}

void listar(void *pBuffer){
    if(*(int*)(pBuffer) > 0){
        for (int i = 0; i < *(int*)(pBuffer); i++){
            printf("Nome: %s - ", (char *)(pBuffer + sizeof(int) + (sizeof(char) * 10 + sizeof(int)*2) * i)); 
            printf("Idade: %d - ", *(int *)(pBuffer + sizeof(int) + sizeof(char)*10 + (sizeof(char) * 10 + sizeof(int)*2) * i)); 
            printf("Telefone: %d \n", *(int *)(pBuffer + sizeof(int)*2 + sizeof(char)*10  + (sizeof(char) * 10 + sizeof(int)*2) * i)); 
        }
    }
    else{
        printf("A lista está vazia.\n");
    }
}
