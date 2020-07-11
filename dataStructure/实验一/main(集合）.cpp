#include "linkset.h"

int main(void)
{
	int count;
	cin>>count;
	SET setA = InitSet(count);
	cin>>count;
	SET setB = InitSet(count);

	cout<<"并集：";
    printSet(setUnion(setA,setB));
    cout<<"\n交集：";
	printSet(setIntersect(setA,setB));
	cout<<"\n差集：";
	printSet(setExcept(setA,setB));
	
}
