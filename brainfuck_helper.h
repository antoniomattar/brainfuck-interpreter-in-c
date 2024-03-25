#include <stdlib.h>
#include <stdint.h>

#define DATA_ARRAY_SIZE 32000

/**
 * @brief Récupère le programme Brainfuck à interpréter depuis un fichier
 *
 * @param input_filename le nom du fichier Brainfuck à récupérer
 * @return un tableau de caractère terminé par le caractère '\0' ou NULL si input_filename
 *         n'existe pas dans le répertoire courant
 */
char* get_input_prog(char* input_filename);

/**
 * @brief Libère ce qui a été alloué par get_input_prog.
 *
 * @param loops
 */
void free_input_prog(char* input_prog);

/**
 * @brief Analyse le programme Brainfuck passé en paramètre pour construire "quelque chose"
 *        qui représente les boucles du programme. Ce "quelque chose" sera ensuite utilisé
 *        lors de l'exécution des instructions, cf 'execute_instruction'.
 *        C'est à vous de décider ce que sera "quelque chose".
 *
 * @param input_prog le programme BrainFuck à analyser
 * @return "quelque chose" qui représente les boucles du programme
 */
void* build_loops(char* input_prog);

/**
 * @brief Libère ce qui a été alloué par build_loops.
 *
 * @param loops
 */
void free_loops(void* loops);

/**
 * @brief Exécute l'instruction pointée par le pointeur pointé par ipp,
 *........et incrémente ce pointeur.
 *
 * @param ipp un pointeur vers le pointeur d'instructions
 * @param dpp un pointeur vers le pointeur de données
 * @param loops le "quelque chose" représentant les boucles, cf 'build_loops'.
 */
void execute_instruction(char** ipp, uint8_t** dpp, void* loops);
