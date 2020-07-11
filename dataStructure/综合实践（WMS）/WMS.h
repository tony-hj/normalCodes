#ifndef FileName_H_
#define FileName_H_  
#include"stdio.h"
#include"stdlib.h"

typedef struct goods{
	int ExpressNumber;//快递单号 
	char name[10];//收件人姓名 
	long long phoneNumber;//收件人电话 
	int size;//货物尺寸，0，1，2分别代表小，中，大 
	struct goods* next;
}Goods;


//入库的操作链表 （从文件中读取货物，将其存入链表，并对其进行入库处理） 
typedef struct inList{
	Goods * iList;
}inList;

//出库的记录链表（对已出库的货物进行记录存档，并将其写入另一个已出库货物的文件） 
typedef struct {
	Goods * iList;
}outList;

typedef struct shelf{
	bool isStore = false;//判断此处是否有货物 
	Goods * good;//指针指向货物 
}Shelf;



Shelf* bigShelf[3][3];
Shelf* midShelf[4][4];
Shelf* smallShell[5][5];





Goods *FilePutaway();//入库函数（从文件中读取）
void putaway(); //入库函数（用以从键盘上手动入库）
void cargoTrace();//查询函数，用户可以通过输入快递单号，收货人姓名，收货人电话对此货物进行查找
Goods* OcargoTrace(int number);
void delieveryCargo(outList *out);//通过输入的单号对货物进行出库处理 
void show();
void outFile(outList *out); 
#endif 
