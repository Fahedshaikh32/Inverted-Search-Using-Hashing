#include "hash.h"

int save_db(hash_t *arr, char *file)
{
    FILE *fd = fopen(file, "w"); // open file in write mode
    if (fd == NULL)
    {
        printf("Error opening file! \n"); // print error if file not opened
        return FAILURE; // return failure
    }

    for (int i = 0; i < 27; i++) // traverse all hash indexes
    {
        if (arr[i].link == NULL) // skip empty index
        {
            continue;
        }

        fprintf(fd, "#%d;", i); // write index number

        main_t *temp = arr[i].link; // get main list

        while (temp) // traverse main list
        {
            fprintf(fd, "%s;%d;", temp->str, temp->count); // write word and file count

            sub_t *sub_temp = temp->sublink; // get sub list

            while (sub_temp) // traverse sub list
            {
                fprintf(fd, "%s;%d;", sub_temp->file, sub_temp->w_count); // write file name and word count
                sub_temp = sub_temp->sub_link; // move to next sub node
            }

            temp = temp->mainlink; // move to next main node
        }

        fprintf(fd, "#\n"); // mark end of index data
    }

    fclose(fd); // close file

    printf("DATABASE saved successfully! \n\n"); // print success message

    return SUCCESS; // return success
}