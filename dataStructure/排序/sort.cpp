#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
using namespace std;

#define  n  10

void print(int a[])
{//输出数据序列 
  for(int i = 0;i<n ;i++)
    cout<<a[i]<<" ";
  cout<<endl;		
}

void swap(int  *a ,int  *b)
{ //交换两个数 
	int  c = *a ;
	*a = *b  ;
	*b = c ;
}

void BubbleSort(int a[])
{//冒泡排序 
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
{//直接选择排序 
	int k,temp;
	    for (int i=0; i<n-1; i++)   {
			k = i ;
        for(int j = i+1 ; j<n;j++ )
		{
          if(a[k] >a[j]) k = j;//找出i后的最小值 
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
//直接插入排序
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
//二分插入排序
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
//希尔排序
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
////归并排序
//	
// } 
// 
// void QuickSort(SortObject *obj)
//{
////快排序
//
// }
 
 int main()
 {
 	
 	//此处测试排序算法 
 	int obj[n];
 	srand(time(NULL)); //用于生成随机数种子 
 	for(int i=0;i<n;i++)
 	  obj[i] = rand(); //随机数给关键码 
// 	print(obj,NN);  //输出排序前的关键码 
 	long t1,t2;
 	t1 = GetTickCount();
 	BubbleSort(obj);//冒泡 
	t2 = GetTickCount();  
 	cout<<"冒泡 需要时间："<<t2-t1<<endl;
 	
// 	t1 = GetTickCount();
//		SelectSort(obj);//选择 
//	t2 = GetTickCount();  
// 	cout<<"选择 需要时间："<<t2-t1<<endl;
 
// 	t1 = GetTickCount();
//		InsertSort(obj);//直接插入 
//	t2 = GetTickCount();  
// 	cout<<"直接插入需要时间："<<t2-t1<<endl;

// 	t1 = GetTickCount();
//		BiInsertSort(obj);//二分插入
//	t2 = GetTickCount();  
// 	cout<<"二分插入需要时间："<<t2-t1<<endl;
 	
// 	t1 = GetTickCount();
//		ShellSort(obj);//希尔 
//	t2 = GetTickCount();  
// 	cout<<"希尔需要时间："<<t2-t1<<endl;

//	int k[5][2] = {{639,7821},{1046,3303},{3680,4921},{77,8942},{666,6666}};
//	int temp;
//	for(int i=0;i<5;i++){
//		temp = obj[k[i][1]];
//		obj[k[i][1]] = obj[k[i][0]];
//		obj[k[i][0]] = temp;
//	}

// 	t1 = GetTickCount();
//		InsertSort(obj);//直接插入 
//	t2 = GetTickCount();  
// 	cout<<"直接插入需要时间："<<t2-t1<<endl;

// 	t1 = GetTickCount();
//		BiInsertSort(obj);//二分插入
//	t2 = GetTickCount();  
// 	cout<<"二分插入需要时间："<<t2-t1<<endl;
	

 	print(obj);  //输出排序后的关键码 
 }
