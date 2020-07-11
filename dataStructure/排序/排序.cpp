#include<iostream>

using namespace std;

int  main(){
	
	int a[] = {6,1, 3, 5,3,9,13 };
	int i, k ,j,temp;
	int n = 7;
	
//	//选择排序 
//    for (i=0; i<n-1; i++)   {
//		k = i ;
//        for(int j = i+1 ; j<n;j++ )
//		{
//          if(a[k] > a[j]) k = j;//找出i后的最小值 
//		}
//        if(k!=i)
//		{
//           temp = a[i];
//		   a[i] = a[k] ;
//		   a[k] = temp;
//		}
//    }
    
      
//    //插入排序 
//for (i=0; i<n-1; i++)   {
//		temp = a[i+1];
//		for( j=i ; j>=0 ;j--)
//		  {
//            if(a[j] >temp) a[j+1] = a[j];
//			else break;
//		  }
//		  a[j+1] = temp;
//    }


//	//冒泡排序
//	for(i=0;i<n;i++){
//		for(j=0;j<n-i-1;j++){
//			if(a[j] > a[j+1]){
//				temp = a[j+1];
//				a[j+1] = a[j];
//				a[j] = temp;
//			}
//		}
//	} 

//	int a[] = {6,1, 3, 5,3,9,13 };
//	int n = 7;
//	int left,right,mid,i,temp;
//	
//	
//	for( i=n-1;i>=0;i--){
//	left = 0;
//	right = i;
//	while(right > left){
//		mid = (left + right)/2;
//		if(a[mid] == a[i]) break;
//		else if(a[mid] > a[i]){
//			right = mid;
//		}else if(a[mid] < a[i]){
//			left = mid;
//		}
//		temp = a[i];
//		for(int s=n-1;s>=mid;s--){
//			a[s] = a[s-1];
//		}
//		a[mid] = temp;
//	}
//
//}


    for(i=0;i<7;i++){
    	cout<<a[i]<<endl;
	}
    
}

