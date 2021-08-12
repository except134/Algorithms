#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

///////////////
// Задача 1 и 2

void SwapInt(int& a, int& b)
{
    int t = a;
    a = b;
    b = t;
}

void PrintArray(const int* array, int arrayLength)
{
    for (int index = 0; index < arrayLength; ++index) {
        printf("%d ", array[index]);
    }
    printf("\n");
}

void SortInsert(int* array, int arrayLength)
{
    for (int index = 1; index < arrayLength; index++) {
        int temp = array[index];
        for (int auxIndex = index - 1; auxIndex >= 0; auxIndex--) {
            if (array[auxIndex] < temp)
                break;

            array[auxIndex + 1] = array[auxIndex];
            array[auxIndex] = temp;
        }
    }
}

void SortHoar(int* array, int first, int last)
{
    int idxFirst = first, idxLast = last, arrayCenter = array[(first + last) / 2];

    do {
        while (array[idxFirst] < arrayCenter)
            idxFirst++;

        while (array[idxLast] > arrayCenter)
            idxLast--;

        if(idxFirst <= idxLast) {
            if (array[idxFirst] > array[idxLast])
                SwapInt(array[idxFirst], array[idxLast]);

            idxFirst++;
            idxLast--;
        }
    } while (idxFirst <= idxLast);

    if (idxFirst < last)
        SortHoar(array, idxFirst, last);

    if (first < idxLast)
        SortHoar(array, first, idxLast);
}

int MedianFrom3(int a, int b, int c)
{
    return (a > b) ^ (a > c) ? a : (a > b) ^ (b > c) ? c : b;
}

void SortBetter(int* array, int first, int last)
{
    int arrayLength = last + 1;

    if (arrayLength <= 20) {
        SortInsert(array, arrayLength);
        return;
    }

    int center = array[(first + last) / 2];
    int median = MedianFrom3(first, center, last);

    SwapInt(array[median], array[center]);

    SortHoar(array, first, last);
}

void SortBlock(int* array, int arrayLength)
{
    const int max = arrayLength;
    const int numberOfBuckets = 10;

    int bucket[numberOfBuckets][max + 1];

    for(int index = 0; index < numberOfBuckets; ++index)
        bucket[index][max] = 0;

}

void Task1_2(bool task1)
{
    int arrayLength=0;
    int* array{nullptr};

    srand(time(0));

    printf("\nЗадача %d.\nВведите длину массива: ", (int)task1 + 1);
    scanf("%d", &arrayLength);

    array=(int*)malloc(arrayLength * sizeof(int) + 1);

    for(int index = 0; index < arrayLength; ++index)
        array[index] = rand()%100;

    array[arrayLength]=0;

    printf("Сгенерированный массив:\n");
    PrintArray(array, arrayLength);

    if(!task1)
        SortBetter(array, 0, arrayLength - 1);
    else
        SortBlock(array, arrayLength);

    printf("Отсортированный массив:\n");
    PrintArray(array, arrayLength);
}

int main()
{
    Task1_2(false);
    Task1_2(true);

    return 0;
}
