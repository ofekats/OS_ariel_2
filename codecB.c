#include "codec.h"

char * encode(char * str, int size)
{
    for(int i=0; i< size; i++)
    {
        if(str[i]+3 > 255)
        {
            str[i] = (str[i]+3 )% 255;
        }
        else{
            str[i] += 3;
        }
    }
    return str;
}

char * decode(char * str, int size)
{
    for(int i=0; i< size; i++)
    {
        if(str[i]-3 < 0)
        {
            str[i] = (str[i]-3)+255;
        }
        else{
            str[i] -= 3;
        }
    }
    return str;
}