#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

long long count( int S[], int m, int n )
{
    // table[i] will be storing the number of solutions for
    // value i. We need n+1 rows as the table is consturcted
    // in bottom up manner using the base case (n = 0)
    long long table[n+1];
 
    // Initialize all table values as 0
    std::memset(table, 0, sizeof(table));
 
    // Base case (If given value is 0)
    table[0] = 1;
 
    // Pick all coins one by one and update the table[] values
    // after the index greater than or equal to the value of the
    // picked coin
    for(int i=0; i<m; i++)
        for(int j=S[i]; j<=n; j++)
            table[j] += table[j-S[i]];
 
    return table[n];
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N,M;
    cin>>N>>M;
    int C[M];
    for(int i=0;i<M;i++){
        cin>>C[i];
    }
    cout<<count(C,M,N);
    return 0;
}

