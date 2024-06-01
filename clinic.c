// Vladislav Zolotukhin
// August 8, 2023

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data); 
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);
            suspend();
            break;
        case 3:
            addAppointment(data); 
            suspend();
            break;
        case 4:
            removeAppointment(data);
            suspend();
            break;
        }
    } while (selection);
}


// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i, noDisplay = 1;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber < 1) //checks if the patient log is completely empty, in which case no table will be displayed
        {
        }
        else if (patient[i].patientNumber == '\0')
        {
        }
        else
        {
            noDisplay = 0; //if at least one patient is present, print the header and patient info
        }
    }
    if (noDisplay == 0);
    {
        displayPatientTableHeader();
        for (i = 0; i < max; i++)
        {
            if (patient[i].patientNumber < 1)
            {
            }
            else if (patient[i].patientNumber == '\0')
            {
            }
            else
            {
                displayPatientData(&patient[i], FMT_TABLE);
            }
        }
    }
    if (noDisplay == 1)
    {
        printf("*** No records found ***\n");
    }
    printf("\n");
}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;
    int selectMenu = 1;
    do
    {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        selection = inputIntRange(0, 2);

        if (selection == 1)
        {
            searchPatientByPatientNumber(patient, max);
            clearInputBuffer();
            suspend();
        }
        else if (selection == 2)
        {
            searchPatientByPhoneNumber(patient, max);
            clearInputBuffer();
            suspend();
        }
        else if (selection == 0)
        {
            selectMenu = 0;
            printf("\n");
        }
        else
        {
            printf("ERROR! Value must be between 0 and 2 inclusive\n");
        }
    } while (selectMenu == 1);
}


// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int i, foundlist = 0;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == 0)
        {
            foundlist = 1;
            patient[i].patientNumber = nextPatientNumber(patient, max);
            inputPatient(&patient[i]);
            i = max;
        }
    }
    if (foundlist == 0)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }

}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int patientNumber, i;
    printf("Enter the patient number: ");
    scanf("%d", &patientNumber);
    printf("\n");
    i = findPatientIndexByPatientNum(patientNumber, patient, max);
    if (i == -1)
    {
        printf("ERROR! Patient record not found!\n\n");
    }
    else
    {
        menuPatientEdit(&patient[i]);
    }
}

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int patientNumber, i, delete;
    struct Patient empty = { 0 };
    printf("Enter the patient number: ");
    scanf("%d", &patientNumber);
    printf("\n");
    i = findPatientIndexByPatientNum(patientNumber, patient, max);
    if (i == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
        clearInputBuffer();
    }
    else
    {
        displayPatientData(&patient[i], FMT_FORM);
        printf("\nAre you sure you want to remove this patient record? (y/n): ");
        delete = inputCharOption("yn");
        switch (delete)
        {
        case 'y':
            patient[i] = empty;
            printf("Patient record has been removed!\n\n");
            clearInputBuffer();
            break;
        case 'n':
            printf("Operation aborted.\n\n");
            clearInputBuffer();
        }
    }

}

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* data)
{
    int i = 0, j = 0;
    struct Appointment temp1;


    for (i = 0; i < data->maxAppointments - 1; i++)
    {
        for (j = i + 1; j < data->maxAppointments; j++)
        {
            if (data->appointments[i].date.year != 0)
            {
                if (data->appointments[i].date.year > data->appointments[j].date.year)
                {
                    temp1 = data->appointments[i];
                    data->appointments[i] = data->appointments[j];
                    data->appointments[j] = temp1;
                }
                else if (data->appointments[i].date.year == data->appointments[j].date.year)
                {
                    if (data->appointments[i].date.month > data->appointments[j].date.month)
                    {
                        temp1 = data->appointments[i];
                        data->appointments[i] = data->appointments[j];
                        data->appointments[j] = temp1;
                    }
                    else if (data->appointments[i].date.month == data->appointments[j].date.month)
                    {
                        if (data->appointments[i].date.day > data->appointments[j].date.day)
                        {
                            temp1 = data->appointments[i];
                            data->appointments[i] = data->appointments[j];
                            data->appointments[j] = temp1;
                        }
                        else if (data->appointments[i].date.day == data->appointments[j].date.day)
                        {
                            if (data->appointments[i].time.hour > data->appointments[j].time.hour)
                            {
                                temp1 = data->appointments[i];
                                data->appointments[i] = data->appointments[j];
                                data->appointments[j] = temp1;
                            }
                            else if (data->appointments[i].time.hour == data->appointments[j].time.hour)
                            {
                                if (data->appointments[i].time.min > data->appointments[j].time.min)
                                {
                                    temp1 = data->appointments[i];
                                    data->appointments[i] = data->appointments[j];
                                    data->appointments[j] = temp1;
                                }
                                else
                                {

                                }
                            }
                        }
                        else
                        {

                        }

                    }
                    else
                    {

                    }
                }
                else
                {

                }
            }
        }
    }
    
    displayScheduleTableHeader(NULL,1);
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].date.year < 9999 && data->appointments[i].date.year != 0 && data->appointments[i].date.month <= 12 && data->appointments[i].patientNumber != 0)
        {

            printf("%d-%02d-%02d %02d:%02d ", data->appointments[i].date.year, data->appointments[i].date.month, data->appointments[i].date.day, data->appointments[i].time.hour, data->appointments[i].time.min);
            for (j = 0; j < data->maxAppointments; j++)
            {
                if (data->appointments[i].patientNumber >= 1)
                {
                    if (data->appointments[i].patientNumber == data->patients[j].patientNumber)
                    {
                        printf("%05d %-15s ", data->patients[j].patientNumber, data->patients[j].name);
                        displayFormattedPhone(data->patients[j].phone.number);
                        printf(" (%s)\n", data->patients[j].phone.description);

                    }
                    else
                    {
                        
                    }
                }
                else
                {

                }
            }
           
           
        }
    }
    printf("\n");
}
// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data)
{
    int i, j;
    struct Date selectDate;

    printf("Year        : ");
    selectDate.year = inputInt();
    printf("Month (1-12): ");
    selectDate.month = inputIntRange(1, 12);
    switch (selectDate.month)
    {
    case 1: 
        printf("Day (1-31)  : ");
        selectDate.day = inputIntRange(1, 31);
        break;
    case 2:
        if ((selectDate.year % 4 == 0 && selectDate.year % 100 != 0) || selectDate.year % 400 == 0)
        {
            printf("Day (1-29)  : ");
            selectDate.day = inputIntRange(1, 29);
        }
        else
        {
            printf("Day (1-28)  : ");
            selectDate.day = inputIntRange(1, 28);
        }
        break;
    case 3:
        printf("Day (1-31)  : ");
        selectDate.day = inputIntRange(1, 31);
        break;
    case 4:
        printf("Day (1-30)  : ");
        selectDate.day = inputIntRange(1, 30);
        break;
    case 5:
        printf("Day (1-31)  : ");
        selectDate.day = inputIntRange(1, 31);
        break;
    case 6:
        printf("Day (1-30)  : ");
        selectDate.day = inputIntRange(1, 30);
        break;
    case 7:
        printf("Day (1-31)  : ");
        selectDate.day = inputIntRange(1, 31);
        break;
    case 8:
        printf("Day (1-31)  : ");
        selectDate.day = inputIntRange(1, 31);
        break;
    case 9:
        printf("Day (1-30)  : ");
        selectDate.day = inputIntRange(1, 30);
        break;
    case 10:
        printf("Day (1-31)  : ");
        selectDate.day = inputIntRange(1, 31);
        break;
    case 11:
        printf("Day (1-30)  : ");
        selectDate.day = inputIntRange(1, 30);
        break;
    case 12:
        printf("Day (1-31)  : ");
        selectDate.day = inputIntRange(1, 31);
        break;
    default:
        printf("ERROR TRAP: You shouldn't be seeing this\n");
        break;
    }
    printf("\n");
    displayScheduleTableHeader(&selectDate, 0);

    struct Appointment temp1;
    for (i = 0; i < data->maxAppointments - 1; i++)
    {
        for (j = i + 1; j < data->maxAppointments; j++)
        {
            if (data->appointments[i].date.year != 0)
            {
                if (data->appointments[i].time.hour > data->appointments[j].time.hour)
                {
                    temp1 = data->appointments[i];
                    data->appointments[i] = data->appointments[j];
                    data->appointments[j] = temp1;
                }
                else if (data->appointments[i].time.hour == data->appointments[j].time.hour)
                {
                    if (data->appointments[i].time.min > data->appointments[j].time.min)
                    {
                        temp1 = data->appointments[i];
                        data->appointments[i] = data->appointments[j];
                        data->appointments[j] = temp1;
                    }
                    else
                    {

                    }
                }
                else
                {
                }
            }
        }
    }
    //run a check comparison to the date selected and the appointments & corresponding patients array
    //each time there is a match call displayScheduleData and send the matching indexes
    for (i = 0; i < data->maxAppointments; i++)
    {
        if ((selectDate.year == data->appointments[i].date.year) && (selectDate.month == data->appointments[i].date.month) && (selectDate.day == data->appointments[i].date.day))
        {
            for (j = 0; j < data->maxAppointments; j++)
            {
                if (data->appointments[i].patientNumber >= 1)
                {
                    if (data->appointments[i].patientNumber == data->patients[j].patientNumber)
                    {
                        displayScheduleData(&data->patients[j], &data->appointments[i], 0);

                    }
                    else
                    {

                    }
                }
                else
                {

                }
            }
        }
    }
    printf("\n");
}

