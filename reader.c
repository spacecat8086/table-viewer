#include <stdio.h>
#include <stdlib.h>
#include "reader.h"

int ReadFromFile(char *fName, TABLE *table)
{
    int str, col;

    FILE *file = fopen(fName, "r");

    if (fwscanf(file, L"%d%d\n", &str, &col) != 2)
    {
        printf("Missing table info\n");
        fclose(file);
        return 42;
    }

    table->rows = str;
    table->columns = col;
    table->cells = calloc(str, sizeof (wchar_t **));

    for (int i = 0; i < str; i++)
    {
        table->cells[i] = calloc(col, sizeof (wchar_t *));
        for (int j = 0; j < col; j++)
        {
            table->cells[i][j] = calloc(256, sizeof (wchar_t));

            if (fgetws(table->cells[i][j], 256, file) == NULL)
            {
                wprintf(L"Missing cell\n");
                return 42;
            }
            else
            {
                wprintf(L"%d:%d %s\n", i, j, table->cells[i][j]);
            }            
        }
    }
    fclose(file);
    return 0;
}