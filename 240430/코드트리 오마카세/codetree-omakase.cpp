#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <unordered_map>
#include <cmath>
#include <climits>

using namespace std;

struct t_x {
    int t, x, next_t;
};

// 초밥 현재위치(t 를 현재시간에 맞춘뒤 next_t 를 기준으로 정렬) <-> 게스트 위치(0 으로 고정)
struct Guest {
    int x, n;
};

struct Point {
    Guest guest;
    priority_queue<int, vector<int>, greater<int>> pq;
    queue<t_x> q;
};

int L, Q;
int timer, x, n;
int cnt = 0;
string name;
queue<string> guest;
unordered_map<string, Point> sushi;

int main() {
    // 여기에 코드를 작성해주세요.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int a = 0;

    cin >> L >> Q;

    for (int i = 0; i < Q; i++) {
        cin >> a;

        // 회전

        // 입력 처리
        if (a == 100) {
            cin >> timer >> x >> name;

            int next_time = 0;
            if (sushi[name].guest.n != 0) {
                if (sushi[name].guest.x - x < 0) {
                    next_time = timer + sushi[name].guest.x + L - x;
                }
                else {
                    next_time = timer + sushi[name].guest.x - x;
                }
                sushi[name].pq.push(next_time);
                cnt++;
            }
            else {
                sushi[name].q.push({ timer, x, INT_MAX });
                cnt++;
            }
        }
        else if (a == 200) {
            cin >> timer >> x >> name >> n;

            while (!sushi[name].q.empty()) {
                t_x temp = sushi[name].q.front();
                sushi[name].q.pop();

                int now_x = (timer - temp.t + temp.x) % L;
                int next_time = 0;
                if (x - now_x < 0) {
                    next_time = timer + x + L - now_x;
                }
                else {
                    next_time = timer + x - now_x;
                }
                sushi[name].pq.push(next_time);
            }
            sushi[name].guest = { x, n };
            guest.push(name);
        }
        else if (a == 300) {
            cin >> timer;

            int guest_size = guest.size();
            if (cnt == 0 || guest.size() == 0) {
                cout << guest.size() << " " << cnt << "\n";
                continue;
            }

            for (int i = 0; i < guest_size; i++) {
                string now = guest.front();
                guest.pop();

                while (!sushi[now].pq.empty()) {
                    int temp = sushi[now].pq.top();

                    if (temp <= timer) {
                        sushi[now].pq.pop();
                        sushi[now].guest.n--;
                        cnt--;
                    }
                    else {
                        break;
                    }
                }

                if (sushi[now].guest.n == 0) continue;
                guest.push(now);
            }

            cout << guest.size() << " " << cnt << "\n";
        }
        else {
            cout << "error\n";
            return 0;
        }

    }

    return 0;
}