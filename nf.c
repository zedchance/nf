/*
 * nf is a brainfuck clone that uses integers instead of
 * chars on its tape
 */

#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char ** argv)
{
    // usage
    if (argc < 2)
    {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    // tape and head
    int tape[30000] = {0};
    int * head = &tape[0];

    // open file
    FILE * file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Can't open %s for reading\n", argv[1]);
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

    // parse source char by char
    for (int i = 0; i < file_size; i++)
    {
        printf("%c", source[i]);
        switch(source[i])
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
                break;
            case '.':
                printf("%d", *head);
                break;
            case '[':
                break;
            case ']':
                break;
            default:
                // skip any other char
                break;
        }
    }
}

