#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if(argc < 3 || argc > 5)
    {
        printf("Error:the usage is- cmp <file1> <file2> optional:flags (-v ,-i)\n");
        return 1;
    }
    char* file1 = argv[1];
    char* file2 = argv[2];
    int flagv = 0;
    int flagi = 0;
    if(argc > 3)
    {
        if(strcmp(argv[3], "-v") == 0)
        {
            flagv =1;
        }
        else if(strcmp(argv[3], "-i") == 0)
        {
            flagi =1;
        }
        else{
            printf("Error:the usage is- cmp <file1> <file2> optional:flags (-v ,-i)\n");
            return 1;
        }
    }
    if(argc > 4)
    {
        if(strcmp(argv[4], "-v") == 0)
        {
            flagv =1;
        }
        else if(strcmp(argv[4], "-i") == 0)
        {
            flagi =1;
        }
        else{
            printf("Error:the usage is- cmp <file1> <file2> optional:flags (-v ,-i)\n");
            return 1;
        }
    }
    FILE* f1 = fopen(file1, "rb");
    if (f1 == NULL)
    {
        perror("cant open the file");
        printf("Error:the usage is- cmp <file1> <file2> optional:flags (-v ,-i)\n");
        return 1;
    }
    FILE* f2 = fopen(file2, "rb");
    if (f2 == NULL)
    {
        perror("cant open the file");
        printf("Error:the usage is- cmp <file1> <file2> optional:flags (-v ,-i)\n");
        fclose(f1);
        return errno;
    }
    int isEqual = 1;
    char c1[1];
    char c2[1];
    //is the size equal
    while(fread(c1, sizeof(char), 1, f1) != 0 && fread(c2, sizeof(char), 1, f2) != 0)
    {
        if(flagi)
        {
            if(c1[0] > 64 && c1[0] < 90)
            {
                c1[0] +=32;
            }
            if(c2[0] > 64 && c2[0] < 90)
            {
                c2[0] +=32;
            }
        }
        if(c1[0] != c2[0])
        {
            isEqual = 0;
            break;
        }
        c1[0] = '\0';
    }
    //if one of the files not done
    if(isEqual)
    {
        if(c1[0] != '\0')
        {
            isEqual = 0;
        }
        else if(fread(c1, sizeof(char), 1, f1) != 0)
        {
            isEqual = 0;
        }
        else if(fread(c2, sizeof(char), 1, f2) != 0)
        {
            isEqual = 0;
        }
    }
    fclose(f1);
    fclose(f2);
    if(flagv)
    {
        if(isEqual)
        {
            printf("equal\n");
            return 0;
        }
        else{
            printf("distinct\n");
            return 1;
        }
    }
    else{
        if(isEqual)
        {
            return 0;
        }
        else{
            return 1;
        }
    }

}