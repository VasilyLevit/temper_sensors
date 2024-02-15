#include <stdint.h>
#define SIZE 518402
struct sensor {
    uint8_t day;
    uint8_t month;
    uint16_t year;
    uint8_t hour;
    uint8_t minute;
    int8_t t;
};
void cgangeIJ(struct sensor *info, int i, int j);
//упорядочивающую его по неубыванию температуры
void SortByT(struct sensor *info, int n);
unsigned int DateToInt(struct sensor *info);
//упорядочивающую его по дате
void SortByDate(struct sensor *info, int n);
void AddRecord(struct sensor *info, uint32_t number, uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, int8_t t);
int AddInfo(struct sensor *info);
void Print(struct sensor *info, uint32_t number);
//функция выборки данных из массива по ключам
void DataSampling(struct sensor *info, uint32_t number, char *numMonth);
