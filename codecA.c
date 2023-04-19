#include "codec.h"
#include <ctype.h>

char * encode(char * str, int size)
{
    for(int i=0; i< size; i++)
    {
        if(str[i] > 64 && str[i] < 91)
        {
            str[i] +=32;
        }
        else if(str[i] > 96 && str[i] < 123)
        {
            str[i] -=32;
        }
    }
    return str;
}

char * decode(char * str, int size)
{
    for(int i=0; i< size; i++)
    {
        if(str[i] > 64 && str[i] < 91)
        {
            str[i] +=32;

        }
        else if(str[i] > 96 && str[i] < 123)
        {
            str[i] -=32;
        }
    }
    return str;
}