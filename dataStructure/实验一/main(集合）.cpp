#include "linkset.h"

int main(void)
{
	int count;
	cin>>count;
	SET setA = InitSet(count);
	cin>>count;
	SET setB = InitSet(count);

	cout<<"������";
    printSet(setUnion(setA,setB));
    cout<<"\n������";
	printSet(setIntersect(setA,setB));
	cout<<"\n���";
	printSet(setExcept(setA,setB));
	
}
