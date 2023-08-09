#include <stdlib.h>
#include <stdio.h>

int compare_ints(const void *a, const void *b)
{
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;

    if (arg1 < arg2)
        return -1;
    if (arg1 > arg2)
        return 1;
    return 0;
}

struct Results
{
    int smallest;
    int largest;
    double median;
    double mean;
};

struct Results calculate(int *arr, int size)
{
    qsort(arr, size, sizeof(int), compare_ints);
    struct Results rs;
    rs.smallest = arr[0];
    rs.largest = arr[size - 1];
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    rs.mean = (double)sum / size;

    if (size % 2)
    {
        rs.median = ((double)arr[size / 2 - 1] + (double)arr[size / 2]) / 2;
    }
    else
    {
        rs.median = arr[size / 2];
    }

    return rs;
}

int main(void)
{
    int size = 6;
    int arr[6] = {1, 2, 3, 4, 5, 6};
    struct Results results = calculate(arr, size);
    printf("Smallest: %d, largest: %d, mean: %f, median: %f\n",
           results.smallest,
           results.largest,
           results.mean,
           results.median);
}