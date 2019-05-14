#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101;//迷宫最大大小 
int maze[MAXN][MAXN] = {0};//迷宫
int route[MAXN][MAXN] = {0};//行走记录
int direct[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};//顺时针方向
int n, m;//迷宫实际行和列 
int sx, sy, ex, ey;//起点，终点
int minSteps = 0x7FFFFFFF;

void dfs(int x, int y, int step){
	int cx, cy, i;
	if(x == ex && y == ey){	//找到了 
		if(step < minSteps){
			minSteps = step;
		}
		return;
	}
	for(i = 0; i <= 3; i++){	//四个方向尝试 
		cx = x + direct[i][0];
		cy = y + direct[i][1];
		if(cx < 1 || cx > n || cy < 1 || cy >m){ 
			continue;	//越界，继续尝试 
		}
		if(maze[cx][cy] == 0 && route[cx][cy] == 0){
			route[cx][cy] = 1;
			dfs(cx, cy, step + 1);//走一步 
			route[cx][cy] = 0;
		}	
	}
	//尝试完 
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
