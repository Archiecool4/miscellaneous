/**
 * This program is an interpreter for the esoteric language 
 * Brainfuck. Brainfuck is of particular interest because it
 * is about the simplest model of a Turing machine you can
 * have.
 * (C) 2020 Archie Shahidullah
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 30000

/**
 * Reads and executes operators from a bf program.
 * 
 * @param prog the file that contains the program
 * @param ptr the data pointer
 */
void evaluate(FILE *prog, char *ptr) {
    char op;
    while (1) {
        // Get next operator
        fread(&op, 1, 1, prog);
        if (feof(prog)) {
            // End of program
            return;
        }
        // Evaluate different operators
        switch (op) {
            case '<':
                --ptr;
                break;
            case '>':
                ++ptr;
                break;
            case '-':
                --*ptr;
                break;
            case '+':
                ++*ptr;
                break;
            case '.':
                putchar(*ptr);
                break;
            case ',':
                *ptr = getchar();
                break;
            case '[':
                if (*ptr == 0) {
                    // Deal with nested loops
                    int loop = 1;
                    while (loop != 0) {
                        fread(&op, 1, 1, prog);
                        if (op == '[') {
                            loop++;
                        }
                        else if (op == ']') {
                            loop--;
                        }
                    }
                }
                break;
            case ']':
                if (*ptr != 0) {
                    int loop = 1;
                    while (loop != 0) {
                        // Backtrack by 2 to so next read gets previous char
                        fseek(prog, -2, SEEK_CUR);
                        fread(&op, 1, 1, prog);
                        if (op == ']') {
                            loop++;
                        }
                        else if (op == '[') {
                            loop--;
                        }
                    }
                }
                break;
            case ' ':
            case '\n':
            case '\r':
                // "Whitespace" chars
                break;
            default:
                fprintf(stderr, "Error! Invalid Operator: %c!\n", op);
                exit(1);
        }
    }
}

int main(int argc, char *argv[]) {
    // Check arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }
    if (!strstr(argv[1], ".bf")) {
        fprintf(stderr, "Error! %s is not a .bf program!\n", argv[1]);
        exit(1);
    }

    // Set up tape of default size
    char tape[SIZE] = {0};
    // Data pointer
    char *ptr = tape;
    // Open program
    FILE *prog = fopen(argv[1], "r");
    if (prog) {
        // Evaluate program
        evaluate(prog, tape);
        fclose(prog);
    }
    else {
        fputs("Error! File cannot be opened!\n", stderr);
        exit(1);
    }

    return 0;
}
