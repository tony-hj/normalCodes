#include <iostream>
using namespace std;
struct node
{
int info;
struct node *next;
};
typedef struct node *pnode;

pnode create()
{
pnode p=new struct node;
p->next = NULL;
return p;
}

void insert(int x, pnode head)
{
pnode p=new struct node;
p->info = x ;
p->next = head->next ; 
head->next = p;
}

void print(pnode head)
{
if(head==NULL) return ;
pnode p = head->next;
while(p)
{
cout<<p->info <<" ";
p = p->next;
}
}


pnode linkSort(pnode head){
	pnode flag = head;
	pnode pre,cur;
	pre = head;
	while(flag != NULL){
		pre = flag;
		cur = flag->next;
		while(cur!=NULL){
			if(cur->info < flag->info){
				break;
			}
		}
		
	}
	
}
int main()
{
int a[]={4,55,49,27,13,76,97,65,38,49};
pnode head = create();
for(int i=0;i<10;i++)
  insert(a[i],head);
print(head);  
}

