#ifndef _TABLE_
#define _TABLE_

typedef struct _table
{
    int rows;
    int columns;
    wchar_t ***cells;
} TABLE;

#endif