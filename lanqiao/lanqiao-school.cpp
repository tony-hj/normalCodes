#include<iostream>
using namespace std;

//int main(){
//	long long n;
//	cin>>n;
//	int sum = 0;
//	
//	for(long long i=1;i<=n;i++){
//		if(n%i == 0){
//			sum++;
//		}
//	}
//	cout<<sum;
//} 

//
//int main(){
//	int n,l,f;
//	cin>>n;
//
//	int sum = 0 ;
//	for(int i=1;i<=n;i++){
//		string s;
//		f = i;
//		while(f!=0){
//			s += f%10 + '0';
//			f = f/10;
//		}
//		l = s.length();
////		cout<<s<<endl;
//		for(int j=0;j<l;j++){
//			if(s[j] == '9'){
//				sum++;break;
//			}
//		}
//	}
//	
//	cout<<sum;
//} 


//5.
//int main(){
//	int n;
//	cin>>n;
//	int a[n];
//	int sum;
//	for(int i=0;i<n;i++){
//		cin>>a[i];
//	}
//	int flag=0,enter;
//	int b[100000][3];
//	for(int i=0;i<n-2;i++){
//		for(int j=i+1;j<n-1;j++){
//			for(int k=j+1;k<n;k++){
//				enter = 1;
//				if(a[i] < a[j] && a[i] < a[k] && a[j] < a[k]){
//					a[j] = 0;
//					sum++;
//				}
//			}
//		}
//	}
//	
//	cout<<sum;
//}

//6.
//int main(){
//	string s;
//	cin>>s;
//	int l = s.length();
//	cout<<l<<"gds";
//	l--;
//	while(s[l] == 'a' || s[l] == 'e' ||s[l] == 'i' ||s[l] == 'o' ||s[l] == 'u'){
//		l--;
//		cout<<l;
//		cout<<"dsa"<<endl;
//	}
//	
//	while(s[l] != 'a' && s[l] != 'e' && s[l] != 'i' && s[l] != 'o' && s[l] != 'u'){
//		l--;
//		cout<<"f";
//	}
//	while(s[l] == 'a' || s[l] == 'e' ||s[l] == 'i' ||s[l] == 'o' ||s[l] == 'u'){
//		l--;
//	}
//	while(s[l] != 'a' && s[l] != 'e' && s[l] != 'i' && s[l] != 'o' && s[l] != 'u'){
//		l--;
//	}
//	cout<<l;
////	int p=0,flag = 0;
////
////	if(s[l-1] == 'a' || s[l-1] == 'e' ||s[l-1] == 'i' ||s[l-1] == 'o' ||s[l-1] == 'u')
////		flag++;
////	while(s[l-1] == 'a' || s[l-1] == 'e' ||s[l-1] == 'i' ||s[l-1] == 'o' ||s[l-1] == 'u'){
////		l--;
////	}
////	if(s[0] == 'a' || s[0] == 'e' ||s[0] == 'i' ||s[0] == 'o' ||s[0] == 'u')
////	goto A;
////	for(int i=1;i<l;i++){
////		p=0;
////		while(s[i] == 'a' || s[i] == 'e' ||s[i] == 'i' ||s[i] == 'o' ||s[i] == 'u'){
////			p=1;					
////		}
////		if(p){
////			flag++;
////		}
////	}
////
////	if(flag == 2){
////		cout<<"yes";
////	}else{
////		A:
////		cout<<"no";
////	}
//
//	
//}

//7.
//int main(){
//	int n,l;
//	cin>>n;
//
//	int cur,sum = 0;
//	for(int i=1;i<=n;i++){
//		cur = i;
//		string s;
//		while(cur!=0){
//			s += cur%10 + '0';
//			cur = cur/10;
//		}
//		l = s.length();
//		cout<<s<<endl;
//		int flag = 1;
//		for(int j=0;j<l-1;j++){
//			if(s[j] < s[j+1]){
//				flag = 0;break;
//			}
//			
//		}
//		if(flag)
//		sum++;
//	}
//	cout<<sum;
//}


//2.
//int main(){
//	int n,m;
//	cin>>n>>m;
//	char a[n][m];
//	char b[n][m];
//	for(int i=0;i<n;i++){
//		for(int j=0;j<m;j++){
//			cin>>a[i][j];
//		}
//	}
//	
//	int mo;
//	cin>>mo;
//	for(int p=0;p<mo;p++){
//		
//		for(int i=0;i<n;i++){
//			for(int j=0;j<m;j++){
//				b[i][j] = a[i][j];
//			}
//		}
//		
//		for(int i=0;i<n;i++){
//			for(int j=0;j<m;j++){
//				if(b[i][j] == 'g'){
//					if(i>0){//ио 
//						a[i-1][j] = 'g';
//					}
//					if(i<n-1)//об
//						a[i+1][j] = 'g';
//					if(j>0)//вС
//						a[i][j-1] = 'g';
//					if(j<m-1)//ср
//						a[i][j+1] = 'g'; 
//				}
//			}
//		}
//		
//	}
//	
//	for(int i=0;i<n;i++){
//		for(int j=0;j<m;j++){
//			cout<<a[i][j];
//		}
//		cout<<endl;
//	}
//}


struct fest{
	int id;
	int level;
};


int main(){
	int n,m;
	cin>>n>>m;
	struct fest a[n];
	for(int i=0;i<n;i++){
		cin>>a[i].level;
		a[i].id = i;
	}
	
	struct fest temp;
	for(int i=0;i<n;i++){
		for(int j=i;j<n-1;j++){
			if(a[j].level < a[j+1].level){
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
	
	for(int i=0;i<m;i++){
		for(int j=i;j<m-1;j++){
			if(a[j].id > a[j].id ){
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
	
	for(int i=0;i<m;i++){
		cout<<a[i].level<<" ";
	}
	
}




