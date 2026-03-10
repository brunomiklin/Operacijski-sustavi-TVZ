# Operacijski-sustavi-TVZ

**Labos 1** — Generiranje i ispis slučajnih vrijednosti
Datoteka: prviProgram.c

Program alocira globalno polje od 100000 elemenata tipa char.
Svakom elementu dodjeljuje vrijednost -1 ili 1, generiranu pomoću rand().
Ispisuje sve vrijednosti na ekran.
Program spava 50 sekundi (sleep(50)) kako bi se mogao analizirati u sustavu (npr. kroz top).

**Cilj labosa:** uvod u memoriju procesa, globalne varijable i osnovnu interakciju sa sustavom.

**Labos 2** — Osnovno stvaranje child procesa
Datoteka: drugiProgram.c

Program prima argument: broj child procesa koje treba stvoriti.
U petlji poziva fork() i stvara N child procesa.
Svako dijete ispisuje svoj redni broj, a roditelj također ispisuje poruku.
Nakon stvaranja svih procesa, roditelj poziva wait() za svako dijete.

**Cilj labosa**: razumjeti fork(), parent-child odnose i sinkronizaciju pomoću wait().
Napomena: program ne ograničava broj aktivnih procesa, pa pri velikim vrijednostima može preopteretiti sustav.

**Labos 3** — Poboljšano upravljanje procesima
Datoteka: drugiProgramFix.c

Poboljšana verzija Labosa 2 koja uvodi ograničenje:
Cmaksimalno_aktivnih = 10000;Prikaži više redaka

Ako je dostignut maksimalan broj aktivnih procesa, program čeka (wait()) da se jedan završi.
Time se kontrolira paralelizam i sprječava da sustav ostane bez resursa.

Cilj labosa: primjena kontrole nad brojem aktivnih procesa + stabilniji dizajn.

**Labos 4** — Očekivana analiza procesa i optimizacija
(Program nije priložen, ali iz konteksta slijedi.)

Tipično uključuje mjerenje vremena izvršavanja, ponašanje procesa pod opterećenjem,
i razumijevanje granica OS-a.
Očekuje se nadogradnja znanja iz Labosa 2 i 3.


**Labos 5** — 
**Zadatak 1** — Rezervacija sjedala (100 dretvi)
Datoteka: Zadatak1.c [unicath-my...epoint.com]
Opis

Kreira se 100 dretvi, svaka predstavlja jednog putnika.
Postoji globalno polje sjedala mjesta[100].
Svaka dretva:

“kasni” nasumično vrijeme,
pokušava preuzeti slučajno sjedalo,
zaključava pristup (pthread_mutex_lock) kako bi izbjegla utrku (“race condition”),
zauzima mjesto ako je slobodno.



**Važne točke:**

Simulira problem kritične sekcije.
Korištenje globalnog mutexa garantira konzistentnost.
Na kraju se ispisuje broj zauzetih i slobodnih mjesta te ukupno trajanje simulacije.

**Tema:**dretve, kritične sekcije, sinkronizacija, mutexi, simulacija resursa.

**Zadatak 2** — Simulacija kućanstva i kuharice
Datoteka: Zadatak2.c [unicath-my...epoint.com]
Opis
U ovoj simulaciji sudjeluje pet dretvi:
👨‍💻 Davor
🎾 Ivica
🎹 Ivan
😴 Tin
👩‍🍳 Kuharica
Sve dretve dijele jedan kritični resurs: stol, na koji kuharica stavlja obroke, a ostali ih uzimaju.
Ključni elementi:

Globalna varijabla stol tipa obrok_t.
Mutex za zaštitu pristupa stolu.
Svaki “student” ima svoje preferencije što jede, a što odbija.
Svaki student radi ciklus aktivnosti:

spavanje,
programiranje,
dolazak do stola,
konzumiranje, preskakanje ili pronalazak praznog stola,
neki imaju dodatne radnje (npr. Tin i kvarovi).


Kuharica kontinuirano priprema obroke dok broj_obroka > 0.
Nakon završetka, glavna dretva prikazuje statistiku:

broj konzumiranih obroka
broj odbijenih
broj puta kada je stol bio prazan.

**Što se ovime vježba:**

Napredna sinkronizacija u sustavima s više dretvi.
Komunikacija proizvođač–potrošači (kuharica → studenti).
Korištenje mutexa, povratnih vrijednosti dretvi i strukturiranih podataka.
Složeno ponašanje simuliranih agenata.

**Tema:** višedretvena komunikacija, sinkronizacija, simulacija, mutexi, koordinacija dretvi.
