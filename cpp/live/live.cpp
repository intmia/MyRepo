#include <iostream>
using namespace std;
int a[605] = {};
int n, w;
int main()
{
	freopen("live.in", "r", stdin);
	freopen("live.out", "w", stdout);
	int x;
	cin >> n >> w; 
	for (int i = 1; i <= n; i++)
	{
		cin >> x;
		a[x]++; 
		int sum = 0;
		
		for (int j = 600; j >= 0; j--)
		{
			sum = sum + a[j];
			if (sum >= max(1, i * w / 100))
			{
				cout << j << ' ';
				break;
			}
		}
	}
	return 0;
}
