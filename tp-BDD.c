#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
typedef struct record
{
    int Id;
    char TakeOffCity[20];
    char ArriveCity[20];
    char TakeOffTime[20];
    char ArriveTime[20];
} record;
//------------------------------------------------------------helpfull functions------------------------------------------------//
bool testIfstring(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isalpha(str[i]))
        {
            return false; // Not alphabetic
        }
    }
    return true; // Alphabetic
}

bool testIftime(char *str)
{
    // Check if string has exactly 5 characters
    if (strlen(str) != 5)
    {
        return false;
    }

    // Check if first two characters are valid hours (00-23)
    int hours = atoi(str);
    if (hours < 0 || hours > 23)
    {
        return false;
    }

    // Check if third character is a colon
    if (str[2] != ':')
    {
        return false;
    }

    // Check if last two characters are valid minutes (00-59)
    int minutes = atoi(str + 3);
    if (minutes < 0 || minutes > 59)
    {
        return false;
    }

    return true; // Valid time
}

int generateRandomNumber()
{
    int num;
    srand(time(NULL));
    num = rand() % 1000; // generate random numbers of three digit (between 0 and 999)
    return num;
}

bool RepeatedID(FILE *file, int ID)
{
    file = fopen("flightList", "r");
    record flight;
    while (fscanf(file, "%3d %20s %20s %6s %6s", &flight.Id, flight.TakeOffCity, flight.ArriveCity, flight.TakeOffTime, flight.ArriveTime) != EOF)
    {
        if (ID == flight.Id)
        {
            fclose(file);
            return true; // this is Id is repeated
        }
    }
    fclose(file);

    return false; // Not repeated
}
void selection_sort(record arr[], int n) // Selection Sort Used to Sort the flights by the take-off time
{
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(arr[j].TakeOffTime, arr[min_idx].TakeOffTime) < 0)
            {
                min_idx = j;
            }
        }
        record temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}
void displayBeforeAndAfterS(FILE *tmp, FILE *file) // display the state before and after the Sorting the filghts
{
    file = fopen("flightList", "r");
    record before;
    record after;
    char line[100];
    if (file == NULL)
    {
        printf("ther's an error");
        exit(1);
    }
    tmp = fopen("tmp", "r");
    if (tmp == NULL)
    {
        printf("there's an Error !!");
        exit(1);
    }
    bool noChanges = true;
    int i = 1;
    printf("+-----------------------------------------------------------------+     +-----------------------------------------------------------------+\n");
    printf("|                  Display flight (Before):                       | ==> |                  Display flight (After):                        |\n");
    printf("+-----------------------------------------------------------------+     +-----------------------------------------------------------------+\n");
    printf("|Nbr|ID |    Take off city   |    Arrive city     | Ttime | Atime |     |Nbr|ID |    Take off city   |    Arrive city     | Ttime | Atime |\n");
    printf("+-----------------------------------------------------------------+     +-----------------------------------------------------------------+\n");
    while (fscanf(file, "%3d %20s %20s %6s %6s", &before.Id, before.TakeOffCity, before.ArriveCity, before.TakeOffTime, before.ArriveTime) != EOF && fscanf(tmp, "%3d %20s %20s %6s %6s", &after.Id, after.TakeOffCity, after.ArriveCity, after.TakeOffTime, after.ArriveTime) != EOF)
    {
        if (before.Id != after.Id)
        {
            printf("\x1b[31m|%3d|%3d|%20s|%20s|%7s|%7s| ==> \x1b[0m", i, before.Id, before.TakeOffCity, before.ArriveCity, before.TakeOffTime, before.ArriveTime);
            printf("\x1b[32m|%3d|%3d|%20s|%20s|%7s|%7s|\x1b[0m\n", i, after.Id, after.TakeOffCity, after.ArriveCity, after.TakeOffTime, after.ArriveTime);
            noChanges = false;
        }
        else
        {
            printf("|%3d|%3d|%20s|%20s|%7s|%7s|     ", i, before.Id, before.TakeOffCity, before.ArriveCity, before.TakeOffTime, before.ArriveTime);
            printf("|%3d|%3d|%20s|%20s|%7s|%7s|\n", i, after.Id, after.TakeOffCity, after.ArriveCity, after.TakeOffTime, after.ArriveTime);
        }
        i++;
    }
    if (i == 1)
    {
        printf("|                                                            \x1b[36mThere's no flight\x1b[0m                                                            |\n");
        printf("+-----------------------------------------------------------------+     +-----------------------------------------------------------------+\n");
    }
    else if (noChanges)
    {
        printf("+------------------------------------------------------------+\x1b[33mther's no changes\x1b[0m+----------------------------------------------------------+\n");
    }
    else
    {
        printf("+--------------------------------------------------------------+\x1b[33mther's changes\x1b[0m+-----------------------------------------------------------+\n");
    }
    fclose(file);
    fclose(tmp);
}

