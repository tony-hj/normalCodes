/*
   本文件主要用于实现头文件中的函数 
*/
#include "seqlist.h "


/*
   函数名： createNullList
   功能： 创建一个顺序线性表
   参数：max 表示线性表最大能容纳的数据元素个数
   返回值：创建成功，则返回顺序线性表结构地址，若不成功，则返回NULL 
*/
PseqList createNullList(int max) 
{
	PseqList head = new struct seqList ;
	
	if(head == NULL){
		cout<<"分配空间不成功";
		return NULL;
	}
	//此处待优化
	 
	head->curNum = 0;
	head->MAX = max ;
	head->element = new DataType[max] ;
		if(head->element == NULL){
		cout<<"分配空间不成功";
		return NULL;
	}
	//此处待优化
	
	return head ; 
	 
}
 
 /*
   函数名： insertTail
   功能： 在顺序线性表表尾插入数据元素，值为dataX的值 
   参数：PseqList slist:线性表结构地址， DataType dataX：待插入的数据元素 
   返回值：无 
*/
 void insertTail(PseqList slist, DataType dataX)
 {
    //此处待优化
	
	slist->element[slist->curNum] = dataX ;
	slist->curNum++ ;
      
 } 
 
  /*
   函数名： printList
   功能： 输出线性表所有数据元素的值 
   参数：PseqList slist:线性表结构地址 
   返回值：无 
*/
 void printList(PseqList slist) 
 {
 	cout<<"线性表中的数据元素如下\n";
 	for(int i = 0 ;i < slist->curNum ;i++)
 	   cout<<slist->element[i]<<"  " ;
 	
 	cout<<endl; //最后输出一个换行 
 } 
 
 
 bool isFullList(PseqList sList){
 	if(sList->MAX == sList->curNum)
 		return true;
 	else
 		return false;
 }
 
 
  DataType locate(PseqList sList,int pos){
  	pos--; 
  	if(pos >= 0 && pos < sList->curNum )
  		return sList->element[pos];
  	else
  		exit(0);
  }

 void delect(PseqList sList,int pos){
 	for(int i=pos;i < sList->curNum;i++){
 		sList->element[i-1] = sList->element[i];
	 }
	 sList->curNum--;
 }
 
 void copyList(PseqList src,PseqList dest)
 {
 	for(int i=0;i<src->curNum;i++)
 	{
 		dest->element[i]=src->element[i];
 		dest->curNum =src->curNum;
	 }
 }