// Add an appointment record to the appointment array
void addAppointment(struct ClinicData* data)
{
    int searchNum, booked = 0, emptyslot = 0, i, error = 1;
    struct Time searchTime;
    struct Date searchDate;
    do {
        printf("Patient Number: ");
        searchNum = inputInt();
        for (i = 0; i < data->maxPatient; i++)
        {
            if (searchNum == data->patients[i].patientNumber)
            {
                error = 0;
            }
            else
            {

            }
        }
        if (error == 1)
        {
            printf("\n");
            printf("ERROR: Patient record not found!\n\n");
        }
    } while (error == 1);
    do
    {
        printf("Year        : ");
        searchDate.year = inputInt();
        printf("Month (1-12): ");
        searchDate.month = inputIntRange(1, 12);
        switch (searchDate.month)
        {
        case 1:
            printf("Day (1-31)  : ");
            searchDate.day = inputIntRange(1, 31);
            break;
        case 2:
            if ((searchDate.year % 4 == 0 && searchDate.year % 100 != 0) || searchDate.year % 400 == 0)
            {
                printf("Day (1-29)  : ");
                searchDate.day = inputIntRange(1, 29);
            }
            else
            {
                printf("Day (1-28)  : ");
                searchDate.day = inputIntRange(1, 28);
            }
            break;
        case 3:
            printf("Day (1-31)  : ");
            searchDate.day = inputIntRange(1, 31);
            break;
        case 4:
            printf("Day (1-30)  : ");
            searchDate.day = inputIntRange(1, 30);
            break;
        case 5:
            printf("Day (1-31)  : ");
            searchDate.day = inputIntRange(1, 31);
            break;
        case 6:
            printf("Day (1-30)  : ");
            searchDate.day = inputIntRange(1, 30);
            break;
        case 7:
            printf("Day (1-31)  : ");
            searchDate.day = inputIntRange(1, 31);
            break;
        case 8:
            printf("Day (1-31)  : ");
            searchDate.day = inputIntRange(1, 31);
            break;
        case 9:
            printf("Day (1-30)  : ");
            searchDate.day = inputIntRange(1, 30);
            break;
        case 10:
            printf("Day (1-31)  : ");
            searchDate.day = inputIntRange(1, 31);
            break;
        case 11:
            printf("Day (1-30)  : ");
            searchDate.day = inputIntRange(1, 30);
            break;
        case 12:
            printf("Day (1-31)  : ");
            searchDate.day = inputIntRange(1, 31);
            break;
        default:
            printf("ERROR TRAP: You shouldn't be seeing this\n");
            break;
        }
        error = 0;
        do
        {
            printf("Hour (0-23)  : ");
            searchTime.hour = inputIntRange(0, 23);
            printf("Minute (0-59): ");
            searchTime.min = inputIntRange(0, 59);
            if ((searchTime.hour >= START_TIME) && (searchTime.hour <= END_TIME))
            {
                error = 0;
                if ((searchTime.min == 0) || (searchTime.min == APPT_LENGTH))
                {
                    error = 0;
                }
                else
                {
                    error = 1;
                }
            }
            else
            {
                error = 1;
            }
            if (searchTime.hour == 14)
            {
                if (searchTime.min > 0)
                {
                    error = 1;
                }
                else
                {
                    error = 0;
                }
            }
            if (error == 1)
            {
                printf("ERROR: Time must be between %d:00 and %d:00 in %d minute intervals.\n", START_TIME, END_TIME, APPT_LENGTH);
            }
            
            printf("\n");
        } while (error == 1);
        booked = 0;
        for (i = 0; i < data->maxAppointments; i++)
        {
            if (data->appointments[i].date.year == searchDate.year)
            {
                if (data->appointments[i].date.month == searchDate.month)
                {
                    if (data->appointments[i].date.day == searchDate.day)
                    {
                        if (data->appointments[i].time.hour == searchTime.hour)
                        {
                            if (data->appointments[i].time.min == searchTime.min)
                            {
                                booked = 1;                                
                                printf("ERROR: Appointment timeslot is not available!\n");
                                printf("\n");
                            }
                            else
                            {
                            }
                        }
                        else
                        {
                        }
                    }
                    else
                    {
                    }
                }
                else
                {
                }
            }
            else
            {
            }
        }
    } while (booked == 1);
    
   for (i = 0; (i < data->maxAppointments) && (emptyslot == 0); i++)
    {
      if (data->appointments[i].patientNumber == 0);
        {
            emptyslot = 1;
        }
    }
    if (emptyslot == 1)
    {
        data->appointments[i].date = searchDate;
        data->appointments[i].time = searchTime;
        data->appointments[i].patientNumber = searchNum;
        printf("*** Appointment scheduled! ***\n\n");
    }
    else
    {
        printf("ERROR: Appointment listing is FULL!\n\n");
    }
}


