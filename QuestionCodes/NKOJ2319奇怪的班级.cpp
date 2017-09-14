#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;

bool setSex(map<int, int>& sex, vector<vector<int> >& isLoved, int code, int sexCode)
{
	sex[code] = sexCode;
	for (int i = 0; i < isLoved[code].size(); ++i)
	{
		if (sex[isLoved[code][i]] == sexCode)return true;
		if (sex[isLoved[code][i]] ==0&& setSex(sex, isLoved, isLoved[code][i], -sexCode))return true;
	}
	return false;
}

int main()
{
	int t;
	cin >> t;
	for (int i = 0; i < t; ++i)
	{
		map<string, int> nameToCode;
		map<int, int> sex;//编号为i的人的性别。0代表未设定，1、-1分别代表男女
		int N, M;
		scanf("%d%d", &N, &M);
		vector<pair<int, int> > temp;
		int code=1;
		for (int j = 0; j < M; ++j)
		{
			string name1,name2;
			name1.resize(22);
			name2.resize(22);
			scanf(" %s", &name1[0]);
			scanf(" %s", &name2[0]);
			//cout << name1 << name2 << endl;
			if (!nameToCode[name1])
			{
				nameToCode[name1] = code++;
			}
			if (!nameToCode[name2])
			{
				nameToCode[name2] = code++;
			}
			temp.push_back({ nameToCode[name1] ,nameToCode[name2] });
		}
		vector<vector<int> > isLoved;
	    for (int i = 0; i <= nameToCode.size(); ++i)
		{
			isLoved.push_back(vector<int>(0));
		}
		for (int i = 0; i < temp.size(); ++i)
		{
			isLoved[temp[i].first].push_back(temp[i].second);
			isLoved[temp[i].second].push_back(temp[i].first);
		}
		bool hasHomo = 0;
		for (int i = 1; i < nameToCode.size(); ++i)
		{
			if (sex[i]==0)
			{
				if (setSex(sex, isLoved, i, 1) == true)
				{
					hasHomo = true;
					break;
				}
			}
		}
		if (hasHomo) printf("YES\n");
		else printf("NO\n");
	}
}