#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* open_filename(FILE* myfile, char* filename);
void show_with_linenumbers(FILE* myfile);
void show_without_linenumbers(FILE* myfile);
void close_all(FILE* myfile);
void print_help(void);

int main(int argc, char* argv[])
{
    
    if(argc == 3)
    {
        char* filename = argv[1];
        FILE* myfile = NULL;
        myfile = open_filename(myfile, filename);
        int result;
        
        result = strcmp(argv[2], "--no");
        if(result == 0)
            show_without_linenumbers(myfile);
        else
            print_help();
        
        close_all(myfile);
    }
    else if(argc == 2)
    {
        char* filename = argv[1];
        FILE* myfile = NULL;
        
        int result = strcmp(argv[1], "--help");
        
        if(!result)
            print_help();
        else
        {
            myfile = open_filename(myfile, filename);
            show_with_linenumbers(myfile);
            close_all(myfile);
        }
    }
    else
        print_help();
    
    return 0;
}

void print_help()
{
    printf("\n-> show <filename> with linenumbers\n");
    printf("\nUsage: ./show <filename> (--no)\n");
    printf("\t--no = show <filename> without linenumbers\n\n");
    exit(0);
}

FILE* open_filename(FILE* myfile, char* filename)
{
    myfile = fopen(filename, "r");
    if(!myfile)
    {
        printf("%s not found\n", filename);
        exit(0);
    }
    
    return(myfile);
}

void show_with_linenumbers(FILE* myfile)
{    
    int x = 1;
    char c;
    
    printf("%4i : ", x);
    do
    {
        c = (char)fgetc(myfile);
        if(c == '\n')
        {
            x++;
            printf("\n");
            printf("%4i : ", x);
            continue;
        } 
        else if(c == EOF)
            break;
        else
            putchar(c);
    } 
    while(c != EOF);
    printf("\n");
}

void show_without_linenumbers(FILE* myfile)
{
    char c;
    
    do
    {
        c = (char)fgetc(myfile);
        if(c == '\n')
        {
            printf("\n");
            continue;
        } 
        else if(c == EOF)
            break;
        else
            putchar(c);
    } 
    while(c != EOF);
}

void close_all(FILE* myfile)
{
    fclose(myfile);
}
