#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* open_filename(FILE* myfile, char* filename, char* mode);
void show_with_linenumbers(FILE* myfile);
void show_without_linenumbers(FILE* myfile);
void show_hex(FILE* myfile);
void close_all(FILE* myfile);
void print_help(void);

int main(int argc, char* argv[])
{
    
    if(argc == 3)
    {
        char* filename = argv[1];
        FILE* myfile = NULL;
        int result;
        
        result = strcmp(argv[2], "--no");
        if(result == 0)
        {
            myfile = open_filename(myfile, filename, "r");
            show_without_linenumbers(myfile);
        }
        else
        {
            result = strcmp(argv[2], "--hex");
            if(result == 0)
            {
                myfile = open_filename(myfile, filename, "rb");
                show_hex(myfile);
            }
            else
                print_help();
        }
        
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
            myfile = open_filename(myfile, filename, "r");
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
    printf("\nUsage:\t$./show <filename> (--no / --hex)\n\n");
    printf("\t--no  = show <filename> without linenumbers\n");
    printf("\t--hex = show <filename> as hexdump\n\n");
    exit(0);
}

FILE* open_filename(FILE* myfile, char* filename, char* mode)
{
    myfile = fopen(filename, mode);
    if(!myfile)
    {
        printf("%s not found\n", filename);
        exit(1);
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

void show_hex(FILE* hexfile)
{
    int i;
    int x = 0;
    
    while((i = fgetc(hexfile)) != EOF)
    {
        printf("%02X ", i);
        x++;
        if(!(x % 16))
            putchar('\n');
    }
    
    printf("\n\n");
}

void close_all(FILE* myfile)
{
    fclose(myfile);
}
