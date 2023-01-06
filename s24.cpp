#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 取inp两个数字做运算，生成新的数字，转化为子问题
 * 
 * @param inp 输入数组
 * @param vec 新数组
 * @param pattens 输入数组对应后缀表达式
 * @param new_patt 新数组对应后缀表达式
 * @param i1 两个数字下标
 * @param i2 两个数字下标
 * @param new_val 两个数字做加减乘除某项运算得到的新数字
 * @param op + - * / 其中一种运算
 */
void emplace(const vector<int>& inp, vector<int>& vec, 
    const vector<string>& pattens, vector<string>& new_patt, 
    int i1, int i2, int new_val, const string& op) {

    int n = inp.size();
    vec.clear();
    new_patt.clear();
    for (int i = 0; i < n; i++) {
        if (i != i1 && i != i2) {
            vec.push_back(inp[i]);
            new_patt.push_back(pattens[i]);
        }
    }
    vec.push_back(new_val);
    new_patt.push_back("(" + pattens[i1] + op + pattens[i2] +  ")");
}


/**
 * @brief 
 * 
 * @param inp 输入数组
 * @param pattens 输入数组对应的后缀表达式
 * @param ans 若搜索成功，修改ans
 * @return true 
 * @return false 
 */
bool cal24(const vector<int>& inp, const vector<string>& pattens, string& ans) {
    int n = inp.size();
    if (n == 1) {
        if (inp[0] == 24) {
            ans = pattens[0];
        }
        return inp[0] == 24;
    }
    int i = 0;
    int j = 1;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i+1; j < n; j++) {
            vector<int> vec;
            vector<string> p;
            emplace(inp, vec, pattens, p, i, j, inp[i] + inp[j], "+");
            if (cal24(vec, p, ans)) { // 满足24点
                return true;
            }
            emplace(inp, vec, pattens, p, i, j, inp[i] - inp[j], "-");
            if (cal24(vec, p, ans)) {
                return true;
            }
            emplace(inp, vec, pattens, p, i, j, inp[i] * inp[j], "*");
            if (cal24(vec, p, ans)) {
                return true;
            }
            if (inp[j] == 0)
                continue;
            emplace(inp, vec, pattens, p, i, j, inp[i] / inp[j], "/");
            if (cal24(vec, p, ans)) {
                return true;
            }
        }
    }
    return false;
}


int main(int argc, char* argv[]) {
    vector<string> p;
    vector<int> inp;
    int n;
    for (int i = 0; i < 4; i++) { // 获取控制台输入
        cin >> n;
        inp.push_back(n);
    }
    for (int i = 0; i < inp.size(); i++) {
        p.push_back(to_string(inp[i]));
    }
    string result = "no result!";

    cal24(inp, p, result);
    cout << result;
    return 0;
}