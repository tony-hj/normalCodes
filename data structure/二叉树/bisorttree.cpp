#include <iostream>
using namespace std;

//��������������һ�ÿ�����ʼ���� 
typedef int DataType;
struct node
{
   DataType info ;
   struct node *lchild ,*rchild ;	
};

typedef struct node *sortTree;

//����һ����㣬ֵΪx 
sortTree createTree(DataType x)
{
	sortTree temp = new struct node;
	temp->info = x ;
	temp->lchild = NULL;
	temp->rchild = NULL;
	return temp;
}

//�����������Ĵ�����һ�����ϲ�����Ĺ��� 
sortTree insert(DataType x ,sortTree T)
{
  //���TΪ�գ��򴴽���� 
  if(T == NULL)  T = createTree(x);
  //�������ֵС��T��ֵ������õݹ麯�������������� 
  else   if (x < T->info)  T->lchild =insert (x,T->lchild);
  //�������ֵ����T��ֵ������õݹ麯�������������� 
  else   if (x > T->info)  T->rchild = insert(x,T->rchild);
  return T;
} 

//����������������������Եõ�һ����С�������е�˳�� 
void inOrder(sortTree T)
{
	if(T==NULL) return ;
	inOrder(T->lchild);
	cout<<T->info<<"  " ;
	inOrder(T->rchild);
}

void preOrder(sortTree T)
{
	if(T==NULL) return ;
	
	cout<<T->info<<"  " ;
	preOrder(T->lchild);
	preOrder(T->rchild);
}

//��ѯ
int find(sortTree T,DataType x){
	
	if(T == NULL) return 0;
	if(T->info == x) return 1;
	
	else if(x < T->info) find(T->lchild,x);
	else find(T->rchild,x);
} 

DataType findMin(sortTree T) {
	if(T->lchild == NULL) return T->info;
	findMin(T->lchild);
}

//���������� 
int main()
{
	int a[] = {12,23,1,45,6,78,9};//�����������������ֵ���� 
	sortTree T = NULL;//��ʼ����Ϊ�� 
	for(int i = 0; i < 7;i++)
		T = insert(a[i],T); //ѭ��������ֵ���õ����������� 
	inOrder(T); //��֤�����������Ƿ���ȷ 
	cout<<endl;
	preOrder(T);
	cout<<endl;
//	DataType min = findMin(T);
//	cout<<min;
	int x;
	cout<<"����Ҫ��ѯ������";
	cin>>x;
	if(find(T,x))
		cout<<"������ڵ�";
	else
		cout<<"û���ҵ����ֵ";
}

