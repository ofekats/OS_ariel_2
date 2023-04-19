#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, char *argv[])
{
    if(argc < 3) //if not space bad!!!! (!=3)
    {
        printf("Error:decode <codec> <message>\n");
        return 1; 
    }
    typedef char* (*sym)(char *, int);
    void *handle;
    int size = 0;
    for(int i=2; i< argc; i++)
    {
        size+= strlen(argv[i])+1;
    }
    char* st = (char*) malloc(sizeof(char)*size);
    if(st == NULL)
    {
        perror("Error");
        return errno;
    }
    for (int i = 2; i < argc; i++) {
        strcat(st, argv[i]);
        if(i!=argc-1)
        {
            strcat(st, " ");
        }
    }
    size --;
    // printf("string: %s\n", st);
    // printf("size: %d\n", size);
    // printf("argv[1]: %s\n", argv[1]);
    char* lib = argv[1];
    if(strcmp(lib, "codecA") == 0)
    {
        char * str = "./libcodecA.so";
        handle = dlopen(str, RTLD_LAZY);
    }
    else if(strcmp(lib, "codecB") == 0)
    {
        char * str = "./libcodecB.so";
        handle = dlopen(str, RTLD_LAZY);
    }
    else
    {
        printf("Error:dncode <codec> <message>\n");
        return 1; 
    }
    if(handle == NULL)
    {
        printf("dlopen failed: %s\n", dlerror());
    }
    sym decode = (sym)dlsym(handle,"decode");
    char* ret = decode(st, size);
    printf("decoded %s\n", ret);
    free(st);
    dlclose(handle);
    return 0;
}