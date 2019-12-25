/*
   本文件主要用作函数声明和数据类型定义 
*/
#ifndef _SEQLIST_H
#define  _SEQLIST_H //防止重复包含文件

#include <iostream>//为了使用cin cout  new 等 
#include <string>
using namespace std ;//为了使用cin cout  new 等 

typedef int DataType ; //给int定义一个别名，DataType    更改程序类型时方便 
 
struct seqList
{
	int MAX;//线性表最多能存放的数据元素个数 
	int curNum ;//线性表当前有多少数据元素 
	DataType *element ;// 存放数据元素的连续空间的首地址 
 } ;//顺序线性表结构 

typedef struct  seqList *PseqList ;//   为struct  seqList * 定义别名，主要是为了写程序方便的

 PseqList createNullList(int max) ; // 创建线性表 
 
 void insertTail(PseqList , DataType ) ;// 向表尾插入数据元素
 
 void printList(PseqList ) ;//输出线性表数据元素 

 bool isFullList(PseqList );
 
 DataType locate(PseqList sList,int pos);

 void delect(PseqList sList,int pos);
 
  void copyList(seqList src,seqList dest);
#endif
