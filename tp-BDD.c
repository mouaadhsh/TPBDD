#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct record
{
    int Id;
    char TakeOffCity[20];
    char ArriveCity[20];
    char TakeOffTime[20];
    char ArriveTime[20];
} record;

int asciicodeTOnumber(int num)
{
    switch (num)
    {
    case 48:
        return 0;
        break;
    case 49:
        return 1;
        break;
    case 50:
        return 2;
        break;
    case 51:
        return 3;
        break;
    case 52:
        return 4;
        break;
    case 53:
        return 5;
        break;
    case 54:
        return 6;
        break;
    case 55:
        return 7;
        break;
    case 56:
        return 8;
        break;
    case 57:
        return 9;
        break;

    default:
        return -1;
        break;
    }
}
bool testIfstring(char test[])
{
    bool res = true;
    for (int i = 0; i < strlen(test); i++)
    {
        if (res == false)
        {
            break;
        }

        int asciicode = (int)test[i];
        if ((asciicode >= 97 && asciicode <= 122) || (asciicode >= 65 && asciicode <= 90) || asciicode == 95 || asciicode == 45)
        {
            res = true;
        }
        else
        {
            res = false;
        }
    }
    return res;
}
bool testIftime(char test[])
{
    bool res;
    int first2, last2;
    if (asciicodeTOnumber(test[0]) == -1 || asciicodeTOnumber(test[1]) == -1)
    {
        return false;
    }
    else
    {
        first2 = asciicodeTOnumber(test[0]);
        first2 *= 10;
        first2 += asciicodeTOnumber(test[1]);
    }

    if (first2 >= 00 && first2 <= 23)
    {
        res = true;
    }
    else
    {
        return false;
    }
    if (test[2] == ':')
    {
        res = true;
    }
    else
    {
        return false;
    }
    if (asciicodeTOnumber(test[3]) == -1 || asciicodeTOnumber(test[4]) == -1)
    {
        return false;
    }
    else
    {
        first2 = asciicodeTOnumber(test[3]);
        first2 *= 10;
        first2 += asciicodeTOnumber(test[4]);
    }

    if (first2 >= 00 && first2 <= 59)
    {
        res = true;
    }
    else
    {
        return false;
    }
    return res;
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
            return true;
        }
    }
    fclose(file);
    
    return false;
}
void AddFlight(record flight, FILE *file)
{
    char copyid[10];
    printf("+----------------------------------------------------------+\n");
    printf("                       Ajouter un flight                    \n");
    printf("+----------------------------------------------------------+\n");
jump:
    printf("\n> flight Id: ");
    scanf("%s", copyid);
    if (strlen(copyid) > 3)
    {
        printf(">> \x1b[31myour input contain more than 3 digits try again:\x1b[0m\n>> \x1b[33mRe-enter:\x1b[0m");
        goto jump;
    }
    else if (RepeatedID(file,atoi(copyid)))
    {
        printf(">> \x1b[31mThe ID should be unique [your enterd ID is already exist]:\x1b[0m\n>> \x1b[33mRe-enter:\x1b[0m");
        goto jump;
    }

    for (int i = 0; i < strlen(copyid); i++)
    {
        if (asciicodeTOnumber((int)copyid[i]) == -1)
        {
            printf(">> \x1b[31myour input contain a non number value please try again:\x1b[0m\n>> \x1b[33mRe-enter:\x1b[0m");
            goto jump;
        }
        else
        {
            if (i == 0)
            {
                flight.Id = asciicodeTOnumber((int)copyid[0]);
            }
            else
            {
                flight.Id *= 10;
                flight.Id += asciicodeTOnumber((int)copyid[i]);
            }
        }
    }
jump2:
    printf("\n> la ville de depart: ");
    scanf("%s", flight.TakeOffCity);
    if (testIfstring(flight.TakeOffCity) == false)
    {
        printf(">> \x1b[31mthis input is invald!, ");
        printf("the input can only contain regular alphabets case/lower case or undercore or a hyphe.\x1b[0m\n>> \x1b[33mRe-enter:\x1b[0m");
        goto jump2;
    }
    else if (strlen(flight.TakeOffCity) > 20)
    {
        printf(">> \x1b[31myour input contain more than 20 charecters try again:\x1b[0m\n>> \x1b[33mRe-enter:\x1b[0m");
        goto jump2;
    }

jump3:
    printf("\n> la ville de d'arrivee: ");
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
    printf("arrive city : %s\n",flight.ArriveCity);
    printf("take off city : %s\n", flight.TakeOffCity);
    if (strcmp(flight.ArriveCity ,flight.TakeOffCity) == 0){
        printf(">> \x1b[31mThe Arrive time is the same as the take off city:\x1b[0m\n>> \x1b[33mRe-enter:\x1b[0m");
        goto jump3;
    }


jump4:
    printf("\n> l'heure de depart (hh:mm): ");
    scanf("%s", flight.TakeOffTime);
    if (testIftime(flight.TakeOffTime) == false || strlen(flight.TakeOffTime) > 5)
    {
        printf(">> \x1b[31mthis input is invald!, ");
        printf("time input should be as following hh:mm.\x1b[0m\n>> \x1b[33mRe-enter:\x1b[0m");
        goto jump4;
    }

jump5:
    printf("\n> l'heure d'arrivee (hh:mm): ");
    scanf("%s", flight.ArriveTime);
    if (testIftime(flight.ArriveTime) == false || strlen(flight.ArriveTime) > 5)
    {
        printf(">> \x1b[31mthis input is invald!, ");
        printf("time input should be as following hh:mm.\x1b[0m\n>> \x1b[33mRe-enter:\x1b[0m");
        goto jump5;
    }
    else if (strcmp(flight.ArriveTime,flight.TakeOffTime) < 0)
    {
        printf(">> \x1b[31mthis input is invald!, ");
        printf("Arrive time can't be after the take off time. \x1b[0m\n>> \x1b[33mRe-enter:\x1b[0m");
        goto jump5;
    }
    file = fopen("flightList", "a");
    fprintf(file, "%3d %20s %20s %6s %6s \n", flight.Id, flight.TakeOffCity, flight.ArriveCity, flight.TakeOffTime, flight.ArriveTime);
    printf("+------------------------------------------------------------+");
    printf("\x1b[32m Flight included succesfully.\x1b[0m ");
    printf("+------------------------------------------------------------+\n");
    fclose(file);
}

