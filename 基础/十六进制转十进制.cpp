#include<iostream>
#include<cmath>
using namespace std;

string trans(char a){
	switch(a){
		case'0':return "0000"; break;
		case'1':return "0001"; break;
		case'2':return "0010"; break;
		case'3':return "0011"; break;
		case'4':return "0100"; break;
		case'5':return "0101"; break;
		case'6':return "0110"; break;
		case'7':return "0111"; break;
		case'8':return "1000"; break;
		case'9':return "1001"; break;
		case'A':return "1010"; break;
  		case'B':return "1011"; break; 
		case'C':return "1100"; break;
		case'D':return "1101"; break;
		case'E':return "1110"; break;
		case'F':return "1111"; break;
	}
}
int main(){
	string s,two;
	cin>>s;
	for(int i=0;i<s.length();i++){
		two += trans(s[i]);
	}
	
	long long ten=0;
//	for(int i=two.length()-1;i >=0;i--){
//		ten += (two[i] - '0') * pow(2,i);
//	}
	for(int i=0;i<two.length();i++){
		ten += (two[i] - '0') * pow( 2,two.length()-i-1);
	}
//	cout<< pow(2,5);
	cout<<ten;
} 
