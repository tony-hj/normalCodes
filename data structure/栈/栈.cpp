#include<iostream>
using namespace std;
typedef int DataType;
struct SeqStack{
	int MAXNUM;
	int top;
	DataType *ele;
};
typedef struct SeqStack *PSeqStack;

PSeqStack createNullStack(int max){
	PSeqStack tmp = new struct SeqStack;
	tmp->MAXNUM = max;
	tmp->top = 0;
	tmp->ele = new DataType[max]; 
}

int isEmptyStack(PSeqStack s){
	if(s->top == 0){
		return 1;
	}
	else
		return 0;
}

int isFullStack(PSeqStack s){
	if(s->top == s->MAXNUM){
		return 1;
	}
	else
		return 0;
}
//²åÈëÕ»¶¥ÔªËØ 
void push(PSeqStack s,DataType x){
	if(isFullStack(s) == 0){
	s->ele[s->top] = x;
	s->top++;
	}

}
//É¾³ýÕ»¶¥ÔªËØ 
void pop(PSeqStack s){
	if(isEmptyStack(s) == 0){
	s->top--;	
	}

}
//¶ÁÈ¡Õ»¶¥ÔªËØ 
DataType top(PSeqStack s){
	if(isEmptyStack(s) == 0)
	return s->ele[s->top-1];
}

void convert(int x,int n){
	PSeqStack stack = createNullStack(50);
	while(x != 0){
		push(stack,x%n);
		x = x / n;
	}
	while(isEmptyStack(stack) == 0){
		cout<<top(stack);
		pop(stack);
	}
}

int main(){
	PSeqStack stack = createNullStack(50);
	convert(10,8);

}
