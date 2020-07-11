#ifndef FileName_H_
#define FileName_H_  
#include"stdio.h"
#include"stdlib.h"

typedef struct goods{
	int ExpressNumber;//��ݵ��� 
	char name[10];//�ռ������� 
	long long phoneNumber;//�ռ��˵绰 
	int size;//����ߴ磬0��1��2�ֱ����С���У��� 
	struct goods* next;
}Goods;


//���Ĳ������� �����ļ��ж�ȡ�������������������������⴦�� 
typedef struct inList{
	Goods * iList;
}inList;

//����ļ�¼�������ѳ���Ļ�����м�¼�浵��������д����һ���ѳ��������ļ��� 
typedef struct {
	Goods * iList;
}outList;

typedef struct shelf{
	bool isStore = false;//�жϴ˴��Ƿ��л��� 
	Goods * good;//ָ��ָ����� 
}Shelf;



Shelf* bigShelf[3][3];
Shelf* midShelf[4][4];
Shelf* smallShell[5][5];





Goods *FilePutaway();//��⺯�������ļ��ж�ȡ��
void putaway(); //��⺯�������ԴӼ������ֶ���⣩
void cargoTrace();//��ѯ�������û�����ͨ�������ݵ��ţ��ջ����������ջ��˵绰�Դ˻�����в���
Goods* OcargoTrace(int number);
void delieveryCargo(outList *out);//ͨ������ĵ��ŶԻ�����г��⴦�� 
void show();
void outFile(outList *out); 
#endif 
