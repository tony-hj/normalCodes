/*
   ���ļ���Ҫ���������������������Ͷ��� 
*/
#ifndef _SEQLIST_H
#define  _SEQLIST_H //��ֹ�ظ������ļ�

#include <iostream>//Ϊ��ʹ��cin cout  new �� 
#include <string>
using namespace std ;//Ϊ��ʹ��cin cout  new �� 

typedef int DataType ; //��int����һ��������DataType    ���ĳ�������ʱ���� 
 
struct seqList
{
	int MAX;//���Ա�����ܴ�ŵ�����Ԫ�ظ��� 
	int curNum ;//���Ա�ǰ�ж�������Ԫ�� 
	DataType *element ;// �������Ԫ�ص������ռ���׵�ַ 
 } ;//˳�����Ա�ṹ 

typedef struct  seqList *PseqList ;//   Ϊstruct  seqList * �����������Ҫ��Ϊ��д���򷽱��

 PseqList createNullList(int max) ; // �������Ա� 
 
 void insertTail(PseqList , DataType ) ;// ���β��������Ԫ��
 
 void printList(PseqList ) ;//������Ա�����Ԫ�� 

 bool isFullList(PseqList );
 
 DataType locate(PseqList sList,int pos);

 void delect(PseqList sList,int pos);
 
  void copyList(seqList src,seqList dest);
#endif
