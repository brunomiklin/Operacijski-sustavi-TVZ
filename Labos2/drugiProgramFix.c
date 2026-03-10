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
    int maksimalno_aktivnih = 10000;
    int active = 0;

    for (int i = 0; i < child_proces; i++) {
        if (active >= maksimalno_aktivnih) {
            wait(NULL); 
            active--;
        }

        pid_t pid = fork();
        if (pid == 0) {
            printf("Dijete #%d\n", i + 1);
            exit(0);
        } else if (pid > 0) {
            printf("Roditelj #%d\n", i + 1);
            active++;
        } else {
            perror("fork failed");
            exit(1);
        }
    }


    while (active > 0) {
        wait(NULL);
        active--;
    }

    return 0;
}
