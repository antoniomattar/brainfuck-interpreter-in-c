#include "brainfuck_helper.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

char* get_input_prog(char* input_filename) {
    // on utilise la fonction fopen pr avoir un pointeur vers une variable de type FILE
    FILE* file = fopen(input_filename, "rb");

    if (file == NULL) {
        printf("Le fichier n'existe probablement pas!");
        return NULL;
    }

    // on parcours jusqu a la fin du fichier
    fseek(file, 0, SEEK_END);

    // on appelle la fonction ftell qui nous donne la position du byte sur lequel on se situe (ici c'est bien le dernier)
    long file_size = ftell(file);

    // apres avoir recup la taille on reviens au premier byte 
    rewind(file);

    // on alloue en memoire la taille necessaire pr stocker les char du fichier
    char* buffer = (char*) calloc(file_size + 1, sizeof(char));

    if (buffer == NULL) {
        printf("Le systeme n'a pas pus allouer totalement la memoire necessaire pour lire le code");
        fclose(file);
        return NULL;
    }

    // on lit le fichier et on stocke les char dans le buffer
    int bytesRead = fread(buffer, sizeof(uint8_t), file_size, file);

    if (bytesRead != file_size) {
        printf("Le systeme n'a pas pus lire totalement le fichier");
        fclose(file);
        free(buffer);
        return NULL;
    }

    // on ajoute le backslash 0 a la fin du buffer
    buffer[file_size] = '\0';

    fclose(file);

    return buffer;

    
}

void free_input_prog(char* input_prog) {
    free(input_prog);
}

// on cree une structure de donne Tuple qui contiendra les indices de debut et de fin de chaque boucle
typedef struct Tuple {
    int start_index;
    int end_index;
} Tuple;

int count_loops(char* input_org) {
    // on suppose que le code est bien ecrit et bien paranthesé
    int count = 0;
    while (*input_org != '\0') {
        if (*input_org == '[') {
            count++;
        }
        input_org++;
    }
    return count;
}

void* build_loops(char* input_prog) {

    int loops_count = count_loops(input_prog);
    
    // on alloue en memoire la taille necessaire pr stocker les tuples d'indices
    Tuple* loops = (Tuple*) calloc(loops_count, sizeof(Tuple));

    if (loops == NULL) {
        printf("Le systeme n'a pas pus allouer totalement la memoire necessaire pour stocker les boucles");
        return NULL;
    }

    // on utilise une pile pr stocker les indices de debut de boucle et on les depile lorsqu'on trouve le bon indice de fin
    // tout en creant les tuples
    int* stack = (int*) calloc(loops_count, sizeof(int));
    int stack_size = 0;
    int index = 0;
    
    while (*input_prog != '\0') {

        if (*input_prog == '[') {
            stack[stack_size] = index;
            stack_size++;
        } else if (*input_prog == ']') {
            stack_size--;
            loops[stack_size].start_index = stack[stack_size];
            loops[stack_size].end_index = index;
            printf("start: %d, end: %d\n", loops[stack_size].start_index, loops[stack_size].end_index);
        }

        index++;
        input_prog++;
    }

    return (void *) loops;
}

void free_loops(void* loops) {
    free(loops);
    return;
}

void execute_instruction(char** ipp, uint8_t** dpp, void* loops) {
    // recast loops vers Tuple
    struct Tuple* loops = (struct Tuple*) loops;
    switch (**ipp)
    {
        case '>':
            (*dpp)++;
            break;
        case '<':
            (*dpp)--;
            break;
        case '+':
            (**dpp)++;
            break;
        case '-':
            (**dpp)--;
            break;
        case '.':
            putchar(**dpp);
            break;
        case ',':
            **dpp = getchar();
            break;
        case '[':
            break;
        case ']':
            break;
        default:
            break;
    }
    (*ipp)++;
}
