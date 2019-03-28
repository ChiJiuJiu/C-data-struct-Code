#include<bits/stdc++.h>
using namespace std;
const int N=101;//max size of maze
int maze[N][N]={0};
int record[N][N]={0};// 记录行走的过程 
int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}}; //顺时针方向 
int n,m;//实际行 和  列 
int sx,sy,ex,ey;//起点，终点 
int steps=99999;//设置最小步数 

void dfs(int x,int y,int step)
{
	int i,cx,cy;
	if(x==ex && y==ey) // 找到目标点 
	{
		if(step<steps)  steps=step;
		return ;
	}
	
	for(i=0;i<=3;i++)
	{
		//四个方向的点尝试 
		cx=x+dir[i][0];
		cy=y+dir[i][1];
		// 判断是否越界
		if(cx<1||cx>n||cy<1||cy>m) continue;
		// 判断是否有障碍 并且未走过
		if(maze[cx][cy]==0&&record[cx][cy]==0)
		{
			record[cx][cy]=1;//标记
			dfs(cx,cy,step+1);
			record[cx][cy]=0;//取消标记 
		 } 
		
	}
	return ;
}
int main()
{
	freopen("maze.in","r",stdin);
//	freopen("maze.out","w",stdout);
	int i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			cin>>maze[i][j];
			
	cin>>sx>>sy>>ex>>ey;
	
	record[sx][sy]=1;//设置起点记录
	dfs(sx,sy,0);
	cout<<"steps= "<<steps<<endl;
	
	return 0;
	 
}
