#include <stdio.h>
#include <stdlib.h>

struct s_elemento{
    int value;
    struct s_elemento *next;
};

typedef struct s_elemento elemento;

void stampaLista(elemento* first);
elemento* aggiungiTesta(elemento* first, int value);
elemento* aggiungiCoda(elemento* first, int value);
elemento* ordinaLista(elemento* first);
float calcolaTempo(elemento* first, int numeroProcessi);
void svuotaLista(elemento* first);

int main(int argc, char** argv) {
    int flag, i = 0;
    int ExecuteTime;
    float tempoMedio;
    elemento *primo = NULL;
    
    do{
        i++;
        printf("Inserisci il tempo d'esecuzione del processo n.%d :", i);
        scanf("%d", &ExecuteTime);
        primo=aggiungiCoda(primo, ExecuteTime);
        
        printf("Vuoi inserire un nuovo processo (1|0) : ");
        scanf("%d", &flag);
    }while(flag!=0);
    
    ordinaLista(primo);
    printf("Lista processi in ordine di esecuzione (SJF):\n");
    stampaLista(primo);
    

    tempoMedio=calcolaTempo(primo, i);
    printf("\nTempo di attesa medio: %f\n", tempoMedio);
    svuotaLista(primo);
    
    return (EXIT_SUCCESS);
}

elemento* ordinaLista(elemento* first){
    elemento* scorri, *pj, *pk;
    int temp;
    scorri=first;
    
    while(scorri->next!=NULL){
        pj=first;
        while(pj->next!=NULL){
            pk=pj->next;
            if(pj->value > pk->value){
                temp=pj->value;
                pj->value=pk->value;
                pk->value=temp;
            }
            pj=pj->next;
        }
        scorri=scorri->next;
    }
    return first;
}

void stampaLista(elemento* first){
    elemento* scorri=first;
    while(scorri!=NULL){
        printf("%d ", scorri->value);
        scorri=scorri->next;
    }
    return;
}

elemento* aggiungiTesta(elemento* first, int value){
    elemento* temp;
    temp = (elemento*) malloc(sizeof(elemento));
    if(temp == NULL) {
        exit(1);
    }
    temp->value=value;
    temp->next = first;
    first = temp;
    return first;
}

elemento* aggiungiCoda(elemento* first, int value){
    elemento* scorri=first;
    elemento* temp;
    temp = (elemento*) malloc(sizeof(elemento));
    if(temp == NULL) {
        exit(1);
    }
    temp->value=value;
    if (first!=NULL){
        while(scorri->next!=NULL){
            scorri=scorri->next;
        }
       scorri->next=temp; 
    }
    else {
        first=temp;
    }
    return first;
}

float calcolaTempo(elemento* first, int numeroProcessi){
    elemento* scorri=first;
    float acc,accExecuteTime=0;
    float tempo=0;
    
    while(scorri->next!=NULL){
        accExecuteTime+=scorri->value;
        acc+=accExecuteTime;
        scorri=scorri->next;
    }
    tempo=acc/numeroProcessi;
    return tempo;
}

void svuotaLista (elemento* first){
    elemento* temp;
    printf("Svuotamento lista in corso...\n");
    while(first!=NULL){
        temp=first->next;
        free(first);
        first=temp;
    }
    printf("Completato.");
}
