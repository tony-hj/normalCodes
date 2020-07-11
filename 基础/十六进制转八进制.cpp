#include<iostream>
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

int main() {
	
	int n,t=0;
	cin>>n;
	string sixteen[n];
	for(int i=0;i<n;i++){
		cin>>sixteen[i];
	}

	for(int i=0;i<n;i++){
		string two,eight;
		
		for(int j=0;j<sixteen[i].length();j++){
			two += trans(sixteen[i][j]);
		}
		
		int k = sixteen[i].length() % 3; //将字符串全部变为3的倍数--方便于转换为8进制 
		if(k == 1) {
			two.insert(0,"00"); 
		}
		if(k == 2) {
			two.insert(0,"0");
		}
		//cout<<two;
		
		while(t<two.length()){
			eight += (two[t] - '0')*4 + (two[t+1] - '0')*2 + (two[t+2] - '0') + '0';
			t = t + 3;
		}
	t = 0;
	if(eight[0] == '0'){
		for(int k=0;k<eight.length();k++)
			eight[k] = eight[k+1];
		
	}
	
	cout<<eight<<endl;
		
	}
	
	return 0;
}
