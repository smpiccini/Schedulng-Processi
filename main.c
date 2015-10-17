#include <stdio.h>
#include <stdlib.h>

struct s_elemento{
    int executeTime;
    int returnTime;
    int waitingTime;
    int remainTime;
    struct s_elemento *next;
};

typedef struct s_elemento elemento;

void stampaLista(elemento* first);
void svuotaLista(elemento* first);
elemento* aggiungiElemento(elemento* first, int value);
int controllaTempoRimasto(elemento* first);

int main(int argc, char** argv) {
    int flag, i, tempoAssoluto = 0;
    int ExecuteTime;
    float tempoMedio;
    elemento *primo = NULL;
    
    do{
        i++;
        printf("Inserisci il tempo d'esecuzione del processo n.%d : ", i);
        scanf("%d", &ExecuteTime);
        primo=aggiungiElemento(primo, ExecuteTime);
        
        printf("Vuoi inserire un nuovo processo (1|0) : ");
        scanf("%d", &flag);
    }while(flag!=0);

    while(controllaTempoRimasto!=0){
        
    }
    
    svuotaLista(primo);
    
    return (EXIT_SUCCESS);
}

void stampaLista(elemento* first){
    elemento* scorri=first;
    while(scorri!=NULL){
        printf("%d ", scorri->executeTime);
        scorri=scorri->next;
    }
    return;
}

void svuotaLista (elemento* first){
    elemento* temp;
    printf("\nSvuotamento lista in corso...\n");
    while(first!=NULL){
        temp=first->next;
        free(first);
        first=temp;
    }
    printf("Completato.");
}

elemento* aggiungiElemento(elemento* first, int value){
    elemento* scorri=first;
    elemento* temp;
    temp = (elemento*) malloc(sizeof(elemento));
    if(temp == NULL) {
        exit(1);
    }
    temp->executeTime=value;
    temp->returnTime=0;
    temp->waitingTime=0;
    temp->remainTime=value;
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

int controllaTempoRimasto(elemento* first){
    elemento* scorri=first;
    int cond=0;
    while(scorri!=NULL){
        if (scorri->remainTime!=0){
            cond=1;
        }
        scorri=scorri->next;
    }
    return cond;
}