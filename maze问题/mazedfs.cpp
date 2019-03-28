#include<bits/stdc++.h>
using namespace std;
const int N=101;//max size of maze
int maze[N][N]={0};
int record[N][N]={0};// ��¼���ߵĹ��� 
int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}}; //˳ʱ�뷽�� 
int n,m;//ʵ���� ��  �� 
int sx,sy,ex,ey;//��㣬�յ� 
int steps=99999;//������С���� 

void dfs(int x,int y,int step)
{
	int i,cx,cy;
	if(x==ex && y==ey) // �ҵ�Ŀ��� 
	{
		if(step<steps)  steps=step;
		return ;
	}
	
	for(i=0;i<=3;i++)
	{
		//�ĸ�����ĵ㳢�� 
		cx=x+dir[i][0];
		cy=y+dir[i][1];
		// �ж��Ƿ�Խ��
		if(cx<1||cx>n||cy<1||cy>m) continue;
		// �ж��Ƿ����ϰ� ����δ�߹�
		if(maze[cx][cy]==0&&record[cx][cy]==0)
		{
			record[cx][cy]=1;//���
			dfs(cx,cy,step+1);
			record[cx][cy]=0;//ȡ����� 
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
	
	record[sx][sy]=1;//��������¼
	dfs(sx,sy,0);
	cout<<"steps= "<<steps<<endl;
	
	return 0;
	 
}
