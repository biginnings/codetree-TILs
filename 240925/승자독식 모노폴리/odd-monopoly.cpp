#include <iostream>
#include <deque>

using namespace std;

struct Player {
    int y, x, d;
    int prio_d[5][5];
};

struct Grid {
    int player_n, t;
    Grid* prev = nullptr;
};

struct Point {
    int y, x;
};

struct TPoint {
    int y, x, d;
};

int n, m, k, player_cnt;
Grid grid[20][20];
int dy[5] = { 0, -1, 1, 0, 0 }, dx[5] = { 0, 0, 0, -1, 1 };
Player player[401];
int visited[401];

int main() {
    cin >> n >> m >> k;
    player_cnt = m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j].player_n;
            
            if (grid[i][j].player_n != 0) {
                player[grid[i][j].player_n] = { i, j };
                grid[i][j].t = k;
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        cin >> player[i].d;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= 4; j++) {
            for (int z = 1; z <= 4; z++) {
                cin >> player[i].prio_d[j][z];
            }
        }
    }

    //cout << "\n\n";

    for (int i = 0; i <= 1000; i++) {
        for (int j = 0; j < n; j++) {
            for (int z = 0; z < n; z++) {
                //cout << grid[j][z].player_n << grid[j][z].t << " ";
                if (grid[j][z].t != 0) {
                    grid[j][z].t--;
                    if (grid[j][z].t == 0) {
                        grid[j][z].player_n = 0;
                    }
                }
            }
            //cout << "\n";
        }
        //cout << "\n";
        if (player_cnt == 1) {
            cout << i << '\n';
            return 0;
        }
        if (i == 1000) {
            cout << -1 << "\n";
            return 0;
        }

        //for (int j = 1; j <= m; j++) {
        //    if (visited[j] == 1 && grid[player[j].y][player[j].x].t == 0) continue;
        //    Grid* p_g = &grid[player[j].y][player[j].x];
        //    p_g->t--;
        //    if (p_g->t == 0) {
        //        p_g->player_n = 0;
        //        continue;
        //    }

        //    while (p_g->prev != nullptr) {
        //        Grid* t_p_g = p_g->prev;

        //        t_p_g->t--;
        //        if (t_p_g->t == 0) {
        //            p_g->prev = nullptr;
        //            t_p_g->player_n = 0;
        //            break;
        //        }
        //        p_g = t_p_g;
        //    }
        //}
        
        for (int j = 1; j <= m; j++) {
            if (visited[j] == 1) continue;
            if (player_cnt == 1) break;

            Point now = { player[j].y, player[j].x };

            TPoint next_d = { -1, -1, -1 };
            for (int z = 1; z <= 4; z++) {
                Point next = { now.y + dy[player[j].prio_d[player[j].d][z]], now.x + dx[player[j].prio_d[player[j].d][z]] };
                if (next.y < 0 || next.x >= n || next.y >= n || next.x < 0) {
                    if (z == 4) {
                        grid[next_d.y][next_d.x].player_n = j;
                        grid[next_d.y][next_d.x].t = k;
                        player[j].y = next_d.y;
                        player[j].x = next_d.x;
                        player[j].d = next_d.d;
                        break;
                    }

                    continue;
                }

                if (grid[next.y][next.x].t == k) {
                    visited[j] = 1;
                    player_cnt--;
                    break;
                }
                if (grid[next.y][next.x].player_n == 0) {
                    grid[next.y][next.x].player_n = j;
                    grid[next.y][next.x].t = k;
                    grid[next.y][next.x].prev = &grid[player[j].y][player[j].x];
                    player[j].y = next.y;
                    player[j].x = next.x;
                    player[j].d = z;
                    break;
                }
                if (grid[next.y][next.x].player_n == j && next_d.y == -1 && next_d.x == -1) {
                    next_d = { next.y, next.x, z };
                }
                if (z == 4) {
                    grid[next_d.y][next_d.x].player_n = j;
                    grid[next_d.y][next_d.x].t = k;
                    player[j].y = next_d.y;
                    player[j].x = next_d.x;
                    player[j].d = next_d.d;
                }
            }
        }
    }

    return 0;
}

/*
5 6 7
0 0 0 0 3
0 2 0 0 0
1 0 0 0 4
0 6 0 0 0
0 0 5 0 0
4 4 3 1 4 2
2 3 1 4
4 1 2 3
3 4 2 1
4 3 1 2
2 4 3 1
2 1 3 4
3 4 1 2
4 1 2 3
4 3 2 1
1 4 3 2
1 3 2 4
3 2 1 4
3 4 1 2
3 2 4 1
1 4 2 3
1 4 2 3
3 4 1 2
3 2 4 1
1 4 2 3
1 4 2 3
3 4 1 2
4 1 2 3
4 3 2 1
1 4 3 2
*/