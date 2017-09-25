#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"

#define UNKNOWN_SYMBOL_ERR 0
#define NOT_REACHED_FINAL_STATE 1
#define REACHED_FINAL_STATE 2

char ALFABETS[100];
char STATES[100];
char FINAL_STATES[100];
char current_state;
int JUMLAH_STATE;
int JUMLAH_ALFABET;
int JUMLAH_FINALSTATE;

boolean IsCharValid(char current_char);
void PrintState(char current_state);

int main()
{
    FILE *inputFile;
    char c;
    char DFA_State[100][100];
    int i, j, k;
    char current_char;
    char result;
    int a, b, input, state;
    boolean found;

    /*** PARSING DFA TABLE ***/
    inputFile = fopen("socket_config.txt", "r");
    if  (inputFile == NULL)
    {
        printf("Error: FILE NOT FOUND");
    }
    else
    {
        i = 0;
        j = 0;
        k = 0;
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
                    if ( c == '*' )
                    {
                        c = fgetc(inputFile);
                        FINAL_STATES[k] = c;
                        k++;
                    }
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
    JUMLAH_FINALSTATE= k;
    current_state = STATES[0];

    /*** TEST ISI TABEL DFA ***/
    /*
    printf("DFA READY!\nJumlah Alfabet:%d\nJumlah State: %d\nJumlah Final State: %d\n\n", JUMLAH_ALFABET, JUMLAH_STATE, JUMLAH_FINALSTATE);

    printf("TABLE FUNCTION:\n");
    for ( i = 0 ; i <= JUMLAH_STATE-1; i++)
    {
        for ( j = 0; j <= JUMLAH_ALFABET-1; j++)
        {
            printf("%c ", DFA_State[i][j]);
        }
        printf("\n");
    }

    printf("STATES: ");
    for (i = 0; i <= JUMLAH_STATE-1; i++)
    {
        printf("%c ", STATES[i]);
    }
    printf("\n");

    printf("ALFABETS: ");
    for (i = 0; i <= JUMLAH_ALFABET-1; i++)
    {
        printf("%c ", ALFABETS[i]);
    }
    printf("\n");

    printf("FINAL STATES: ");
    for (i = 0; i <= JUMLAH_FINALSTATE-1; i++)
    {
        printf("%c ", FINAL_STATES[i]);
    }
    printf("\n");
    */
    printf("\n************************  TUGAS BESAR TBFO  ************************\n");
     printf("***********************  PERMODELAN  SOCKET  ************************\n");
    printf("\nOLEH:\nJonathan Tjandra (13516058)\nI Kadek Yuda Budipratama Giri (13516115)\n\n");
    printf("***** PETUNJUK MENGENAI FUNGSI *****\n\n");
    printf("s - Socket()    [ Initialize Socket ]\n");
    printf("n - Set_NB()    [ Switch to Non-Blocking mode ]\n");
    printf("d - Set_B()     [ Switch to Blocking mode (default) ]\n");
    printf("b - Bind()      [ Bind socket to a designated IP Address and Port ]\n");
    printf("l - Listen()    [ Open socket to accept connections ]\n");
    printf("c - Connect()   [ Open a connection ]\n");
    printf("a - Accept()    [ Accept connection from client ]\n");
    printf("r - Read()      [ Read data from connection ]\n");
    printf("w - Write()     [ Write data to file/console ]\n");
    printf("k - Return()    [ Return data after processing in server ]\n");
    printf("t - Wait()      [ Waiting for server to finish processing ]\n");
    printf("i - Interrupt() [ Interrupt program from computer/OS ]\n");
    printf("x - Close()     [ Close Socket/Connection ]\n");
    printf("\n");

    /*** PENGUNAAN TABEL DFA ***/

    printf("Masukkan string yang akan diolah: ");

    current_char = getchar();
    PrintState(current_state);

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

            printf(" --> "); PrintState(current_state);

            current_char = getchar();

            if (!IsCharValid(current_char))
                {
                    result = UNKNOWN_SYMBOL_ERR;
                }
        }
        /*SELESAI BACA PER KARAKTER */

        result = NOT_REACHED_FINAL_STATE;
        i = 0;
        while ( i < JUMLAH_FINALSTATE && result != REACHED_FINAL_STATE )
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
            case NOT_REACHED_FINAL_STATE:printf("\nNot accepted\n"); break;
            case REACHED_FINAL_STATE:printf("\nAccepted\n");break;
            default: printf("\nUnknown Error\n");
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

void PrintState(char current_state)
{
    switch (current_state)
    {
        case 'A':
            printf("Closed");
            break;
        case 'B':
            printf("Init_B");
            break;
        case 'C':
            printf("Bound_B");
            break;
        case 'D':
            printf("Listening_B");
            break;
        case 'E':
            printf("Connected_B");
            break;
        case 'F':
            printf("Waiting...");
            break;
        case 'G':
            printf("Init_NB");
            break;
        case 'H':
            printf("Bound_NB");
            break;
        case 'I':
            printf("Listening_NB");
            break;
        case 'J':
            printf("Connected_NB");
            break;
        case 'Z':
            printf("Dead State");
            break;
        case 'X':
            printf("ERROR");
            break;
        default:
            printf("UNKNOWN STATE");
    }
}
