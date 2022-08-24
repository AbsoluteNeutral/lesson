#include <stdio.h>

void Question1();
void Question2();
void Question3();
void Question4();
void Question5();
void Question6();

int main(){
  /**/
   Question5();
  return 0;
}

/* what is the result? */
void Question1()
{
  int i = 11;
  int j = 2;
  printf("%d\n", i=i+1);    /**/
  printf("%d %d\n", i, j);  /**/
  printf("%d\n", i---++j);  /**/
  printf("%d %d\n", i, j);  /**/
}

void Question2()
{
  int i = 99;
  int j = 1;
  printf("%d\n", ++i-j--);
  printf("%d %d\n", i, j);
  printf("%d\n", i<=j<1<=0);
}

void Question3()
{
  int i = 0;
  int j = -1;
  printf("%d\n", ++i && j++ || ++j);
  printf("%d %d\n", i, j);
  printf("%d\n", i>j);
}

void Question4()
{
  int i = 12;
  int j = 34;
  printf("%d\n", ++i || j++ > ++j);
  printf("%d %d\n", i, j);
  printf("%d\n", i>j);
}

void Question5()
{
  int num, i = 80;
  num = i < 10 ? i > 100 ? 0 : 1 : 2; 
  printf("%d\n", num);
}

void Question6()
{
  /* rewrite question 5 in if else format */
  
}


void Question7()
{
  int i = 10, j = 5, k = 3;
  if(b<a<=4 && (a=b))
    if(a%5)
      printf("A\n");
      else if(b%c<c<1)
        prinf("B\n");
        else
          prinf("C\n");
          else
            prinf("D\n");
}
