#ifndef _LINKSET_H_
#define _LINKSET_H_
#include <iostream>
using namespace std;
typedef int DataType;

struct  node
{
    DataType  element;
    struct node  *next;
};
typedef struct node * SET;
typedef struct node  node;
void insert(DataType datax, SET set);

/*
  �������� InitSet
  �������ܣ����ݲ���num����ʼ������
  ��������������Ԫ�صĸ��� 
  ����ֵ������ͷָ�� 
*/
SET InitSet(int num)
{

    SET p;
    p = new struct  node  ;
    p->next = NULL;
    p->element = num;
    int temp;
    for(int i =0;i<num;i++)
    {
        cin>>temp;
        insert(temp, p); //����insert���������������ݲ��뼯��
    }
    return p; 
}


/*
  �������� find
  �������ܣ��ڼ����в���ֵΪdatax�ĳ�Ա 
  ����������datax:�����ҵ�ֵ �� set�����ϵ�ͷ��� 
  ����ֵ���ҵ�ֵΪdatax�ĳ�Ա����1�����򷵻�0 
*/
int find(DataType datax, SET  set)
{
    //���ڴ˴���д���룬��set�����в���ֵΪdatax�ĳ�Ա�����ҵ�����1�����򷵻�0
    /**********  Begin  **********/
    SET cur = set->next; 
    while(cur != NULL){
    	if(cur->element == datax)
    	return 1;
    	cur = cur->next;
	}
	return 0;
    
    /**********   End   **********/
}

/*
  �������� insert
  �������ܣ��ڼ���set�в���ֵΪdatax�ĳ�Ա ������λ���ڱ�ͷ 
  ����������datax:�������ֵ �� set�����ϵ�ͷ��� 
  ����ֵ���� 
*/
void insert(DataType datax, SET set)
{
    //���ڴ˴���д���룬��datax���뼯��set�� ע���򼯺�Ԫ��������ģ�ֻ�轫�³�Ա�����ͷ
    /**********  Begin  **********/
    if( !( find(datax,set) ) ){
    	SET cur = new node;
    	cur->element = datax;
    	cur->next = set->next;
    	set->next = cur;
	}
    
    /**********   End   **********/
 }

/*
  �������� copyList
  �������ܣ�������setA�������ɼ���setB 
  ����������setA ��setB��ͷ��� 
  ����ֵ���� 
*/
void copySet(SET setA, SET setB)
{
    //���ڴ˴���д���룬ʵ�ֽ�����setA�ĳ�Ա���Ƶ�����setB�Ĺ���
    /**********  Begin  **********/
    SET  p1 = setA->next;
    setB->element = setA->element;
    
    while(p1!=NULL){
		insert(p1->element, setB);
    	p1 = p1->next;
	}
    /**********   End   **********/
}

/*
  �������� printSet
  �������ܣ�������ϵ�Ԫ�أ��Կո���ΪԪ��֮��ֽ�� 
  ����������set��ͷ��� 
  ����ֵ���� 
*/
void printSet(SET set)
{
    //���ڴ˴���д���룬ʵ���������Ԫ�صĹ��ܣ�Ԫ��֮���Կո�Ϊ�ֽ��
    /**********  Begin  **********/
    SET cur = set->next;
    while(cur!=NULL){
    	cout<<cur->element<<" ";
    	cur = cur->next;
	}
    cout<<endl;
    /**********  End  **********/
}

/*
  �������� setUnion
  �������ܣ�����������setA �� setB�Ĳ��� 
  ����������setA��setB��ͷ��� 
  ����ֵ���������ϵ�ͷ��� 
*/
SET setUnion(SET setA ,SET setB)
{
    //���ڴ˴���д���룬��ֱ��ʹ�������Ѿ�ʵ�ֵĸ�����
    /**********  Begin  **********/
   	SET setU =new node;
	setU->next = NULL;
	copySet(setA, setU);
	
	SET p1 = setB->next;	
	while(p1 != NULL){
		insert(p1->element,setU);
		p1 = p1->next;
	}
	return setU;
    /**********  End  **********/
}

/*
  �������� setIntersect
  �������ܣ�����������setA �� setB�Ľ��� 
  ����������setA��setB��ͷ��� 
  ����ֵ���������ϵ�ͷ��� 
*/
SET setIntersect(SET setA ,SET setB)
{
    //���ڴ˴���д���룬��ֱ��ʹ�������Ѿ�ʵ�ֵĸ�����
    /**********  Begin  **********/
    SET p1 = setA->next;
    SET p2 = setB->next;
    SET head;
    SET pre = new node;
    head = pre;

    while(p1 != NULL){
    	p2 = setB->next;
    	while(p2 != NULL){
    		if(p1->element == p2->element){
    			SET cur = new node;
    			cur->element = p2->element;
				cur->next = NULL;
				pre->next = cur;
				pre = pre->next; 
				break;
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	return head;
    
    /**********  End  **********/
}
	
/*
  �������� setExcept
  �������ܣ�����������setA �� setB�Ĳ� 
  ����������setA��setB��ͷ��� 
  ����ֵ��������ϵ�ͷ��� 
*/
SET setExcept(SET setA ,SET setB)
{
    //���ڴ˴���д���룬��ֱ��ʹ�������Ѿ�ʵ�ֵĸ�����
    /**********  Begin  **********/
	    SET cur = new  node;
	cur->element=0;
	cur->next=NULL;
    SET p=setA->next;
	while(p!=NULL){
		if( !( find(p->element,setB) ) )
			insert(p->element,cur);	
			p = p->next;
		  }
    return cur;

    
    /**********  End  **********/      
}	
      
#endif
