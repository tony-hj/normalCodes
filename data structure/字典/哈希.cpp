#include <iostream>
using namespace std;

typedef int keyType;
typedef int DataType;

typedef struct {
	keyType key;
	DataType value;
}DicElement;

 struct HashTable{
	int maxNum;
	int curNum;
	DicElement *element;
}; 

typedef struct HashTable * hash;
struct HashTable *InitHashTable(int m){
	struct HashTable * p = new struct HashTable;
	p->maxNum = m;
	p->curNum = 0;
	p->element = new DicElement[m];
	for(int i=0;i<m;i++){
		p->element[i].key = -1;
	}
	
	return p; 
}

int HashFun(keyType key){
	return key%10;
}

void InsertHash(keyType key,hash h){
	int add = HashFun(key);
	int i=1;
	L:if(h->element[add].key == -1){
		h->element[add].key = key;
		return ;
	}

	add = (add + i) % h->maxNum;
//	i++;
	goto L;
	
}

void print(hash h){
	for(int i=0;i<h->maxNum;i++){
		cout<<h->element[i].key<<" ";
	}
}
int main(){
	
	int m;
	cin>>m;
	hash Hash = InitHashTable(m);
	int array[] = {6,7,6,3};
	for(int i=0;i<4;i++){
		InsertHash(array[i],Hash);
	}
	print(Hash);
}
