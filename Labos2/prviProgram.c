#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define velicina_polja 100000

char polje[velicina_polja] =  {0};

int main()
{
    srand(time(NULL));
    for(int i=0;i<velicina_polja;i++)
    {
        int random_broj = (rand() % 2) * 2 - 1;
        polje[i] = random_broj;


        printf("%d ",polje[i]);
    }
    

    sleep(50);
    return 0;
}