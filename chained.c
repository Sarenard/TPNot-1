#include <stdio.h>
#include <stdlib.h>

typedef struct maillon_t {
    int content;
    void* suivant;
} maillon_t;

typedef struct list_t {
    maillon_t* maillon; // HEAD
} list_t;

void print_list(list_t liste) {
    printf("Print of list : ");
    maillon_t* maillon = liste.maillon;
    while (maillon->suivant != NULL) {
        maillon = (maillon_t*) maillon->suivant;
        printf("%d ", maillon->content);
    }
    printf("\n");
}

list_t list_create() {
    maillon_t* start_maillon = malloc(sizeof(maillon_t));
    // 42 shouldnt ever be read
    start_maillon->content = 42;
    start_maillon->suivant = NULL;
    list_t empty_list = {
        .maillon = start_maillon
    };

    return empty_list;
}

// on renvoie un int étant (position + 1) ou 0 représentant false
// gratuit en temps mais permet d'avoir + d'infos
int list_contains(list_t l, int el) {
    maillon_t* maillon = l.maillon;
    while (maillon->suivant != NULL) {
        maillon = (maillon_t*) maillon->suivant;
        if (maillon->content == el) {
            return true;
        }
    }
    return false;
}

list_t list_add(list_t l, int el) {
    // si on est déja dedans (la liste représente un ensemble, on skip)
    if (list_contains(l, el)) {
        return l;
    }

    // 
    maillon_t* maillon = l.maillon;
    while (maillon->suivant != NULL && ((maillon_t*) maillon->suivant)->content < el) {
        maillon = (maillon_t*) maillon->suivant;
    }
    maillon_t* new_maillon = malloc(sizeof(maillon));
    new_maillon->content = el;
    new_maillon->suivant = NULL;
    if (maillon->suivant == NULL) {
        // si on est a la fin
        maillon->suivant = new_maillon;
    } else {
        // sinon, on rajoute à l'endroit où on est et on fait passer les pointeurs
        new_maillon->suivant = maillon->suivant;
        maillon->suivant = new_maillon;
    }

    return l;
}

list_t list_remove(list_t l, int el) {
    maillon_t* maillon = l.maillon;
    while (maillon->suivant != NULL) {
        maillon_t* prochain = (maillon_t*) maillon->suivant;
        if (prochain->content == el) {
            // on a trouvé l'élément, et on fait le changement
            // ensuite, on return (l'élément ne peut être présent qu'une seule fois)
            maillon->suivant = prochain->suivant;
            free(prochain);
        }
        maillon = (maillon_t*) maillon->suivant;
    }
    return l;
}

void maillon_free(maillon_t* maillon) {
    maillon_t* maillon_suivant = maillon->suivant;
    
    if (maillon_suivant->suivant == NULL) {
        free(maillon);
    } else {
        maillon_free(maillon_suivant);
        free(maillon);
    }
}

// ne pas utiliser l après
void list_free(list_t l) {
    maillon_free(l.maillon);
}

int main(int argc, char** argv) {
    printf("Exercice 2 : liste chainée !\n");

    list_t liste = list_create();
    print_list(liste);

    printf("contains 3 : %s\n", list_contains(liste, 3) ? "true" : "false");

    liste = list_add(liste, 0);
    liste = list_add(liste, 9);
    liste = list_add(liste, 5);
    liste = list_add(liste, 4);
    liste = list_add(liste, 3);
    print_list(liste);

    printf("contains 3 : %s\n", list_contains(liste, 3) ? "true" : "false");

    liste = list_remove(liste, 3);
    print_list(liste);

    printf("contains 3 : %s\n", list_contains(liste, 3) ? "true" : "false");

    list_free(liste);

}