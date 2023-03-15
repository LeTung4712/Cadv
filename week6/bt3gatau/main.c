#include <stdio.h>
void tinh(int*n,int*m)
{
    printf("%d\n",n);
    
    printf("%d\n",*n);
    *n=2+*n;
    printf("%d\n",*n);
} 
int main()
{
   int n=2;
   int m=3;
   tinh(&n,&m);
   printf("%d\n",&n);
   printf("%d\n",&m);
   printf("%d\n",n);
   return 0;
}
