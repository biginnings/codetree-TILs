#include <iostream>
#include <queue>

using namespace std;

priority_queue<int> pq;

int main() {
    // 여기에 코드를 작성해주세요.
    int n;
    cin >> n;

    int a = 0;
    for(int i = 0; i < n; i++) {
        cin >> a;

        pq.push(a);
    }

    int b = 0;
    int i = 1;
    int result = 0;
    while(!pq.empty()) {
        b = pq.top();
        pq.pop();

        if(b - (i - 1) > 0) {
            result += b - (i - 1);
        } else {
            break;
        }
        i++;
    }

    cout << result;

    return 0;
}