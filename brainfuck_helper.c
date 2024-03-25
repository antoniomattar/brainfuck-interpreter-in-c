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
    char* buffer = (char*) calloc(file_size + 1, sizeof(uint8_t));

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

void* build_loops(char* input_prog) {
    return NULL;
}

void free_loops(void* loops) {
    return;
}

void execute_instruction(char** ipp, uint8_t** dpp, void* loops) {
    return;
}
