#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int zbroj = 0;
pthread_mutex_t mtx;

void* funkcija(void* arg)
{
    zbroj++;

    return 0;
}

int main(int argc,char*argv[])
{
    int br_dretvi = 0;

    if(argc!=2)
    {
        printf("Unesen je krivi broj argumenata!\n");
        exit(1);
    }
    if(sscanf(argv[1],"%d",&br_dretvi)!=1)
    {
        printf("Krivi unos broja dretvi!");
        exit(1);
    }

    pthread_t* dretve = (pthread_t*)calloc(br_dretvi,sizeof(pthread_t));
    if(dretve==NULL)
    {
        printf("Greška pri alokaciji memorije!\n");
        exit(1);
    }
    for(long i=0;i<br_dretvi;i++)
    {
        if(pthread_create(&dretve[i],NULL,funkcija,(void*)i))
        {
            printf("Greška pri stvaranju dretve %ld\n",i);
        }
    }
    for(long i=0;i<br_dretvi;i++)
    {
        pthread_join(dretve[i],NULL);
    }

    printf("Zbroj na kraju kada sve dretve završe %d\n",zbroj);

    free(dretve);
    return 0;

}