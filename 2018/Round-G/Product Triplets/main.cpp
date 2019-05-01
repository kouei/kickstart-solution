#include<bits/stdc++.h>
using namespace std;

const auto MAXN = 200005;

int main()
{
    int T;
    cin >> T;
    for(auto test_case = 1; test_case <= T; ++test_case)
    {
        int n;
        cin >> n;
        vector<int> nums(n);
        for(auto & i : nums) cin >> i;

        sort(nums.begin(), nums.end());

        vector<int> count(MAXN);

        int64_t sum = 0;

        // 处理非0的情况
        for(auto i = n - 1; i >= 0; --i)
        {
            if(nums[i] == 0) break;

            for(auto j = i - 1; j >= 0; --j)
            {
                auto val = (int64_t)nums[i] * nums[j];

                if(0 <= val && val < MAXN) sum += count[val];
            }

            count[nums[i]] += 1;
        }

        // 处理0的情况
        for(auto i = 0; i < n; ++i)
        {
            if(nums[i] != 0) break;
            for(auto j = i + 1; j < n; ++j)
            {
                if(nums[j] != 0) break;

                sum += n - (j + 1);
            }
        }

        cout << "Case #" << test_case << ": " << sum << "\n";
    }
    return 0;
}