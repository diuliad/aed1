#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void listar(int *vetor, int tamanho);
void verificar(int *vetor, int tamanho);
int* copia(int *vetor, int tamanho);
void insertionSort(int *vetor, int tamanho);
void selectionSort(int *vetor, int tamanho);
void quickSort(int *vetor, int esquerda, int direita);
void mergeSort(int *vetor, int inicio, int fim);
void merge(int *vetor, int inicio, int meio, int fim);
float time_diff(struct timeval *start, struct timeval *end);

int main(){
    int *vetor, *vetorAuxiliar;
    int tamanho = 0, escolha;
    struct timeval begin, end;

    printf("Digite o tamanho do vetor: ");
    scanf("%d", &tamanho);
    vetor = malloc(sizeof(int) * tamanho);
    srand(time(NULL));

    for(int i=0; i<tamanho; i++){
        vetor[i] = rand()%100000;
    }

    printf("\nVETOR CRIADO: \n");
    listar(vetor, tamanho);
    printf("--------------");

    do{
        printf("\n\nDigite a opção desejada: \n1 - Insertion Sort \n2 - Selection Sort \n3 - Quick Sort \n4 - Merge Sort \n5 - Sair \n");
        scanf("%d", &escolha);

        switch(escolha){
            case 1:
                printf("\nINSERTION SORT\n");
                vetorAuxiliar = copia(vetor, tamanho);
                gettimeofday(&begin, NULL);
                insertionSort(vetorAuxiliar, tamanho);
                gettimeofday(&end, NULL);
                listar(vetorAuxiliar, tamanho);
                verificar(vetorAuxiliar, tamanho);
                printf("\nTempo gasto na execução: %0.5f segundos.\n", time_diff(&begin, &end));
                free(vetorAuxiliar);
                break;
            case 2:
                printf("\nSELECTION SORT\n");
                vetorAuxiliar = copia(vetor, tamanho);
                gettimeofday(&begin, NULL);
                selectionSort(vetorAuxiliar, tamanho);
                gettimeofday(&end, NULL);
                listar(vetorAuxiliar, tamanho);
                verificar(vetorAuxiliar, tamanho);
                printf("\nTempo gasto na execução: %0.5f segundos.\n", time_diff(&begin, &end));
                free(vetorAuxiliar);
                break;
            case 3:
                printf("\nQUICK SORT\n");
                vetorAuxiliar = copia(vetor, tamanho);
                gettimeofday(&begin, NULL);
                quickSort(vetorAuxiliar, 0, tamanho-1);
                gettimeofday(&end, NULL);
                listar(vetorAuxiliar, tamanho);
                verificar(vetorAuxiliar, tamanho);
                printf("\nTempo gasto na execução: %0.5f segundos.\n", time_diff(&begin, &end));
                free(vetorAuxiliar);
                break;
            case 4:
                printf("\nMERGE SORT\n");
                vetorAuxiliar = copia(vetor, tamanho);
                gettimeofday(&begin, NULL);
                mergeSort(vetorAuxiliar, 0, tamanho-1);
                gettimeofday(&end, NULL);
                listar(vetorAuxiliar, tamanho);
                verificar(vetorAuxiliar, tamanho);
                printf("\nTempo gasto na execução: %0.5f segundos.\n", time_diff(&begin, &end));
                free(vetorAuxiliar);
                break;
            case 5:
                free(vetor);
                exit(1);
                break;
            default:
                printf("Opção inválida.\n");
                break;
        }
    }while(escolha!=5);

}

void listar(int *vetor, int tamanho){
    for (int i = 0; i < tamanho; i++){
        printf("%d - ", vetor[i]);
    }
    printf("\n");
}

void verificar(int *vetor, int tamanho){
    int verificador = 0;
    for (int i = 0; i < (tamanho-1); i++){
        if(vetor[i]>vetor[i+1]){
            verificador++;
        }
    }

    if (verificador==0){
        printf("Está correto.");
    }
    else{
        printf("Não está correto.");
    }    
}

int* copia(int *vetor, int tamanho){
    int *vetorAuxiliar;
    vetorAuxiliar = malloc(sizeof(int) * tamanho);
    for (int i = 0; i < tamanho; i++){
        vetorAuxiliar[i] = vetor[i];
    }
    
    return vetorAuxiliar;
}

void insertionSort(int *vetor, int tamanho){
    for (int i = 1; i < tamanho; i++){
        int j = i-1;
        int x = vetor[i];

        while ((j>=0) && (vetor[j]>x)){
            vetor[j+1] = vetor[j];
            j--;
        }
        vetor[j+1] = x;
    }
}

void selectionSort(int *vetor, int tamanho){
    int min, tmp, i, j, min_id=0;
    for (i = 0; i < (tamanho-1); i++){
        min = vetor[i];
        for (j = (i+1); j < tamanho; j++){
            if (vetor[j]<min){
                min = vetor[j];
                min_id = j;
            }
        }
        tmp = vetor[i];
        vetor[i] = vetor[min_id];
        vetor[min_id] = tmp;
        min_id = i+1;
    }
}

void quickSort(int *vetor, int esquerda, int direita){
    int mid, tmp, i, j;
    i = esquerda;
    j = direita;
    mid = vetor[(esquerda+direita)/2];

    do{
        while (vetor[i]<mid){
            i++;
        }
        while (mid<vetor[j]){
            j--;
        }

        if(i<=j){
            tmp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = tmp;
            i++;
            j--;
        }        
    }while (i<=j);

    if(esquerda<j){
        quickSort(vetor, esquerda, j);
    }
    if(i<direita){
        quickSort(vetor, i, direita);
    }
}

void mergeSort(int *vetor, int inicio, int fim){
    int meio;
    if(inicio<fim){
        meio = (inicio+fim)/2;
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio+1, fim);
        merge(vetor, inicio, meio, fim);
    }
}

void merge(int *vetor, int inicio, int meio, int fim){
    int *tmp, a1, a2, tamanho, i, j, k, fim1=0, fim2=0;

    tamanho = fim - inicio + 1;
    a1 = inicio;
    a2 = meio + 1;
    tmp = malloc(tamanho * sizeof(int));

    if(tmp != NULL){
        for (i = 0; i < tamanho; i++){
            if(!fim1 && !fim2){
                if(vetor[a1]<vetor[a2]){
                    tmp[i] = vetor[a1++];
                }
                else{
                    tmp[i] = vetor[a2++];
                }

                if(a1>meio){
                    fim1 = 1;
                }

                if (a2>fim){
                    fim2 = 1;
                }
            }
            else{
                if(!fim1){
                    tmp[i] = vetor[a1++];
                }
                else{
                    tmp[i] = vetor[a2++];
                }
            }
        }
        
        for (j = 0, k = inicio; j < tamanho; j++, k++){
            vetor[k] = tmp[j];
        }        
    }

    free(tmp);
}

float time_diff(struct timeval *start, struct timeval *end){
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}