// Remove an appointment record from the appointment array
void removeAppointment(struct ClinicData* data)
{
    int searchNum, i, j, error = 1, noAppointments = 1, compare = 0;
    char removeConfirm;
    struct Date searchDate;
    struct Appointment empty = { 0 };

        printf("Patient Number: ");
        searchNum = inputInt();
        for (i = 0; i < data->maxPatient; i++)
        {
            if (searchNum == data->patients[i].patientNumber)
            {
                error = 0;
            }
            else
            {

            }
        }

        if (error == 1)
        {
            printf("ERROR: Patient record not found!\n\n");
        }
        else
        {
            noAppointments = 0;
            for (i = 0; (i < data->maxAppointments) && (noAppointments == 0); i++)
            {
                if (searchNum == data->appointments[i].patientNumber)
                {
                    compare = 1;
                    printf("Year        : ");
                    searchDate.year = inputInt();
                    printf("Month (1-12): ");
                    searchDate.month = inputIntRange(1, 12);
                    switch (searchDate.month)
                    {
                    case 1:
                        printf("Day (1-31)  : ");
                        searchDate.day = inputIntRange(1, 31);
                        break;
                    case 2:
                        if ((searchDate.year % 4 == 0 && searchDate.year % 100 != 0) || searchDate.year % 400 == 0)
                        {
                            printf("Day (1-29)  : ");
                            searchDate.day = inputIntRange(1, 29);
                        }
                        else
                        {
                            printf("Day (1-28)  : ");
                            searchDate.day = inputIntRange(1, 28);
                        }
                        break;
                    case 3:
                        printf("Day (1-31)  : ");
                        searchDate.day = inputIntRange(1, 31);
                        break;
                    case 4:
                        printf("Day (1-30)  : ");
                        searchDate.day = inputIntRange(1, 30);
                        break;
                    case 5:
                        printf("Day (1-31)  : ");
                        searchDate.day = inputIntRange(1, 31);
                        break;
                    case 6:
                        printf("Day (1-30)  : ");
                        searchDate.day = inputIntRange(1, 30);
                        break;
                    case 7:
                        printf("Day (1-31)  : ");
                        searchDate.day = inputIntRange(1, 31);
                        break;
                    case 8:
                        printf("Day (1-31)  : ");
                        searchDate.day = inputIntRange(1, 31);
                        break;
                    case 9:
                        printf("Day (1-30)  : ");
                        searchDate.day = inputIntRange(1, 30);
                        break;
                    case 10:
                        printf("Day (1-31)  : ");
                        searchDate.day = inputIntRange(1, 31);
                        break;
                    case 11:
                        printf("Day (1-30)  : ");
                        searchDate.day = inputIntRange(1, 30);
                        break;
                    case 12:
                        printf("Day (1-31)  : ");
                        searchDate.day = inputIntRange(1, 31);
                        break;
                    default:
                        printf("ERROR TRAP: You shouldn't be seeing this\n");
                        break;
                    }
                    printf("\n");     
                    noAppointments = 1;
                }
                else
                {
                    noAppointments = 0;
                }
            }
        }
        if (compare == 1)
        {
            noAppointments = 1;
            for (i = 0; i < data->maxAppointments; i++)
            {
                if (searchDate.year == data->appointments[i].date.year)
                {
                    if (searchDate.month == data->appointments[i].date.month)
                    {
                        if (searchDate.day == data->appointments[i].date.day)
                        {
                            noAppointments = 0;
                            for (j = 0; j < data->maxPatient; j++)
                            {
                                if ((searchNum == data->patients[j].patientNumber) && (data->appointments[i].patientNumber == data->patients[j].patientNumber))
                                {
                                    printf("Name  : %s\n", data->patients[j].name);
                                    printf("Number: %05d\n", data->patients[j].patientNumber);
                                    printf("Phone : ");
                                    displayFormattedPhone(data->patients[j].phone.number);
                                    printf(" (%s)\n", data->patients[j].phone.description);
                                    printf("Are you sure you want to remove this appointment (y,n): ");
                                    removeConfirm = inputCharOption("yn");
                                    if (removeConfirm == 'y')
                                    {
                                        data->appointments[i] = empty;
                                        printf("\nAppointment record has been removed!\n\n");
                                        clearInputBuffer();

                                    }
                                    else
                                    {
                                        printf("\nOperation Aborted.\n\n");
                                        clearInputBuffer();
                                    }
                                }
                                else
                                {

                                }
                            }
                        }
                        else
                        {
                        }
                    }
                    else
                    {
                    }
                }
                else
                {
                }
            }


        }



        if (noAppointments == 1)
        {
            if (error == 0)
            printf("ERROR: Appointment record not found!\n\n");
        }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientNumber, i;
    printf("\nSearch by patient number: ");
    scanf("%d", &patientNumber);
    printf("\n");
    i = findPatientIndexByPatientNum(patientNumber, patient, max);
    if (i == -1)
    {
        printf("*** No records found ***\n");
    }
    else
    {
        displayPatientData(&patient[i], FMT_FORM);

    }
    printf("\n");
}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i, noNum = 0;
    char phoneNum[PHONE_LEN + 1];
    printf("\nSearch by phone number: ");
    scanf("%10s", phoneNum);
    printf("\n");
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (strcmp(phoneNum, patient[i].phone.number) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
            noNum = 1;
        }
    }
    if (noNum == 0)
    {
        printf("\n*** No records found ***\n");
    }
    printf("\n");
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int temp = 0, i;
    for (i = 0; i < max; i++)
    {
        if (temp < patient[i].patientNumber)
        {
            temp = patient[i].patientNumber;
        }
    }
    temp++;
    return temp;
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max)
{
    int i, found = -1;
    for (i = 0; i < max; i++)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            found = i;
        }
    }
    return found;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    int len, error = 0;
    char copy[50] = { '\0' };
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    do
    {
        scanf("%[^\n]", copy);

        len = (strlen(copy));
        if (len > NAME_LEN)
        {
            printf("ERROR: String length must be no more than 15 chars: ");
            error = 1;
            clearInputBuffer();
        }
        else
        {
            strcpy(patient->name, copy);
            error = 0;
        }
    } while (error == 1);

    clearInputBuffer();
    printf("\n");
    inputPhoneData(&patient->phone);
    printf("*** New patient record added ***\n\n");

}

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    char tempNumber[80] = { '\0' };
    int contactMethod, noNum = 0, error = 0, len;
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    contactMethod = inputIntRange(1, 4);
    switch (contactMethod)
    {
    case 1:
        strcpy(phone->description, "CELL");
        printf("\n");
        break;
    case 2:
        strcpy(phone->description, "HOME");
        printf("\n");
        break;
    case 3:
        strcpy(phone->description, "WORK");
        printf("\n");
        break;
    case 4:
        strcpy(phone->description, "TBD");
        noNum = 1;
        break;
    }
    if (noNum == 0)
    {
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        do
        {
            error = 0;
            scanf("%[^\n]", tempNumber);
            len = strlen(tempNumber);
            if (len != 10)
            {
                printf("Invalid 10-digit number! Number: ");
                error = 1;
                clearInputBuffer();
            }
            else
            {
                error = 0;
                strcpy(phone->number, tempNumber);
            }

        } while (error == 1);
        //scanf("%10s", phone->number);
        clearInputBuffer();
    }
    printf("\n");
}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient pets[], int max)
{
    FILE* fp = NULL;
    fp = fopen("patientData.txt", "r");
    int i = 0, record = 0, entries = 0;
    if (fp!= NULL)
    {
        do
        {
                record = fscanf(fp, "%d|%15[^|]|%4[^|]|%10[^\n]", &pets[i].patientNumber, pets[i].name, pets[i].phone.description, pets[i].phone.number);
                i++;
                if (record >= 3) entries++;
                if (entries > 20) entries = 20;
                    
        } while (feof(fp) == 0);
    }
    fclose(fp);
    fp = NULL;
    return entries;
}


// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    FILE* fp = NULL;
    fp = fopen("appointmentData.txt", "r");
    int i = 0, c, appointments = 0;
    if (fp != NULL)
    {
        do
        {
            c = fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[i].patientNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min);
            i++;
            if (c == 6) appointments++;
            if (appointments > 50) appointments = 50;
        } while (feof(fp) == 0);
    }

    fclose(fp);
    fp = NULL;
    return appointments;
}

