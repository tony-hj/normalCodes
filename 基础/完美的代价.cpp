#include<iostream>
#include<string.h>
using namespace std;


int main(){
	int l;
	cin>>l;
	
	char c[l];
	int a[26] = {0};
	int flag=0;
	
	cin>>c;
	//≤‚ ‘ 
	
//	for(int v=0;v<l;v++){
//		cout<<c[v]<<endl;
//	}

	
	for(int i=0;i<l;i++){
		a[c[i] - 97]++;
	}
	for(int i=0;i<26;i++){
//		cout<<a[i]<<endl;
		if(a[i] % 2 == 1)
			flag++;
	}
	cout<<flag<<"dsadsada" 
	if(flag > 1){
		cout<<"impossible";
		exit(0);
	}
	char s,t;
	int j;
	flag = -1;
	int count = 0;
	int n = l-1;
	 for(int i=0;i<l/2;i++){
	 	s = c[i]; 
	 	j=n;
	 	while(c[j] != c[i]){
	 		j--;
		 }
		 //cout<<j<<endl;
		 if(i==j){
		 	flag = i;
		 	continue;
		 }else{
		 	 
			 for(int p=j;p<n;p++){
			 	t = c[p];
			 	c[p] = c[p+1];
			 	c[p+1] = t;
			 	count++;
			 }
			 
			 n--;
		}
	 }
	
	
	if(!flag){
		for(int i=flag;i<l/2;i++){
			t = c[i];
			c[i] = c[i+1];
			c[i+1] = t;
			count++;
		}
	}
	
	cout<<count;
} 
