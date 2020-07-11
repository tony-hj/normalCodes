#include<iostream> 

using namespace std;

typedef char DataType;
struct node{
	int MAXNUM;
	int curNum;
	DataType *info;
};

typedef struct SeqList *PSeqList;

PSeqList createSeqList(int m)
{
	PSeqlist temp = new struct SeqList;
	
	temp->curNum = 0;
	temp->maxNum = m;
	temp->info = new DataType[m];
	return temp;
}

PSeqList creatBiTree(PseqList tree){
	
	char ch;
	cout<<"ÇëÊäÈë¶þ²æÊ÷£º";
	cin>>ch;

	while(ch != '#'){
		tree->info[i] = ch;
		tree->curNum++;
		cin>>ch;
	}
		
}


int main(){
	PSeqList BiTree = createSeqList(100);
	BiTree = creatBiTree(BiTree);
}





