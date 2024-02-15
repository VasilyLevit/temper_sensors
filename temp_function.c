#include <stdio.h>
#include "temp_function.h"
#include <string.h>

void cgangeIJ(struct sensor *info, int i, int j)
{
    struct sensor temp;
    temp = info[i];
    info[i] = info[j];
    info[j] = temp;
}
//упорядочивающую его по неубыванию температуры
void SortByT(struct sensor *info, int n)
{
    for(int i = 0; i < n; ++i)
        for(int j = i; j < n; ++j)
            if(info[i].t >= info[j].t)
                cgangeIJ(info, i, j);
}
unsigned int DateToInt(struct sensor *info)
{
    return info->year << 16 | info->month << 8 |
           info->day;
}
//упорядочивающую его по дате
void SortByDate(struct sensor *info, int n)
{
    for(int i = 0; i < n; ++i)
        for(int j = i; j < n; ++j)
            if(DateToInt(info+i) >= DateToInt(info+j))
                  cgangeIJ(info, i, j);
}
//запись данных в массив
void AddRecord(struct sensor *info, uint32_t number, uint16_t year, uint8_t month, uint8_t day, u_int8_t hour, u_int8_t minute, int8_t t)
{
    info[number].year = year;
    info[number].month = month;
    info[number].day = day;
    info[number].hour = hour;
    info[number].minute = minute;
    info[number].t = t;
}
//тестовые данные для записи в массив
int AddInfo(struct sensor *info)
{
    int counter = 0; 
    AddRecord(info, counter++, 2021, 9, 16, 12, 45, 9);
    AddRecord(info, counter++, 2022, 9, 2, 12, 45, -9);
    AddRecord(info, counter++, 2021, 1, 7, 12, 45, 8);
    AddRecord(info, counter++, 2021, 9, 5, 12, 45, 1);
    return counter;
}
void Print(struct sensor *info, uint32_t number)
{
    printf("===================================\n");
    for(int i = 0; i < number; i++)
        printf("%04d-%02d-%02d-%02d-%02d t=%3d\n",
            info[i].year,
            info[i].month,
            info[i].day,
            info[i].hour,
            info[i].minute,
            info[i].t);
}
//функция выборки данных из массива по ключам
void DataSampling(struct sensor *info, uint32_t number, char *numMonth)
{
    int32_t sum = 0;
    int32_t count = 0;
    int8_t max, min;
    max = info[0].t;
    min = info[0].t;

    for(int i = 0; i < number; i++)     
        if (numMonth == NULL) //by year
        {
            count++;
            sum += info[i].t;
            if (max < info[i].t)
                max = info[i].t;
            else if (min > info[i].t)
                min = info[i].t;
        }
        else if (info[i].month == *numMonth-48) //filter by month
        {            
            count++;
            sum += info[i].t;
            if (max < info[i].t)
                max = info[i].t;
            else if (min > info[i].t)
                min = info[i].t;
        }
    // printf("month: %d\n", *numMonth-48); //test    
    printf("number of values: %d\n", count); //test   
    printf("month: %s\n", numMonth);
    printf("average temperature: %d\n", sum/count);
    printf("max temperature: %d\n", max);
    printf("min temperature: %d\n", min);
}