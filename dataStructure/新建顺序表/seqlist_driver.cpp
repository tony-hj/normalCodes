/*
   主程序，用于测试各操作是否成功 
*/
#include "seqlist.cpp"

#include "linkList.h"

int main()
{
	
	linkList head = new linkList;
	head = createLinkList();
	insetTail(head,12);
	insetTail(head,32);
	
	printLlist(head);
	
//	PseqList head = createNullList(20); //测试创建函数 
//	for(int i = 1; i < 23 ;i++){
//		if(isFullList(head ) )	{
//			cout<<"链表已满不能继续插入!";
//			break;
//		}
//	  insertTail(head , i); //测试尾插函-
//
//	  
//	}
//
//	printList(head);  //测试输出函数 
//		  int pos,dataX;
//	  cout<<"输入你要查找的第n个值：";
//	  cin>>pos;
//	  if(pos<0 || pos>20){
//	  	cout<<"请输入正确的数字！";
//	  	exit(0);
//	  }
//	  dataX = locate(head,pos);
//	  cout<<"第n个值为:"<<dataX<<endl;
//	  cout<<"输入你要删除的数的位数：";
//	  cin>>pos;
//	  delect(head,pos);
//	  printList(head);


//	PseqList A = createNullList(5);
////	PseqList B = createNullList(5);	
//	A->element = {1,3,5,7,9};
//	A->curNum = 5 ;
//    printList(A);
	


}
