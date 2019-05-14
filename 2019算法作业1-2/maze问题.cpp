#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101;//�Թ�����С 
int maze[MAXN][MAXN] = {0};//�Թ�
int route[MAXN][MAXN] = {0};//���߼�¼
int direct[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};//˳ʱ�뷽��
int n, m;//�Թ�ʵ���к��� 
int sx, sy, ex, ey;//��㣬�յ�
int minSteps = 0x7FFFFFFF;

void dfs(int x, int y, int step){
	int cx, cy, i;
	if(x == ex && y == ey){	//�ҵ��� 
		if(step < minSteps){
			minSteps = step;
		}
		return;
	}
	for(i = 0; i <= 3; i++){	//�ĸ������� 
		cx = x + direct[i][0];
		cy = y + direct[i][1];
		if(cx < 1 || cx > n || cy < 1 || cy >m){ 
			continue;	//Խ�磬�������� 
		}
		if(maze[cx][cy] == 0 && route[cx][cy] == 0){
			route[cx][cy] = 1;
			dfs(cx, cy, step + 1);//��һ�� 
			route[cx][cy] = 0;
		}	
	}
	//������ 
	return;
}   

int main() {
	freopen("maze.in", "r", stdin);
	cin >> n >> m;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			cin >> maze[i][j];
	cin >> sx >> sy >> ex >> ey;
	route[sx][sy] = 1;
	dfs(sx,sy,0);
	cout << "minSteps= " << minSteps << endl;
}
