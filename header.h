#ifndef _HEADER_
#define _HEADER_

#include <pthread.h>


struct Monitor
{
    int buffer;

    int buffer_stato;

    pthread_mutex_t mutex;
    pthread_cond_t cv_produttori;
    pthread_cond_t cv_consumatori;

};

void * Produttori(void * d);
void * Consumatori(void * d);

void produci(struct Monitor * p, int valore);
void consuma(struct Monitor * p);

#endif