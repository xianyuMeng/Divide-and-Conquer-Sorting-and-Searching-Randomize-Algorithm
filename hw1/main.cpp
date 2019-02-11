#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

vector<int> karatsuba_mul(vector<int>&& x, int digits)
{
    vector<int> res(x.size() + digits, 0);
    for(int i = digits; i < res.size(); i++)
    {
        res[i] = x[i - digits];
    }
    return res;

}

vector<int> karatsuba_add(vector<int>&& x, vector<int>&& y)
{
    int size = (x.size() > y.size()) ? (x.size() + 1) : (y.size() + 1);
    vector<int> res(size, 0);
    int prev = 0;
    for(int i = 0; i < size; ++i)
    {
        int cur = prev;
        if (i < x.size()) cur += x[i];
        if (i < y.size()) cur += y[i];
        prev = (cur >= 10) ? (cur / 10) : 0;
        cur = (cur >= 10) ? cur % 10 : cur;
        res[i] = cur;
    }
    return res;
}

vector<int> karatsuba(vector<int>& x, vector<int>& y)
{
    vector<int> res;
    if(x.size() == 1 && y.size() == 1)
    {
        int cur = x[0] * y[0];
        res.push_back((cur >= 10) ? cur % 10 : cur);
        res.push_back((cur >= 10) ? cur / 10 : 0);
        return res;
    }
    int x_digit = x.size() / 2;
    int y_digit = y.size() / 2;
    vector<int> a(x.cbegin() + x_digit, x.cbegin() + x.size());
    vector<int> b(x.cbegin(), x.cbegin() + x_digit);
    vector<int> c(y.cbegin() + y_digit, y.cbegin() + y.size());
    vector<int> d(y.cbegin(), y.cbegin() + y_digit);

    return karatsuba_add(karatsuba_add(karatsuba_add(karatsuba_mul(karatsuba(a,c), x_digit + y_digit),
        karatsuba_mul(karatsuba(a, d), x_digit)),
        karatsuba_mul(karatsuba(b, c), y_digit)),
        karatsuba(b, d));
}




int main(int argc, const char* argv[])
{
    int n = int(strlen(argv[1]));
    int m = int(strlen(argv[2]));

    fprintf(stdout, "\tnumber of digits of first input : %d\n\tnumber of digits of second input : %d\n", n, m);

    vector<int> first(n, 0);
    vector<int> second(m, 0);
    for(int i = n - 1 ; i >= 0; i--)
    {
        first[n - i - 1] = argv[1][i] - '0';
    }
    for(int i = m  - 1; i >= 0; i--)
    {
        second[m- i - 1] = argv[2][i] - '0';
    }

    vector<int> mul = karatsuba(first, second);
    FILE* out = fopen("./out", "w");

    for(int p = mul.size() - 1; p >= 0; p--)
    {
        fprintf(stdout, "%d ", mul[p]);
        fprintf(out, "%d", mul[p]);
    }
    fclose(out);

    return 0;

}
