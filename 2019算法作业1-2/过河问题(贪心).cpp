#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100;

int N, A[MAXN];

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> A[i];
    sort(A, A + N);
    int l = 0, r = N - 1, ans;  //l,r表示当前还需处理的人区间的左端点和右端点（已排序）
    while (r - l >= 0) {
        if (r - l < 2) {
            ans += A[r];
            break;
        }
        if (r - l < 3) {
            ans += A[l] + A[l + 1] + A[r];
            break;
        }  //特判人少的两种情况
        if (A[l + 1] * 2 > A[l] + A[r - 1]) ans += A[l] * 2 + A[r] + A[r - 1];  //考虑上面说的两种情况，这个是时间最少的人带时间最多的两个过河
        else ans += A[l + 1] * 2 + A[l] + A[r];  //这种就是第二中时间最多的两个一起过河的
        r -= 2;  //其实l端点在整个过程中都不会动，因此可以只用r端点
    }
    cout << ans << endl;
    return 0;
}
