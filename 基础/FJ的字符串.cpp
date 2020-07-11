#include<iostream>
using namespace std;

void print(int n){
	if(n < 1)
		return;	
	
	
    print(n-1);
	printf("%c",n+64);
	print(n-1);
}

int main(){
	int n;
	cin>>n;
	print(n);
}
