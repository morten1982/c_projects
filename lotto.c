#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 6

const int maxballs = 49;

void seedrnd(void);
int rnd(int range);
void sort_array(int* array, int size);
void print_array(int* array, int size);

int main()
{
    int x;
    int b;
    int numbers[maxballs];
    int balls[SIZE];
    
    // Array mit 0 fuellen
    for(x = 0; x < maxballs; x++)
        numbers[x] = 0;
    
    printf("L O T T O - Z I E H U N G\n\n");
    printf("Eingabe druecken zum Starten ...\n");
    getchar();
    
    seedrnd();
    
    // Zahlen ziehen:
    for(x = 0; x < SIZE; x++)
    {
        // Zahl ziehen und pruefen, ob sie schon gezogen wurde
        do
        {
            b = rnd(maxballs);
        }
        while(numbers[b-1]);    // bereits gezogen?, wdh bis 0(FALSE)
        
        numbers[b-1] = 1;       // dann als gezogen markieren mit 1;
        balls[x] = b;               // und in neues Array[6] legen;
    }
    
    sort_array(balls, SIZE);    // bubble sort
    print_array(balls, SIZE);   // Ausgabe
    
    return 0;
}

void seedrnd()
{
    srand((unsigned)time(NULL));
}

int rnd(int range)
{
    int x;
    x = rand() % range + 1;
    return(x);
}

void print_array(int* array, int size)
{
    int x = 0;
    
    while(size--)
    {
        printf("%i\t", array[x]);
        x++;
    }
    printf("\n");
}

void sort_array(int* array, int size)
{
    // Veraendert urspruengliches Array !
    
    int temp;
    int a, b;
    
    for(a = 0; a < SIZE - 1; a++)
    {
        for(b = a + 1; b < SIZE; b++)
        {
            if(*(array+a) > *(array+b))     // pointer notation fuer
            {                               // array[a] > array[b]
                temp = *(array + a);
                *(array + a) = *(array + b);
                *(array + b) = temp;
            }
        }
        
    }
}
