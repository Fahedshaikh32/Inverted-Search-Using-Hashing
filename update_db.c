#include "hash.h"

int update_db(hash_t *arr, node_t *head)
{
    char backup_file[100]; // store backup file name
    printf("Enter backup file name: ");
    scanf("%s", backup_file); // read backup file name

    FILE *fp = fopen(backup_file, "r"); // open backup file
    if (!fp)
    {
        perror("fopen"); // print error if file not opened
        return FAILURE; // return failure
    }

    char ch; // store character

    while (fscanf(fp, " %c", &ch) == 1) // read file till EOF
    {
        if (ch != '#') // check start symbol
            continue;

        int index; // store hash index
        fscanf(fp, "%d;", &index); // read index

        while (1) // read words under index
        {
            char word[100]; // store word
            int file_count; // store number of files

            if (fscanf(fp, "%[^;];%d;", word, &file_count) != 2) // read word and file count
                break;

            main_t *m_new = malloc(sizeof(main_t)); // create main node
            if (!m_new)
            {
                fclose(fp);
                return FAILURE;
            }

            word[99] = '\0'; // safety null
            m_new->str = strdup(word); // copy word
            m_new->count = file_count; // set file count
            m_new->sublink = NULL; // initialize sublink
            m_new->mainlink = NULL; // initialize mainlink

            sub_t *sub_tail = NULL; // tail pointer for sub list

            for (int i = 0; i < file_count; i++) // read file details
            {
                char fname[100]; // store file name
                int w_count; // store word count

                fscanf(fp, "%[^;];%d;", fname, &w_count); // read file name and count

                node_t *prev = NULL; // previous pointer
                node_t *temp = head; // start from head

                while (temp) // remove file from list if exists
                {
                    if (strcmp(temp->str, fname) == 0) // compare file name
                    {
                        if (prev)
                            prev->link = temp->link;
                        else
                            head = temp->link;

                        free(temp); // free node
                        break;
                    }

                    prev = temp;
                    temp = temp->link;
                }

                sub_t *s_new = malloc(sizeof(sub_t)); // create sub node
                if (!s_new)
                {
                    fclose(fp);
                    return FAILURE;
                }

                s_new->file = strdup(fname); // copy file name
                s_new->w_count = w_count; // set word count
                s_new->sub_link = NULL; // initialize sub link

                if (!m_new->sublink) // if first sub node
                    m_new->sublink = sub_tail = s_new;
                else
                {
                    sub_tail->sub_link = s_new; // attach at end
                    sub_tail = s_new; // move tail
                }
            }

            if (!arr[index].link) // if index empty
                arr[index].link = m_new;
            else
            {
                main_t *t = arr[index].link; // get main list
                while (t->mainlink) // go to last node
                    t = t->mainlink;
                t->mainlink = m_new; // attach new node
            }

            int c = fgetc(fp); // read next character

            if (c == '#' || c == EOF) // check end of index
            {
                break;
            }

            ungetc(c, fp); // put character back
        }
    }

    fclose(fp); // close file
    printf("Database updated successfully\n"); // print success message
    return SUCCESS; // return success
}