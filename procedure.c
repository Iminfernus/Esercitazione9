#include "header.h"
#include <stdio.h>
#include <stdlib.h>



void * Produttori ( void * d) {
    struct Monitor * p = (struct Monitor *) d;

    srand(getpid());

    int valore;

    for (int i = 0; i < 3; i++)
    {   
        valore = rand() % 100;
        printf("Inizio Produzione...\n");
        produci(p,valore);
        printf("Fine Produzione\n");
    }
    
    pthread_exit(NULL);

}

void * Consumatori ( void * d) {
    struct Monitor * p = (struct Monitor *) d;

    for (int i = 0; i < 3; i++)
    {
        printf("Inizio Consumazione...\n");
        consuma(p);
        printf("Fine Consumazione\n");
    }
    
    pthread_exit(NULL);

}




void produci(struct Monitor * p, int valore) {
    
    pthread_mutex_lock(&(p->mutex));

    while (p->buffer_stato == 1)
    {
        printf("Sono un produttore, mi metto in attesa...\n");
        pthread_cond_wait(&(p->cv_produttori), &(p->mutex));
    }
    
    p->buffer = valore;
    p->buffer_stato = 1;

    printf("Produco: %d\n", valore);

    sleep(1);

    pthread_cond_signal(&(p->cv_consumatori));

    pthread_mutex_unlock(&(p->mutex));

}

void consuma(struct Monitor * p) {

    pthread_mutex_lock(&(p->mutex));

    while (p->buffer_stato == 0)
    {
        printf("Sono un consumatore, mi metto in attesa...\n");
        pthread_cond_wait(&(p->cv_consumatori), &(p->mutex));
    }
    
    int valore = p->buffer;
    p->buffer_stato = 0;

    printf("Consumo: %d\n", valore);

    sleep(1);

    pthread_cond_signal(&(p->cv_produttori));

    pthread_mutex_unlock(&(p->mutex));

}