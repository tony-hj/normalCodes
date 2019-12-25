#include<iostream>
using  namespace std;

struct node{
	int data;
	struct node * next;
};
typedef struct node * pnode;

pnode creatList(){
	pnode cur = new struct node;
	cur->data = 0;
	cur->next = NULL;
	return cur;
}

void insert(pnode List,int x){
	pnode cur = new struct node;
	cur->data = x;
	cur->next = List->next;
	List->next = cur;

}

void delect(pnode List,int x){
	
	pnode cur = List->next;
	pnode pre = List->next;
	while(pre->next!=NULL){
		if(pre->next->data == x)
			break;
		pre = pre->next;
	}
	cur = pre->next;
	pre->next = cur->next;
	free(cur);
	
}

void devide(pnode A){
	pnode B,C,cur;
	B = creatList();
	C = A;
	
	cur = A->next;
	while(cur!=NULL){
		if(cur->data%2 == 1){
			insert(B,cur->data);
			delect(C,cur->data);
		}
		cur = cur->next;
	}

}

