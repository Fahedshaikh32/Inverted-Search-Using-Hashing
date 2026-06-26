#include "hash.h"

int validation(hash_t *arr, char *name, char *filename, int i)
{
    main_t *temp = arr[i].link; // get main list at hash index

    while (temp) // traverse main list
    {
        if (strcmp(temp->str, name) == 0) // check if word already exists
        {
            sub_t *temp1 = temp->sublink; // get sub list

            while (temp1) // traverse sub list
            {
                if (strcmp(temp1->file, filename) == 0) // check if file already exists
                {
                    temp1->w_count++; // increase word count
                    return 1; // word updated
                }
                temp1 = temp1->sub_link; // move to next sub node
            }

            temp->count++; // increase file count

            sub_t *new1 = malloc(sizeof(sub_t)); // create new sub node
            if (new1 == NULL)
            {
                return FAILURE; // memory fail
            }

            new1->file = malloc(sizeof(char) * 100); // allocate memory for file name
            if (new1->file == NULL)
            {
                free(new1); // free memory
                return FAILURE;
            }

            strcpy(new1->file, filename); // copy file name
            new1->w_count = 1; // set word count
            new1->sub_link = NULL; // set link to NULL

            sub_t *temp2 = temp->sublink; // get first sub node

            if (temp2 == NULL) // if no sub node
            {
                temp->sublink = new1; // attach new sub node
                return 1;
            }
            else
            {
                while (temp2->sub_link != NULL) // go to last sub node
                {
                    temp2 = temp2->sub_link;
                }

                temp2->sub_link = new1; // attach new sub node at end
                return 1;
            }
        }

        temp = temp->mainlink; // move to next main node
    }

    return 0; // word not found
}

int openfile(hash_t *arr, char *filename)
{
    FILE *fp = fopen(filename, "r"); // open file in read mode
    if (fp == NULL)
    {
        return FAILURE; // file open failed
    }

    char write[100]; // buffer to store word

    while (fscanf(fp, "%s", write) != EOF) // read word by word
    {
        int i; // hash index

        if (write[0] >= 'a' && write[0] <= 'z') // if lowercase
        {
            i = (write[0] - 'a') % 26; // calculate index
        }
        else if (write[0] >= 'A' && write[0] <= 'Z') // if uppercase
        {
            i = (write[0] - 'A') % 26; // calculate index
        }
        else
        {
            i = 26; // special characters index
        }

        if (validation(arr, write, filename, i)) // check if word exists
        {
            continue; // skip if updated
        }

        write[99] = '\0'; // safety null character

        if (arr[i].link == NULL) // if index empty
        {
            main_t *new = malloc(sizeof(main_t)); // create new main node
            if (new == NULL)
            {
                return FAILURE;
            }

            new->str = malloc(sizeof(char) * 100); // allocate memory for word
            if (new->str == NULL)
            {
                free(new);
                return FAILURE;
            }

            strcpy(new->str, write); // copy word
            new->count = 1; // set file count
            new->sublink = NULL; // initialize sub link
            new->mainlink = NULL; // initialize main link
            arr[i].link = new; // attach to hash table

            sub_t *new1 = malloc(sizeof(sub_t)); // create sub node
            if (new1 == NULL)
            {
                free(new->str);
                free(new);
                return FAILURE;
            }

            new1->file = malloc(sizeof(char) * 100); // allocate file name memory
            if (new1->file == NULL)
            {
                return FAILURE;
            }

            strcpy(new1->file, filename); // copy file name
            new1->w_count = 1; // set word count
            new1->sub_link = NULL; // initialize sub link
            new->sublink = new1; // attach sub node
        }
        else
        {
            main_t *new = malloc(sizeof(main_t)); // create new main node
            if (new == NULL)
            {
                return FAILURE;
            }

            new->str = malloc(sizeof(char) * 100); // allocate memory for word
            if (new->str == NULL)
            {
                free(new);
                return FAILURE;
            }

            strcpy(new->str, write); // copy word
            new->count = 1; // set file count
            new->sublink = NULL; // initialize sub link
            new->mainlink = NULL; // initialize main link

            main_t *temp = arr[i].link; // get first main node

            while (temp->mainlink != NULL) // go to last main node
            {
                temp = temp->mainlink;
            }

            temp->mainlink = new; // attach new main node

            sub_t *new1 = malloc(sizeof(sub_t)); // create sub node
            if (new1 == NULL)
            {
                free(new->str);
                free(new);
                return FAILURE;
            }

            new1->file = malloc(sizeof(char) * 100); // allocate file name
            if (new1->file == NULL)
            {
                return FAILURE;
            }

            strcpy(new1->file, filename); // copy file name
            new1->w_count = 1; // set word count
            new1->sub_link = NULL; // initialize sub link
            new->sublink = new1; // attach sub node
        }
    }

    fclose(fp); // close file
}

int create_db(hash_t *arr, node_t *head)
{
    if (head == NULL) // check if file list empty
    {
        return FAILURE;
    }

    while (head) // traverse file list
    {
        openfile(arr, head->str); // open each file
        head = head->link; // move to next file
    }

    printf("DATABASE created successfully! \n\n"); // print success message

    return SUCCESS; // return success
}