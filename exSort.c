#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
int cutoff = 3;
LARGE_INTEGER begin, end, frequency;
typedef int ElementType;
#define MAX 20
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
void Start(){
    QueryPerformanceCounter(&begin);
}
void Stop(){
    QueryPerformanceCounter(&end);
}
double getTime(LARGE_INTEGER begin,LARGE_INTEGER end){
    return (double)(end.QuadPart - begin.QuadPart) / (double)(frequency.QuadPart);
}
int ImportTofile(int nums[], int N, char filename[]){
    FILE *FP = NULL;
    FP = fopen(filename,"wb");
    if(!FP){
        printf("Open file error! Please check the FilePath!\n");
        fclose(FP);
        return 0;
    }
    int i = 0;
    for (i = 0; i < N; i++){
        if(fwrite(&nums[i],sizeof(int),1,FP) != 1){
        	printf("Import to file error! Please import again!\n");
        	fclose(FP);
        	return 0;
        }
	}
	fclose(FP);
	return 1;
}
int LoadFromfile(int nums[], int N,char filename[]){
	FILE *FP = NULL;
    FP = fopen(filename, "rb");
    if (!FP){
        printf("Open file error! Please check the FilePath!\n");
        fclose(FP);
        return 0;
    }
    int i = 0;
    fseek(FP, 0, 0);
    for (i = 0; i < N; i++){
        if(fread(&nums[i],sizeof(int),1,FP) != 1){
            printf("Loading to memory error! Please import again!\n");
            fclose(FP);
            return 0;
        }
    }
    fclose(FP);
	return 1;
}
int* GenerateRandomNums(int size){
    int *nums = (int *)malloc(sizeof(int) * size);
    if(!nums)
		return NULL; 
    int i = 0;
    for (i = 0; i < size; i++){
        nums[i] = rand() % RAND_MAX;
    }
    return nums;
}
void Display(int nums[], int size){
    int i = 0;
    int cnt = 1;
    for (i = 0; i < size; i++){
        printf("%d ", nums[i]);
        if(cnt++ % 20 == 0)
            printf("\n");
    }
    printf("\n");
}
int main()
{	QueryPerformanceFrequency(&frequency);
    char x = 0;
    int i = 0;
    int cnt = 1;
    srand(time(NULL));
    int *Previous;
    int *Sorted;
    char* file;
    char input[2];
    do
    {
        printf("1.Generate random numbers\n");
        printf("2.Read nums from file\n");
        printf("3.Write nums to file\n");
        printf("4.Bubble Sort\n");
        printf("5.Insert Sort\n");
        printf("6.Shell  Sort\n");
        printf("7.Quick  Sort\n");
        printf("8.Merge  Sort\n");
        printf("9.Heap   Sort\n");
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
        cnt = 1;
        switch (x)
        {
        case '1':
            Previous = GenerateRandomNums(MAX);
            if(Previous){
            	printf("Below are the Random numbers:\n");
            	Display(Previous, MAX);
			}else{
				printf("Malloc memory fail!\n");	
			}
            break;
        case '2':
        	if(LoadFromfile(Previous,MAX,"data.txt"))
        		Display(Previous,MAX);
        	break;
        case '3':
        	if(ImportTofile(Previous,MAX,"data.txt"))
				printf("Write nums to file success!\n");
        	break;
        case '4':
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
            ImportTofile(Previous, MAX, "data.txt");
            Start();
            Bubble(Previous, MAX);
            Stop();
            printf("\nSorted Arrary:\n");
            for (i = 0; i < MAX; i++)
            {
                printf("%d ", Previous[i]);
                if (cnt++ % 20 == 0)
                    printf("\n");
            }
            printf("Running Time: %lfs",getTime(begin,end));
            printf("\n");
            break;
        case '5':
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
            Start();
            InsertSort(Previous, MAX);
            Stop();
            printf("\nSorted Arrary:\n");
            for (i = 0; i < MAX; i++)
            {
                printf("%d ", Previous[i]);
                if (cnt++ % 20 == 0)
                    printf("\n");
            }
            printf("\n");
            printf("Running Time: %lfs", getTime(begin, end));
            printf("\n");
            break;
        case '6':
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
            Start();
            ShellSort(Previous, MAX);
            Stop();
            printf("\nSorted Arrary:\n");
            for (i = 0; i < MAX; i++)
            {
                printf("%d ", Previous[i]);
                if (cnt++ % 20 == 0)
                    printf("\n");
            }
            printf("\n");
            printf("Running Time: %lfs", getTime(begin, end));
            printf("\n");
            break;
        case '7':
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
            Start();
            QuickSort(Previous, MAX);
            Stop();
            printf("\nSorted Arrary:\n");
            for (i = 0; i < MAX; i++)
            {
                printf("%d ", Previous[i]);
                if (cnt++ % 20 == 0)
                    printf("\n");
            }
            printf("\n");
            printf("Running Time: %lfs", getTime(begin, end));
            printf("\n");
            break;
        case '8':
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
            Start();
            MergeSort(Previous, MAX);
            Stop();
            printf("\nSorted Arrary:\n");
            for (i = 0; i < MAX; i++)
            {
                printf("%d ", Previous[i]);
                if (cnt++ % 20 == 0)
                    printf("\n");
            }
            printf("\n");
            printf("Running Time: %lfs", getTime(begin, end));
            printf("\n");
            break;
        case '9':
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
            Start();
            HeapSort(Previous, MAX);
            Stop();
            printf("\nSorted Arrary:\n");
            for (i = 0; i < MAX; i++)
            {
                printf("%d ", Previous[i]);
                if (cnt++ % 20 == 0)
                    printf("\n");
            }
            printf("\n");
            printf("Running Time: %lfs", getTime(begin, end));
            printf("\n");
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
