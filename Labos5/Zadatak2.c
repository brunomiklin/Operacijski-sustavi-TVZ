#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>
#include<string.h>

typedef enum {
    PRAZNO,
    COKOLADA,
    CEVAPI,
    JANJETINA,
    STRUKLE,
    GRAH,
    KEKSI,
    KELJ,
    JABUKA
} obrok_t;

typedef enum {
    OSTALO,
    DIZNE,
    ELEKTRONIKA
} kvar_t;

typedef struct {
    char ime[10];
    int konzumiranje;
    int odbijanje;
    int prazan_stolic;
} stats_t;

pthread_mutex_t mtx;
obrok_t stol = PRAZNO;
int broj_obroka = 0;
int kraj = 0;

int rand_f(int min,int max)
{
    return (rand() %(max-min+1))+min;
}

int faktorijel(int n)
{
    if(n<=1) return 1;
    else return n*faktorijel(n-1);
}

void programiranje(const char* ime)
{
    printf("%s upravo programira!\n",ime);
    faktorijel(rand_f(1,10));
}

void spavanac(const char* ime)
{
    int min = 5;
    int max = 10;

    if(strcmp("Tin",ime)==0)
    {
        min=6;
        max=13;
    }
    printf("%s trenutno spava!\n",ime);
    sleep(rand_f(min,max));
}

const char* obrok_string(obrok_t obrok)
{
    switch(obrok){
        case COKOLADA: return "Čokolada";
        case CEVAPI: return "Čevapi";
        case JANJETINA: return "Janjetina";
        case STRUKLE: return "Štrukle";
        case GRAH: return "Grah";
        case KEKSI: return "Keksi";
        case KELJ: return "Kelj";
        case JABUKA: return "Jabuka";
        default: return "Prazno";
    }
}
void *davor()
{
    const char* ime = "Davor";
    static stats_t stats = {"Davor",0,0,0};

    while(!kraj)
    {
        spavanac(ime);
        programiranje(ime);

        pthread_mutex_lock(&mtx);
        if(stol==PRAZNO)
        {
            printf("%s je nasao prazan stol!\n",ime);
            stats.prazan_stolic++;
        }
        else if(stol!=COKOLADA && stol!=KEKSI)
        {
            printf("%s jede %s\n",ime,obrok_string(stol));
            stats.konzumiranje++;
            stol=PRAZNO;
        }
        else
        {
            printf("%s preskace obrok\n",ime);
            stats.odbijanje++;
        }

        pthread_mutex_unlock(&mtx);  

        printf("%s gleda televizor\n",ime);
        sleep(rand_f(2,4));
    }
    return &stats;
}

void *ivica()
{
    const char* ime = "Ivica";
    static stats_t stats = {"Ivica",0,0,0};

    while(!kraj)
    {
        spavanac(ime);
        printf("%s igra tenis!\n",ime);
        sleep(rand_f(2,4));

        pthread_mutex_lock(&mtx);

        if(stol==PRAZNO)
        {
            printf("%s je nasao prazan stol!\n",ime);
            stats.prazan_stolic++;
        }
        else if(stol!=GRAH && stol!=KELJ)
        {
            printf("%s jede %s\n",ime,obrok_string(stol));
            stats.konzumiranje++;
            stol=PRAZNO;
        }
        else
        {
            printf("%s preskace obrok\n",ime);
            stats.odbijanje++;
        }

        pthread_mutex_unlock(&mtx); 

        programiranje(ime);
    }
    return &stats;
}

void *ivan()
{
    const char* ime = "Ivan";
    static stats_t stats = {"Ivan",0,0,0};

    while(!kraj)
    {
        spavanac(ime);
        printf("%s slusa ili svira klavir\n",ime);
        sleep(rand_f(2,4));

        pthread_mutex_lock(&mtx);

        if(stol==PRAZNO)
        {
            printf("%s je nasao prazan stol!\n",ime);
            stats.prazan_stolic++;
        }
        else if(stol!=STRUKLE)
        {
            printf("%s jede %s\n",ime,obrok_string(stol));
            stats.konzumiranje++;
            stol=PRAZNO;
        }
        else
        {
            printf("%s preskace obrok\n",ime);
            stats.odbijanje++;
        }

        pthread_mutex_unlock(&mtx);   
        programiranje(ime);
    }
    return &stats;
}

void *tin()
{
    const char* ime = "Tin";
    static stats_t stats = {"Tin",0,0,0};

    while(!kraj)
    {
        spavanac(ime);
        programiranje(ime);

        pthread_mutex_lock(&mtx);

        if(stol==PRAZNO)
        {
            printf("%s je nasao prazan stol!\n",ime);
            stats.prazan_stolic++;
        }
        else if(stol!=CEVAPI && stol!=JANJETINA)
        {
            printf("%s jede %s\n",ime,obrok_string(stol));
            stats.konzumiranje++;
            stol=PRAZNO;
        }
        else
        {
            printf("%s preskace obrok\n",ime);
            stats.odbijanje++;
        }

        pthread_mutex_unlock(&mtx);   

        kvar_t kvar;
        int r = rand_f(1,100);       
        if(r <= 25) kvar = DIZNE;
        else if(r <= 45) kvar = ELEKTRONIKA;
        else kvar = OSTALO;

        switch(kvar)
        {
            case ELEKTRONIKA: sleep(2); break;
            case DIZNE: sleep(4); break;
            case OSTALO: sleep(rand_f(2,4)); break;
        }
    }
    return &stats;
}

void *kuharica()
{
    while(broj_obroka > 0)
    {
        obrok_t gotov_obrok = rand_f(1,8);
        printf("Kuharica slaze obrok %s\n", obrok_string(gotov_obrok));
        sleep(rand_f(1,2));

        pthread_mutex_lock(&mtx);   
        if(stol == PRAZNO)
        {
            stol = gotov_obrok;
            broj_obroka--;
            printf("Kuharica je na stol stavila %s\n", obrok_string(stol));
        }
        pthread_mutex_unlock(&mtx);   

        printf("Kuharica odmara\n");
        sleep(rand_f(1,2));
    }

    kraj = 1;
    return NULL;
} 


int main(int argc,char *argv[])
{
    pthread_t ljudi[5];

    if(argc!=2)
    {
        printf("Greška prilikom poziva programa!");
        exit(1);
    }
    if(sscanf(argv[1],"%d",&broj_obroka)!=1)
    {
        printf("Greška kod unosa argumenta u komandnu liniju!");
        exit(1);
    }

    srand(time(NULL));
    pthread_mutex_init(&mtx,NULL);

    pthread_create(&ljudi[0],NULL,davor,NULL);
    pthread_create(&ljudi[1],NULL,ivica,NULL);
    pthread_create(&ljudi[2],NULL,ivan,NULL);
    pthread_create(&ljudi[3],NULL,tin,NULL);
    pthread_create(&ljudi[4],NULL,kuharica,NULL);

    stats_t stats[4];

    for(int i=0;i<5;i++)
    {
        void *temp;
        pthread_join(ljudi[i],&temp);
        if(temp!=NULL)
        {
            stats[i] = *(stats_t*)temp;
        }
    }
    for(int i=0;i<4;i++)
    {
        printf("%s -> konzumiranje: %d - odbijanje: %d- prazan stol: %d\n",stats[i].ime,stats[i].konzumiranje,stats[i].odbijanje,stats[i].prazan_stolic);
    }
    pthread_mutex_destroy(&mtx);
    return 0;
}