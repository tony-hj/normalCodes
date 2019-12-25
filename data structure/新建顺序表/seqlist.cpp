/*
   ���ļ���Ҫ����ʵ��ͷ�ļ��еĺ��� 
*/
#include "seqlist.h "


/*
   �������� createNullList
   ���ܣ� ����һ��˳�����Ա�
   ������max ��ʾ���Ա���������ɵ�����Ԫ�ظ���
   ����ֵ�������ɹ����򷵻�˳�����Ա�ṹ��ַ�������ɹ����򷵻�NULL 
*/
PseqList createNullList(int max) 
{
	PseqList head = new struct seqList ;
	
	if(head == NULL){
		cout<<"����ռ䲻�ɹ�";
		return NULL;
	}
	//�˴����Ż�
	 
	head->curNum = 0;
	head->MAX = max ;
	head->element = new DataType[max] ;
		if(head->element == NULL){
		cout<<"����ռ䲻�ɹ�";
		return NULL;
	}
	//�˴����Ż�
	
	return head ; 
	 
}
 
 /*
   �������� insertTail
   ���ܣ� ��˳�����Ա��β��������Ԫ�أ�ֵΪdataX��ֵ 
   ������PseqList slist:���Ա�ṹ��ַ�� DataType dataX�������������Ԫ�� 
   ����ֵ���� 
*/
 void insertTail(PseqList slist, DataType dataX)
 {
    //�˴����Ż�
	
	slist->element[slist->curNum] = dataX ;
	slist->curNum++ ;
      
 } 
 
  /*
   �������� printList
   ���ܣ� ������Ա���������Ԫ�ص�ֵ 
   ������PseqList slist:���Ա�ṹ��ַ 
   ����ֵ���� 
*/
 void printList(PseqList slist) 
 {
 	cout<<"���Ա��е�����Ԫ������\n";
 	for(int i = 0 ;i < slist->curNum ;i++)
 	   cout<<slist->element[i]<<"  " ;
 	
 	cout<<endl; //������һ������ 
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

