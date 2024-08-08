#include<iostream>

using namespace std;

struct Node {
	int n;

	Node* prev;
	Node* next;
};

Node node[100001];
int n, m;
int cnt;
Node* belt_start[100001];
Node* belt_end[100001];
int belt_cnt[100001];

void init(int t_n, int t_m) {
	n = t_n;
	m = t_m;
	cnt = 0;

	int a = 0;
	for (int i = 0; i < t_m; i++) {
		cin >> a;
		Node t = { ++cnt, nullptr, nullptr };
		node[cnt] = t;

		if (belt_start[a] != nullptr) {
			belt_end[a]->next = &node[cnt];
			node[cnt].prev = belt_end[a];
			belt_end[a] = &node[cnt];
			belt_cnt[a]++;
		}
		else {
			belt_start[a] = &node[cnt];
			belt_end[a] = &node[cnt];
			belt_cnt[a]++;
		}
	}
}

void move_obstacle(int m_src, int m_dst) {
	if (belt_start[m_src] != nullptr) {
		belt_end[m_src]->next = belt_start[m_dst];
		if (belt_end[m_src]->next == nullptr) {
			belt_end[m_dst] = belt_end[m_src];
		}
		else {
			belt_start[m_dst]->prev = belt_end[m_src];
		}
		belt_start[m_dst] = belt_start[m_src];
		belt_end[m_src] = nullptr;
		belt_start[m_src] = nullptr;
		belt_cnt[m_dst] += belt_cnt[m_src];
		belt_cnt[m_src] = 0;

		cout << belt_cnt[m_dst] << '\n';
	}
	else {
		cout << belt_cnt[m_dst] << "\n";
	}
}

void change_first(int m_src, int m_dst) {
	if (belt_start[m_src] == nullptr && belt_start[m_dst] == nullptr) {
		cout << 0 << "\n";
	}
	else if (belt_start[m_src] == nullptr) {
		Node* now = belt_start[m_dst];
		belt_start[m_dst] = belt_start[m_dst]->next;
		if (belt_start[m_dst] == nullptr) {
			belt_end[m_dst] = nullptr;
		}
		else {
			belt_start[m_dst]->prev = nullptr;
		}
		belt_start[m_src] = now;
		now->next = nullptr;
		belt_end[m_src] = now;
		belt_cnt[m_src]++;
		belt_cnt[m_dst]--;

		cout << belt_cnt[m_dst] << "\n";
	}
	else if (belt_start[m_dst] == nullptr) {
		Node* now = belt_start[m_src];
		belt_start[m_src] = belt_start[m_src]->next;
		if (belt_start[m_src] == nullptr) {
			belt_end[m_src] = nullptr;
		}
		else {
			belt_start[m_src]->prev = nullptr;
		}
		belt_start[m_dst] = now;
		now->next = nullptr;
		belt_end[m_dst] = now;
		belt_cnt[m_dst]++;
		belt_cnt[m_src]--;

		cout << belt_cnt[m_dst] << "\n";
	}
	else {
		Node* now = belt_start[m_src];
		Node* now2 = belt_start[m_dst];
		Node* temp = now->next;
		Node* temp2 = now2->next;

		if (belt_cnt[m_src] == 1) {
			belt_start[m_src] = now2;
			belt_end[m_src] = now2;
			now2->next = nullptr;
		}
		else {
			belt_start[m_src] = now2;
			temp->prev = now2;
			now2->next = temp;
		}

		if (belt_cnt[m_dst] == 1) {
			belt_start[m_dst] = now;
			belt_end[m_dst] = now;
			now->next = nullptr;
		}
		else {
			belt_start[m_dst] = now;
			temp2->prev = now;
			now->next = temp2;
			cout << belt_cnt[m_dst] << "\n";
		}
	}

}

void half_obstacle(int m_src, int m_dst) {
	int half_s = belt_cnt[m_src] / 2;

	if (half_s != 0) {
		int  tmp = 1;
		Node* temp = belt_start[m_src];

		while (tmp < half_s) {
			temp = temp->next;
			tmp++;
		}

		Node* next = temp->next;
		next->prev = nullptr;

		if (belt_cnt[m_dst] == 0) {
			belt_start[m_dst] = belt_start[m_src];
			belt_end[m_dst] = temp;
			belt_start[m_dst]->prev = nullptr;
			belt_end[m_dst]->next = nullptr;
		}
		else {
			temp->next = belt_start[m_dst];
			belt_start[m_dst]->prev = temp;
			belt_start[m_dst] = belt_start[m_src];
		}

		belt_start[m_src] = next;
		belt_cnt[m_dst] += tmp;
		belt_cnt[m_src] -= tmp;
	}

	cout << belt_cnt[m_dst] << "\n";
}

void get_obstacle(int p_num) {
	int a = 0;
	int b = 0;

	if (node[p_num].prev != nullptr) {
		a = node[p_num].prev->n;
	}
	else {
		a = -1;
	}

	if (node[p_num].next != nullptr) {
		b = node[p_num].next->n;
	}
	else {
		b = -1;
	}

	cout << a + (2 * b) << "\n";
}

void get_belt(int b_num) {
	int a = 0;
	int b = 0;
	int c = 0;
	
	if (belt_cnt[b_num] != 0) {
		a = belt_start[b_num]->n;
		b = belt_end[b_num]->n;
		c = belt_cnt[b_num];

		cout << a + 2 * b + 3 * c << "\n";
	}
	else {
		cout << -3 << "\n";
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int q = 0;

	cin >> q;

	for (int i = 0; i < q; i++) {
		int a = 0;

		cin >> a;

		if (a == 200) {
			int m_src = 0, m_dst = 0;
			
			cin >> m_src >> m_dst;
			move_obstacle(m_src, m_dst);
		}
		else if (a == 300) {
			int m_src = 0, m_dst = 0;

			cin >> m_src >> m_dst;
			change_first(m_src, m_dst);
		}
		else if (a == 600) {
			int b_num = 0;

			cin >> b_num;
			get_belt(b_num);
		}
		else if (a == 500) {
			int p_num = 0;

			cin >> p_num;
			get_obstacle(p_num);
		}
		else if (a == 400) {
			int m_src = 0, m_dst = 0;

			cin >> m_src >> m_dst;
			half_obstacle(m_src, m_dst);
		}
		else {
			int t_n = 0, t_m = 0;

			cin >> t_n >> t_m;

			init(t_n, t_m);
		}
	}

	return 0;
}