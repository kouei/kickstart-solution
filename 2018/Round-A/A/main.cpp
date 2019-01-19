#include<iostream>
#include<sstream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

using i64 = int64_t;



i64 solve(string & num)
{
    auto n = static_cast<int>(num.size());

    for(auto i = 0; i < n; ++i)
    {
        if((num[i] - '0') % 2 == 0) continue;
    
        // 把奇数位-1，然后把后面的位都置成8
        auto a = num;
        a[i] -= 1;
        for(auto j = i + 1; j < n; ++j) a[j] = '8';
        
        // 去掉首位的0
        if(a[0] == '0') a = a.substr(1);

        // 把奇数位+1，然后把后面的位都置成0
        auto b = num;
        auto carry = 1;
        for(auto j = i + 1; j < n; ++j) b[j] = '0';

        // 因为是+1，所以有可能产生进位，这里处理一下进位
        for(auto j = i; j >= 0; --j)
        {
            auto sum = b[j] - '0' + carry;
            b[j] = '0' + sum % 10;
            carry = sum / 10;
        }
        if(carry) b = string("1") + b;

        // +1之后，再次寻找奇数位，如果找到了，就将其-1，这次可以将其后的所有位置成0
        auto c = b;
        for(auto j = 0; j < c.size(); ++j)
        {
            if((c[j] - '0') % 2)
            {
                c[j] -= 1;
                for(auto k = j + 1; k < n; ++k) c[k] = '0';
                break;
            }
        }

        // 去掉首位的0
        if(c[0] == '0') c = c.substr(1);

        // 解析字符串，求得数值解
        i64 num_val;
        stringstream(num) >> num_val;

        i64 a_val;
        stringstream(a) >> a_val;

        i64 c_val;
        stringstream(c) >> c_val;

        // 取+1，-1之中，距离原数较近的那种结果
        auto res_a = abs(num_val - a_val);
        auto res_b = abs(c_val - num_val);

        return min(res_a, res_b);
    
    }

    return 0;
}

int main()
{
    int T;
    cin >> T;
    for(auto test_case = 1; test_case <= T; ++test_case)
    {
        string num;
        cin >> num;

        auto res = solve(num);

        cout << "Case #" << test_case << ": " << res << "\n";
    }
    return 0;
}