#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

#define HMAX 3


// @content : l'entier contenu
// @niveaux -> la liste des pointeurs
// @hauteur -> le nombre de pointeurs (la hauteur du maillon)
typedef struct maillon_t {
    int content;
    void* niveaux[HMAX];
    int hauteur;
} maillon_t;

typedef struct skiplist_t {
    maillon_t* maillon; // HEAD
} skiplist_t;

skiplist_t skiplist_create() {
    maillon_t* maillon = malloc(sizeof(maillon_t));
    // should not ever be read
    maillon->content = 42;
    maillon->hauteur = HMAX;
    for (int i = 0; i < HMAX; i++) {
        maillon->niveaux[i] = 0;
    }
    
    skiplist_t skiplist_vide = {
        .maillon = maillon
    };

    return skiplist_vide;
}

// TODO
bool skiplist_contains(skiplist_t l, int el) {
    return false;
}

// hauteur du nouveau maillon
int get_random_hauteur() {
    int result = 0;
    while (rand()%2) {
        result++;
    }
    return MIN(result, HMAX-1);
}

// TODO
skiplist_t skiplist_add(skiplist_t l, int el) {

}

// TODO
skiplist_t skiplist_remove(skiplist_t l, int el) {

}

// aux of skiplist_free
void maillon_free(maillon_t* maillon) {
    maillon_t* maillon_suivant = maillon->niveaux[0];
    if (maillon_suivant->niveaux[0] == NULL) {
        free(maillon);
    } else {
        maillon_free(maillon_suivant);
        free(maillon);
    }
}

// il ne faut pas utiliser l après
void skiplist_free(skiplist_t l) {
    // on va passer sur chacun des maillons dans l'ordre en regardant le pointeur du bas
    // (linéaire mais de toute façon on doit tout free)
    // en libérant au passage
    maillon_free(l.maillon);
}

int main(int argc, char** argv) {
    printf("Exercice 3 : Skiplist !\n");
    
    // init of random
    srand(time(NULL));

    printf("5 bits aléatoires : %d %d %d %d %d\n", rand()%2, rand()%2, rand()%2, rand()%2, rand()%2);

    skiplist_t skiplist = skiplist_create();

    printf("Contains 3 : %d\n", skiplist_contains(skiplist, 3));

    int* results = malloc(20 * sizeof(int));

    for (int i = 0; i < 20; i++) {
        results[i] = get_random_hauteur();
    }

    printf("Resultats get_hauteur : ");
    for (int i = 0; i < 20; i++) {
        printf("%d ", results[i]);
    }
    printf("\n");


}