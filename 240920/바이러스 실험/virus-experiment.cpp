#include<iostream>
#include<queue>
#include <algorithm>
#include <vector>

using namespace std;

struct Grid {
	int energy = 5;
	int p_ene;
	int use_ene;
};

struct Tree {
	int y, x, age;
};

bool Compare(Tree a, Tree b) {
	return a.age > b.age;
}

Grid grid[11][11];
vector<Tree> tree(10000000);
int dy[8] = { 0, 0, 1, -1, 1, 1, -1, -1 }, dx[8] = { 1, -1, 0, 0, 1, -1, 1, -1 };
int t_cnt = -1;
int t_end = 0;
int N, M, K, x, y, z;
queue<Tree> q;

int main() {
	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> grid[i][j].p_ene;
		}
	}

	for (int i = 0; i < M; i++) {
		cin >> y >> x >> z;
		tree[++t_cnt] = { y, x, z };
	}

	sort(tree.begin(), tree.begin() + t_cnt + 1, Compare);

	for (int i = 0; i < K; i++) {
		int tt_cnt = t_cnt;
		for (int j = tt_cnt; j >= t_end; j--) {
			if (grid[tree[j].y][tree[j].x].energy + grid[tree[j].y][tree[j].x].p_ene * i - grid[tree[j].y][tree[j].x].use_ene - tree[j].age < 0) {
				q.push(tree[j]);

				Tree temp = tree[j];
				tree[j] = tree[t_end];
				tree[t_end++] = temp;
				j++;
				continue;
			}
			
			grid[tree[j].y][tree[j].x].use_ene += tree[j].age;
			tree[j].age++;

			if (tree[j].age % 5 == 0) {
				for (int z = 0; z < 8; z++) {
					Tree next = tree[j];
					next.y += dy[z];
					next.x += dx[z];

					if (next.y < 1 || next.x < 1 || next.y > N || next.x > N) {
						continue;
					}

					tree[++t_cnt] = { next.y, next.x, 1 };
				}
			}
		}

		while (!q.empty()) {
			Tree now = q.front();
			q.pop();

			grid[now.y][now.x].energy += (now.age >> 1);
		}
	}

	cout << t_cnt - t_end + 1 << "\n";
}