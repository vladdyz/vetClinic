
// Vladislav Zolotukhin
// August 8, 2023

#ifndef CORE_H
#define CORE_H

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//Return Integer, Receive no Arguments, Validate Input
int inputInt(void);

//Return Integer, Receive no Arguments, Same as above but validate that input is > 0
int inputIntPositive(void);

//Return Integer, Receive 2 arguments (a range)
int inputIntRange(int lower, int upper);

//Return Char, Receive String Array
char inputCharOption(char validChar[]);

//Obtain user input for string value with range between 2nd and 3rd argument
void inputCString(char* stringInput, int minChar, int maxChar);

//Display array of 10 digits as a phone number
void displayFormattedPhone(const char* number);

#endif // !CORE_H
