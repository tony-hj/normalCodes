#include <iostream>
using namespace std;
 
typedef char DataType;
 
//��������㶨�� 
struct node
{
   DataType data; //��Ž������ 
   struct node *lchild, *rchild ; //���Һ���ָ�� 
};
typedef struct  node  BiTree;
typedef struct  node  *ptree;

//������ֱ��ʹ�ã����ܣ�����������
void print(DataType d)
 {
   cout<<d<<" ";
 }

/*
��������createBiTree
�������ܣ������������������ض������ĸ����ָ�� 
�������� 
����ֵ���������ĸ����ָ�� 
*/ 
BiTree *createBiTree() {
//���ڴ˴���д���룬��ɴ��������������ض����������ָ��Ĺ���    
/*-------begin--------*/          
    char x;
	cin>>x;
	ptree root = new BiTree;
	root->data = x;
	if(x == '#') return root;

	root->lchild = createBiTree();
	root->rchild = createBiTree();
    
	return root;
/*-------end--------*/    
}

/*
��������preOrder
�������ܣ��ȸ����������� 
�����������������ָ�� 
����ֵ���� 
*/ 
void preOrder(BiTree *T) 
{
//���ڴ˴���д���룬����ȸ���������������    
/*-------begin--------*/
    if(T->data == '#') return;
	print(T->data);
	preOrder(T->lchild);
	preOrder(T->rchild);
    
/*-------end--------*/  
}
 
/*
�������� inOrder
�������ܣ��и����������� 
�����������������ָ�� 
����ֵ���� 
*/  
void inOrder(BiTree *T) 
{
    //���ڴ˴���д���룬����и���������������    
/*-------begin--------*/
    if(T->data == '#')return;
	inOrder(T->lchild);
	print(T->data);
	inOrder(T->rchild);
    
/*-------end--------*/  
}

/*
��������postOrder
�������ܣ�������������� 
�����������������ָ�� 
����ֵ���� 
*/  
 void postOrder(BiTree *T)  
    {  
      //���ڴ˴���д���룬��ɺ����������������    
/*-------begin--------*/
    if(T->data == '#')return;
	postOrder(T->lchild);
	postOrder(T->rchild);
	print(T->data);
    
/*-------end--------*/  
    }  
 
//������������ 
int countLevel(BiTree *root){
	if(root->data == '#')return -1;
	else{
		int left,right;
		left = 1 + countLevel(root->lchild);
		right = 1 + countLevel(root->rchild);
		return left>right?left:right;
	}
}  

//�ı���������������� 
void changeLR(BiTree *root){
	if(root->data == '#') return;
	BiTree *Temp;
	Temp = root->lchild;
	root->lchild = root->rchild;
	root->rchild = Temp;
	
	if(root->lchild->data == '#')
		changeLR(root->rchild);
	if(root->rchild->data == '#')
		changeLR(root->lchild);
}

//�������������ڵ������Է���ֵ��һ����˶���������� 
int  extendedNodeNum(BiTree *T){
	static int num=0;
    if(T->data == '#') {
    	num++;
    	return -1;
	}
	extendedNodeNum(T->lchild);
	extendedNodeNum(T->rchild);
	return num;
}
//���������Ҷ�ӽڵ���� 
int leafNodeNum(BiTree *T){
	static int num=0;
	if(T->data == '#') return -1;
	
	if(T->lchild->data == '#' && T->rchild->data == '#')
	num++; 
	
	leafNodeNum(T->lchild);
	leafNodeNum(T->rchild);
	return num;
}


int main()
{  
    BiTree    *T;  
     T =  createBiTree(   ); //���ô������������ܣ��õ��������ĸ����ָ��
// 
//	 
//    preOrder(  T );//�����ȸ����������������ȸ�����˳�������������㹦�� 
//    cout<<endl; //����
//	inOrder(T);//�����и����������������и�����˳�������������㹦�� 
//	cout<<endl; 
//    postOrder(T);//���ú�����������������������˳�������������㹦�� 
//	cout<<endl;   
//   
//	int deep = countLevel(T);
//	cout<<"����������ȣ�"<<deep<<endl;
//	changeLR(T);
//	preOrder(  T );//�����ȸ����������������ȸ�����˳�������������㹦�� 
//    cout<<endl; //����
//	inOrder(T);//�����и����������������и�����˳�������������㹦�� 
//	cout<<endl; 
//    postOrder(T);//���ú�����������������������˳�������������㹦��    
//   
	int deep = countLevel(T);
	cout<<"����������ȣ�"<<deep<<endl;
//	int extendeNode = extendedNodeNum(T);
//	cout<<"������������ڵ������"<<extendeNode<<endl;
	int leafNode = leafNodeNum(T);
	cout<<"��������Ҷ�ӽڵ������"<<leafNode<<endl; 
	
	
   return 1;
}  
