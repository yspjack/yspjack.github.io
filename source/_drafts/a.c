
#include <stdio.h>
#include <string.h>

int main()
{
	int L,ans=0;
	scanf("%d",&L);
	if(L<=4)
		ans=L+1;
	else if(L<=9)
		ans=5;
	else if(L<=14)
		ans=L+1-5;
	else if(L<=19)
		ans=10;
	else
		ans=L+1-5-5;
	printf("%d\n",ans);
	return 0;
}