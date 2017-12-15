#include<iostream>
#include<memory.h>
#include<string>
#define INIT(x) memset(x,0,sizeof(x))
using namespace std;

int w, h, n;
int num[20][20];//每个空格的编号
int conn[200][200];//邻接表
int visited[200][200][200];
char G[20][20];
int goal[3];
int start[3];
int queue[10000000][4],front,rear;
void queIns(int a[3],int step)
{
	queue[rear][0] = step;
	queue[rear][1] = a[0];
	queue[rear][2] = a[1];
	queue[rear][3] = a[2];
	rear += 1;
}
void quePop(){++front;}
int* getQueFront(){
	return queue[front];
}
bool queIsEmpty(){return front == rear;}

void init()
{
	INIT(num);
	INIT(conn);
	INIT(visited);
	INIT(G);
	INIT(goal);
	INIT(start);
	INIT(queue);
	front = 0; rear = 0;
}

bool isOverlap(int a[3])//是否位置重叠
{
	if (n == 3)
	{
		return (a[1] == a[2] || a[1] == a[0] || a[2] == a[0]);
	}
	else if (n == 2)
	{
		return (a[1] == a[0]);
	}
	else if (n == 1)
	{
		return false;
	}
}

bool isAvalible(int a[3], int b[3])//移动是否可行（防止互穿）
{
	if (n == 3)
	{
		if (a[1] == b[2] && a[2] == b[1])return false;
		if (a[1] == b[0] && a[0] == b[1])return false;
		if (a[0] == b[2] && a[2] == b[0])return false;
		else return true;
	}
	else if (n == 2)
	{
		if (a[1] == b[0] && a[0] == b[1])return false;
		else return true;
	}
	else if (n == 1) return true;
}

bool isEqual(int a[3], int b[3])
{
	if (a[0] == b[0] && a[2] == b[2] && a[1] == b[1])return true;
	else return false;
}

int bfs()
{
	conn[0][0] = 1;
	visited[start[0]][start[1]][start[2]] = true;
	queIns(start,0);
	int curStatus[3],curStep;
	int nextStatus[3];
	while (!queIsEmpty())
	{
		curStep = getQueFront()[0];
		curStatus[0] = getQueFront()[1];
		curStatus[1] = getQueFront()[2];
		curStatus[2] = getQueFront()[3];
		//cout << curStatus[0] << " " << curStatus[1] << " " << curStatus[2] << " " << endl;
		quePop();
		if (isEqual(curStatus, goal)) 
			return curStep;
		//TODO:处理n！=3时此处的取值。
		for (int i = 1; i <= conn[curStatus[0]][0]; ++i)
		{
			nextStatus[0] = conn[curStatus[0]][i];
			for (int j = 1; j <= conn[curStatus[1]][0]; ++j)
			{
				nextStatus[1] = conn[curStatus[1]][j];
				for (int k = 1; k <= conn[curStatus[2]][0]; ++k)
				{
					nextStatus[2] = conn[curStatus[2]][k];
					if (isOverlap(nextStatus))continue;//若点重叠则跳过
					if (!isAvalible(nextStatus, curStatus)) continue;//若互穿则跳过
					if (visited[nextStatus[0]][nextStatus[1]][nextStatus[2]]) continue;//若已经经过这个状态则跳过
					//若状态可行
					visited[nextStatus[0]][nextStatus[1]][nextStatus[2]]=true;
					queIns(nextStatus, curStep + 1);
				}
			}
		}
	}
	return -1;
}

int dh[] = {1,-1,0,0,0};
int dw[] = {0,0,1,-1,0};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	while (cin >> w >> h >> n&&w != 0)
	{
		init();
		int tnum = 1;
		for (int i = 1; i <= h; ++i)
		{
			string line;
			while (line == "")getline(cin, line);
			for (int j = 1; j <= w; ++j)
			{
				G[i][j]=line[j-1];
				if (G[i][j] != '#') num[i][j] = tnum++;
				if (G[i][j] == 'A')goal[0] = num[i][j];
				else if (G[i][j] == 'B')goal[1] = num[i][j];
				else if (G[i][j] == 'C')goal[2] = num[i][j];
				else if (G[i][j] == 'a')start[0] = num[i][j];
				else if (G[i][j] == 'b')start[1] = num[i][j];
				else if (G[i][j] == 'c')start[2] = num[i][j];
			}
		}
		for (int i = 1; i <= h; ++i)
		{
			for (int j = 1; j <= w; ++j)
			{
				if (G[i][j] == '#')continue;
				int tpos = 1, ti, tj;
				for (int k = 0; k < 5; ++k)
				{
					ti = i + dh[k];
					tj = j + dw[k];
					if (ti > 0 && ti <= h&&tj > 0 && tj <= w&&G[ti][tj] != '#')
					{
						conn[num[i][j]][0] += 1;
						conn[num[i][j]][tpos++] = num[ti][tj];
					}
				}
			}
		}
		int step = bfs();
		cout << step << endl;
	}
}