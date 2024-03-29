# Brainfuck Interpreter in C

This is a Brainfuck language interpreter written in C. It allows you to execute Brainfuck programs and see the output.

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [Testing](#testing)
- [Logic](#logic)

## Installation

To compile the Brainfuck interpreter, you need to have a C compiler installed on your system. You can use the provided Makefile to build the interpreter.

1. Clone the repository:

    ```bash
    git clone https://github.com/your-username/brainfuck-interpreter-in-c.git
    ```

2. Navigate to the project directory:

    ```bash
    cd brainfuck-interpreter-in-c
    ```

3. Build the interpreter using the Makefile:

    ```bash
    make
    ```

## Usage

Once you have built the interpreter, you can run Brainfuck programs using the following command:

```bash
./brainfuck your_program.bf
```

## Testing

Once you have built the interpreter, you can run the unit tests to ensure everything is working as expected. The unit tests are written to test the functionality of the Brainfuck interpreter.

To run the unit tests, use the following command:

```bash
make test
```

Other wise, the test folder is full of fun small programs to test, do not hesitate to check it !

## Logic

The Brainfuck interpreter works by reading Brainfuck programs, which are text files containing Brainfuck commands. Each command is a single character:

- `>`: increment the data pointer
- `<`: decrement the data pointer
- `+`: increment the byte at the data pointer
- `-`: decrement the byte at the data pointer
- `.`: output the byte at the data pointer
- `,`: accept one byte of input, storing its value in the byte at the data pointer
- `[`: if the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching `]` command
- `]`: if the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching `[` command

The interpreter reads these commands and performs the corresponding operations on an array of bytes, which is initialized to zero at the start of the program. The 'data pointer' mentioned above is an index into this array.

