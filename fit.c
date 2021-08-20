#include <stdio.h>
#include <stdlib.h>
int nh, np;
int copy(float arr1[], float arr2[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        arr2[i] = arr1[i];
    }
    return 0;
}
int to_display(int alloc_info[], float processes[])
{
    printf(" Process No.\tProcess Size\tHole size\n");
    for (int i = 0; i < np; i++)
    {
        printf(" %d\t\t%0.0f\t\t", i + 1, processes[i]);
        if (alloc_info[i] != -32767)
            printf("%d", alloc_info[i]);
        else
            printf("Waiting..");
        printf("\n");
    }
    return 0;
}
int first_fit(float holes[], float processes[])
{
    float temp[nh];
    copy(holes, temp, nh);
    int i, j;
    int alloc_info[np];
    for (i = 0; i < np; i++)
        alloc_info[i] = -32767;
    for (i = 0; i < np; i++)
    {
        for (j = 0; j < nh; j++)
        {
            if (processes[i] <= holes[j])
            {
                alloc_info[i] = holes[j];
                holes[j] -= processes[i];
                break;
            }
        }
    }
    copy(temp, holes, nh);
    to_display(alloc_info, processes);
    return 0;
}
int compare1(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
int compare2(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}
int best_fit(float holes[], float processes[])
{
    float temp[nh];
    copy(holes, temp, nh);
    int i, j;
    int alloc_info[np];
    for (i = 0; i < np; i++)
    {
        alloc_info[i] = -32767;
    }
    qsort(holes, nh, sizeof(float), compare1);
    for (i = 0; i < np; i++)
    {
        qsort(holes, nh, sizeof(float), compare1);
        for (j = 0; j < nh; j++)
        {
            if (processes[i] <= holes[j])
            {
                alloc_info[i] = holes[j];
                holes[j] -= processes[i];
                break;
            }
        }
    }
    copy(temp, holes, nh);
    to_display(alloc_info, processes);
    return 0;
}
int worst_fit(float holes[], float processes[])
{
    float temp[nh];
    copy(holes, temp, nh);
    int i, j;
    int alloc_info[np];
    for (i = 0; i < np; i++)
    {
        alloc_info[i] = -32767;
    }
    qsort(holes, nh, sizeof(float), compare2);
    for (i = 0; i < np; i++)
    {
        qsort(holes, nh, sizeof(float), compare2);
        for (j = 0; j < nh; j++)
        {
            if (processes[i] <= holes[j])
            {
                alloc_info[i] = holes[j];
                holes[j] -= processes[i];
                break;
            }
        }
    }
    copy(temp, holes, nh);
    to_display(alloc_info, processes);
    return 0;
}
int main()
{
    printf(" Enter the number of holes : ");
    scanf("%d", &nh);
    printf(" Enter the number of processes : ");
    scanf("%d", &np);
    float holes[nh];
    float processes[np];
    if (np <= nh)
    {
        int i;
        printf(" Enter the size of %d holes :\n", nh);
        for (i = 0; i < nh; i++)
        {
            printf(" ");
            scanf("%f", &holes[i]);
        }
        printf(" Enter the size of %d processes :\n", np);
        for (i = 0; i < np; i++)
        {
            printf(" ");
            scanf("%f", &processes[i]);
        }
        printf(" First-Fit Algorithm :\n");
        first_fit(holes, processes);
        printf("\n Best-Fit Algorithm :\n");
        best_fit(holes, processes);
        printf("\n Worst-Fit Algorithm :\n");
        worst_fit(holes, processes);
    }
    else
        printf(" The number of holes should be greater than the number of processes.");
    return 0;
}