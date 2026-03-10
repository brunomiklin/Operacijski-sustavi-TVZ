# Operacijski sustavi — Laboratorijske vježbe

Repozitorij sadrži laboratorijske zadatke iz kolegija **Operacijski sustavi**, implementirane u programskom jeziku **C**.
Vježbe pokrivaju osnovne koncepte rada s **procesima, dretvama i sinkronizacijom**.

---

## Pregled labosa

### Labos 1 — Generiranje slučajnih vrijednosti

**Datoteka:** `prviProgram.c`
Program koristi globalno polje od **100000 `char` elemenata** kojima dodjeljuje vrijednosti **-1 ili 1** pomoću `rand()`.
Vrijednosti se ispisuju na ekran, a program se zadržava aktivnim (`sleep(50)`) radi analize procesa.

**Tema:** memorija procesa, globalne varijable

---

### Labos 2 — Stvaranje child procesa

**Datoteka:** `drugiProgram.c`
Program prima argument koji predstavlja broj child procesa.
U petlji koristi `fork()` za stvaranje procesa, a roditelj nakon toga poziva `wait()` za sinkronizaciju.

**Tema:** `fork()`, parent–child odnos, sinkronizacija procesa

---

### Labos 3 — Kontrola broja procesa

**Datoteka:** `drugiProgramFix.c`
Poboljšana verzija Labosa 2 koja uvodi ograničenje maksimalnog broja aktivnih procesa kako bi se spriječilo preopterećenje sustava.

**Tema:** upravljanje procesima, kontrola paralelizma

---

### Labos 4 — Analiza performansi procesa

Labos uključuje analizu ponašanja procesa pod opterećenjem te mjerenje vremena izvršavanja.

**Tema:** performanse i ograničenja operacijskog sustava

---

### Labos 5 — Višedretveni programi

**Zadatak 1 — Rezervacija sjedala (`Zadatak1.c`)**
Simulacija rezervacije sjedala s **100 dretvi** gdje svaka dretva pokušava zauzeti slučajno sjedalo uz zaštitu kritične sekcije pomoću `pthread_mutex`.

**Zadatak 2 — Kuharica i studenti (`Zadatak2.c`)**
Simulacija sustava proizvođač–potrošač gdje kuharica priprema obroke, a studenti ih uzimaju sa zajedničkog stola.

**Tema:** dretve, mutexi, sinkronizacija, kritične sekcije

---

## Kompajliranje

```bash
gcc program.c -o program -pthread
```

## Pokretanje

```bash
./program
```
