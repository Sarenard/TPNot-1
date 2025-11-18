#include <stdio.h>
#include <stdlib.h>

typedef struct dynarray_t {
    int size;
    int capacity;
    int* content;
} dynarray_t;

dynarray_t dynarray_create() {
    dynarray_t empty_tab = {.size = 0, .capacity = 0, .content = NULL};

    return empty_tab;
}

void print_dynarray(dynarray_t a) {
    printf("Print of array (size %d)", a.size);
    if (a.size > 0) {
        printf(" : ");
    }
    for (int i = 0; i < a.size; i++) {
        printf("%d ", a.content[i]);
    }
    printf("\n");
}

// on renvoie un int étant (position + 1) ou 0 représentant false
// gratuit en temps mais permet d'avoir + d'infos
int dynarray_contains(dynarray_t a, int el) {
    for (int i = 0; i < a.size; i++) {
        if (a.content[i] == el) {
            return i + 1;
        }
    }
    return 0;
}

dynarray_t dynarray_add(dynarray_t a, int el) {
    // si on est déja dedans (le tableau représente un ensemble, on skip)
    if (dynarray_contains(a, el)) {
        return a;
    }

    // si le tableau est vide
    if (a.capacity == 0) {
        a.capacity = 4;
        a.content = calloc(4, sizeof(int));
    }

    // si on a plus de place
    if (a.capacity == a.size) {
        a.capacity *= 2;
        a.content = realloc(a.content, a.capacity);
    }

    // on rajoute l'élément à la fin
    // on est garanti d'avoir la place
    a.content[a.size] = el;
    a.size++;

    return a;
}

dynarray_t dynarray_remove(dynarray_t a, int el) {
    int position = dynarray_contains(a, el);
    
    // si on ne contient pas l'élément
    if (position == 0) {
        return a;
    }
    // sinon, on est garanti par le sujet qu'il n'apparaisse qu'une seule fois
    // on a juste à décaler d'un et à réduire la size de 1
    for (int i = position - 1; i < a.size; i++) {
        a.content[i] = a.content[i+1];
    }
    a.size--;

    return a;
}

// ne pas utiliser a après
void dynarray_free(dynarray_t a) {
    // on free les pointeurs de a
    free(a.content);
    a.size = 0;
    a.capacity = 0;
}

int main(int argc, char** argv) {
    printf("Exercice 1 : tableau dynamique !\n");

    printf("Attention, les résultats de dynarray_contains peuvent être contrintuitifs\n");
    printf("Il faut lire la documentation de la fonction\n");

    dynarray_t array = dynarray_create();
    print_dynarray(array);

    printf("Contiens 3 : %d\n", dynarray_contains(array, 3));

    array = dynarray_add(array, 0);
    array = dynarray_add(array, 3);
    array = dynarray_add(array, 4);
    array = dynarray_add(array, 5);
    array = dynarray_add(array, 5);
    array = dynarray_add(array, 9);
    print_dynarray(array);
    
    printf("Contiens 3 : %d\n", dynarray_contains(array, 3));
    array = dynarray_remove(array, 3);
    print_dynarray(array);

    dynarray_free(array);
}