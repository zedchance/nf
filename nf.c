/*
 * nf is a brainfuck clone that uses integers instead of
 * chars on its tape
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    // tape and head
    int tape[30000] = {0};
    int * head = &tape[0];

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }

    FILE * file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Can't open %s for reading\n", argv[1]);
    }

    // read file char by char
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        switch(c)
        {
            case '+':
                ++*head;
                break;
            case '-':
                --*head;
                break;
            case '>':
                ++head;
                break;
            case '<':
                --head;
                break;
            case '[':
                break;
            case ']':
                break;
            case ',':
                scanf("%d", head);
                break;
            case '.':
                printf("%d", *head);
                break;
            default:
                // skip any other char
                break;
        }
    }
}
