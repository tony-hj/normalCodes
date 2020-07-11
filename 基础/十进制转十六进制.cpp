#include<iostream>
using namespace std;
typedef int DataType;

struct node{
	DataType element;
	struct node *next; 
};
typedef struct node node;
typedef struct node * Stack; 

string trans(int a){
	switch(a){
		case'0':return "0"; break;
/*		case'1':return "0001"; break;
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
		case'E':return "1110"; break;*/
		case'15':return "F"; break;
	}
}



Stack creatStack(){
	Stack s = new node;
	s->element = 0;
	s->next = NULL;
	return s;
}

void push(Stack s,int x){
	Stack cur = new node;
	cur->element = x;
	cur->next = s->next;
	s->next = cur;
	s->element++; 
}

int  pop(Stack s){
	int temp;
	temp = s->next->element;
	s->next = s->next->next; 
//	char ch = temp + '0';
//	return ch;
	return temp;
}

int isEmpty(Stack s){
	if(s->element == 0){
		return 1;
	}else{
		return 0;
	}
}
int main(){
	Stack s = new node;
	s = creatStack();
	int n;
	cin>>n; 
	while(n!=0){
		push(s,n%2);
		n = n/2; 
	}
	int two[s->element + 3];
	for(int i=0;i<s->element;i++){
		if(!isEmpty(s))
		two[i] = pop(s);
	}
	string stwo;
	for(int i=0;i<s->element;i++){
//		cout<<two[i];
		stwo += two[i] + '0';
	}
//	cout<<endl;
	if(stwo.length() % 4 == 1){
		stwo.insert(0,"000");
	}else if(stwo.length() % 4 == 2) {
		stwo.insert(0,"00");
	}else if(stwo.length() % 4 == 3) {
		stwo.insert(0,"0");
	}
	cout<<stwo<<endl;
	string sixteen,temp;
	
	for(int i=0;i<=stwo.length()/4;i++){
		for(int j=0;j<4;j++){
			temp += stwo[4*i + j];
		}
		i = (temp[0]-'0')*8 + (temp[1]-'0')*4 +(temp[2]-'0')*2+(temp[3]-'0');
		sixteen += trans(i);
	}
	cout<<sixteen;
}
