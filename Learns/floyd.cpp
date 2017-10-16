#include<iostream>
#define MAXSIZE 10005
using namespace std;
int n;
int matrix[MAXSIZE][MAXSIZE];

int min(int n1,int n2)
{
	return n1 > n2 ? n2 : n1;
}

void floyd()
{
	for (int k = 0; k < n; ++k)
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				//�ڵ�ǰi��j����k���·����ֱ����·����ѡ���
				matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
			}
		}
	}
}

int main()
{

}