// Vladislav Zolotukhin
// August 8, 2023

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

int inputInt(void)
{
    char newLine = 'x';
    int userInputInt;
    int error = 0;

    do
    {
        scanf("%d%c", &userInputInt, &newLine);
        if (newLine == '\n')
        {
            error = 0;
            return userInputInt;
        }
        else
        {
            printf("Error! Input a whole number: ");
            error = 1;
            clearInputBuffer();
        }
    } while (error == 1);
    return userInputInt;
}

int inputIntPositive(void)
{
    int intPositive;
    int error = 0;
    do
    {
        scanf("%d", &intPositive);
        if (intPositive > 0)
        {
            error = 0;
            return intPositive;
        }
        else
        {
            error = 1;
            printf("ERROR! Value must be > 0: ");
        }
    } while (error == 1);
    return intPositive;
}

int inputIntRange(int lower, int upper)
{
    int rangeInt;
    int error = 0;
    char newLine = 'x';
    do
    {
        scanf("%d%c", &rangeInt, &newLine);
        if (newLine == '\n')
        {
            if (rangeInt >= lower && rangeInt <= upper)
            {
                error = 0;
                return rangeInt;
            }
            else
            {
                error = 1;
                printf("ERROR! Value must be between %d and %d inclusive: ", lower, upper);

            }
        }
        else
        {
            printf("Error! Input a whole number: ");
            error = 1;
            clearInputBuffer();
        }

    } while (error == 1);
    return rangeInt;
}

char inputCharOption(char validChar[])
{
    int error = 0, i = 0, j = 0, len;
    char inputChar[50] = { '\0' };
    char firstchar;
    do
    {
        error = 0;
        scanf(" %s", inputChar);
        len = strlen(inputChar);
        if (len == 1)
        {
            firstchar = inputChar[0];
            for (i = 0; validChar[i] != '\0'; i++)
            {
                if (firstchar == validChar[i])
                {
                    error = 0;
                    return firstchar;
                }
                else {
                    error = 1;
                }
            }
            if (error == 1)
            {
                printf("ERROR: Character must be one of [");
                for (j = 0; validChar[j] != '\0'; j++)
                {
                    printf("%c", validChar[j]);
                }
                printf("]: ");
            }
        }
        else
        {
            printf("ERROR: Character must be one of [");
            for (j = 0; validChar[j] != '\0'; j++)
            {
                printf("%c", validChar[j]);
            }
            printf("]: ");
            error = 1;
            clearInputBuffer();
        }
    } while (error == 1);
    return firstchar;
}

void inputCString(char* stringInput, int minChar, int maxChar)
{
    int i, error = 0;
    char enterInput[50];

    do
    {
        scanf(" %[^\n]s", enterInput);
        for (i = 0; enterInput[i] != '\0'; i++)
        {
            if ((i + 1) >= minChar && (i + 1) <= maxChar)
            {
                error = 0;

            }
            else
            {
                error = 1;

            }
        }
        if (error == 1)
        {

            if (minChar == maxChar)
            {
                printf("ERROR: String length must be exactly %d chars: ", minChar);

            }
            else if (i > maxChar)
            {
                printf("ERROR: String length must be no more than %d chars: ", maxChar);
            }
            else
            {
                printf("ERROR: String length must be between %d and %d chars: ", minChar, maxChar);

            }
        }
        else
        {
            for (i = 0; i < maxChar; i++)
            {
                stringInput[i] = enterInput[i];
            }
        }
    } while (error == 1);
}

void displayFormattedPhone(const char* number)
{
    int i = 0, length = 0;

    if (number == NULL)
    {
        printf("(__)___-____");
    }
    else
    {
        while (number[i] != '\0')
        {
            if (number[i] <= '0' || number[i] >= '9')
            {
            }
            i++;
            length++;
        }
        if (length != 10)
        {
            printf("(___)___-____");
        }
        else
        {
            i = 0;
            printf("(");
            while (number[i] != '\0')
            {
                if (i < 2)
                {
                    printf("%c", number[i]);
                }
                else if (i == 3)
                {
                    printf(")");
                    printf("%c", number[i]);
                }
                else if (i < 5)
                {
                    printf("%c", number[i]);
                }
                else if (i == 5)
                {
                    printf("%c", number[i]);
                    printf("-");

                }
                else
                {
                    printf("%c", number[i]);
                }
                i++;
            }
        }
    }

}
