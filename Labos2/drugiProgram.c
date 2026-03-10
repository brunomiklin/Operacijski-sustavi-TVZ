#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Krivi broj argumenata!!\n");
        printf("./drugiProgram <child_proces>!!\n");
        return -1;
    }

    setbuf(stdout, NULL);

    int child_proces = atoi(argv[1]);


    for (int i = 0; i < child_proces; i++) {
    
        
        pid_t pid = fork();
        if (pid == 0) {
            printf("Dijete #%d\n", i + 1);
            exit(0);
        } else if (pid > 0) {
            printf("Roditelj #%d\n", i + 1);
        
        } else {
            perror("fork failed");
            exit(1);
        }
    }


  	for(int i=0;i<child_proces;i++)
  	{
	wait(NULL);
 	 }

    return 0;
}
