#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Krivi broj parametra!");
        printf("Piši: ime_programa /buffer/ /ulazna datoteka/ <izlazna datoteka>\n");
        return 1;
    }
    int velicinaBuffera = -1;
    if (sscanf(argv[1], "%d", &velicinaBuffera) != 1)
    {
        printf("Veličina buffera nije ispravno upisina!\n");
        return 2;
    }
    if (velicinaBuffera < 1)
    {
        printf("Veličina buffera ne može biti negativan broj!\n");
        return 2;
    }
    char *buffer = (char *)calloc(velicinaBuffera, 1);
    if (buffer == NULL)
    {
        printf("Pokazivač pokazuje na NULL! -> GREŠKA KOD ALOKACIJE BUFFERA!\n");
        return 2;
    }

    FILE *ulaz = fopen(argv[2], "rb");
    FILE *izlaz = fopen(argv[3], "wb");
    if (ulaz == NULL || izlaz == NULL)
    {
        printf("GREŠKA KOD OTVARANJA DATOTEKA!\n");
        return 2;
    }

    printf("Kopiranje datoteke pomoću buffera veličine %d bajta...!\n", velicinaBuffera);

    while (fread(buffer, velicinaBuffera, 1, ulaz) != 0)
    {
        fwrite(buffer, velicinaBuffera, 1, izlaz);
    }

    fclose(ulaz);
    fclose(izlaz);
    return 0;
}