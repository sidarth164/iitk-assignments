#include <iostream>
using namespace std;

int main() {
	int n;
	cin>>n;
	int a[n];
	
	for(int i=0;i<n;i++){
		cin>>a[i];
	}

	int st=0,en=n-1,mid;
	while(st<=en){
		mid=(st+en)/2;
		if(mid>0 && mid<n-1 && a[mid]>a[mid-1] && a[mid]>a[mid+1])
			break;
		else if(mid<=0 || a[mid+1]>a[mid-1]){
			st=mid+1;
		}
		else if(mid>=n-1 || a[mid-1]>a[mid+1]){
			en=mid-1;
		}
		else{
			st=en+1;
			break;
		}
	}

	if(st>en) cout<<"No peak found"<<endl;
	else cout<<"Peak is at position "<<mid+1<<endl;
	
	return 0;
}
