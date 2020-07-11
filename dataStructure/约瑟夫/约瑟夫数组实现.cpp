#include<iostream>
using namespace std;
struct list{
	
	int num;
	int *element;
};
typedef struct list *nlist;
typedef struct list List;

nlist createList(nlist alist,int totalNum);
void print(nlist alist);
void Joseph(nlist alist,int n);

int main(){
	nlist alist = new List;
	int totalNum;
	cout<<"请输入总人数：";
	cin>>totalNum;//总人数 
	cout<<endl;
	alist = createList(alist,totalNum);
	print(alist);
//	int n;//记录报数杀死的数 
//	cout<<"请输入循环的数：";
//	cin>>n;
//	cout<<n;
int n = 3;
	Joseph(alist,n);

	
}

nlist createList(nlist alist,int totalNum){
	alist->num = totalNum;
	for(int i=1;i<=totalNum;i++){
		alist->element[i-1] = i;
	}
	return alist;
}

void print(nlist alist){
	cout<<"初始化后的数组为："; 
	for(int i=0;i<alist->num;i++){
		cout<<alist->element[i]<<" ";
	}
	cout<<endl;
}

void Joseph(nlist alist,int n){
	cout<<"dsagggg"; 
	int flag = alist->num;
	int i = 0;
	while(flag>=1){
		i = i + n-1;
		if(i > alist->num-1){
			i = i - alist->num;
		}
		while(1){
			if(alist->element[i]){
				cout<<"死！"<<alist->element[i]<<endl;
				alist->element[i] = -1;
				flag--;
				i++;
				break;
			}
			else{
				i++;
				if(i > alist->num-1)	i = i - alist->num;
			}
		}
		
	}
}

