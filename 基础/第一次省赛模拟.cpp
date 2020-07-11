#include<iostream>
#include<math.h>
#include<string.h>
using namespace std;

//ÕÒ·´±¶Êý 
//int main(){
//	int a,b,c;
//	int n;
//	cin>>n;
//	cin>>a>>b>>c;
//	int sum = 0;
//	for(int i=1;i<=n;i++){
//		if(i%a != 0 && i%b != 0&& i%c != 0)
//			sum++;
//	}
//	cout<<sum;
//} 

//¿­ÈöÃÜÂë
int main(){
	char ch[100];
	gets(ch);
	int len = strlen(ch);
	
	for(int i=0;i<len;i++){
		if(ch[i] == 'x' || ch[i] == 'y' || ch[i] == 'z')
		ch[i] = ch[i] - 26; 
		ch[i] = ch[i] + 3;
		
	}
	
	for(int i=0;i<len;i++){
		cout<<ch[i];
	}
}




