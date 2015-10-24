#include <stdio.h>
#include <stdlib.h>

struct s_elemento{
    int executeTime;
    int returnTime;
    int waitingTime;
    int remainTime;
    int arrivalTime;
    struct s_elemento *next;
};

typedef struct s_elemento elemento;

void svuotaLista(elemento* first);
elemento* aggiungiElemento(elemento* first, int value);
int controllaTempoRimasto(elemento* first);

int main(int argc, char** argv) {
    int flag, numeroTask, i, tempoAssoluto = 0;
    int ExecuteTime;
    float attesaMedia = 0;
    elemento *primo = NULL;
    elemento *puntaShorterTask = NULL;
    elemento *scorri = NULL;
    
    do{
        numeroTask++;
        printf("Inserisci il tempo d'esecuzione del processo n.%d : ", numeroTask);
        scanf("%d", &ExecuteTime);
        primo=aggiungiElemento(primo, ExecuteTime);
        
        printf("Vuoi inserire un nuovo processo (1|0) : ");
        scanf("%d", &flag);
    }while(flag!=0);
    
    while(controllaTempoRimasto(primo)!=0){
        tempoAssoluto++;
        scorri=primo;
        puntaShorterTask=primo;
        for(i=0; i<tempoAssoluto && i<numeroTask; i++){
            if ((scorri->remainTime < puntaShorterTask->remainTime && scorri->remainTime>0 ) || puntaShorterTask->remainTime==0){
                puntaShorterTask=scorri;
            }
        scorri=scorri->next;
        }
        puntaShorterTask->remainTime--;
        if (puntaShorterTask->remainTime==0){
            puntaShorterTask->returnTime=tempoAssoluto-puntaShorterTask->arrivalTime;
            puntaShorterTask->waitingTime=puntaShorterTask->returnTime-puntaShorterTask->executeTime;
        }
    }
    scorri=primo;
    i=1;
    while(scorri!=NULL){
        printf("Processo %d:\n Tempo di Esecuzione: %d\n Tempo di Ritorno: %d\n Tempo di Attesa: %d\n\n", i, scorri->executeTime, scorri->returnTime, scorri->waitingTime);
        i++;
        scorri=scorri->next;
    }
    scorri=primo;
    while(scorri!=NULL){
        attesaMedia+=scorri->waitingTime;
        scorri=scorri->next;
    }
    attesaMedia/=numeroTask;
    printf("Tempo di attesa medio: %.2f\n", attesaMedia);
    svuotaLista(primo);
    
    return (EXIT_SUCCESS);
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
    temp->remainTime=temp->executeTime;
    temp->arrivalTime=0;
    
    if (first!=NULL){
        temp->arrivalTime++;
        while(scorri->next!=NULL){
            scorri=scorri->next;
            temp->arrivalTime++;
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