int DisplayAllFlights(FILE *file)
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
    while (fscanf(file, "%3d %20s %20s %6s %6s", &flight.Id, flight.TakeOffCity, flight.ArriveCity, flight.TakeOffTime, flight.ArriveTime) != EOF)
    {
        printf("|%3d|%3d|%20s|%20s|%7s|%7s|\n", i, flight.Id, flight.TakeOffCity, flight.ArriveCity, flight.TakeOffTime, flight.ArriveTime);
        i++;
    }
    if (i == 1)
    {
        printf("|                           \x1b[36mThere's no fly\x1b[0m                        |\n");
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
void displayBeforeAndAfterS(FILE *tmp, FILE *file)
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
        printf("|                                                             \x1b[36mThere's no fly\x1b[0m                                                              |\n");
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
void displayBeforeAndAfterD(FILE *tmp, FILE *file, int id)
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
        printf("|                                                             \x1b[36mThere's no fly\x1b[0m                                                              |\n");
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
void DeleteFlight(FILE *file)
{
    file = fopen("flightList", "r");
    if (file == NULL)
    {
        printf("there's an Error !!");
        exit(1);
    }

    char line[100];
    int IdToDelet;
    if (DisplayAllFlights(file))
    {
        printf("\x1b[31m >> there's no flight to delete\n \x1b[0m");
        fclose(file);
        goto quit;
    }

    FILE *tmp = fopen("tmp", "w");

    if (tmp == NULL)
    {
        printf("there's an Error !!");
        exit(1);
    }
    printf("> Enter the Id to delete the flight: ");
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
    displayBeforeAndAfterD(tmp, file, IdToDelet);
    remove("flightList");
    rename("tmp", "flightList");
quit:
}
void selection_sort(record arr[], int n)
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

void SortFlight(FILE *file)
{
    file = fopen("flightList", "r");
    if (file == NULL)
    {
        printf("there's an Error !! 3labali ghir hana");
        exit(1);
    }
    record Array[100];
    int i = 0;
    while (fscanf(file, "%d %20s %20s  %5s  %5s", &Array[i].Id, Array[i].TakeOffCity, Array[i].ArriveCity, Array[i].TakeOffTime, Array[i].ArriveTime) != EOF)
    {
        i++;
    }
    selection_sort(Array, i);
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
int main(int argc, char const *argv[])
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
            fflush(stdin);
            getc(stdin);
            break;
        case 2: // display all the list
            system("cls");
            char any;
            DisplayAllFlights(FlighList);
            printf("> presse [Enter] to continue: ");
            fflush(stdin);
            getc(stdin);
            break;
        case 3: // delete fly
            system("cls");
            DeleteFlight(FlighList);
            printf("> presse [Enter] to continue: ");
            fflush(stdin);
            getc(stdin);
            break;
        case 4: // sort fly
            system("cls");
            SortFlight(FlighList);
            printf("> presse [Enter] to continue: ");
            fflush(stdin);
            getc(stdin);
            break;
        case 0:
            system("cls");
            exit(1);
            break;
        default:
            printf("Unvalide choice\n");
            break;
        }
        system("cls");

    } while (1);

    return 0;
}