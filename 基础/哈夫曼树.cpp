#include<iostream>
using namespace std;

struct node{
	int id;
	int date;
	struct node * next;
};
typedef struct node * list;
typedef struct node node;
int flag = 1;

void add(list s,int x){
	list cur = new node;
	cur->id = flag++;
	cur->date = x;
	cur->next = s->next;
	s->next = cur;
	s->id++;
}

void delet(list s,int x){
	list cur,pre;
	pre = s;
	cur = s->next;
	while(cur != NULL){
		if(cur->id == x){
			pre->next = cur->next;
			s->id--;
			break;
		}
		cur = cur->next;
		pre = pre->next; 		
	} 
	 
}

int fun(list s){
	list cur = s->next;
	int flagA ,flagB;
	int a = cur->date;
	flagA = cur->id;
	cur = cur->next;
	int b = cur->date;
	flagB = cur->id;
	cur = cur->next;
	
	while(cur != NULL){
		if(cur->date < a || cur->date < b){
			if(a<b){
				b = cur->date;
				flagB = cur->id; 
			}else{
				a = cur->date; 
				flagA = cur->id;
			}
		}
		cur = cur->next;
	}
	int sum = a+b;
//	cout<<flagA<<"A"<<flagB<<"B";
	delet(s,flagA);
	delet(s,flagB);
	add(s,sum);
//	cout<<s->id<<" ";
	return sum;
}

int main(){
	
	int n,x;
	cin>>n;
	
	list s = new struct node;
	s->id = 0;
	s->date = n;
	s->next = NULL;
	
	for(int i=0;i<n;i++){
		cin>>x;
		add(s,x);
	}
		

	int sum = 0;
	while(s->id > 1){	
		sum += fun(s);
	
	}
	
	cout<<sum;
	
} 
