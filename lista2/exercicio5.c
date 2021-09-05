#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[30];
    int idade;
    int altura;
}Pessoa;

int quantidade = 0;
void *adicionar(Pessoa *lista);
void listar(Pessoa *lista);

int main(){

    Pessoa *lista = NULL;

    int opcao;

    do{
        printf("--MENU-- \n1 - Adicionar \n2 - Imprimir \n3 - Sair \n");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                lista = adicionar(lista);
                break;
            case 2:
                listar(lista);
                break;
            case 3:
                free(lista);
                exit(1);
            default:
                printf("Opção inexistente.\n");
            break;
        }
    }while(opcao != 3);

}

void *adicionar(Pessoa *lista){
    if(quantidade == 0){
        lista = (Pessoa *)malloc(sizeof(Pessoa));
    }
    else{
        lista = (Pessoa *)realloc(lista, sizeof(Pessoa)*(quantidade+1));
    }

    printf("Nome: ");
    getchar();
    scanf("%[^\n]", lista[quantidade].nome);
    printf("Idade: ");
    scanf("%d", &lista[quantidade].idade);
    printf("Altura (em cm): ");
    scanf("%d", &lista[quantidade].altura);

    quantidade++;
    return lista;

}

void listar(Pessoa *lista){
    if(quantidade > 0){
        for (int i = 0; i < quantidade; i++){
            printf("%s , ", lista[i].nome);
            printf("%d anos, ", lista[i].idade);
            printf("%d cm \n", lista[i].altura);
        }
    }
    else{
        printf("Lista vazia.\n");
    }
    
}