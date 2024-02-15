#include <stdio.h>
#include <unistd.h>
#include "temp_function.h"

//функция чтение файла данных
int ReadCsv(struct sensor *info, char *fileName, char *numMonth)
{
    int r, t;
    unsigned int y, m, d, h, minute;
    uint32_t counter = 0;

    FILE *f = fopen(fileName, "r");
    if (f == NULL)
        return 1;
    
    while ((r = fscanf(f, "%u;%u;%u;%u;%u;%d", &y, &m, &d, &h, &minute, &t)) > 0)
    {
        if (r != 6) // если число полей не равно 6-и
        {
            char s[20]; //массив для сохранения ошибочных данных в виде строки
            r = fscanf(f, "%[^\n]", s);
            printf("ERROR %d=%s\n", r, s);
        }
        else // если данные валидны
            AddRecord(info, counter++, y, m, d, h, minute, t);  
    }      
    fclose(f);
    printf("records in file: %d\n", counter); //test
    // printf("month: %s\n", numMonth); //test   
    DataSampling(info, counter, numMonth);
    return 0;
}

void PrintHelp(void)
{
    printf("-h - for help\n" 
           "-f <filename.csv> - file name for load this file\n"
           "-m <number of month> - statistic for month\n");
}

int main(int argc, char **argv)
{
    struct sensor info[SIZE]; // массив структур данных с датчика
    int param = 0;
    char *fileName, *numMonth;
    
    //обработка аргументов командной строки
    while ( (param = getopt(argc, argv, "hf:m::")) != -1)
    {
        switch (param)
        {
            case 'h': PrintHelp(); 
            break;
            case 'f': fileName = optarg;
            break;
            case 'm': numMonth = optarg;
            break;
            case '?': PrintHelp();
            break;
        }
    }
    ReadCsv(info, fileName, numMonth); //test
    return 0;
}