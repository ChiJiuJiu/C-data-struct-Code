#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100;

int N, A[MAXN];

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> A[i];
    sort(A, A + N);
    int l = 0, r = N - 1, ans;  //l,r��ʾ��ǰ���账������������˵���Ҷ˵㣨������
    while (r - l >= 0) {
        if (r - l < 2) {
            ans += A[r];
            break;
        }
        if (r - l < 3) {
            ans += A[l] + A[l + 1] + A[r];
            break;
        }  //�������ٵ��������
        if (A[l + 1] * 2 > A[l] + A[r - 1]) ans += A[l] * 2 + A[r] + A[r - 1];  //��������˵����������������ʱ�����ٵ��˴�ʱ��������������
        else ans += A[l + 1] * 2 + A[l] + A[r];  //���־��ǵڶ���ʱ����������һ����ӵ�
        r -= 2;  //��ʵl�˵������������ж����ᶯ����˿���ֻ��r�˵�
    }
    cout << ans << endl;
    return 0;
}
