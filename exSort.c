#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int cutoff = 3;
typedef int ElementType;
#define MAX 2000
void InsertSort(int PreviousArray[], int n)
{
    int temp = 0, i = 0, j = 0;
    for (i = 1; i < n; i++)
    {
        temp = PreviousArray[i];
        for (j = i; PreviousArray[j - 1] > temp && j > 0; j--)
        {
            PreviousArray[j] = PreviousArray[j - 1];
        }
        PreviousArray[j] = temp;
    }
}
void ShellSort(int PreviousArray[], int n)
{
    int D = 0, i = 0, j = 0;
    int temp = 0;
    for (D = n; D > 0; D /= 2)
    {
        for (i = D; i < n; i++)
        {
            temp = PreviousArray[i];
            for (j = i; PreviousArray[j - D] > temp && j >= D; j -= D)
            {
                PreviousArray[j] = PreviousArray[j - D];
            }
            PreviousArray[j] = temp;
        }
    }
}
void swap(int *a, int *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}
int Medium3(int A[], int left, int right)
{
    int center = (left + right) / 2;
    if (A[left] > A[center])
        swap(&A[left], &A[center]);
    if (A[left] > A[right])
        swap(&A[left], &A[right]);
    if (A[center] > A[right])
        swap(&A[center], &A[right]);
    swap(&A[center], &A[right - 1]);
    return A[right - 1];
}
void Qsort(int A[], int left, int right)
{
    int pivot, low, high;
    if (cutoff <= right - left)
    {
        pivot = Medium3(A, left, right);
        low = left;
        high = right - 1;
        while (1)
        {
            while (A[++low] < pivot)
                ;
            while (A[--high] > pivot)
                ;
            if (low < high)
                swap(&A[low], &A[high]);
            else
                break;
        }
        swap(&A[low], &A[right - 1]);
        Qsort(A, left, low - 1);
        Qsort(A, low + 1, right);
    }
    else
    {
        InsertSort(A + left, right - left + 1);
    }
}
void QuickSort(int A[], int N)
{
    Qsort(A, 0, N - 1);
}
void Merge(int A[], int Temp[], int L, int R, int RightEnd)
{
    int LeftEnd, Num, Tmp;
    int i;
    LeftEnd = R - 1;
    Tmp = L;
    Num = RightEnd - L + 1;
    while (L <= LeftEnd && R <= RightEnd)
    {
        if (A[L] < A[R])
            Temp[Tmp++] = A[L++];
        else
            Temp[Tmp++] = A[R++];
    }
    while (L <= LeftEnd)
    {
        Temp[Tmp++] = A[L++];
    }
    while (R <= RightEnd)
    {
        Temp[Tmp++] = A[R++];
    }
    for (i = 0; i < Num; i++, RightEnd--)
    {
        A[RightEnd] = Temp[RightEnd];
    }
}
void Msort(int A[], int Temp[], int L, int RightEnd)
{
    int Center;
    if (L < RightEnd)
    {
        Center = (L + RightEnd) / 2;
        Msort(A, Temp, L, Center);
        Msort(A, Temp, Center + 1, RightEnd);
        Merge(A, Temp, L, Center + 1, RightEnd);
    }
}
void MergeSort(int A[], int N)
{
    int *Temp;
    Temp = (int *)malloc(sizeof(int) * N);
    if (Temp)
    {
        Msort(A, Temp, 0, N - 1);
        free(Temp);
    }
    else
    {
        printf("Over Flow!\n");
    }
}
void PercDown(int A[], int p, int N)
{
    int Parent, Child;
    int x;
    x = A[p];
    for (Parent = p; (Parent * 2 + 1) < N; Parent = Child)
    {
        Child = Parent * 2 + 1;
        if ((Child != N - 1) && (A[Child] < A[Child + 1]))
            Child++;
        if (x >= A[Child])
            break;
        else
            A[Parent] = A[Child];
    }
    A[Parent] = x;
}
void HeapSort(int A[], int N)
{
    int i;
    for (i = N / 2 - 1; i >= 0; i--)
    {
        PercDown(A, i, N);
    }
    for (i = N - 1; i > 0; i--)
    {
        swap(&A[0], &A[i]);
        PercDown(A, 0, i);
    }
}
void Bubble(int Previous[], int N)
{
    int i = 0, j = 0;
    int temp = 0;
    int flag = 0;
    for (i = 0; i < N; i++)
    {
        for (j = 1; j < N - i; j++)
        {
            if (Previous[j] < Previous[j - 1])
            {
                temp = Previous[j];
                Previous[j] = Previous[j - 1];
                Previous[j - 1] = temp;
                flag = 1;
            }
        }
        if (!flag)
            break;
        flag = 0;
    }
}
int main()
{
    char x = 0;
    int i = 0;
    int cnt = 1;
    srand(time(NULL));
    int Previous[MAX];
    char input[2];
    do
    {
        printf("1.Bubble Sort\n");
        printf("2.Insert Sort\n");
        printf("3.Shell  Sort\n");
        printf("4.Quick  Sort\n");
        printf("5.Merge  Sort\n");
        printf("6.Heap   Sort\n");
        printf("0.exit\n");
        printf("Please Select:");
        fflush(stdin);
        scanf("%s", input);
        while (strlen(input) > 1 || input[0] < '0' || input[0] > '9')
        {
            printf("Illegal input! Please input again!\n");
            fflush(stdin);
            scanf("%s", input);
        }
        x = input[0];
        switch (x)
        {
        case '1':
            printf("\nBubble sort:\n");
            for (i = 0; i < MAX; i++)
            {
                Previous[i] = rand() % 100 + 1;
            }
            printf("Previous Arrary:\n");
            for (i = 0; i < MAX; i++)
            {
                printf("%d ", Previous[i]);
                if(cnt++ % 20 == 0)
                    printf("\n");
            }
            Bubble(Previous, MAX);
            printf("\nSorted Arrary:\n");
            for (i = 0; i < MAX; i++)
            {
                printf("%d ", Previous[i]);
                if (cnt++ % 20 == 0)
                    printf("\n");
            }
            printf("\n");
            cnt = 0;
            break;
        case '2':
            printf("\nInsert sort:\n");
            for (i = 0; i < MAX; i++)
            {
                Previous[i] = rand() % 100 + 1;
            }
            printf("Previous Arrary:\n");
            for (i = 0; i < MAX; i++)
            {
                printf("%d ", Previous[i]);
                if (cnt++ % 20 == 0)
                    printf("\n");
            }
            InsertSort(Previous, MAX);
            printf("\nSorted Arrary:\n");
            for (i = 0; i < MAX; i++)
            {
                printf("%d ", Previous[i]);
                if (cnt++ % 20 == 0)
                    printf("\n");
            }
            printf("\n");
            cnt = 0;
            break;
        case '3':
            printf("\nShell sort:\n");
            for (i = 0; i < MAX; i++)
            {
                Previous[i] = rand() % 100 + 1;
            }
            printf("Previous Arrary:\n");
            for (i = 0; i < MAX; i++)
            {
                printf("%d ", Previous[i]);
                if (cnt++ % 20 == 0)
                    printf("\n");
            }
            ShellSort(Previous, MAX);
            printf("\nSorted Arrary:\n");
            for (i = 0; i < MAX; i++)
            {
                printf("%d ", Previous[i]);
                if (cnt++ % 20 == 0)
                    printf("\n");
            }
            printf("\n");
            cnt = 0;
            break;
        case '4':
            printf("\nQuick sort:\n");
            for (i = 0; i < MAX; i++)
            {
                Previous[i] = rand() % 100 + 1;
            }
            printf("Previous Arrary:\n");
            for (i = 0; i < MAX; i++)
            {
                printf("%d ", Previous[i]);
                if (cnt++ % 20 == 0)
                    printf("\n");
            }
            QuickSort(Previous, MAX);
            printf("\nSorted Arrary:\n");
            for (i = 0; i < MAX; i++)
            {
                printf("%d ", Previous[i]);
                if (cnt++ % 20 == 0)
                    printf("\n");
            }
            printf("\n");
            cnt++;
            break;
        case '5':
            printf("\nMerge sort:\n");
            for (i = 0; i < MAX; i++)
            {
                Previous[i] = rand() % 100 + 1;
            }
            printf("Previous Arrary:\n");
            for (i = 0; i < MAX; i++)
            {
                printf("%d ", Previous[i]);
                if (cnt++ % 20 == 0)
                    printf("\n");
            }
            MergeSort(Previous, MAX);
            printf("\nSorted Arrary:\n");
            for (i = 0; i < MAX; i++)
            {
                printf("%d ", Previous[i]);
                if (cnt++ % 20 == 0)
                    printf("\n");
            }
            printf("\n");
            cnt++;
            break;
        case '6':
            printf("\nHeap sort:\n");
            for (i = 0; i < MAX; i++)
            {
                Previous[i] = rand() % 100 + 1;
            }
            printf("Previous Arrary:\n");
            for (i = 0; i < MAX; i++)
            {
                printf("%d ", Previous[i]);
                if (cnt++ % 20 == 0)
                    printf("\n");
            }
            HeapSort(Previous, MAX);
            printf("\nSorted Arrary:\n");
            for (i = 0; i < MAX; i++)
            {
                printf("%d ", Previous[i]);
                if (cnt++ % 20 == 0)
                    printf("\n");
            }
            printf("\n");
            cnt++;
            break;
        case '0':
            printf("Thank to use!\n");
            exit(1);
            break;
        default:
            printf("ILLEGAL INPUT!\n");
            break;
        }
    } while (x);
}
