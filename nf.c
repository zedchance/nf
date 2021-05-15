/*
 * nf is a brainfuck clone that uses integers instead of
 * chars on its tape
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// #define DEBUG

// tape and head
int tape[30000] = {0};
int * head = &tape[0];

void print_debug(char * source, int index)
{
    fprintf(stderr, " symbol: %c\n", source[index]);
    fprintf(stderr, "   tape: ");
    for (int i = 0; i < 10; i++)
    {
        fprintf(stderr, "%-8d ", tape[i]);
    }
    fprintf(stderr, "\n");
    fprintf(stderr, "pointer: ");
    int pad = (head - tape) * 9;
    for (int i = 0; i < pad; i++)
    {
        fprintf(stderr, " ");
    }
    fprintf(stderr, "^\n\n");
}

void parse(char c)
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
        case ',':
            scanf("%d", head);
            fflush(stdin);
            break;
        case '.':
            printf("%d", *head);
            break;
        default:
            // skip any other char
            break;
    }
}

void interpret(char * source, int start, int end)
{
    for (int i = start; i < end; i++)
    {
#ifdef DEBUG
        print_debug(source, i);
#endif
        int loop_start;
        int loop_end;
        int loop_balance;
        switch(source[i])
        {
            case '[':
                // find the end of the loop
                loop_balance = 1;
                loop_start = i + 1;
                for (int j = loop_start; j < end; j++)
                {
                    if (source[j] == '[') loop_balance++;
                    if (source[j] == ']') loop_balance--;
                    if (loop_balance == 0)
                    {
                        loop_end = j;
                        break;
                    }
                }

                // interpret the loop
                while (*head)
                {
                    interpret(source, loop_start, loop_end);
                }

                // jump to end
                i = loop_end;
                break;
            default:
                parse(source[i]);
                break;
        }
    }
}

int main(int argc, char ** argv)
{
    // usage
    if (argc < 2)
    {
        printf("Usage: %s filename\n",  argv[0]);
        printf("       %s -e \'expression\'\n", argv[0]);
        return 1;
    }

    // source
    int source_length = 0;
    char * source = malloc(source_length);

    // get expression off command line
    if (strcmp(argv[1], "-e") == 0)
    {
        source = argv[2];
        source_length = strlen(source);
    }
    else
    {
        // open file
        FILE * file = fopen(argv[1], "r");
        if (!file)
        {
            printf("Can't open %s for reading\n", argv[1]);
            return 1;
        }

        // get file size
        struct stat st;
        if (stat(argv[1], &st) == 0)
        {
            source_length = st.st_size;
        }

        // read in file
        source = realloc(source, sizeof(char *) * source_length);
        fread(source, 1, source_length, file);
    }

    // interpret the source
    interpret(source, 0, source_length);
}