void displayBeforeAndAfterD(FILE *tmp, FILE *file, int id) // display the state before and after deleting a flight
{
    file = fopen("flightList", "r");
    record before;
    record after;
    char line[100];
    if (file == NULL)
    {
        printf("ther's an error here in file");
        exit(1);
    }
    tmp = fopen("tmp", "r");
    if (tmp == NULL)
    {
        printf("there's an Error !!  here in tmp");
        exit(1);
    }
    bool noChanges = true;
    int i = 1;
    printf("+-----------------------------------------------------------------+     +-----------------------------------------------------------------+\n");
    printf("|                  Display flight (Before):                       | ==> |                  Display flight (After):                        |\n");
    printf("+-----------------------------------------------------------------+     +-----------------------------------------------------------------+\n");
    printf("|Nbr|ID |    Take off city   |    Arrive city     | Ttime | Atime |     |Nbr|ID |    Take off city   |    Arrive city     | Ttime | Atime |\n");
    printf("+-----------------------------------------------------------------+     +-----------------------------------------------------------------+\n");
    while (fscanf(file, "%3d %20s %20s %6s %6s", &before.Id, before.TakeOffCity, before.ArriveCity, before.TakeOffTime, before.ArriveTime) != EOF)
    {
        if (before.Id == id)
        {
            printf("\x1b[31m|%3d|%3d|%20s|%20s|%7s|%7s| ==> \x1b[0m", i, before.Id, before.TakeOffCity, before.ArriveCity, before.TakeOffTime, before.ArriveTime);
            printf("\x1b[32m|                            deleted                              |\x1b[0m\n");
            noChanges = false;
        }
        else
        {
            printf("|%3d|%3d|%20s|%20s|%7s|%7s|     ", i, before.Id, before.TakeOffCity, before.ArriveCity, before.TakeOffTime, before.ArriveTime);
            if (fscanf(tmp, "%3d %20s %20s %6s %6s", &after.Id, after.TakeOffCity, after.ArriveCity, after.TakeOffTime, after.ArriveTime) != EOF)
                printf("|%3d|%3d|%20s|%20s|%7s|%7s|\n", i, after.Id, after.TakeOffCity, after.ArriveCity, after.TakeOffTime, after.ArriveTime);
            else
                printf("\n");
        }
        i++;
    }
     if (i == 1)
    {
        printf("|                                                            \x1b[36mThere's no flight\x1b[0m                                                             |\n");
        printf("+-----------------------------------------------------------------+     +-----------------------------------------------------------------+\n");
    }
    else if (noChanges)
    {
        printf("+--------------------------------------------------------------+\x1b[33mno changes\x1b[0m+---------------------------------------------------------------+\n");
        printf(">>\x1b[31m There's no flight with the entered ID\n\x1b[0m");
    }

    else
    {
        printf("+----------------------------------------------------------------+\x1b[33mdeleted\x1b[0m+----------------------------------------------------------------+\n");
    }
    fclose(file);
    fclose(tmp);
}

    //------------------------------------------------------------main functons------------------------------------------------//
    void AddFlight(record flight, FILE * file)
    {
        printf("+----------------------------------------------------------+\n");
        printf("                         Add a flight                       \n");
        printf("+----------------------------------------------------------+\n");
    jump: // generat an Id for the new flight
        flight.Id = generateRandomNumber();
        if (RepeatedID(file, flight.Id))
        {
            goto jump;
        }

    jump2: // read the take-off city from the user
        printf("\n> Take-off city: ");
        scanf("%s", flight.TakeOffCity);
        if (testIfstring(flight.TakeOffCity) == false)
        {
            printf(">> \x1b[31mthis input is invald!, ");
            printf("the input can only contain regular alphabets case/lower case or undercore or a hyphen.\x1b[0m\n>> \x1b[33mRe-enter:\x1b[0m");
            goto jump2;
        }
        else if (strlen(flight.TakeOffCity) > 20)
        {
            printf(">> \x1b[31myour input contain more than 20 charecters try again:\x1b[0m\n>> \x1b[33mRe-enter:\x1b[0m");
            goto jump2;
        }

    jump3: // read the Arrive city form the user
        printf("\n> Arrive city: ");
        scanf("%s", flight.ArriveCity);
        if (testIfstring(flight.ArriveCity) == false)
        {
            printf(">> \x1b[31mthis input is invald!, ");
            printf("the input can only contain regular alphabets case/lower case or undercore or a hyphe.\x1b[0m\n>> \x1b[33mRe-enter:\x1b[0m");
            goto jump3;
        }
        else if (strlen(flight.ArriveCity) > 20)
        {
            printf(">> \x1b[31myour input contain more than 20 charecters try again:\x1b[0m\n>> \x1b[33mRe-enter:\x1b[0m");
            goto jump3;
        }
        if (strcmp(flight.ArriveCity, flight.TakeOffCity) == 0)
        {
            printf(">> \x1b[31mThe Arrive city is the same as the take off city:\x1b[0m\n>> \x1b[33mRe-enter:\x1b[0m");
            goto jump3;
        }

    jump4: // read the take-off time from the user
        printf("\n> Time of take-off (hh:mm): ");
        scanf("%s", flight.TakeOffTime);
        if (testIftime(flight.TakeOffTime) == false)
        {
            printf(">> \x1b[31mthis input is invald!, ");
            printf("time input should be as following hh:mm.\x1b[0m\n>> \x1b[33mRe-enter:\x1b[0m");
            goto jump4;
        }

    jump5: // read the Arrive time from the user
        printf("\n> Arrive time (hh:mm): ");
        scanf("%s", flight.ArriveTime);
        if (testIftime(flight.ArriveTime) == false)
        {
            printf(">> \x1b[31mthis input is invald!, ");
            printf("time input should be as following hh:mm.\x1b[0m\n>> \x1b[33mRe-enter:\x1b[0m");
            goto jump5;
        }

        // affecting all the readed and checked values to the file (flightList)
        file = fopen("flightList", "a"); // opening the file in the appand mode to add the new flight to the other flights
        fprintf(file, "%3d %20s %20s %6s %6s \n", flight.Id, flight.TakeOffCity, flight.ArriveCity, flight.TakeOffTime, flight.ArriveTime);
        printf("+---------------------------------+");
        printf("\x1b[32m Flight included succesfully.\x1b[0m "); // message of succes
        printf("+---------------------------------+\n");
        fclose(file);
    }

    int DisplayAllFlights(FILE * file)
    {
        file = fopen("flightList", "r");
        record flight;
        if (file == NULL)
        {
            printf("ther's an error");
            exit(1);
        }
        printf("+-----------------------------------------------------------------+\n");
        printf("                          Display flight :                         \n");
        printf("+-----------------------------------------------------------------+\n");
        printf("|Nbr|ID |    Take off city   |    Arrive city     | Ttime | Atime |\n");
        printf("+-----------------------------------------------------------------+\n");
        int i = 1;
        while (fscanf(file, "%3d %20s %20s %6s %6s", &flight.Id, flight.TakeOffCity, flight.ArriveCity, flight.TakeOffTime, flight.ArriveTime) != EOF) // display the content of file (flightList) line per line till the end of the file
        {
            printf("|%3d|%3d|%20s|%20s|%7s|%7s|\n", i, flight.Id, flight.TakeOffCity, flight.ArriveCity, flight.TakeOffTime, flight.ArriveTime);
            i++;
        }
        if (i == 1)
        {
            printf("|                          \x1b[36mThere's no flight\x1b[0m                      |\n");
        }
        printf("+-----------------------------------------------------------------+\n");
        fclose(file);
        if (i == 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

   
void DeleteFlight(FILE *file) // delet a flight
{
    file = fopen("flightList", "r");
    if (file == NULL)
    {
        printf("there's an Error !!");
        exit(1);
    }

    char line[100];
    int IdToDelet;
    if (DisplayAllFlights(file)) // verifing if the there's flight to delete it or not
    {
        printf("\x1b[31m >> there's no flight to delete\n \x1b[0m");
        fclose(file);
        goto quit;
    }

    FILE *tmp = fopen("tmp", "w"); // open this tmp file in write mode to copy all the filght that are in the file (flightList) expect the flight that we wanna delet .

    if (tmp == NULL)
    {
        printf("there's an Error !!");
        exit(1);
    }

    printf("> Enter the Id to delete the flight: "); // read the Id of the flight that we wanna delet
    scanf("%d", &IdToDelet);
    char Id[4];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        for (int i = 0; i < 3; i++)
            Id[i] = line[i];
        if (IdToDelet != strtol(Id, NULL, 10))
        {
            fputs(line, tmp);
        }
    }

    fclose(tmp);
    fclose(file);
    displayBeforeAndAfterD(tmp, file, IdToDelet); // display the list after deleting the selected flight
    remove("flightList");
    rename("tmp", "flightList");
quit:
}

void SortFlight(FILE *file) // Sorting the file
{
    file = fopen("flightList", "r"); // open the file in read mode
    if (file == NULL)
    {
        printf("there's an Error !!");
        exit(1);
    }
    record Array[100];
    int i = 0;
    while (fscanf(file, "%d %20s %20s  %5s  %5s", &Array[i].Id, Array[i].TakeOffCity, Array[i].ArriveCity, Array[i].TakeOffTime, Array[i].ArriveTime) != EOF)
    {
        i++;
    }
    selection_sort(Array, i); // using the selction sort for sorting
    FILE *tmp = fopen("tmp", "w");
    if (tmp == NULL)
    {
        printf("there's an Error !!");
        exit(1);
    }

    int n = i;
    for (i = 0; i < n; i++)
    {
        fprintf(tmp, "%3d %20s %20s %6s %6s \n", Array[i].Id, Array[i].TakeOffCity, Array[i].ArriveCity, Array[i].TakeOffTime, Array[i].ArriveTime);
    }

    fclose(file);
    fclose(tmp);
    displayBeforeAndAfterS(tmp, file);
    remove("flightList");
    rename("tmp", "flightList");
}
int main(int argc, char const *argv[]) // the main that will call all the main function that we need
{
    FILE *FlighList;
    record flight;
    do
    {
        printf("+---------------------------------------------------------------+\n");
        printf("|                             Menu :                            |\n");
        printf("|---------------------------------------------------------------|\n");
        printf("| [1] Add a flight:                                             |\n");
        printf("| [2] Display all the flights:                                  |\n");
        printf("| [3] Delete a flight:                                          |\n");
        printf("| [4] Sort the flight:                                          |\n");
        printf("| [0] Exit:                                                     |\n");
        printf("+---------------------------------------------------------------+\n");
        int choix;
        printf(">Enter your choice: ");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1: // add a fly
            system("cls");
            AddFlight(flight, FlighList);
            printf("> presse [Enter] to continue: ");
            fflush(stdin); // to clean the buffer
            getc(stdin);   // to catch any key preesed from the user
            break;
        case 2: // display all the list
            system("cls");
            char any;
            DisplayAllFlights(FlighList);
            printf("> presse [Enter] to continue: ");
            fflush(stdin); // to clean the buffer
            getc(stdin);   // to catch any key preesed from the user
            break;
        case 3: // delete fly
            system("cls");
            DeleteFlight(FlighList);
            printf("> presse [Enter] to continue: ");
            fflush(stdin); // to clean the buffer
            getc(stdin);   // to catch any key preesed from the user
            break;
        case 4: // sort fly
            system("cls");
            SortFlight(FlighList);
            printf("> presse [Enter] to continue: ");
            fflush(stdin); // to clean the buffer
            getc(stdin);   // to catch any key preesed from the user
            break;
        case 0:
            system("cls");
            exit(1);
            break;
        default:
            printf("Invalide choice\n");
            break;
        }
        system("cls");

    } while (1);

    return 0;
}