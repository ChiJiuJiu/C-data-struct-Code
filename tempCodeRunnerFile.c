
    for (i = N - 1; i > 0; i--)
    {
        swap(&A[0], &A[i]);
        PercDown(A, 0, i);