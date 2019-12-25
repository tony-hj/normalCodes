#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;

#define  n  10

void print(int a[])
{//����������� 
  for(int i = 0;i<n ;i++)
    cout<<a[i]<<" ";
  cout<<endl;		
}

void swap(int  *a ,int  *b)
{ //���������� 
	int  c = *a ;
	*a = *b  ;
	*b = c ;
}

void BubbleSort(int a[])
{//ð������ 
int temp,flag;
  for(int i = 0;i<n ;i++){
  	flag = 1;
    for(int j = n-1;j>=0;j--)
	 if(a[j] > a[j+1])
	  {
	  	temp = a[j+1];
	  	a[j+1] = a[j];
	  	a[j] = temp;
	  	flag = 0;
		  }	
	if(flag)
		break;
	}	
//	print(a,n);	
}

void SelectSort(int a[])
{//ֱ��ѡ������ 
	int k,temp;
	    for (int i=0; i<n-1; i++)   {
			k = i ;
        for(int j = i+1 ; j<n;j++ )
		{
          if(a[k] >a[j]) k = j;//�ҳ�i�����Сֵ 
		}
        if(k!=i)
		{
        temp = a[k];
	  	a[k] = a[i];
	  	a[i] = temp;
		}
    }
	//print(a,n);
}

void InsertSort(int a[])
{
//ֱ�Ӳ�������
	int temp,j;
	for (int i=0; i<n-1; i++)   {
		temp = a[i+1];
		for(j=i ; j>=0 ;j--)
		  {
            if(a[j] >temp) a[j+1] = a[j];
			else break;
		  }
		  a[j+1] = temp;
    }	
	//print(a,n);
 } 
 
 void BiInsertSort(int a[])
{
//���ֲ�������
int i;
    for( i=0; i<n; i++) {
        int low=0;
        int high=i-1;
        int temp=a[i];
        int mid=0;
        while(low<=high) {
            mid=(low+high)/2;
            if(a[mid]<temp) {
                low=mid+1;
            } else {
                high=mid-1;
            }
        }
        int j;
        for(j=i-1; j>=low; j--) {
            a[j+1]=a[j];
        }
        if(i!=low)
            a[low]=temp;
    }

	//print(a,n);
 }
 
 
 void ShellSort(int a[])
{
//ϣ������
	int j;
	
	for(int gap = n /2;gap>0;gap /= 2){
		for(int i=gap;i<n;i++){
			int  tmp = a[i];
			for(j=i;j>=gap && (tmp < a[j-gap]);j -= gap)
				a[j] = a[j-gap];
			a[j] = tmp; 
		}
	} 
	
//	print(a,n);
	
 } 
 
// void MergeSort(SortObject *obj)
//{
////�鲢����
//	
// } 
// 
// void QuickSort(SortObject *obj)
//{
////������
//
// }
 
 int main()
 {
 	
 	//�˴����������㷨 
 	int obj[n];
 	srand(time(NULL)); //����������������� 
 	for(int i=0;i<n;i++)
 	  obj[i] = rand(); //��������ؼ��� 
// 	print(obj,NN);  //�������ǰ�Ĺؼ��� 
 	long t1,t2;
 	t1 = GetTickCount();
 	BubbleSort(obj);//ð�� 
	t2 = GetTickCount();  
 	cout<<"ð�� ��Ҫʱ�䣺"<<t2-t1<<endl;
 	
// 	t1 = GetTickCount();
//		SelectSort(obj);//ѡ�� 
//	t2 = GetTickCount();  
// 	cout<<"ѡ�� ��Ҫʱ�䣺"<<t2-t1<<endl;
 
// 	t1 = GetTickCount();
//		InsertSort(obj);//ֱ�Ӳ��� 
//	t2 = GetTickCount();  
// 	cout<<"ֱ�Ӳ�����Ҫʱ�䣺"<<t2-t1<<endl;

// 	t1 = GetTickCount();
//		BiInsertSort(obj);//���ֲ���
//	t2 = GetTickCount();  
// 	cout<<"���ֲ�����Ҫʱ�䣺"<<t2-t1<<endl;
 	
// 	t1 = GetTickCount();
//		ShellSort(obj);//ϣ�� 
//	t2 = GetTickCount();  
// 	cout<<"ϣ����Ҫʱ�䣺"<<t2-t1<<endl;

//	int k[5][2] = {{639,7821},{1046,3303},{3680,4921},{77,8942},{666,6666}};
//	int temp;
//	for(int i=0;i<5;i++){
//		temp = obj[k[i][1]];
//		obj[k[i][1]] = obj[k[i][0]];
//		obj[k[i][0]] = temp;
//	}

// 	t1 = GetTickCount();
//		InsertSort(obj);//ֱ�Ӳ��� 
//	t2 = GetTickCount();  
// 	cout<<"ֱ�Ӳ�����Ҫʱ�䣺"<<t2-t1<<endl;

// 	t1 = GetTickCount();
//		BiInsertSort(obj);//���ֲ���
//	t2 = GetTickCount();  
// 	cout<<"���ֲ�����Ҫʱ�䣺"<<t2-t1<<endl;
	

 	print(obj);  //��������Ĺؼ��� 
 }
