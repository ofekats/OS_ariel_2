#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    if(argc < 3 || argc > 5)
    {
        printf("Error:the usage is- copy <file1> <file2> optional:flags (-v ,-f)\n");
        return 1;
    }
    char* file1 = argv[1];
    char* file2 = argv[2];
    int flagv = 0;
    int flagf = 0;
    if(argc > 3)
    {
        if(strcmp(argv[3], "-v") == 0)
        {
            flagv =1;
        }
        else if(strcmp(argv[3], "-f") == 0)
        {
            flagf =1;
        }
        else{
            printf("Error:the usage is- copy <file1> <file2> optional:flags (-v ,-f)\n");
            return 1;
        }
    }
    if(argc > 4)
    {
        if(strcmp(argv[4], "-v") == 0)
        {
            flagv =1;
        }
        else if(strcmp(argv[4], "-f") == 0)
        {
            flagf =1;
        }
        else{
            printf("Error:the usage is- copy <file1> <file2> optional:flags (-v ,-f)\n");
            return 1;
        }
    }
    FILE* f1 = fopen(file1, "rb");
    if (f1 == NULL)
    {
        perror("general failure");
        printf("Error:the usage is- copy <file1> <file2> optional:flags (-v ,-f)\n");
        return errno;
    }
    if(!flagf)
    {
        if (access(file2, F_OK) != -1) {
            if(flagv)
            {
                printf("target file exist\n");
            }
            return 1;
        } 
    }
    FILE* f2 = fopen(file2, "wb");
    if (f2 == NULL)
    {
        perror("general failure");
        printf("Error:the usage is- copy <file1> <file2> optional:flags (-v ,-f)\n");
        fclose(f1);
        return errno;
    }
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    // Read data from file1 and write it to file2
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, f1)) > 0)
    {
        fwrite(buffer, 1, bytes_read, f2);
    }
    fclose(f1);
    fclose(f2);
    if(flagv)
    {
        printf("success\n");
    }
    return 0;
}