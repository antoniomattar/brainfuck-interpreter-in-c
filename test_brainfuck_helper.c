/*
    Module de test de ldc.c utilisant la bibliothèque Criterion.

    Ces tests utilisent deux macros :
    - cr_assert(cond) qui arrête le programme si cond est fausse ;
    - cr_expect(cond) qui indique que le test courant a échoué si cond est fausse.

    ATTENTION :
    Ces détails sont donnés à titre d'information, on ne s'attend pas à ce que vous
    complétiez ce fichier. Néanmoins, si vous souhaitez rajouter vos propres tests,
    n'hésitez pas surtout pas !
*/

#include <stdlib.h>
#include <stdint.h>
#include <criterion/criterion.h>

#include "brainfuck_helper.h"

