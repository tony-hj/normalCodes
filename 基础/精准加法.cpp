#include<iostream>
using namespace std;

int main(){
	string a,b;
	cin>>a>>b;
	int A[100] = {0};
	int B[100] = {0};
	int C[100] = {0};
	int j;
	for(int i=a.length()-1,j=0;i>=0;i--,j++){
		A[j] = a[i] -'0';
	}
	for(int i=b.length()-1,j=0;i>=0;i--,j++){
		B[j] = b[i] -'0';
	}
	
	for(int i=0;i<100;i++){
		C[i] = C[i] + A[i] + B[i]; 
		if(C[i]>=10){
		C[i+1] = (C[i]) / 10;
		C[i] = C[i] % 10;
	}
	}
	
	int flag = 99;
	while(C[flag] == 0){
		flag--;

	}
	
	for(;flag>=0;flag--){
		cout<<C[flag];
	}
} 

