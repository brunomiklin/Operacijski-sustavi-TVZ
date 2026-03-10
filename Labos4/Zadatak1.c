#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
int zbroj = 0;
int main(int argc, char* argv[]){
    int br_procesa=0;
    	
	if(argc != 2){
        printf("Krivi unos argumenata!\n");
		exit(1);
	}
    if(sscanf(argv[1], "%d", &br_procesa) != 1){
        printf("Krivi unos broja procesa!\n");
		exit(1);
	}

    pid_t pid;  
    for(int i=0;i<br_procesa;i++)
    {
        switch(pid = fork())
        {
            case -1:
            {
                printf("Greška pri kreiranju procesa!\n");
                exit(2);
            }    
            case 0:
            {
                zbroj++;
                exit(0);
            }
            default:
            {
                wait(NULL);
                break;
            }
        }
     
    }
    printf("Zbroj na kraju procesa roditelja: %d\n", zbroj);
    return 0;

}
