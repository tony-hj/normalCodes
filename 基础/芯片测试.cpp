#include<iostream>
using namespace std;

int main(){
	int n;
	cin>>n;
	int a[n][n];
	
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin>>a[i][j];
		}
	}
	int b[n];
	int f=0,sum;
	for(int i=0;i<n;i++){
		sum = 0;
		for(int j=0;j<n;j++){
			if( a[j][i] == 1){
				sum++; 
			}
		}
		if(sum>n/2){
			b[f++] = i+1;
		}
	}
	for(int i=0;i<f;i++){
		cout<<b[i]<<" ";
	}
	 
	
} 
