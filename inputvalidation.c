#include "hash.h"

int inputvalidation(int argc, char *argv[], node_t **head)
{
    for (int i = 1; i < argc; i++) // check each command line file
    {
        int j = 0;

        for (j = 0; argv[i][j]; j++) // find dot in file name
        {
            if (argv[i][j] == '.')
            {
                break; // stop at dot
            }
        }

        if (strcmp(argv[i] + j, ".txt") != 0) // allow only .txt files
        {
            continue; // skip if not txt
        }

        FILE *fd = fopen(argv[i], "r"); // open file in read mode
        if (fd == NULL)
        {
            continue; // skip if cannot open
        }

        char c = getc(fd); // read first character
        if (c == EOF)
        {
            fclose(fd); // close empty file
            continue; // skip empty file
        }

        fclose(fd); // close file after checking

        node_t *temp = *head; // start from head
        int flag = 0; // duplicate check flag

        while (temp) // check if file already added
        {
            if (strcmp(temp->str, argv[i]) == 0) // compare file names
            {
                flag = 1; // duplicate found
                break;
            }
            temp = temp->link; // move to next node
        }

        if (flag == 1)
        {
            continue; // skip duplicate file
        }

        if (*head == NULL) // if list empty
        {
            node_t *new = malloc(sizeof(node_t)); // create new node
            strcpy(new->str, argv[i]); // copy file name
            new->link = NULL; // set link NULL
            *head = new; // assign head
        }
        else
        {
            temp = *head; // go to head

            while (temp->link != NULL) // go to last node
            {
                temp = temp->link;
            }

            node_t *new = malloc(sizeof(node_t)); // create new node
            strcpy(new->str, argv[i]); // copy file name
            new->link = NULL; // set link NULL
            temp->link = new; // attach at end
        }
    }

    return SUCCESS; // return success
}