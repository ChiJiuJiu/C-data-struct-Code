#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100;

int t[MAXN], N;

int dp(int n){
	if(n <= 2){
		return t[n];	//只有1或2个人 
	} 
	if(n == 3){			//有三个人 
		return t[1] + t[2] + t[3]; 
	} 
	//有四个人或以上 
	int fn_2 = t[2];		//n-2 = 2, n = 4
	int fn_1 = t[1] + t[2] + t[3];    // n-1 = 3, n = 4
	int fn   = 0;
	for(int i = 4; i <= n; ++i){
		fn = t[1] + 2*t[2] + t[i] + fn_2;
		fn_2 = fn_1;
		fn_1 = fn;
	}
	return fn;
}

int main(){
	cin >> N;
	t[0] = 0;
	for(int i = 1; i <= N; i++){
		cin >> t[i];
	}
	sort(t, t + N);
	cout << dp(N) << endl;
} 
