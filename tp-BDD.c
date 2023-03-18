#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct record
{
    int Id;
    char TakeOffCity[20];
    char ArriveCity[20];
    char TakeOffTime[20];
    char ArriveTime[20];
} record;
// int getId(FILE *file)
// {
//     char line[4];
//     file = fopen("record", "r");
//     if (file == NULL)
//     {
//         return 0;
//     }
//     fseek(file, 0, SEEK_END);
//     fseek(file, -60, SEEK_CUR);
//     fgets(line, sizeof(line), file);
//     int num;
//     num = strtol(line, NULL, 10);
//     fclose(file);
//     return num;
// }
void AddFlight(record flight, FILE *file)
{
    file = fopen("flightList", "a");
    printf("------------------------------------------------------------\n");
    printf("                       Ajouter un flight                    \n");
    printf("------------------------------------------------------------\n");
    printf("\n> flight Id: ");
    scanf("%d", &flight.Id);
    printf("\n> la ville de depart: ");
    scanf("%s", flight.TakeOffCity);
    printf("\n> la ville de d'arrivee: ");
    scanf("%s", flight.ArriveCity);
    printf("\n> l'heure de depart (hh:mm): ");
    scanf("%s", flight.TakeOffTime);
    printf("\n> l'heure d'arrivee (hh:mm): ");
    scanf("%s", flight.ArriveTime);
    fprintf(file, "%3d %20s %20s %6s %6s \n", flight.Id, flight.TakeOffCity, flight.ArriveCity, flight.TakeOffTime, flight.ArriveTime);
    printf("--------------------------------------------------------------\n");
    fclose(file);
}

void DisplayAllFlights(FILE *file)
{
    file = fopen("flightList", "r");
    record flight;
    char line[100];
    if (file == NULL)
    {
        printf("ther's an error");
        exit(1);
    }
    printf("-------------------------------------------------------------------\n");
    printf("                          Display flight :                         \n");
    printf("-------------------------------------------------------------------\n");
    printf("|Nbr|ID |    Take off city   |    Arrive city     | Ttime | Atime |\n");
    printf("-------------------------------------------------------------------\n");
    int i = 1;
    while (fscanf(file, "%3d %20s %20s %6s %6s", &flight.Id, flight.TakeOffCity, flight.ArriveCity, flight.TakeOffTime, flight.ArriveTime) != EOF)
    {
        printf("|%3d|%3d|%20s|%20s|%7s|%7s|\n", i, flight.Id, flight.TakeOffCity, flight.ArriveCity, flight.TakeOffTime, flight.ArriveTime);
        i++;
    }
    printf("-------------------------------------------------------------------\n");
    fclose(file);
}
void DeleteFlight(FILE *file)
{
    file = fopen("flightList", "r");
    if (file == NULL)
    {
        printf("there's an Error !!");
        exit(1);
    }

    FILE *tmp = fopen("tmp.txt", "w");
    if (tmp == NULL)
    {
        printf("there's an Error !!");
        exit(1);
    }
    char line[100];
    int IdToDelet;
    DisplayAllFlights(file);
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
    fclose(file);
    fclose(tmp);
    remove("flightList");
    rename("tmp.txt", "flightList");
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
        printf("there's an Error !!");
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
    remove("flightList");
    rename("tmp", "flightList");
}
int main(int argc, char const *argv[])
{
    FILE *FlighList;
    record flight;
    do
    {
        printf(" --------------------------------------------------------------- \n");
        printf("|                             Menu :                            |\n");
        printf("|---------------------------------------------------------------|\n");
        printf("| [1] Add a flight:                                             |\n");
        printf("| [2] Display all the flights:                                  |\n");
        printf("| [3] Delete a flight:                                          |\n");
        printf("| [4] Sort the flight:                                          |\n");
        printf("| [0] Exit:                                                     |\n");
        printf(" --------------------------------------------------------------- \n");
        int choix;
        printf(">Enter your choice: ");
        scanf("%d", &choix);
        switch (choix)
        {
        case 1:
            system("cls");
            AddFlight(flight, FlighList);
            break;
        case 2:
            system("cls");
            char any;
            DisplayAllFlights(FlighList);
            printf("> presse [any key + Enter] to continue: ");
            scanf(" %c", &any);
            break;
        case 3:
            system("cls");
            DeleteFlight(FlighList);
            break;
        case 4:
            system("cls");
            SortFlight(FlighList);
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
//toDo: adding the before after display in the sorting function.
//toDo: adding controls to the inputs in the add function.
    //date control
    //repeted Id
    //two flights with the same parameters (the same : take off palce and the same time of take off)