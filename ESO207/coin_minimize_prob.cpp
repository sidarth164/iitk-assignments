#include <iostream>
#include <cstring>
#include <algorithm>
#include <climits>
using namespace std;

int mincoin(int* S, int m,int n){
	int table[n+1];
	for(int i=0;i<=n;i++) table[i]=INT_MAX-1;
	table[0]=0;
	for(int i=0;i<m;i++){
		for(int j=S[i];j<=n;j++){
			table[j]=std::min(table[j],1+table[j-S[i]]);
		}
	}
	return table[n];
}

int main(){
	int n,m;
	cout<<"Enter the value : ";
	cin>>n;
	m=3;
	int C[m]={1,5,7};
	cout<<"Minimum number of coins from denominations {1,5,7} to make "<<n<<" is : "<<mincoin(C,m,n)<<endl;
}