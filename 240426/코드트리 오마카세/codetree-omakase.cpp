#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <unordered_map>
#include <cmath>

using namespace std;

struct t_x {
    int t, x;
};

struct Point {
    queue<t_x> q;
};

struct Guest {
    int x, n, now_time;
    string name;

    bool operator<(Guest other) const {
        return now_time > other.now_time;
    }
};

int L, Q;
int timer, x, n;
int cnt = 0;
string name;
priority_queue<Guest> guest;
unordered_map<string, Point> sushi;

void rotate() {

}

int main() {
    // 여기에 코드를 작성해주세요.
    int a = 0;

    cin >> L >> Q;

    for (int i = 0; i < Q; i++) {
        cin >> a;

        // 회전

        // 입력 처리
        if (a == 100) {
            cin >> timer >> x >> name;

            if (sushi.find(name) != sushi.end()) {
                sushi[name].q.push({ timer, x });
            }
            else {
                sushi[name] = { queue<t_x>() };
                sushi[name].q.push({ timer, x });
            }
            cnt++;
        }
        else if (a == 200) {
            cin >> timer >> x >> name >> n;

            guest.push({ x, n, timer, name });
        }
        else if (a == 300) {
            int temp_time;
            cin >> temp_time;

            if (temp_time - 1 != timer) {
                timer = temp_time - 1;

                while (!guest.empty()) {
                    Guest now = guest.top();
                    guest.pop();

                    if (now.now_time > timer) {
                        guest.push(now);
                        break;
                    }
                    if (sushi.find(now.name) != sushi.end()) {
                        for (int i = 0; i < sushi[now.name].q.size(); i++) {
                            t_x temp = sushi[now.name].q.front();
                            sushi[now.name].q.pop();

                            int t_gap = timer + 1 - now.now_time;
                            int x_gap = temp.x - now.x;

                            if (now.now_time > temp.t) {
                                x_gap += now.now_time - temp.t;
                                x_gap %= L;
                            }

                            if ((x_gap <= 0 && x_gap + t_gap >= 0) || (x_gap > 0 && x_gap + t_gap > L)) {
                                now.n--;
                                cnt--;
                                continue;
                            }
                            temp.x = (temp.x + t_gap) % L;
                            temp.t = timer + 1;

                            sushi[now.name].q.push(temp);
                        }
                    }

                    if (now.n == 0) continue;
                    now.now_time = timer + 1;
                    guest.push(now);
                }
            }
            timer = temp_time;

            cout << guest.size() << " " << cnt << "\n";
        }
        else {
            cout << "error\n";
            return 0;
        }

        while (!guest.empty()) {
            Guest now = guest.top();
            guest.pop();

            if (now.now_time > timer) {
                guest.push(now);
                break;
            }
            if (sushi.find(now.name) != sushi.end()) {
                int abc = sushi[now.name].q.size();
                for (int i = 0; i < abc; i++) {
                    t_x temp = sushi[now.name].q.front();
                    sushi[now.name].q.pop();

                    int t_gap = timer + 1 - now.now_time;
                    int x_gap = temp.x - now.x;

                    if (now.now_time > temp.t) {
                        x_gap += now.now_time - temp.t;
                        x_gap %= L;
                    }

                    if ((x_gap <= 0 && x_gap + t_gap >= 0) || (x_gap > 0 && x_gap + t_gap > L)) {
                        now.n--;
                        cnt--;
                        continue;
                    }
                    temp.x = (temp.x + timer + 1 - temp.t) % L;
                    temp.t = timer + 1;

                    sushi[now.name].q.push(temp);
                }
            }

            if (now.n == 0) continue;
            now.now_time = timer + 1;
            guest.push(now);
        }
    }

    return 0;
}