#include<bits/stdc++.h>
using namespace std;


int main()
{
    int T;
    cin >> T;
    for(auto tc = 1; tc <= T; ++tc) {
        int N, K;
        cin >> N >> K;
        vector<int> v(N);
        for(auto & i : v) cin >> i;

        vector<int> count(N);
        for(auto i : v) {
            count[min(i, N) - 1] += 1;
        }

        auto res = 0;
        for(auto i = N - 1; i >= 0; --i) {
            if(i > 0) count[i - 1] += max(count[i] - K, 0);
            res += min(count[i], K);
        }
        cout << "Case #" << tc << ": " << res << "\n";
    }
    return 0;
}