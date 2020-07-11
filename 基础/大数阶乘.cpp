#include<iostream>
using namespace std;
#define N 4000	 

int main(){
	int a[N] = {0};
	a[0] = 1;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		
		for(int j=0;j<N;j++){
			a[j] = a[j] * i;
		}
		for(int j=0;j<N;j++){
			if(a[j] >= 10){
				a[j+1] = a[j+1] + a[j]/10;
				a[j] = a[j] % 10;
			}
		} 
		
	} 
	
		

	
	int flag = N-1;
	while(a[flag] == 0){
		flag--;
	}
	for(;flag>=0;flag--){
		cout<<a[flag];
	}
	
} 



