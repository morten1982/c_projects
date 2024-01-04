#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* open_filename(FILE* file, char* filename, char* mode);
void show_with_linenumbers(FILE* file);
void show_without_linenumbers(FILE* file);
void show_hex(FILE* file);
void close_all(FILE* file);
void print_help(void);

int main(int argc, char* argv[])
{
    
    if(argc == 3)
    {
        char* filename = argv[1];
        FILE* file = NULL;
        int result;
        
        result = strcmp(argv[2], "--no");
        if(result == 0)
        {
            file = open_filename(file, filename, "r");
            show_without_linenumbers(file);
        }
        else
        {
            result = strcmp(argv[2], "--hex");
            if(result == 0)
            {
                file = open_filename(file, filename, "rb");
                show_hex(file);
            }
            else
                print_help();
        }
        
        close_all(file);
        
    }
    else if(argc == 2)
    {
        char* filename = argv[1];
        FILE* file = NULL;
        
        int result = strcmp(argv[1], "--help");
        
        if(!result)
            print_help();
        else
        {
            file = open_filename(file, filename, "r");
            show_with_linenumbers(file);
            close_all(file);
        }
    }
    else
        print_help();
    
    return 0;
}

void print_help()
{
    printf("\n-> Read <filename> with linenumbers\n");
    printf("\nUsage:\t$./show <filename> (--no / --hex)\n\n");
    printf("\t--no  = show <filename> without linenumbers\n");
    printf("\t--hex = show <filename> as hexdump\n\n");
    exit(0);
}

FILE* open_filename(FILE* file, char* filename, char* mode)
{
    file = fopen(filename, mode);
    if(!file)
    {
        printf("%s not found\n", filename);
        exit(1);
    }
    
    return(file);
}

void show_with_linenumbers(FILE* file)
{    
    int x = 1;
    char c;
    
    printf("%4i : ", x);
    do
    {
        c = (char)fgetc(file);
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

void show_without_linenumbers(FILE* file)
{
    char c;
    
    do
    {
        c = (char)fgetc(file);
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

void close_all(FILE* file)
{
    fclose(file);
}
