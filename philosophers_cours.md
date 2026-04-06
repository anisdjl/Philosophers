# 🍝 Cours Complet — Philosophers (42)
> *"I never thought philosophy would be so deadly"*

---

## Table des matières

1. [Le but du projet — comprendre l'abstraction](#1-le-but-du-projet--comprendre-labstraction)
2. [Le problème des philosophes — contexte et histoire](#2-le-problème-des-philosophes--contexte-et-histoire)
3. [Processus vs Threads — les bases](#3-processus-vs-threads--les-bases)
4. [Les threads POSIX (pthreads) en C](#4-les-threads-posix-pthreads-en-c)
5. [La mémoire partagée et les data races](#5-la-mémoire-partagée-et-les-data-races)
6. [Les mutex — l'outil de synchronisation](#6-les-mutex--loutil-de-synchronisation)
7. [Le deadlock — l'ennemi principal](#7-le-deadlock--lennemi-principal)
8. [Le starvation — l'autre ennemi](#8-le-starvation--lautre-ennemi)
9. [Le temps en C — gettimeofday et usleep](#9-le-temps-en-c--gettimeofday-et-usleep)
10. [Architecture générale du projet](#10-architecture-générale-du-projet)
11. [Checklist des erreurs classiques](#11-checklist-des-erreurs-classiques)
12. [Sources utilisées et recommandées](#12-sources-utilisées-et-recommandées)

---

## 1. Le but du projet — comprendre l'abstraction

Quand on lit le sujet pour la première fois, on se dit : *"Des philosophes qui mangent des spaghettis... c'est quoi ce délire ?"*. L'abstraction est volontaire. Voilà ce que le projet cherche vraiment à t'enseigner :

### Ce que les philosophes représentent dans la vraie vie

| Métaphore du projet | Réalité informatique |
|---|---|
| Un philosophe | Un **thread** (ou processus) en cours d'exécution |
| Une fourchette | Une **ressource partagée** (fichier, variable, connexion réseau…) |
| Manger | Une **section critique** — le moment où on utilise une ressource |
| Penser | Travailler sans avoir besoin de ressource partagée |
| Dormir | Attendre, se suspendre |
| Mourir de faim | Un thread qui ne reçoit jamais les ressources dont il a besoin (**starvation**) |
| Tout le monde attend, personne ne mange | **Deadlock** — blocage total du système |

### Le vrai problème que ça modélise

Imagine un serveur web qui gère 1000 connexions simultanées. Chaque connexion est un thread. Ces threads ont besoin d'accéder à une base de données (ressource partagée). Si deux threads écrivent en même temps dans la même ligne de la base → données corrompues. Si chaque thread attend que l'autre finisse → personne n'avance jamais.

C'est **exactement** le problème des philosophes. Ce projet t'apprend les outils fondamentaux pour gérer ce genre de situations dans n'importe quel système concurrent réel : OS, serveurs, jeux vidéo, applications multithreadées.

### Ce que tu vas concrètement apprendre

- Créer et gérer des threads en C avec `pthread`
- Protéger des ressources partagées avec des **mutex**
- Éviter le deadlock et le starvation
- Gérer le temps avec précision en millisecondes
- Penser en termes de **concurrence** et non plus de code séquentiel

---

## 2. Le problème des philosophes — contexte et histoire

### Origine

Le problème a été formulé en 1965 par **Edsger Dijkstra** (l'inventeur de l'algorithme de plus court chemin qui porte son nom). Il voulait illustrer les difficultés de la synchronisation entre processus concurrents. La formulation avec les philosophes et les fourchettes (à la place des bandes magnétiques originales) vient de **Tony Hoare**.

### Le scénario

```
         [Philosophe 1]
        /               \
  [Fourchette 5]   [Fourchette 1]
      |                   |
[Philosophe 5]       [Philosophe 2]
      |                   |
  [Fourchette 4]   [Fourchette 2]
        \               /
         [Philosophe 4]
              |
         [Fourchette 3]
              |
         [Philosophe 3]
```

Chaque philosophe est assis à une table ronde. Entre chaque paire de philosophes voisins, il y a **une seule** fourchette. Pour manger, un philosophe a besoin des **deux** fourchettes à ses côtés. Donc fourchette de gauche ET fourchette de droite.

### Le cycle de vie d'un philosophe

```
  ┌─────────────────────────────────────────┐
  │                                         │
  ▼                                         │
[PENSER] ──────────────────────────► [PRENDRE FOURCHETTES]
                                            │
                                            ▼
                                        [MANGER]
                                            │
                                            ▼
                                    [POSER FOURCHETTES]
                                            │
                                            ▼
                                        [DORMIR]
                                            │
                                            └──────────────────► retour à PENSER
```

### Pourquoi c'est un problème ?

Si **tous** les philosophes décident de manger en même temps et prennent leur fourchette **gauche** simultanément :

- Philosophe 1 a la fourchette 1, attend la fourchette 2
- Philosophe 2 a la fourchette 2, attend la fourchette 3
- Philosophe 3 a la fourchette 3, attend la fourchette 4
- Philosophe 4 a la fourchette 4, attend la fourchette 5
- Philosophe 5 a la fourchette 5, attend la fourchette 1

→ **Personne ne peut avancer. C'est le deadlock.**

---

## 3. Processus vs Threads — les bases

Avant de parler des threads, comprendre la différence avec les processus est essentiel.

### Le processus

Un processus est un **programme en cours d'exécution**. Il possède :
- Son propre espace mémoire (heap, stack, segments de données)
- Ses propres ressources (descripteurs de fichiers, etc.)
- Un PID (Process ID) unique

Deux processus sont **isolés** : si l'un plante, l'autre continue. Ils ne partagent pas leur mémoire par défaut (sauf via des mécanismes spéciaux comme les pipes, la mémoire partagée ou les sémaphores).

```
Processus A          Processus B
┌──────────┐         ┌──────────┐
│  Stack A │         │  Stack B │
│  Heap A  │         │  Heap B  │
│  Code A  │         │  Code B  │
└──────────┘         └──────────┘
   Mémoire              Mémoire
   isolée               isolée
```

### Le thread

Un thread est un **fil d'exécution** à l'intérieur d'un processus. Plusieurs threads d'un même processus **partagent** :
- Le heap (mémoire allouée dynamiquement)
- Les variables globales
- Les descripteurs de fichiers

Mais chaque thread possède son propre :
- **Stack** (variables locales, appels de fonction)
- **Registres du processeur** (état d'exécution courant)
- **Program Counter** (l'instruction en cours d'exécution)

```
Un seul processus avec 3 threads :

┌─────────────────────────────────────────┐
│            PROCESSUS                    │
│                                         │
│  ┌────────┐  ┌────────┐  ┌────────┐     │
│  │Stack T1│  │Stack T2│  │Stack T3│     │
│  └────────┘  └────────┘  └────────┘     │
│                                         │
│  ┌──────────────────────────────────┐   │
│  │      HEAP PARTAGÉ                │   │
│  │  (malloc, variables globales…)   │   │
│  └──────────────────────────────────┘   │
│                                         │
│  ┌──────────────────────────────────┐   │
│  │      CODE PARTAGÉ                │   │
│  └──────────────────────────────────┘   │
└─────────────────────────────────────────┘
```

### Pourquoi utiliser des threads plutôt que des processus ?

| Critère | Threads | Processus |
|---|---|---|
| Création | Rapide et légère | Plus lente, plus coûteuse |
| Communication | Simple (mémoire partagée) | Complexe (IPC, pipes, sockets…) |
| Isolation | Aucune (danger !) | Totale (sécurité) |
| Utilisation CPU | Efficace sur multi-cœurs | Aussi, mais overhead plus grand |
| Crash propagation | Un thread peut tuer tout le processus | Processus isolés |

Pour Philosophers (partie obligatoire), on utilise des **threads** car ils partagent naturellement la mémoire, ce qui permet de modéliser facilement la table de fourchettes partagée.

---

## 4. Les threads POSIX (pthreads) en C

POSIX (Portable Operating System Interface) est un standard qui définit une interface uniforme pour les systèmes Unix/Linux. La bibliothèque `pthread` implémente les threads selon ce standard.

### Compiler avec pthreads

Il faut ajouter le flag `-pthread` (ou `-lpthread`) à la compilation :

```bash
gcc -Wall -Wextra -Werror -pthread mon_fichier.c -o mon_programme
```

### Créer un thread : `pthread_create`

```c
#include <pthread.h>

int pthread_create(
    pthread_t *thread,           // Identifiant du thread créé (sortie)
    const pthread_attr_t *attr,  // Attributs (NULL = défaut)
    void *(*start_routine)(void *), // Fonction à exécuter dans le thread
    void *arg                    // Argument passé à la fonction
);
```

**Retourne** : 0 si succès, un code d'erreur sinon.

**Exemple simple** :

```c
#include <stdio.h>
#include <pthread.h>

void    *ma_fonction(void *arg)
{
    int id = *(int *)arg;
    printf("Je suis le thread %d\n", id);
    return (NULL);
}

int main(void)
{
    pthread_t   tid;
    int         id = 42;

    pthread_create(&tid, NULL, ma_fonction, &id);
    // Ici, le thread est lancé et tourne en parallèle du main
    pthread_join(tid, NULL);
    return (0);
}
```

### Attendre la fin d'un thread : `pthread_join`

```c
int pthread_join(
    pthread_t thread,  // Le thread qu'on attend
    void **retval      // Valeur de retour du thread (NULL si on s'en fout)
);
```

`pthread_join` **bloque** le thread appelant jusqu'à ce que le thread ciblé termine son exécution. C'est comme `waitpid` pour les processus.

**Si tu ne joins pas un thread** et que le processus se termine, le thread est brutalement arrêté. C'est une fuite de ressources.

### Détacher un thread : `pthread_detach`

```c
int pthread_detach(pthread_t thread);
```

Un thread **détaché** se nettoie lui-même quand il se termine. On ne peut pas lui faire `pthread_join` après. Utile pour les threads "fire and forget".

### Terminer un thread : `pthread_exit`

```c
void pthread_exit(void *retval);
```

Termine le thread courant proprement. La valeur passée peut être récupérée par `pthread_join`.

### Obtenir son propre identifiant : `pthread_self`

```c
pthread_t pthread_self(void);
```

Retourne l'identifiant du thread qui appelle la fonction. Utile pour du débogage ou pour savoir quel philosophe on est.

### Cycle de vie d'un thread

```
pthread_create()
      │
      ▼
   [RUNNING] ◄─────────────────────────────-┐
      │                                     │
      │  Bloqué sur mutex/join/sleep        │
      ▼                                     │
  [BLOCKED] ──────── Ressource dispo ───────┘
      │
      │  Thread termine (return ou pthread_exit)
      ▼
 [TERMINATED]
      │
      │  pthread_join() ou pthread_detach()
      ▼
  [DESTROYED]
```

### Passer des données à plusieurs threads

La façon la plus propre est de créer une **structure** contenant toutes les données nécessaires à chaque thread, et de passer un pointeur vers cette structure :

```c
typedef struct s_philosopher
{
    int             id;
    int             nb_meals;
    long            last_meal_time;
    // ...
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    // pointeur vers les données globales de la simulation
    t_simulation    *sim;
}   t_philosopher;

// Dans main :
pthread_create(&threads[i], NULL, philosopher_routine, &philosophers[i]);
```

---

## 5. La mémoire partagée et les data races

### Le problème fondamental

Quand plusieurs threads partagent une variable, des situations dangereuses peuvent apparaître.

**Exemple concret** : deux threads incrémentent un compteur.

```c
int counter = 0; // variable partagée

void *increment(void *arg)
{
    counter = counter + 1; // ⚠️ DANGEREUX
    return NULL;
}
```

Voilà ce qui peut se passer au niveau du processeur :

```
Thread 1                    Thread 2
────────────────────────────────────────
Lit counter (= 0)
                            Lit counter (= 0)
Calcule 0 + 1 = 1
                            Calcule 0 + 1 = 1
Écrit 1 dans counter
                            Écrit 1 dans counter

RÉSULTAT FINAL : counter = 1  (au lieu de 2 !)
```

Cette situation s'appelle une **data race** (course aux données). Le résultat dépend de l'ordre d'exécution des threads, qui est **non-déterministe** (décidé par le système d'exploitation).

### Pourquoi `counter++` n'est pas atomique

L'instruction `counter++` en C se décompose en **3 instructions assembleur** :
1. **LOAD** : charger la valeur de `counter` depuis la mémoire dans un registre
2. **ADD** : ajouter 1 au registre
3. **STORE** : écrire le résultat en mémoire

Un thread peut être interrompu par le scheduler **entre** ces 3 instructions. C'est là que réside le danger.

### La section critique

Une **section critique** est une portion de code qui accède à une ressource partagée et qui ne doit être exécutée que par **un seul thread à la fois**.

```
Thread 1 :  [code normal] → [ENTRÉE section critique] → [code partagé] → [SORTIE] → [code normal]
Thread 2 :  [code normal] → [attente...............] → [ENTRÉE] → [code partagé] → [SORTIE]
```

La règle d'or : **toute variable partagée entre threads doit être protégée**.

Dans Philosophers, les variables partagées typiques sont :
- L'état de chaque fourchette (prise ou disponible)
- L'horodatage du dernier repas de chaque philosophe
- Un flag "quelqu'un est mort" pour stopper la simulation
- Le compteur de repas

### `valgrind --helgrind` : détecter les data races

```bash
valgrind --tool=helgrind ./philo 5 800 200 200
```

Helgrind est un outil de `valgrind` qui détecte les data races à l'exécution. Utilise-le pour vérifier ton programme.

---

## 6. Les mutex — l'outil de synchronisation

### Qu'est-ce qu'un mutex ?

**Mutex** = **Mut**ual **Ex**clusion. C'est un verrou qui garantit qu'un seul thread à la fois peut accéder à une section critique.

Imagine la porte des toilettes : si quelqu'un est à l'intérieur et a verrouillé la porte, les autres font la queue. Quand la personne sort et déverrouille, quelqu'un d'autre peut entrer.

```
Thread 1 : lock() ─── [section critique] ─── unlock()
Thread 2 :            [attend...]            lock() ─── [section critique] ─── unlock()
Thread 3 :            [attend...]                       [attend...]            lock() ─── ...
```

### Déclarer un mutex

```c
#include <pthread.h>

pthread_mutex_t mon_mutex;
```

### Initialiser un mutex

**Méthode 1 — Statique** (pour les variables globales ou membres d'une structure) :
```c
pthread_mutex_t mon_mutex = PTHREAD_MUTEX_INITIALIZER;
```

**Méthode 2 — Dynamique** (recommandée, nécessaire si dans une structure allouée dynamiquement) :
```c
int pthread_mutex_init(
    pthread_mutex_t *mutex,          // Le mutex à initialiser
    const pthread_mutexattr_t *attr  // Attributs (NULL = défaut)
);
```

```c
pthread_mutex_t fork;
if (pthread_mutex_init(&fork, NULL) != 0)
{
    // Gérer l'erreur
}
```

### Verrouiller un mutex : `pthread_mutex_lock`

```c
int pthread_mutex_lock(pthread_mutex_t *mutex);
```

- Si le mutex est **déverrouillé** → le thread le verrouille et continue immédiatement.
- Si le mutex est **verrouillé** → le thread est **suspendu** jusqu'à ce qu'il soit libéré.

⚠️ **Si un thread essaie de `lock` un mutex qu'il a déjà locké lui-même → comportement indéfini / deadlock selon le type de mutex.**

### Déverrouiller un mutex : `pthread_mutex_unlock`

```c
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

Libère le mutex. Le thread qui possède le mutex est le seul qui devrait appeler `unlock`.

### Détruire un mutex : `pthread_mutex_destroy`

```c
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

Libère les ressources associées au mutex. À appeler quand on n'en a plus besoin (à la fin du programme). Ne jamais détruire un mutex qui est encore verrouillé.

### Exemple complet d'utilisation

```c
#include <stdio.h>
#include <pthread.h>

typedef struct s_data
{
    int             counter;
    pthread_mutex_t mutex;
}   t_data;

void    *increment(void *arg)
{
    t_data  *data = (t_data *)arg;
    int     i;

    i = 0;
    while (i < 10000)
    {
        pthread_mutex_lock(&data->mutex);    // Verrouille
        data->counter++;                     // Section critique
        pthread_mutex_unlock(&data->mutex);  // Déverrouille
        i++;
    }
    return (NULL);
}

int main(void)
{
    t_data      data;
    pthread_t   t1;
    pthread_t   t2;

    data.counter = 0;
    pthread_mutex_init(&data.mutex, NULL);

    pthread_create(&t1, NULL, increment, &data);
    pthread_create(&t2, NULL, increment, &data);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Counter = %d (attendu : 20000)\n", data.counter);

    pthread_mutex_destroy(&data.mutex);
    return (0);
}
```

### Les règles d'or du mutex

1. **Toujours `unlock` après `lock`** — un mutex non libéré bloque tout.
2. **Minimiser le temps passé en section critique** — ne verrouille que ce qui est nécessaire.
3. **Ne jamais appeler une fonction bloquante dans une section critique** — évite les deadlocks.
4. **Un mutex protège UNE ressource** — ne pas réutiliser le même mutex pour des ressources sans rapport.
5. **Toujours gérer les erreurs de retour** — `pthread_mutex_lock` peut échouer.

### `pthread_mutex_trylock` : tenter sans bloquer

```c
int pthread_mutex_trylock(pthread_mutex_t *mutex);
```

Tente de verrouiller le mutex. Si le mutex est déjà pris, retourne immédiatement avec `EBUSY` sans bloquer. Utile pour éviter des situations d'attente potentiellement infinies.

---

## 7. Le deadlock — l'ennemi principal

### Définition

Un **deadlock** (interblocage) est une situation où un ensemble de threads sont **tous bloqués** car chacun attend une ressource détenue par un autre thread du même groupe. Personne ne peut avancer. Le programme est gelé pour toujours.

### Les 4 conditions de Coffman

Pour qu'un deadlock se produise, ces **4 conditions** doivent être simultanément vraies :

1. **Exclusion mutuelle** : une ressource ne peut être utilisée que par un thread à la fois.
2. **Détention et attente** : un thread tient une ressource et attend d'en obtenir une autre.
3. **Non-préemption** : on ne peut pas forcer un thread à libérer une ressource.
4. **Attente circulaire** : Thread A attend B, B attend C, C attend A → cycle.

**Pour éviter le deadlock, il suffit de briser UNE de ces 4 conditions.**

### Exemple classique de deadlock

```c
pthread_mutex_t mutex_A;
pthread_mutex_t mutex_B;

void *thread_1(void *arg)
{
    pthread_mutex_lock(&mutex_A);  // Prend A
    sleep(1);                      // Pause (pour rendre le deadlock reproductible)
    pthread_mutex_lock(&mutex_B);  // Attend B... qui est tenu par thread_2
    // ... code ...
    pthread_mutex_unlock(&mutex_B);
    pthread_mutex_unlock(&mutex_A);
    return NULL;
}

void *thread_2(void *arg)
{
    pthread_mutex_lock(&mutex_B);  // Prend B
    sleep(1);
    pthread_mutex_lock(&mutex_A);  // Attend A... qui est tenu par thread_1
    // DEADLOCK : thread_1 attend B, thread_2 attend A, personne n'avance
    pthread_mutex_unlock(&mutex_A);
    pthread_mutex_unlock(&mutex_B);
    return NULL;
}
```

### Comment éviter le deadlock dans Philosophers

**Solution principale : imposer un ordre d'acquisition des ressources.**

Si tous les threads doivent acquérir les ressources dans le même ordre (ex : toujours prendre la fourchette de plus petit numéro en premier), le cycle d'attente devient impossible.

```
Philosophe pair  : prend d'abord la fourchette gauche, puis droite
Philosophe impair: prend d'abord la fourchette droite, puis gauche
```

Ou encore : imposer que les philosophes de numéro impair attendent un court instant avant de commencer, pour désynchroniser leurs tentatives.

Il existe d'autres stratégies, mais l'idée clé est toujours de **briser l'attente circulaire**.

---

## 8. Le starvation — l'autre ennemi

### Définition

Le **starvation** (famine) se produit quand un thread est perpétuellement privé d'une ressource dont il a besoin, sans qu'il y ait de deadlock. Le système tourne, mais certains threads ne progressent jamais.

Dans Philosophers : un philosophe qui n'arrive jamais à prendre les deux fourchettes parce que ses voisins les prennent toujours avant lui va mourir de faim.

### Différence deadlock vs starvation

| Deadlock | Starvation |
|---|---|
| Tout le monde est bloqué | Le système avance, mais pas tous les threads |
| Aucun progrès global | Des progrès sont faits (juste pas pour la victime) |
| Problème structurel (cycle d'attente) | Problème d'équité (scheduling, priorités) |
| Détectable (le programme se fige) | Plus subtil (un thread meurt lentement) |

### Comment l'éviter dans Philosophers

La clé est de s'assurer qu'aucun philosophe n'attend trop longtemps entre deux repas. Stratégies :

- **Désynchronisation au démarrage** : les philosophes pairs commencent par penser pendant un court délai pour laisser les philosophes impairs manger en premier.
- **Monitoring** : un thread observateur vérifie régulièrement les timestamps du dernier repas de chaque philosophe.
- **Ordre d'acquisition équitable** : garantir qu'aucun philosophe n'est systématiquement défavorisé.

---

## 9. Le temps en C — gettimeofday et usleep

La gestion du temps est **cruciale** dans Philosophers. Tu dois pouvoir mesurer le temps avec une précision à la milliseconde.

### `gettimeofday` — obtenir le temps actuel

```c
#include <sys/time.h>

int gettimeofday(struct timeval *tv, struct timezone *tz);
```

`struct timeval` contient :
```c
struct timeval {
    time_t      tv_sec;   // secondes depuis epoch (1er janvier 1970)
    suseconds_t tv_usec;  // microsecondes (0 à 999999)
};
```

**Obtenir le temps en millisecondes** :

```c
#include <sys/time.h>

long    get_time_ms(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
```

**Usage typique** :
```c
long start = get_time_ms();
// ... faire quelque chose ...
long elapsed = get_time_ms() - start;
printf("Ça a pris %ld ms\n", elapsed);
```

### `usleep` — attendre un certain temps

```c
#include <unistd.h>

int usleep(useconds_t usec); // usec = microsecondes
```

Pour attendre **200 ms** : `usleep(200000)` (200 * 1000 microsecondes).

⚠️ **Attention** : `usleep` n'est pas précis. Le système peut te faire dormir **plus** longtemps que demandé (jamais moins). Sur un système chargé, le surcoût peut être significatif.

### Implémenter un sleep précis

Pour respecter le timing du sujet (`time_to_die` doit être détecté dans les 10 ms), on utilise une boucle d'attente active avec de courts `usleep` :

```c
void    precise_sleep(long duration_ms, t_simulation *sim)
{
    long    start;
    long    elapsed;

    start = get_time_ms();
    while (1)
    {
        if (simulation_is_over(sim)) // Vérifie si la simulation est terminée
            break ;
        elapsed = get_time_ms() - start;
        if (elapsed >= duration_ms)
            break ;
        usleep(500); // Dors 0.5ms, puis vérifie à nouveau
    }
}
```

Cette technique de "polling" permet de réagir rapidement à la fin de la simulation tout en attendant.

### Timestamp au format du sujet

Le sujet demande que chaque message soit préfixé par le **timestamp en ms depuis le début de la simulation** :

```
timestamp_in_ms X is eating
```

Donc tu dois calculer : `temps_actuel_ms - temps_debut_simulation_ms`.

---

## 10. Architecture générale du projet

### Vue d'ensemble des structures

Voici une organisation typique (pas la seule valide, mais une bonne base de réflexion) :

```
t_simulation                    t_philosopher
─────────────────               ─────────────────────────
nb_philosophers                 id (numéro du philosophe)
time_to_die                     nb_meals_eaten
time_to_eat                     last_meal_time
time_to_sleep                   left_fork  ──────► pthread_mutex_t
nb_meals_required               right_fork ──────► pthread_mutex_t
start_time                      thread     ──────► pthread_t
is_over (flag global)           sim        ──────► t_simulation *
mutex_print (pour printf)
mutex_death (pour is_over)
forks[]  ──────────────────► tableau de pthread_mutex_t
philosophers[] ─────────────► tableau de t_philosopher
```

### Le thread de chaque philosophe

Chaque philosophe est un thread qui tourne en boucle :

```
PSEUDOCODE du thread philosophe :

while (simulation pas terminée)
{
    1. Prendre la fourchette gauche   [lock fork_left]
    2. Prendre la fourchette droite   [lock fork_right]
    3. Afficher "X is eating"
    4. Mettre à jour last_meal_time   [protégé par mutex]
    5. Incrémenter nb_meals_eaten     [protégé par mutex]
    6. Dormir time_to_eat ms
    7. Poser les fourchettes          [unlock fork_right, unlock fork_left]
    8. Afficher "X is sleeping"
    9. Dormir time_to_sleep ms
   10. Afficher "X is thinking"
   11. [penser... pas de sleep obligatoire]
}
```

### Le thread de monitoring (death watcher)

Un thread séparé surveille les philosophes :

```
PSEUDOCODE du death watcher :

while (1)
{
    for chaque philosophe i :
    {
        temps_depuis_dernier_repas = temps_actuel - philosophe[i].last_meal_time
        if (temps_depuis_dernier_repas > time_to_die)
        {
            afficher "X died"
            mettre is_over = 1
            return
        }
    }
    if (tous les philosophes ont mangé nb_meals_required fois)
    {
        mettre is_over = 1
        return
    }
    usleep(1000) // Checker toutes les 1ms
}
```

### L'ordre des fourchettes — éviter le deadlock

```c
// Philosophes pairs : gauche d'abord
if (philosophe->id % 2 == 0)
{
    pthread_mutex_lock(philosophe->left_fork);
    pthread_mutex_lock(philosophe->right_fork);
}
// Philosophes impairs : droite d'abord
else
{
    pthread_mutex_lock(philosophe->right_fork);
    pthread_mutex_lock(philosophe->left_fork);
}
```

### Cas du philosophe seul (n = 1)

Si `number_of_philosophers == 1` :
- Il y a une seule fourchette
- Le philosophe ne peut jamais manger (il a besoin de deux fourchettes)
- Il doit mourir après `time_to_die` ms

Gère ce cas spécifiquement : le thread prend sa seule fourchette, attend `time_to_die` ms, et meurt. Le death watcher détecte la mort et affiche le message.

### Affichage thread-safe

Tout `printf` doit être protégé par un mutex pour éviter que deux messages se superposent :

```c
void    print_status(t_philosopher *philo, char *status)
{
    pthread_mutex_lock(&philo->sim->mutex_print);
    if (!philo->sim->is_over) // Ne pas afficher après la mort
        printf("%ld %d %s\n", get_time_ms() - philo->sim->start_time,
               philo->id, status);
    pthread_mutex_unlock(&philo->sim->mutex_print);
}
```

---

## 11. Checklist des erreurs classiques

### ❌ Data races fréquentes

- [ ] Lire/écrire `is_over` sans mutex
- [ ] Lire `last_meal_time` dans le death watcher sans mutex
- [ ] Incrémenter `nb_meals_eaten` sans mutex
- [ ] `printf` sans mutex (affichage entrelacé)

### ❌ Memory leaks

- [ ] Threads non joinés / non détachés
- [ ] Mutex non détruits avec `pthread_mutex_destroy`
- [ ] Malloc sans free en cas d'erreur intermédiaire

### ❌ Timing incorrect

- [ ] Utiliser `time()` (précision à la seconde) au lieu de `gettimeofday` (précision à la microseconde)
- [ ] `usleep(time_to_eat * 1000)` sans vérifier si la simulation est terminée entre-temps
- [ ] Ne pas afficher la mort dans les 10ms (death watcher qui dort trop longtemps)

### ❌ Logique incorrecte

- [ ] Démarrer `last_meal_time` à 0 au lieu de `start_time`
- [ ] Ne pas gérer le cas `nb_philosophers == 1`
- [ ] Ne pas vérifier si la simulation est terminée avant d'afficher un état
- [ ] Afficher "X died" alors que la simulation s'est arrêtée pour une autre raison
- [ ] Continuer à afficher des états après "X died"

### ❌ Deadlocks

- [ ] Tous les philosophes prennent la même fourchette en premier
- [ ] Appel à `pthread_mutex_lock` deux fois sur le même mutex depuis le même thread

### ✅ Bonne pratique

```bash
# Tester les data races
valgrind --tool=helgrind ./philo 5 800 200 200

# Tester les fuites mémoire
valgrind --leak-check=full ./philo 5 800 200 200

# Test de base : personne ne doit mourir
./philo 5 800 200 200

# Test : un philosophe doit mourir
./philo 1 800 200 200

# Test avec nb_repas
./philo 5 800 200 200 7  # doit s'arrêter proprement après 7 repas chacun

# Test timing
./philo 4 410 200 200    # personne ne doit mourir (410 > 200+200)
./philo 4 310 200 200    # quelqu'un doit mourir
```

---

## 12. Sources utilisées et recommandées

### Sources utilisées pour ce cours

- **Wikipedia — Dining philosophers problem** : https://en.wikipedia.org/wiki/Dining_philosophers_problem
- **GeeksForGeeks — Dining Philosopher Problem** : https://www.geeksforgeeks.org/operating-systems/dining-philosophers-problem/
- **ScienceDirect — Dining Philosophers Problem** : https://www.sciencedirect.com/topics/computer-science/dining-philosophers-problem
- **Open Group — pthread_mutex_lock spec** : https://pubs.opengroup.org/onlinepubs/009604499/functions/pthread_mutex_lock.html
- **codequoi.com — Threads, Mutexes and Concurrent Programming in C** : https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/
- **Dartmouth CS — POSIX Thread Programming** : https://www.cs.dartmouth.edu/~campbell/cs50/threads.html
- **Villanova University — Synchronizing Threads with Mutexes** : http://www.csc.villanova.edu/~mdamian/threads/posixmutex.html
- **Oracle Docs — Mutex Lock Code Examples** : https://docs.oracle.com/cd/E19455-01/806-5257/sync-12/index.html

### Sources fortement recommandées à lire

#### Pour les threads et mutex en C :

1. **codequoi.com — Threads, Mutexes and Concurrent Programming in C** ⭐⭐⭐⭐⭐
   - https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/
   - **Spécialement écrit pour 42**, exemples en C, très clair.

2. **LLNL — POSIX Threads Programming (Blaise Barney)** ⭐⭐⭐⭐⭐
   - https://hpc-tutorials.llnl.gov/posix/
   - La référence absolue sur pthreads. Exhaustif et rigoureux.

3. **man pages** ⭐⭐⭐⭐⭐
   ```bash
   man pthread_create
   man pthread_mutex_init
   man gettimeofday
   man usleep
   ```
   Les pages de manuel sont la référence officielle.

#### Pour comprendre la concurrence :

4. **UMass — Dining Philosophers & Deadlocks** ⭐⭐⭐⭐
   - https://lass.cs.umass.edu/~shenoy/courses/fall13/lectures/Lec10_notes.pdf
   - PDF académique clair sur les deadlocks et les 4 conditions de Coffman.

5. **JMU — Computer Systems Fundamentals (Chapter 8.5)** ⭐⭐⭐⭐
   - https://w3.cs.jmu.edu/kirkpams/OpenCSF/Books/csf/html/DiningPhil.html
   - Excellent chapitre sur les Dining Philosophers avec explications et code.

#### Vidéos YouTube recommandées :

6. **"Dining Philosophers Problem" — Neso Academy** sur YouTube
   - Chercher : `Neso Academy Dining Philosophers Problem`
   - Explication visuelle animée, très pédagogique.

7. **"Unix Threads in C" — CodeVault** sur YouTube
   - Chercher : `CodeVault pthreads C`
   - Série complète sur pthreads en C, exemples concrets.

#### Pour les étudiants 42 :

8. **42Docs / forums 42** : https://harm-smits.github.io/42docs/projects/philosophers
   - Notes et conseils d'anciens étudiants.

---

## Glossaire rapide

| Terme | Définition |
|---|---|
| **Thread** | Fil d'exécution au sein d'un processus |
| **Mutex** | Verrou d'exclusion mutuelle pour protéger une section critique |
| **Section critique** | Portion de code accédant à une ressource partagée |
| **Data race** | Accès concurrent non synchronisé à une variable partagée |
| **Deadlock** | Blocage circulaire : tout le monde attend tout le monde |
| **Starvation** | Un thread ne reçoit jamais les ressources dont il a besoin |
| **Livelock** | Les threads s'activent mais ne progressent pas (cas particulier) |
| **Atomique** | Opération indivisible, ne peut pas être interrompue à mi-chemin |
| **Concurrence** | Plusieurs tâches semblent s'exécuter simultanément |
| **Parallélisme** | Plusieurs tâches s'exécutent vraiment en même temps (multi-cœurs) |
| **Scheduler** | Composant de l'OS qui décide quel thread s'exécute à quel moment |
| **pthread_t** | Type représentant l'identifiant d'un thread POSIX |
| **pthread_mutex_t** | Type représentant un mutex POSIX |
| **POSIX** | Standard définissant les interfaces pour les systèmes Unix/Linux |

---

*Bonne chance pour ton projet Philosophers ! N'oublie pas : la clé est de comprendre chaque ligne de ton code, pas juste de le faire compiler.* 🧠
