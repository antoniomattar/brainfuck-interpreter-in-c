#include <criterion/criterion.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "brainfuck_helper.h"


Test(get_input_prog, test_file_exists)
{
    char* input_filename = "test_input.txt";
    char* expected_output = "Hello, World!";
    FILE* file = fopen(input_filename, "w");
    fprintf(file, "%s", expected_output);
    fclose(file);

    char* result = get_input_prog(input_filename);

    cr_assert_str_eq(result, expected_output);

    free_input_prog(result);
    remove(input_filename);
}

Test(get_input_prog, test_file_not_exists)
{

    char *input_filename = "nonexistent_file.txt";

    char* result = get_input_prog(input_filename);

    cr_assert_null(result);
}

Test(count_loops, test_valid_loops)
{
    char* input_prog = "[[[ ]]]";
    int result = count_loops(input_prog);
    cr_assert_eq(result, 3);

    input_prog = "[[[[[[[[[[[[[]]]]]]]]]]]]]";
    result = count_loops(input_prog);
    cr_assert_eq(result, 13);
}

Test(count_loops, test_no_loops)
{
    char* input_prog = "++++++++";

    int result = count_loops(input_prog);

    cr_assert_eq(result, 0);
}

Test(stack_init, test_stack_init){
    Stack* stack = stack_init(5);

    cr_assert_eq(stack->size, 0);
    cr_assert_not_null(stack->indexes);
    cr_assert_eq(stack->capacity, 5);

    free(stack->indexes);
    free(stack);
}

Test(stack_push, test_stack_push){
    Stack* stack = stack_init(5);
    char* index = "test";

    stack_push(stack, index);

    cr_assert_eq(stack->size, 1);
    cr_assert_str_eq(stack->indexes[0], index);

    free(stack->indexes);
    free(stack);
}

Test(stack_pop, test_stack_pop){
    Stack* stack = stack_init(5);
    char* index = "test";

    stack_push(stack, index);

    char* result = stack_pop(stack);

    cr_assert_eq(stack->size, 0);
    cr_assert_str_eq(result, index);

    free(stack->indexes);
    free(stack);
}

Test(build_loops, test_valid_input)
{
    char* input_prog = "[[[.]]]";

    void* result = build_loops(input_prog);

    // Cast the result back to Tuple array 
    struct Tuple* loops = (struct Tuple*)result;

    cr_assert_not_null(result);

    cr_assert_eq(loops[0].start_index, input_prog + 2);
    cr_assert_eq(loops[0].end_index, input_prog + 4);

    cr_assert_eq(loops[1].start_index, input_prog + 1);
    cr_assert_eq(loops[1].end_index, input_prog + 5);

    cr_assert_eq(loops[2].start_index, input_prog);
    cr_assert_eq(loops[2].end_index, input_prog + 6);

    free_loops(result);
}

Test(execute_instruction, test_valid_input)
{
    char* input_prog = "[[[]]]";
    uint8_t data = 0;
    void* loops = build_loops(input_prog);

    char* ipp = input_prog;
    uint8_t* dpp = &data;

    execute_instruction(&ipp, &dpp, loops);

    cr_assert_eq(data, 0);

    free_loops(loops);

}