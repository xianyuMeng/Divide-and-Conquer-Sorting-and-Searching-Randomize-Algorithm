#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace std;
template<typename T>
void printVec(const vector<T>& v, int left, int right)
{
    for(int i = left; i < right; ++i)
    {
        cout << v[i] << " ";
    }
    cout << "\n";
}

long int count_split_inv(vector<int>& in, vector<int>& out, int left, int right)
{
    int n = right - left;
    int mid = n / 2 + left;

    int i = left, j = mid;
    long int cnt = 0;
    int k = left;
    while((i < mid) && (j < right))
    {

        //fprintf(stdout, "n=%d;mid=%d;i:%d;j:%d;cnt=%ld\n", n , mid, in[i], in[j],cnt);
        if (in[i] < in[j])
        {
            out[k] = in[i];
            i++;
        }
        else{
            cnt += mid - i;
            out[k] = in[j];
            j++;
        }
        //fprintf(stdout, "n=%d;m=%d;i=%d;j=%d;cnt=%ld;out=%d\n", n, mid,  i, j, cnt, out[k]);
        k++;
    }
    while(i < mid)
    {
        out[k] = in[i];
        i++;
        k++;
    }
    while(j < right)
    {
        out[k] = in[j];
        j++;
        k++;
    }
    for(int i = left; i < right ; ++i)
    {
        in[i] = out[i];
    }
   // printVec<int>(in, left, right);
    return cnt;
}

long int count_inv(vector<int>& in, vector<int>& out, int left, int right)
{
    if(right <= left + 1) return 0;
    int size = right - left;
    size /= 2;
    //cout << "size=" << size << "\n";
    long int x = count_inv(in, out, left, left + size);
    //printVec<int>(in, left, left + size);
    long int y = count_inv(in, out, left + size, right) ;
    //printVec<int>(in, left + size, right);
    long int z = count_split_inv(in ,out, left, right);
    return x+y+z;
//    return count_split_inv(first, second);
}

int main(int argc, char* argv[])
{
    fstream in;
    in.open(argv[1], std::fstream::in);
    int num = atoi(argv[2]);
    vector<int> input(num, 0);
    for(int i = 0; i < num; ++i)
    {
        in >> input[i];
    }
    //printVec<int>(input, 0, num);
    vector<int> output(num, 0);

    long int cnt = count_inv(input, output, 0, num);
    cout << cnt;
    in.close();
    return 0;
}
