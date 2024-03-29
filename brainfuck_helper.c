#include "brainfuck_helper.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

char* get_input_prog(char* input_filename) {
    // on utilise la fonction fopen pr avoir un pointeur vers une variable de type FILE
    FILE* file = fopen(input_filename, "rb");

    if (file == NULL) {
        fprintf(stderr, "Le fichier '%s' n'existe probablement pas!\n", input_filename);
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

Stack* stack_init(int capacity) {
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    stack->indexes = (char**) calloc(capacity, sizeof(char*));
    stack->size = 0;
    stack->capacity = capacity;
    return stack;
}

void stack_push(struct Stack* stack, char* index) {
    if (stack->size == stack->capacity) {
        return;
    }
    stack->indexes[stack->size] = index;
    stack->size++;
}

char* stack_pop(struct Stack* stack) {
    if (stack->size == 0) {
        return NULL;
    }
    stack->size--;
    return stack->indexes[stack->size];
}

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

    struct Stack* stack = stack_init(loops_count);

    struct Tuple* loops = (struct Tuple*) malloc(loops_count * sizeof(struct Tuple));

    struct Tuple* current_loop = loops;

    while (*input_prog != '\0') {
        if (*input_prog == '[') {
            stack_push(stack, input_prog);
        } else if (*input_prog == ']') {
            char* start_index = stack_pop(stack);
            char* end_index = input_prog;
            current_loop->start_index = start_index;
            current_loop->end_index = end_index;
            current_loop++;
        }
        input_prog++;
    }

    free(stack->indexes);
    free(stack);

    return (void*) loops;
}

void free_loops(void* loops) {
    free(loops);
    return;
}

void execute_instruction(char** ipp, uint8_t** dpp, void* loops) {  
    // on cast les void* en struct Tuple*
    struct Tuple* couples = (struct Tuple*) loops;
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
            if (**dpp == 0) {
                while (couples->start_index != *ipp) {
                    couples++;
                }
                *ipp = couples->end_index;
            }
            break;
        case ']':
            if (**dpp != 0) {
                while (couples->end_index != *ipp) {
                    couples++;
                }
                *ipp = couples->start_index;
            }
            break;
        default:
            break;
    }
    (*ipp)++;
}
