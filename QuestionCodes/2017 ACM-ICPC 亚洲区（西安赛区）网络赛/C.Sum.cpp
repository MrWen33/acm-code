#include<iostream>
using namespace std;

void printAnswer()
{
	for (int i = 0; i < 233; ++i)
	{
		printf("9");
	}
	printf("\n");
}

int main()
{
	int T, x;
	scanf("%d", &T);
	for (int i = 0; i < T; ++i)
	{
		scanf("%d", &x);
		printAnswer();
	}
}