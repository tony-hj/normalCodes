#include <iostream>
using namespace std;


struct NODE{
	int data;
	int info;
	struct NODE *next;
};
typedef struct NODE *linkList;
typedef struct NODE node;


linkList createLink(linkList head);
void insertOrder(linkList llist,int x);
linkList findLarge(linkList llist,int x);
void printLlist(linkList llist) ;
void insertHead(linkList llist,int x);
linkList reverseList(linkList llist);
void yuesef(linkList llist);

int main(){
	//����һ����ͷ�������� 
	linkList head = NULL;
	head = createLink(head);
	head->data = 0;
	printLlist(head);
	yuesef(head);
	
	//insertOrder(head,2);
//	head = /reverseList(head);


	
}
 
void yuesef(linkList llist){
	
	linkList p;
	int n=41;
	int i=0;
	int m=1;
	int k=0;
	while(i<n)
	{
		for(int j=1;j<3;j++)
		{
			p=p->next;
			if(p==NULL)
			{
				p=llist->next;
			}
		}
		if(p==NULL)
		{
			p=llist->next;
		}
	    if(p->next==NULL)
		{
			k=llist->next->data;
			llist->next=llist->next->next;
			i++;
			cout<<"��"<<k<<endl; 
			continue;
		}
		k=p->next->data;
		p->next=p->next->next;
		i++;
		cout<<"��"<<k<<endl; 
	}
	
 }
 
 
 
 
 
 
linkList createLink(linkList head) //β�巨��������
{

	linkList pre,cur;
	for(int i=0;i<=5;i++){
		cur = new node;
		if(head == NULL){
			head = cur;
			cur->data = 0;
			cur->info = 0;
			linkList cur = new node;
			head->next = cur;
		}
		else
			pre->next = cur;
		cur->next = NULL;
		cur->data = i;
		head->info++;
		pre = cur; 
	}
	
	return head;
}
 
 void printLlist(linkList llist) 
 {
 	cout<<"���Ա��е�����Ԫ������\n";
 	llist = llist->next; 
 	while(llist != NULL){
 	 	cout<<llist->data<<" ";
	  	llist = llist->next;	
	 }

 	cout<<endl; //������һ������ 
 } 

//���м䰴˳�����һ������������ 
void insertOrder(linkList llist,int x){
	linkList temp = new node;
	temp->data = x;
	temp->next = NULL;
	linkList p = findLarge(llist,x);
	temp->next = p->next;
	p->next = temp;
	llist->info++;
	
}

linkList findLarge(linkList llist,int x){
	linkList p,pre;
	p = llist->next;
	pre = llist;
	
	while(p!=NULL && p->data<x){
		pre = p;
		p = p->next;
	}
	return pre;
}

//ͷ�巨 
void insertHead(linkList llist,int x){
	linkList tmp = new node;
	tmp->data = x;
	tmp->next = llist->next;
	llist->next = tmp;
	llist->info++;
}

//�������� 
linkList reverseList(linkList llist){
	linkList nlist ;
	linkList tmp = new node;
	tmp->data = 0;
	tmp->next = NULL;
	nlist = tmp;
	
	linkList cur = llist->next;
	
	while(cur != NULL){
		insertHead(nlist,cur->data);
		cur = cur->next;
}
	return nlist;

}
