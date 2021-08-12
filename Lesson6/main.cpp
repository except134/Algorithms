#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

///////////////
// Задача 1

void SwapInt(int& a, int& b)
{
    int t = a;
    a = b;
    b = t;
}

void PrintArrayBubble(int *const *array, int sizeX, int sizeY)
{
    for(int y = 0; y < sizeY; ++y) {
        for(int x = 0; x < sizeX; ++x) {
            printf("%4d", array[y][x]);
        }
        printf("\n");
    }
}

// Сортировка пузырьком двумерного массива через одномерный массив
void BubbleSort(int *const *array, int sizeX, int sizeY)
{
    for (int xy = 0; xy < sizeX * sizeY; ++xy) {
        int cur_y = (xy / sizeY);
        int cur_x = xy - cur_y * sizeX;
        for(int index = 0; index <= xy; ++index) {
            int y = (index / sizeX);
            int x = index - y * sizeY;
            if(array[cur_y][cur_x] < array[y][x]) {
                SwapInt(array[cur_y][cur_x], array[y][x]);
            }
        }
    }
}

void Task1()
{
    int** array{};
    int sizeX, sizeY;

    srand(time(0));

    printf("\nЗадача 1.\nВведите ширину массива: ");
    scanf("%d", &sizeX);
    printf("Введите высоту массива: ");
    scanf("%d", &sizeY);

    array = (int**)malloc(sizeY * sizeof(int*));
    for(int y = 0;y < sizeY; ++y) {
        array[y] = (int*)malloc(sizeX * sizeof(int));
        for(int x = 0; x < sizeX; ++x) {
            array[y][x] = rand()%100;
        }
    }

    printf("Сгенерированный массив\n\n");
    PrintArrayBubble(array, sizeX, sizeY);

    BubbleSort(array, sizeX, sizeY);

    printf("\nОтсортированный массив\n\n");
    PrintArrayBubble(array, sizeX, sizeY);

    for(int y = 0;y < sizeY; ++y) {
        free(array[y]);
    }
    free(array);
}

///////////////
// Задача 2

void SwapDouble(double& a, double& b)
{
    double t = a;
    a = b;
    b = t;
}

void PrintArrayTPK(const double *array) {
    for (int index = 0; index < 11; ++index) {
        printf("%lf ", array[index]);
    }
    printf("\n");
}

void Task2()
{
    double array[11] = {0}, y = 0, *head = nullptr, *tail = nullptr;

    printf("\nЗадача 2.\n");

    for (int index = 0; index < 11; ++index) {
        printf("Введите число %d: ", index + 1);
        scanf("%lf", &array[index]);
    }

    printf("Введенная последовательность:\n");
    PrintArrayTPK(array);

    for(head = &array[0], tail = &array[0] + (sizeof(array) / sizeof(array[0])) - 1; head < tail; ++head, --tail )
        SwapDouble(*head, *tail);

    printf("Инвертированная последовательность:\n");
    PrintArrayTPK(array);

    printf("\n");

    for (int index = 0; index < 11; ++index) {
        y = sqrt(fabs(array[index])) + 5 * pow(array[index], 3);

        if (y > 400)
            printf("Число %lf слишком большое\n", array[index]);
        else
            printf("Число %lf %.16g\n", array[index], y);
    }
}

int main()
{
    Task1();
    Task2();

    return 0;
}
