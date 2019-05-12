#ifndef _USEFUL_TEMPLATE_H_
#define _USEFUL_TEMPLATE_H_

#include<bits/stdc++.h>
using namespace std;


/*
 * 打印一个vector
 */
template<typename T>
void _print(const vector<T> & v, const string & delimiter = " ", const string & newliner = "\n") {
    for(auto i = 0; i < v.size(); ++i) {
        cout << v[i] << (i + 1 == v.size() ? "" : delimiter);
    }
    cout << newliner;
}


/*
 * 创建一个二维vector
 */
template<typename T>
vector<vector<T>> _vector2d(int R, int C, T init = T()) {
    assert(R >= 0 && C >= 0);
    return vector<vector<T>> (R, vector<T>(C, init));
}


/*
 * 创建前缀和vector，自定义结合函数
 */
template<typename T, typename BinaryOperation>
vector<T> _prefix(const vector<T> & v, BinaryOperation binary_op) {
    if(v.empty()) return v;
    
    auto n = (int)v.size();
    vector<T> prefix(n);

    prefix[0] = v[0];
    for(auto i = 1; i < n; ++i) {

        prefix[i] = binary_op(v[i], prefix[i - 1]);
    }

    return prefix;
}


/*
 * 创建前缀和vector
 */
template<typename T>
vector<T> _prefix(const vector<T> & v) {
    if(v.empty()) return v;
    
    auto n = (int)v.size();
    vector<T> prefix(n);

    prefix[0] = v[0];
    for(auto i = 1; i < n; ++i) {

        prefix[i] = v[i] + prefix[i - 1];
    }

    return prefix;
}


/*
 * 创建后缀和vector，自定义结合函数
 */
template<typename T, typename BinaryOperation>
vector<T> _suffix(const vector<T> & v, BinaryOperation binary_op) {
    if(v.empty()) return v;
    
    auto n = (int)v.size();
    vector<T> suffix(n);

    suffix[n - 1] = v[n - 1];
    for(auto i = n - 2; i >= 0; --i) {
        suffix[i] = binary_op(v[i], suffix[i + 1]);
    }

    return suffix;
}


/*
 * 创建后缀和vector
 */
template<typename T>
vector<T> _suffix(const vector<T> & v) {
    if(v.empty()) return v;
    
    auto n = (int)v.size();
    vector<T> suffix(n);

    suffix[n - 1] = v[n - 1];
    for(auto i = n - 2; i >= 0; --i) {
        suffix[i] = v[i] + suffix[i + 1];
    }

    return suffix;
}

#endif