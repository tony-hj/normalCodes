#ifndef _SEQLIST_H
#define  _SEQLIST_H
#include "linkList.cpp"


struct node{
	DataType info;
	struct node *link;
};

typedef struct *node linkList;

linkList createNUllList();

void insetTail(linkList llist,DataType x );

void printLlist(linkList llist);

#endif
