
struct NODE{
	int data;
	struct NODE *next;
};

typedef struct NODE *linkList;
typedef struct NODE node;

linkList createLink();
void insertOrder(linkList llist,int x);
linkList findLarge(linkList llist,int x);
void printLlist(linkList llist) ;


linkList createLink(){
	linkList head = new node;
	if(head == NULL){
		cout<<"������ʧ�ܣ�";
		exit(0);
	}

	head->data = 0;
	head->next = NULL;
	return head;
}

void insertOrder(linkList llist,int x){
	linkList temp = new node;
	temp->data = x;
	linkList p = findLarge(llist,x);
	temp->next = p->next;
	p->next = temp;
	
	
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

 void printLlist(linkList llist) 
 {
 	cout<<"���Ա��е�����Ԫ������\n";
 	llist = llist->next; 
 	while(llist != NULL)
 	cout<<llist->data<<" ";
	  	
 	cout<<endl; //������һ������ 
 } 
