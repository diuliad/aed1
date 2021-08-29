#include <stdio.h> //padrão
#include <string.h> //manipulação de strings
#include <stdlib.h> //alocação dinamica

char *adicionar(char *string);
char *remover(char *string);
void listar(char *string);

int main(){
    char *string = NULL;
    int escolha;

    do{
        printf("--MENU-- \n1) Adicionar nome \n2) Remover nome \n3) Listar \n4) Sair\n");
        scanf("%d", &escolha);

        switch (escolha){
        case 1:
            string = adicionar(string);
            break;
        case 2:
            string = remover(string);
            break;
        case 3:
            listar(string);
            break;
        case 4:
            free(string);
            exit(1);
            break;
        }
    } while(escolha != 4);

}

char *adicionar(char *string){
    printf("Digite o nome que deseja adicionar: \n");
    getchar();
    char *nome = (char *)malloc(sizeof(char)*100);
    scanf("%[^\n]", nome);

    if(string == NULL){
        string = (char *) malloc(sizeof(char) * (strlen(nome) + 2));
        strcpy(string, nome);
    }
    else{
        string = (char *) realloc(string, (strlen(string) + strlen(nome) + 2));
        strcat(string, nome);
    }

    strcat(string, "-");

    if(string == NULL){
        printf("Erro ao alocar.\n");
        exit(1);
    }

    free(nome);
    return string;

}

char *remover(char *string){
    if(string == NULL){
        printf("A lista de nomes está vazia.\n");
    }
    else{
        printf("Digite o nome que deseja remover: \n");
        getchar();
        char *nome_remover = (char*)malloc(sizeof(char) * 100);
        scanf("%[^\n]", nome_remover);

        int busca = 0;

        char *guardar_nome = NULL;
        char *comparar_nome = NULL;

        comparar_nome = strtok(string, "-");

        while(comparar_nome != NULL){
            if(strcmp(comparar_nome, nome_remover) != 0){
                if(guardar_nome == NULL){
                    guardar_nome = (char *)malloc(sizeof(char) * (strlen(comparar_nome) + 2));
                    strcpy(guardar_nome, comparar_nome);
                }
                else{
                    guardar_nome = (char *)realloc(guardar_nome, (strlen(guardar_nome) + strlen(comparar_nome) + 2));
                    strcat(guardar_nome, comparar_nome);
                }
                strcat(guardar_nome, "-");
            }
            else{
                busca = 1;
            }
            comparar_nome = strtok(NULL, "-");
        }
        if(busca != 1){
            printf("O nome não foi encontrado.\n");
        }
        
        if(guardar_nome != NULL){
            string = (char *)realloc(string, sizeof(char) * (strlen(guardar_nome) + 1));
            strcpy(string, guardar_nome);
        }
        else{
            string = (char *)realloc(string, sizeof(char)*0);
        }

        free(comparar_nome);
        free(guardar_nome);
        free(nome_remover);
    }

    return string;
}

void listar(char *string){
    if(string == NULL){
        printf("A lista está vazia.\n");
    }
    else{
        while(*string){
            if(*string != '-'){
                putchar(*string);
            }
            else{
                printf("\n");
            }
            string++;
        }
    }
}
