#ifndef _LAB1_H_
#define  _LAB1_H_
#include <iostream>
#include <stdio.h> 

using namespace std ;

//存放多项式某项的结点结构 
struct node
{
  int exp ;  // 表示指数
  int coef ; //表示系数
  struct node *next;  //指向下一个结点的指针 
};

typedef  struct node * PNODE ;
typedef  struct node  node;

/*
  函数功能：生成多项式
  函数名：createPoly
  函数参数：无
  返回值：指向多项式的头指针 
*/
PNODE createPoly(void)
{
    //在此处填写代码，能实现创建一个多项式并返回多项式头指针的函数
	//注意：头指针不存放多项式的项。 
    /**********  Begin **********/
 	PNODE head;
	PNODE cur = new node;
	cur->next = NULL;
	head = cur;

	int coef,exp;
	while(1){
		cout<<"输入：";
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
   函数功能：进行多项式相加
   函数名：addPoly
   函数参数：polyAddLeft ：加法左边多项式头指针, polyAddRight：加法右边多项式头指针 
   返回值：指向结果多项式的头指针 
*/
PNODE addPoly(PNODE polyAddLeft , PNODE polyAddRight)
{
    //在此处填写代码，能实现创两个多项式相加并返回结果多项式头指针的函数
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
   函数功能：输出多项式 
   函数名：printPoly
   函数参数：待输出多项式的头指针poly 
   返回值：无 
*/
 void printPoly(PNODE poly)
 {
 	//在此处填写代码，能实现按格式输出多项式的功能，输出格式样例见说明 
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
