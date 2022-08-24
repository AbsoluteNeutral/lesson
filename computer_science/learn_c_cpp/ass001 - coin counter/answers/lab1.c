/* Possible Answer(s)*/
#include <stdio.h>
int main(){
	int scanfCount = 0;
	int dollars = 0, cents = 0;
	int cent50 = 0, cent20 = 0, cent10 = 0, cent5 = 0;
	
	printf("Please Enter a value:");
	
	scanfCount = scanf("%d.%2d", &dollars, &cents);
	printf("\n");
	if(scanfCount <= 0)
	{
		printf("Wrong input");
	}
	else 
	{
		printf("Values Entered:$%d.%2.2d\n", dollars, cents);
		
		cent50 = cents / 50;
		cents -= cent50 * 50;
		
		cent20 = cents / 20;
		cents -= cent20 * 20;
		
		cent10 = cents / 10;
		cents -= cent10 * 10;
		
		cent5 = cents / 5;
		cents -= cent5 * 5;
		
		printf("There %s %d dollar %s.\n", dollars > 1 ? "are":"is", dollars, dollars > 1 ? "coins":"coin");
		printf("There %s %d fifty-cent %s.\n", cent50 > 1 ? "are":"is", cent50, cent50 > 1 ? "coins":"coin");
		printf("There %s %d twenty-cent %s.\n", cent20 > 1 ? "are":"is", cent20, cent20 > 1 ? "coins":"coin");
		printf("There %s %d ten-cent %s.\n", cent10 > 1 ? "are":"is", cent10, cent10 > 1 ? "coins":"coin");
		printf("There %s %d five-cent %s.\n", cent5 > 1 ? "are":"is", cent5, cent5 > 1 ? "coins":"coin");
		printf("There %s %d one-cent %s.\n", cents > 1 ? "are":"is", cents, cents > 1 ? "coins":"coin");
	}
	
	return 0;
}
