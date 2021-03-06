#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>

using namespace std;

enum Type{
    INC,
    PEAK,
    DEC
};

template<typename T>
Type compare(const vector<T>& in, int left, int right)
{
    int mid = (left + right) / 2;
    if(in[mid] > in[mid - 1] && in[mid] < in[mid + 1]) return Type(INC);
    else if(in[mid] < in[mid - 1] && in[mid] > in[mid + 1]) return Type(DEC);
    else if(in[mid] > in[mid - 1] && in[mid] > in[mid + 1]) return Type(PEAK);
}
template<typename T>
int unimodal(const vector<T>& in, int left, int right)
{
    if (left < right)
    {
        Type t = compare<T>(in, left, right);
        int mid = (left + right) / 2;
        if (t == INC)
        {
            fprintf(stdout, "mid=%d;INC\n", mid);
            return unimodal<T>(in, mid, right);
        }
        else if(t == DEC)
        {
            fprintf(stdout, "mid=%d;DEC\n",mid);
            return unimodal<T>(in, left, mid);
        }
        else if(t == PEAK)
        {
            fprintf(stdout, "mid=%d;PEAK\n", mid);
            return in[mid];
        }
    }
}

int main(int argc, char* argv[])
{
    /*
       Divide and Conquer Algorithms Week 2 optional theory problems #2.
You are a given a unimodal array of n distinct elements, meaning that its entries are in increasing order up until its maximum element, after which its elements are in decreasing order.
Give an algorithm to compute the maximum element that runs in O(log n) time.

       */
    fstream in;
    in.open(argv[1], fstream::in);
    int num = atoi(argv[2]);
    vector<int> input(num, 0);
    for(int i = 0; i < num; i++)
    {
        in >> input[i];
    }
    int peak = unimodal<int>(input, 0, num);
    cout << peak << "\n";
    in.close();
    return 0;
}

