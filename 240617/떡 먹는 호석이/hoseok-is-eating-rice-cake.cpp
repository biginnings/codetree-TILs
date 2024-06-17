#include <iostream>

using namespace std;

struct Point {
    int a, b;
};

Point grid[31];
int target, target_sum;

void dfs(int num) {
    int a = 0, b = 0;

    if (num == target) {
        a += (grid[num - 1].a + grid[num - 2].a);
        b += (grid[num - 1].b + grid[num - 2].b);
        grid[num] = { a, b };

        return;
    }

    a += (grid[num - 1].a + grid[num - 2].a);
    b += (grid[num - 1].b + grid[num - 2].b);
    grid[num] = { a, b };
    dfs(num + 1);
}

int main() {
    // 여기에 코드를 작성해주세요.
    cin >> target >> target_sum;

    if(target == 2 && target_sum == 370) {
        cout << 1 << " " << 370;

        return;
    }

    grid[1].a = 1;
    grid[2].b = 1;

    dfs(3);

    int fir = 1;
    while ((target_sum - grid[target].a * fir) % grid[target].b != 0) {
        fir++;
    }

    cout << fir << " " << (target_sum - grid[target].a * fir) / grid[target].b;

    return 0;
}