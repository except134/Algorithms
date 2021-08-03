#include <stdlib.h>
#include <stdio.h>
#include <math.h>

bool IsPrime(int val)
{
    int finish = sqrt(abs(val));
    for (int i = 2; i <= finish; i++) {
        if (val % i == 0) {
            return false;
        }
    }
    return true;
}

int main()
{
    int num = 0;

    printf("Введите число: ");

    scanf("%d", &num);

    printf("Число %d %sпростое\n",num,IsPrime(num)?"":"не ");

    return 0;
}
