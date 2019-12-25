#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
int MAXINT = 300;
struct HtNode{
	int ww;
	int parent,lchild,rchild;
}; 


struct HtTree{
	int m;
	int root;
	struct HtNode *ht;
};
typedef struct HtTree *PHtTree;

PHtTree huffman(int m,int *w){
	PHtTree pht;
	int i,j,x1,x2,m1,m2;
	pht = new struct HtTree;
	if(pht == NULL){
		cout<<"分配空间失败"<<endl;
		return pht;
	}
	
//	pht->ht = (struct HtNode)malloc(sizeof(struct HtNode) * (2*m-1));
//	pht->ht = new (struct HtNode) * ( 2*m-1 ); 
		pht->ht = new struct HtNode;
	if(pht->ht == NULL){
		cout<<"分配空间失败"<<endl;
		return pht;
	}
	//为外部节点赋值 
	for(i=0;i<2*m-1;i++){
		pht->ht[i].lchild = -1;
		pht->ht[i].rchild = -1;
		pht->ht[i].parent = -1;
		if(i<m)
			pht->ht[i].ww = w[i];
		else
			pht->ht[i].ww = -1;
	}
	
	for(i=0;i<m-1;i++){
		m1 = MAXINT;
		m2 = MAXINT;
		x1 = -1;
		x2 = -1;
		for(j = 0;j<m + i;j++){
			if(pht->ht[j].ww < m1 && pht->ht[j].parent == -1){
				m2 = m1;
				x2 = x1;
				m1 = pht->ht[j].ww;
				x1 = j;
			}
			else if(pht->ht[j].ww < m2 && pht->ht[j].parent == -1){
				m2 = pht->ht[j].ww;
				x2 = j;
			}
		}
		pht->ht[x1].parent = m + i;
		pht->ht[x2].parent = m + i;
		pht->ht[m+i].ww = m1 + m2;
		pht->ht[m+i].lchild = x1;
		pht->ht[m+i].rchild = x2;
		
	}
	pht->root = 2*m-2;
	return pht;
}


int main(){
	int w[] = {2,3,5,7,11,13,17,19,23,29,31,37,41};
	
	PHtTree pht = huffman(13,w);
	for(int i=0;i<25;i++){
		cout<<pht->ht[i].ww<<" "<<pht->ht[i].parent<<" "<<pht->ht[i].lchild<<" "<<pht->ht[i].rchild<<endl;
	} 
}
 
