/*
   ���������ڲ��Ը������Ƿ�ɹ� 
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
	
//	PseqList head = createNullList(20); //���Դ������� 
//	for(int i = 1; i < 23 ;i++){
//		if(isFullList(head ) )	{
//			cout<<"�����������ܼ�������!";
//			break;
//		}
//	  insertTail(head , i); //����β�庯-
//
//	  
//	}
//
//	printList(head);  //����������� 
//		  int pos,dataX;
//	  cout<<"������Ҫ���ҵĵ�n��ֵ��";
//	  cin>>pos;
//	  if(pos<0 || pos>20){
//	  	cout<<"��������ȷ�����֣�";
//	  	exit(0);
//	  }
//	  dataX = locate(head,pos);
//	  cout<<"��n��ֵΪ:"<<dataX<<endl;
//	  cout<<"������Ҫɾ��������λ����";
//	  cin>>pos;
//	  delect(head,pos);
//	  printList(head);


//	PseqList A = createNullList(5);
////	PseqList B = createNullList(5);	
//	A->element = {1,3,5,7,9};
//	A->curNum = 5 ;
//    printList(A);
	


}
