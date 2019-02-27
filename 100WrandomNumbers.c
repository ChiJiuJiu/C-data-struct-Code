#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct randomNumberStruct
{
    int number;
    int cnt;
}randomNumber;
#define MAX 100
randomNumber numbersArray[MAX];
void getRandomNumbers(randomNumber array[], int length, char filename[])
{
    int i = 0;
    int j = 0;
    FILE *fp;  
    fp=fopen(filename,"w");
	if(fp==NULL)  
    {  
        printf("cannot open file/n");  
        return;  
    }  
    srand((unsigned)time(NULL));
    for (i = 0; i < length; i++)
    {
        int randomNumber = rand();
        for (j = 0; j < i; j++)
        {
            if (array[j].number == randomNumber)
            {
                array[j].cnt++;
                if (array[j].cnt > 80)
                {
                    randomNumber = rand();
                    j = 0;
                    array[j].cnt--;
                    continue;
                }
            }
        }
        array[i].number = randomNumber;
        fprintf(fp,"%d ",randomNumber);  
    }
}
void swap(randomNumber *a, randomNumber *b)
{
    randomNumber *temp = (randomNumber*)malloc(sizeof(randomNumber));
    *temp = *a;
    *a = *b;
    *b = *temp;
}

void PercDown(randomNumber A[], int p, int N)
{
    int Parent, Child;
    randomNumber x;
    x = A[p];
    for (Parent = p; (Parent * 2 + 1) < N; Parent = Child)
    {
        Child = Parent * 2 + 1;
        if ((Child != N - 1) && (A[Child].number < A[Child + 1].number))
            Child++;
        if (x.number >= A[Child].number)
            break;
        else
            A[Parent] = A[Child];
    }
    A[Parent] = x;
}
void HeapSort(randomNumber A[], int N)
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
void show(randomNumber array[], int length){
    int i = 0;
    for (i = 0; i < length; i++){
        if((i + 1) % 10 == 0)
            printf("\n");
        printf("%d ", array[i].number);
    }
}
void initialize(randomNumber array[], int length){
	int i = 0;
	for(i =0; i < length; i++){
		array[i].number = 0;
		array[i].cnt = 0;
	}
}
void getTop100(randomNumber array[], int length, char filename[]){
	FILE *fp;  
    fp=fopen(filename,"w");
	if(fp==NULL)  
    {  
        printf("cannot open file/n");  
        return;  
    }
    int i = 0;
    for(i = length - 100; i < length; i++){
    	fprintf(fp,"%d ",array[i]);
	}
}
int main()
{
    int i = 0;
    initialize(numbersArray, MAX);
    getRandomNumbers(numbersArray, MAX, "data.txt");
    HeapSort(numbersArray, MAX);
    show(numbersArray, MAX);
    getTop100(numbersArray, MAX, "sortedTop100.txt");
}
