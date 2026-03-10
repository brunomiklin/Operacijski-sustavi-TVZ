#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>

#define N 100

long mjesta[N] = {0}; 
pthread_mutex_t mtx;  

int random_funk(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

void kasni(int min, int max)
{
    sleep(random_funk(min, max));
}

long* dohvati_polje()
{
    kasni(1, 3);
    return mjesta;
}

void* check_in(void* arg)
{
    long id = *(long*)arg;

    kasni(1, 5);   // login()
    long* p = dohvati_polje(); // dohvat polja

    while (1)
    {
        int sjedalo = random_funk(0, 99);

        if (random_funk(0, 1) == 0)
            continue;

        kasni(1, 2);

        pthread_mutex_lock(&mtx);
        if (p[sjedalo] == 0)
        {
            p[sjedalo] = id + 1;
            printf("%ld -> mjesto %d\n", id + 1, sjedalo + 1);
            pthread_mutex_unlock(&mtx);
            break;
        }
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main()
{
    pthread_t t[N];
    long id[N];

    srand(time(NULL));
    pthread_mutex_init(&mtx, NULL);

    time_t start = time(NULL);   

    for (int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&t[i], NULL, check_in, &id[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(t[i], NULL);

    time_t end = time(NULL);   

    int zauz = 0;
    for (int i = 0; i < N; i++)
        if (mjesta[i] != 0) zauz++;

    printf("\nZauzeta: %d\n", zauz);
    printf("Slobodna: %d\n", N - zauz);
    printf("Vrijeme simulacije: %ld s\n", end - start);

    pthread_mutex_destroy(&mtx);
    return 0;
}
