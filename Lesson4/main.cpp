#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

///////////////
// Задача 1

void Dec2Bin(unsigned int num)
{
    if(num) {
        Dec2Bin(num >> 1);
        printf("%d", num & 1);
    }
}

void Task1()
{
    unsigned int num = 0;

    printf("\nЗадача 1.\nВведите число: ");
    scanf("%d", &num);
    Dec2Bin(num);
    printf("\n");
}

///////////////
// Задача 2

double Pow(double baseval, unsigned int exponent)
{
    if(exponent == 0) {
        return 1;
    }

    if(exponent == 1) {
        return baseval;
    }

    return baseval * Pow(baseval, exponent - 1);
}

void Task2_1()
{
    double baseval = .0;
    unsigned int exponent = 0;

    printf("\nЗадача 2.1.\nВведите число: ");
    scanf("%lf", &baseval);
    printf("Введите степень: ");
    scanf("%d", &exponent);

    double ret = Pow(baseval, exponent);

    printf("%.2lf в степени %d = %.2lf\n", baseval, exponent, ret);
}

double BinPow(double baseval, unsigned int exponent)
{
    if(exponent == 0)
        return 1;

    double x = (exponent % 2) ? baseval : 1;
    double c = BinPow(baseval, exponent / 2);

    return x * c * c;
}

void Task2_2()
{
    double baseval = .0;
    unsigned int exponent = 0;

    printf("\nЗадача 2.2.\nВведите число: ");
    scanf("%lf", &baseval);
    printf("Введите степень: ");
    scanf("%d", &exponent);

    double ret = BinPow(baseval, exponent);

    printf("%.2lf в степени %d = %.2lf\n", baseval, exponent, ret);
}

///////////////
// Задача 3

int ChessRoutes(unsigned int x, unsigned int y, unsigned int width, char* field)
{
    if((x == 0 && y == 0) || *(field + y * width + x) == '1')
        return 0;
    else if(x == 0 ^ y == 0)
        return 1;
    else
        return ChessRoutes(x, y - 1, width, field) + ChessRoutes(x - 1, y, width, field);
}

void Task3()
{
    srand(time(NULL));

    unsigned int width = 0, height = 0;

    printf("\nЗадача 3.\nВведите ширину поля: ");
    scanf("%d", &width);
    printf("Введите высоту поля: ");
    scanf("%d", &height);

    char* field = NULL;
    field = (char*)malloc(width * height * sizeof(char));

    if(!field) {
        printf("Error! No memory.\n");
        return;
    }

    for(int i = 0; i < width * height; ++i)
        field[i] = rand()%100 > 90 ? '1' : '0';

    printf("Массив барьеров: %s\n\n", field);

    unsigned int maxSteps = 0;

    for(unsigned int y = 0; y < height; ++y) {
        for(unsigned int x = 0; x < width; ++x) {
            maxSteps = ChessRoutes(x, y, width, field);
            printf("%5d", maxSteps);
        }
        printf("\n");
    }

    printf("\nМаксимальное количество ходов королем: %d\n", maxSteps);

    free(field);
}

int main()
{
    Task1();
    Task2_1();
    Task2_2();
    Task3();

    return 0;
}
