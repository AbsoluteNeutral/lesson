/* Possible Answer(s)*/
#include <stdio.h>

int main(){
  float dis = 0.0f;
  float a = 0.0f, b = 0.0f, c = 0.0f;
  
  printf("Enter coeffeicent of x^2:");
  scanf("%f", &a);
  printf("Enter coeffeicent of x:");
  scanf("%f", &b);
  printf("Enter coeffeicent of c:");
  scanf("%f", &c);

  dis = b*b-4*a*c;
  
  printf("\nThe quadratic equation is: %.3fx^2%s%.3fx%s%.3f", a, b < 0.0f ? "" : "+", b, c < 0.0f ? "" : "+", c);
  if (dis < 0)
    printf(" has no real root.");
  else if(dis == 0)
    printf(" has two real roots.");
  else
    printf(" has two distinct roots.");

  return 0;
}