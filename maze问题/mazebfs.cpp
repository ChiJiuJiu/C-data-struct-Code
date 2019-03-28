#include<bits/stdc++.h>
using namespace std;

struct node
{
	int x,y;//����
	int steps;//���� 
}; 


const int N=101;//max size of maze
int maze[N][N]={0};
int record[N][N]={0};// ��¼���ߵĹ��� 
int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}}; //˳ʱ�뷽�� 
int n,m;//ʵ���� ��  �� 
int sx,sy,ex,ey;//��㣬�յ� 
int flag=0;//�Ƿ��ҵ���־ 
int steps=99999;//������С���� 
queue<node *> q;// ��������q; 

void bfs()
{
	int i,cx,cy;
	node *front,*t,*back;
	while(!q.empty())
	{
		
		front=q.front();
		for(i=0;i<4;i++)
		{
			//�ĸ�����ĵ㳢�� 
			cx=front->x+dir[i][0];
			cy=front->y+dir[i][1];
		    // �ж��Ƿ�Խ��
		    if(cx<1||cx>n||cy<1||cy>m) continue;
		    // �ж��Ƿ����ϰ� ����δ�߹�
		    if(maze[cx][cy]==0&&record[cx][cy]==0)
			{
				record[cx][cy]=1;//���
				t=new node();
				t->x=cx;t->y=cy;t->steps=front->steps+1;
				q.push(t);
		 	} 
		    if(cx==ex &&cy==ey)
		    {
		    	flag=1;//�ҵ�Ŀ�� 
				back=q.back();
				if(back->steps<steps)  steps=back->steps;
				break; 
			}
		    
		}
		if(flag==1) break;
		q.pop();
		
		
	 } 
	
	
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
	
	struct node *t=new node();
	t->x=sx; t->y=sy; t->steps=0;
	record[sx][sy]=1;//��������¼
	q.push(t);
	bfs();
	cout<<"steps= "<<steps<<endl;
	
	return 0;
	 
}
