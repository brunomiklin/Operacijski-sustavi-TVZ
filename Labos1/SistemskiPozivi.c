#include <stdio.h>
#include <stdlib.h>

#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>


int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Unijeli ste krivi broj parametara!\n");
        return 1;
    }
    int velicinaBuffera = -1;


    if(sscanf(argv[1],"%d",&velicinaBuffera)!=1)
    {
        printf("Unijeliste krivu vrijednost za velicinu buffera..\n");
        return 2;
    }
    if(velicinaBuffera<1)
    {
        printf("Velicina buffera ne moze biti negativna vrijednost!\n");
        return 2;
    }

    char * buffer = (char*)calloc(velicinaBuffera,1);
    if(buffer==NULL)
    {
        printf("Pokazivac pokazuje na NULL! Greska u alokaciji memorije!\n");
        return 2;
    }
    //int open(const char *path, int oflags);
    int ulaz = open(argv[2],O_RDONLY);

    int zastavice = O_WRONLY | O_CREAT | O_TRUNC;
    int dozvole = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    //fd=open(staza,zastavice,dozvole);
    int izlaz = open(argv[3],zastavice,dozvole);

    if(ulaz==-1 || izlaz==-1)
    {
        printf("Greški pri otvaranju datoteka!!\n");
        return 2;
    }

    printf("Kopiranje datoteke pomocu buffera velicin %d bajtova..\n",velicinaBuffera);
    while(read(ulaz,buffer,velicinaBuffera)>0)
    {
        if(write(izlaz,buffer,velicinaBuffera)==-1)
        {
            printf("Greska pri upisu u datoteku!\n");
            return 2;
        }
    }
    
    close(ulaz);
    close(izlaz);
    free(buffer);

    printf("Kopiranje zavrseno!");
}