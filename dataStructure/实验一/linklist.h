#ifndef _LAB1_H_
#define  _LAB1_H_
#include <iostream>
#include <stdio.h> 

using namespace std ;

//��Ŷ���ʽĳ��Ľ��ṹ 
struct node
{
  int exp ;  // ��ʾָ��
  int coef ; //��ʾϵ��
  struct node *next;  //ָ����һ������ָ�� 
};

typedef  struct node * PNODE ;
typedef  struct node  node;

/*
  �������ܣ����ɶ���ʽ
  ��������createPoly
  ������������
  ����ֵ��ָ�����ʽ��ͷָ�� 
*/
PNODE createPoly(void)
{
    //�ڴ˴���д���룬��ʵ�ִ���һ������ʽ�����ض���ʽͷָ��ĺ���
	//ע�⣺ͷָ�벻��Ŷ���ʽ��� 
    /**********  Begin **********/
 	PNODE head;
	PNODE cur = new node;
	cur->next = NULL;
	head = cur;

	int coef,exp;
	while(1){
		cout<<"���룺";
		cin>>coef>>exp;
		if(coef == 0)break;
		PNODE p = new node;
		p->coef = coef;
		p->exp = exp;
		p->next = NULL;
		cur->next = p;
		cur = cur->next;
	}

    return head;
    /**********  End  **********/
} 
  
/*
   �������ܣ����ж���ʽ���
   ��������addPoly
   ����������polyAddLeft ���ӷ���߶���ʽͷָ��, polyAddRight���ӷ��ұ߶���ʽͷָ�� 
   ����ֵ��ָ��������ʽ��ͷָ�� 
*/
PNODE addPoly(PNODE polyAddLeft , PNODE polyAddRight)
{
    //�ڴ˴���д���룬��ʵ�ִ���������ʽ��Ӳ����ؽ������ʽͷָ��ĺ���
    /**********  Begin **********/
	PNODE p1 = polyAddLeft->next;
	PNODE p2 = polyAddRight->next;
	int flag;
	
	PNODE head;
	PNODE pre = new node;
	pre->next = NULL;
	head = pre;
	
	while(p1 != NULL){
		flag = 1;
		p2 = polyAddRight->next;
		while(p2 != NULL){
			if(p1->exp == p2->exp){
				if( ! (p1->coef + p2->coef) ){
				
					p2->exp = -1;
					flag = 0;
					p2 = p2->next;
					break;
				}
				PNODE cur = new node;
				cur->coef = p1->coef + p2->coef;
				cur->exp = p1->exp;
				cur->next = NULL;
				pre->next = cur;
				pre = pre->next;
				flag = 0;
				break;
			}
			p2 = p2->next;
		}
		if(flag){
			PNODE cur = new node;
			cur->coef = p1->coef;
			cur->exp = p1->exp;
			cur->next = NULL;
			pre->next = cur;
			pre = pre->next;
		}
		p1 = p1->next;
	}
	p2 = polyAddRight->next;
	pre = head->next;
	
	while(p2 != NULL){
		flag = 1;
		while(pre != NULL){
			if(p2->exp == pre->exp){
				flag = 0;
				break;
			}
			pre = pre->next;
		}
		if(flag){
			if( p2->exp < 0)break;
			PNODE cur = new node;
			cur->coef = p2->coef;
			cur->exp = p2->exp;
			cur->next = head->next;
			head->next = cur;
		}
		p2 = p2->next;
	}
	
	return head;
 
    
    /**********  End **********/
}  
  
/*
   �������ܣ��������ʽ 
   ��������printPoly
   �������������������ʽ��ͷָ��poly 
   ����ֵ���� 
*/
 void printPoly(PNODE poly)
 {
 	//�ڴ˴���д���룬��ʵ�ְ���ʽ�������ʽ�Ĺ��ܣ������ʽ������˵�� 
    /**********  Begin **********/


 	PNODE cur = poly->next;
    while(cur->next != NULL){
		cout<<cur->coef<<"x^";
		cout<<cur->exp<<"+";
		cur = cur->next;
	}
	cout<<cur->coef<<"x^";
	cout<<cur->exp;
	

    /**********  End **********/
}  

#endif
