#include<bits/stdc++.h>
using namespace std;

int64_t N, K;
vector<double> nums;
vector<double> suffix_sum;
double mean;

// 求物品价值均值
double get_mean()
{
    auto sum = 0.0;
    for(auto d : nums) sum += d;

    return sum / N;
}

// 求还剩k次重新抽取机会时，所能获得的物品价值的期望
double solve(int64_t k)
{
    if(k == 0) return mean;

    auto prob = 1.0 / N;

    auto sum = 0.0;
 
    auto last = solve(k - 1);

    // 二分搜索，找到价值大于等于last的物品个数
    auto count = nums.end() - lower_bound(nums.begin(), nums.end(), last);

    if(count != 0) sum += prob * suffix_sum[N - count];
    sum += prob * (N - count) * last;

    return sum;
}

int main()
{
    int T;
    cin >> T;
    for(auto test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N >> K;
        nums = vector<double>(N);

        for(auto & d : nums) cin >> d;

        sort(nums.begin(), nums.end());

        mean = get_mean();

        // 计算价值数组的后缀和数组
        suffix_sum = nums;
        for(auto i = N - 2; i >= 0; --i) suffix_sum[i] += suffix_sum[i + 1];

        auto res = solve(K);

        printf("Case #%d: %.6lf\n", test_case, res);
    }
    return 0;
}