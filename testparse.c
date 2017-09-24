#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

#define UNKNOWN_SYMBOL_ERR 0
#define NOT_REACHED_FINAL_STATE 1
#define REACHED_FINAL_STATE 2

char ALFABETS[100];
char STATES[100];
char FINAL_STATES[2] = {'A', 'B'};
char current_state;
int JUMLAH_STATE;
int JUMLAH_ALFABET;

boolean IsCharValid(char current_char);

int main()
{
    FILE *inputFile;
    char c;
    char DFA_State[100][100];
    int i, j;
    char current_char;
    char result;
    int a, b, input, state;
    boolean found;

    /*** PARSING DFA TABLE ***/
    inputFile = fopen("test.txt", "r");
    if  (inputFile == NULL)
    {
        printf("Error: FILE NOT FOUND");
    }
    else
    {
        i = 0;
        j = 0;
        c = fgetc(inputFile);
        while ( c != EOF )
        {
            if (c != ' ' && c != '\n')
            {
                if ( i != 0 && j != 0)
                {
                    DFA_State[i-1][j-1] = c;
                }
                else if ( i == 0 && j != 0)
                {
                    ALFABETS[j-1] = c;
                }
                else if ( i != 0 && j ==0 )
                {
                    STATES[i-1] = c;
                }
                j++;
            }

            else if (c == '\n')
            {
                j = 0;
                i++;
            }
            c = fgetc(inputFile);
        }
    }
    fclose(inputFile);
    JUMLAH_ALFABET = j;
    JUMLAH_STATE = i;
    current_state = STATES[0];

    /*** TEST ISI TABEL DFA ***/
    /*
    printf("DFA READY!\nJumlah Alfabet:%d\nJumlah State: %d\n", JUMLAH_ALFABET, JUMLAH_STATE);
    for ( i = 0 ; i <= JUMLAH_STATE-1; i++)
    {
        for ( j = 0; j <= JUMLAH_ALFABET-1; j++)
        {
            printf("%c ", DFA_State[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i <= JUMLAH_STATE-1; i++)
    {
        printf("%c ", STATES[i]);
    }
    printf("\n");
    for (i = 0; i <= JUMLAH_ALFABET-1; i++)
    {
        printf("%c ", ALFABETS[i]);
    }
    printf("\n");
    */
    /*** PENGUNAAN TABEL DFA ***/

    printf("Masukkan string yang akan diolah: ");

    current_char = getchar();
    printf("%c",current_state);

    if (!IsCharValid(current_char))
    {
        result = UNKNOWN_SYMBOL_ERR;
    }
    else
    {
        /* START LOOPING BACA PER KARAKTER */
        /* WHILE RESULT != UNKNOWN_SYMBOL_ERR || CURRENT_CHAR != '\n' */
        while ( result != UNKNOWN_SYMBOL_ERR && current_char != '\n' )
        {
            b=0;
            found = false;
            while( !found || b < JUMLAH_STATE )
            {
                if ( current_state == STATES[b] )
                {
                    state = b;
                    found = true;
                }
                b++;
            }

            found = false;
            a = 0;
            while( !found || a < JUMLAH_ALFABET )
            {
                if ( current_char == ALFABETS[a] )
                {
                    input = a;
                    found = true;
                }
                a++;
            }

            current_state = DFA_State[state][input];

            printf(" --> %c", current_state);

            current_char = getchar();

            if (!IsCharValid(current_char))
                {
                    result = UNKNOWN_SYMBOL_ERR;
                }
        }
        /*SELESAI BACA PER KARAKTER */

        result = NOT_REACHED_FINAL_STATE;
        i = 0;
        while ( i < 2 && result != REACHED_FINAL_STATE )
        {
            if (current_state == FINAL_STATES[i])
            {
                result = REACHED_FINAL_STATE;
            }
            i++;
        }
    }

    switch (result)
        {
            case UNKNOWN_SYMBOL_ERR:printf("\nUnknown Input %c",current_char);break;
            case NOT_REACHED_FINAL_STATE:printf("\nNot accepted"); break;
            case REACHED_FINAL_STATE:printf("\nAccepted");break;
            default: printf("\nUnknown Error");
        }

    return 0;

}

boolean IsCharValid(char current_char)
{
    int i;
    boolean valid;

    i = 0;
    valid = false;
    while ( i < JUMLAH_ALFABET && !valid )
    {
        if ( current_char == ALFABETS[i] )
        {
            valid = true;
        }
        i++;
    }
    return valid;
}
