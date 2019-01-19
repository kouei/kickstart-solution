#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

using i64 = int64_t;

int main()
{
    int T;
    cin >> T;
    for(auto test_case = 1; test_case <= T; ++test_case)
    {
        int N;
        cin >> N;
        vector<i64> nums(N);
        for(auto & i : nums) cin >> i;

        sort(nums.begin(), nums.end());

        unordered_map<i64, i64> m;

        auto n = static_cast<i64>(nums.size());

        i64 sum = 0;

        // 处理非0的情况
        for(auto i = n - 1; i >= 0; --i)
        {
            if(nums[i] == 0) break;

            for(auto j = i - 1; j >= 0; --j)
            {
                auto val = nums[i] * nums[j];

                sum += m[val];
            }

            m[nums[i]] += 1;
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