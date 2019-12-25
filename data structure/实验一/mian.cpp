#include "linklist.h"

int main(void)
{
	PNODE  polyAddLeft, polyAddRight ,polyAddResult ;
	
	polyAddLeft = createPoly();
	
 	
 	polyAddRight = createPoly();
 	
 	polyAddResult = addPoly(polyAddLeft,polyAddRight);
 	printPoly(polyAddResult);
	
}
