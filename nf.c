/*
 * nf is a brainfuck clone that uses integers instead of
 * chars on its tape
 */

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

// tape and head
int tape[30000] = {0};
int * head = &tape[0];

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
        int loop_start;
        int loop_end;
        switch(source[i])
        {
            case '[':
                loop_start = i + 1;
                for (int j = loop_start; j < end; j++)
                {
                    if (source[j] == ']')
                    {
                        loop_end = j - 1;
                        break;
                    }
                }
                while (*head)
                {
                    interpret(source, loop_start, loop_end);
                }
                i = loop_end + 1;
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
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    // check that its a .nf file
    if (strstr(argv[1], ".nf") == NULL)
    {
        printf("Not a .nf file\n");
        return 1;
    }

    // open file
    FILE * file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Can't open %s for reading\n", argv[1]);
        return 1;
    }

    // get file size
    struct stat st;
    int file_size = 0;
    if (stat(argv[1], &st) == 0)
    {
        file_size = st.st_size;
    }

    // read in file
    char source[file_size];
    fread(source, 1, file_size, file);

    // interpret the file
    interpret(source, 0, file_size);
}

