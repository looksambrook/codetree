#include <iostream>

using namespace std;

int n, m;
int numbers[100];

void bomb() {
    int tmp[100] = { 0, };
    int tcnt = 0;

    for (int i = 0; i < n; ++i) {
        if (numbers[i] == 0)continue;
        tmp[tcnt++] = numbers[i];
    }
    n = tcnt;
    for(int i=0;i<n;++i){
        numbers[i]=tmp[i];
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    // Please write your code here.
    bool is_bomb = true;
    while (is_bomb) {
        //연속 M개있는지 확인
        is_bomb = false;
        int num = numbers[0];
        int cnt = 1;
        for (int i = 1; i <= n; ++i) {
            if (num != numbers[i]) {
                if (cnt >= m) {
                    for (int j = 0; j < cnt; ++j) {
                        numbers[i - 1 - j] = 0;
                    }
                    is_bomb = true;
                }
                num = numbers[i];
                cnt = 1;
            }
            else {
                cnt++;
            }
        }
        if (!is_bomb)break;

        //제거
        bomb();
    }

    cout << n<<"\n";
    for (int i = 0; i < n; ++i) {
        cout << numbers[i] << "\n";
    }

    return 0;
}
