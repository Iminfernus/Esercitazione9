#include "header.h"
#include <stdlib.h>



int main() {

    pthread_t produttore;
    pthread_t consumatore;

    struct Monitor * p = malloc(sizeof(struct Monitor));

    pthread_mutex_init(&(p->mutex),NULL);
    pthread_cond_init(&(p->cv_consumatori), NULL);
    pthread_cond_init(&(p->cv_produttori), NULL);
    

    p->buffer = 0;
    p->buffer_stato = 0;

    pthread_create(&produttore,NULL, Produttori, (void *) p);
    pthread_create(&consumatore,NULL, Consumatori, (void *) p);

    
    pthread_join(produttore,NULL);
    pthread_join(consumatore,NULL);

    pthread_cond_destroy(&(p->cv_consumatori));
    pthread_cond_destroy(&(p->cv_produttori));
    pthread_mutex_destroy(&(p->mutex));
    

    
    return 0;

}