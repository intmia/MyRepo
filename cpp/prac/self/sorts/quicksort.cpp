
#include <bits/stdc++.h>
using namespace std;

static std::mt19937 rng((unsigned)chrono::high_resolution_clock::now().time_since_epoch().count());

int partition(vector<int>& a, int l, int r) {
	int pivot = a[r];
	int i = l - 1;
	for (int j = l; j < r; ++j) {
		if (a[j] <= pivot) {
			++i;
			swap(a[i], a[j]);
		}
	}
	swap(a[i + 1], a[r]);
	return i + 1;
}

void quicksort(vector<int>& a, int l, int r) {
	if (l < r) {
		uniform_int_distribution<int> dist(l, r);
		int piv = dist(rng);
		swap(a[piv], a[r]);
		int m = partition(a, l, r);
		quicksort(a, l, m - 1);
		quicksort(a, m + 1, r);
	}
}

int main(int argc, char** argv) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	if (argc > 1) {
		int n;
		if (!(cin >> n)) return 0;
		vector<int> a(n);
		for (int i = 0; i < n; ++i) cin >> a[i];
		cout << "Before:";
		for (int x : a) cout << ' ' << x;
		cout << '\n';
		quicksort(a, 0, n - 1);
		cout << "After :";
		for (int x : a) cout << ' ' << x;
		cout << '\n';
	} else {
		vector<int> a = {9, 4, 1, 3, 7, 6, 5, 8, 2, 0};
		cout << "Demo array before:";
		for (int x : a) cout << ' ' << x;
		cout << '\n';
		quicksort(a, 0, (int)a.size() - 1);
		cout << "Demo array after :";
		for (int x : a) cout << ' ' << x;
		cout << '\n';
		cout << "\nTo sort custom input, run with any argument and provide:\n";
		cout << "<n> followed by n integers on stdin. Example:\n";
		cout << "echo 5 3 5 1 4 2 | ./quicksort.exe arg\n";
	}

	return 0;
}

