#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<stack>
#include <iterator>
using namespace std;
int find(int u, vector<int>& parent) {
	int x_root = u;
	while (parent[x_root] != -1)//找root
		x_root = parent[x_root];
	return x_root;
}
void merge(int x, int y, vector<int>& parent, vector<int>& rank)
{
	x = find(x, parent), y = find(y, parent);

	if (x == y)return;
	if (rank[x] > rank[y])//高度小的加到高度大的tree
		parent[y] = x;
	else { // rank[x] <= rank[y]
		parent[x] = y;
		if (rank[x] == rank[y])
			rank[y]++;//x加到y中 讓rank[y]變大
	}
}
void Kruskal(vector<vector<int>>& arr, vector<bool>& visited)
{
	unsigned long long int pro = 1;
	unsigned long long int div = 65537;
	vector<int> parent(visited.size() + 1, -1);//每個點的parent
	vector<int> rank(visited.size() + 1, 0); //subtree 高度
	sort(arr.begin(), arr.end());
	for (int i = 0; i < arr.size(); i++) {
		int x_root = find(arr[i][1], parent);
		int y_root = find(arr[i][2], parent);
		if (x_root != y_root) {
			if (arr[i][0] == 0) {
				pro = 0; break;
			}
			pro = (pro * arr[i][0]) % 65537;
			merge(x_root, y_root, parent, rank);
		}
	}
	cout << pro << endl;
}
int main() {
	int edge, point;
	//ifstream infile("in.txt", ios::in | ios::binary);
	while (cin >> point >> edge) {
		if (edge == 0 && point == 0)
			break;
		vector<vector<int>> a;
		vector<bool> visited(point + 1);
		long int f, s, c;
		for (long int i = 0; i < edge; i++) {
			cin >> f >> s >> c;
			a.push_back({ c,f, s });
		}
		Kruskal(a, visited);

		a.clear();
		visited.clear();
	}
	system("pause");
	return 0;
}