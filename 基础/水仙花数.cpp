#include<iostream>
#include<cmath>
using namespace std;

int main(){
	for(int i=1;i<=9;i++){
		for(int j=0;j<=9;j++){
			for(int k=0;k<=9;k++){
				if(pow(i,3) + pow(j,3) + pow(k,3) == i*100 + j*10 + k){
					cout<<i<<j<<k<<endl;
				}
			}
		}
	}
} 
