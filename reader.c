#include "reader.h"

int ReadFromFile(wchar_t *fName, TABLE *table)
{
    int str, col;

    FILE *file = _wfopen(fName, L"r");

    if (fwscanf(file, L"%d%d\n", &str, &col) != 2)
    {
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
                fclose(file);
                return 42;
            }         
        }
    }
    fclose(file);
    return 0;
}