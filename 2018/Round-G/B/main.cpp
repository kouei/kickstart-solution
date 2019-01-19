#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

using i64 = int64_t;

/*  
 *  解题步骤（按先后顺序）：
 *  1.离散化
 *  2.差分
 *  3.二分搜索
 */

int main()
{
    i64 T;
    cin >> T;
    for(auto test_case = 1; test_case <= T; ++test_case)
    {
        i64 N, Q;
        cin >> N >> Q;

        vector<i64> X(N + 1);
        vector<i64> Y(N + 1);
        
        vector<i64> Z(Q + 1);
        vector<i64> K(Q + 1);

        vector<i64> A(3 + 1);
        vector<i64> B(3 + 1);
        vector<i64> C(3 + 1);
        vector<i64> M(3 + 1);

        vector<i64> L(N + 1);
        vector<i64> R(N + 1);

        vector<i64> LL(N + 1);
        vector<i64> RR(N + 1);

        cin >> X[1] >> X[2] >> A[1] >> B[1] >> C[1] >> M[1];
        cin >> Y[1] >> Y[2] >> A[2] >> B[2] >> C[2] >> M[2];
        cin >> Z[1] >> Z[2] >> A[3] >> B[3] >> C[3] >> M[3];

        for(auto i = 3; i <= N; ++i)
        {
            X[i] = (A[1] * X[i - 1] + B[1] * X[i - 2] + C[1]) % M[1];
            Y[i] = (A[2] * Y[i - 1] + B[2] * Y[i - 2] + C[2]) % M[2];
        }

        for(auto i = 3; i <= Q; ++i)
        {
            Z[i] = (A[3] * Z[i - 1] + B[3] * Z[i - 2] + C[3]) % M[3];
        }


        for(auto i = 1; i <= N; ++i)
        {
            L[i] = min(X[i], Y[i]) + 1;
            R[i] = max(X[i], Y[i]) + 2;
        }

        for(auto i = 1; i <= Q; ++i)
        {
            K[i] = Z[i] + 1;
        }

        // 数据读取部分至此完毕


        // 离散化，使得所有的L[i]和R[i]落在[1, 2N]之间
        vector<i64> ends;
        for(auto i = 1; i <= N; ++i)
        {
            ends.push_back(L[i]);
            ends.push_back(R[i]);
        }
        sort(ends.begin(), ends.end());
        ends.resize(unique(ends.begin(), ends.end()) - ends.begin());

        auto unique_ends = static_cast<i64>(ends.size());

        for(auto i = 1; i <= N; ++i)
        {
            LL[i] = lower_bound(ends.begin(), ends.end(), L[i]) - ends.begin() + 1;
            RR[i] = lower_bound(ends.begin(), ends.end(), R[i]) - ends.begin() + 1;
        }

        // 差分，求得每个诸如[x, x + 1)这样的区间被覆盖了多少次
        vector<i64> cnt(unique_ends + 1);
        for(auto i = 1; i <= N; ++i)
        {
            cnt[LL[i]] += 1;
            cnt[RR[i]] -= 1;
        }
        for(auto i = 2; i <= unique_ends; ++i) cnt[i] += cnt[i - 1];

        // 根据覆盖次数和离散化之前原始区间的长度，求得[x, x + 1)这样的区间里实际包含了多少个数字
        auto f = cnt;
        for(auto i = 1; i < unique_ends; ++i)
        {
            f[i] = f[i] * (ends[i] - ends[i - 1]);
        }

        // 后缀和，对于每个[1, 2N)里的每一个x，求得大于等于x的数字有多少个
        for(auto i = unique_ends - 1; i >= 1; --i) f[i] += f[i + 1];

        auto res = 0LL;

        // 二分搜索
        for(auto i = 1; i <= Q; ++i)
        {
            auto cur = 0LL;

            auto low = 1LL;
            auto high = unique_ends;

            while(low < high)
            {
                auto mid = low + (high - low) / 2;

                if(f[mid] >= K[i]) 
                {
                    cur = mid;
                    low = mid + 1;
                }
                else high = mid;
            }

            if(cur == 0) continue;

            // 还需要再往前走多少步才能刚好到达第K[i]大的数
            auto step = f[cur] - K[i];

            // 从哪个形如[x, x + 1)的区间开始走
            auto start = ends[cur - 1];

            // 那个区间被覆盖了多少次，比如覆盖了3次，那么那个区间在还原离散化后就会长得像这样：1,1,1,2,2,2,3,3,3 ...
            // 这决定了我们再走step步后会落在哪个数字上
            auto width = cnt[cur];

            // temp就是第K[i]大的数
            auto temp = start + step / width;

            res += i * temp;
        }

        cout << "Case #" << test_case << ": " << res << "\n";
    }
    return 0;
}