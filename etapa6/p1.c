//Eduarda Trindade 274709

#include <stdio.h>

int a = 111;
int b = 88;
int c = 73;
int retorno = 99;

int incn (int x, int n)
{
  return x + n;
};

int main()
{
    
    if(b==c)
        fprintf(stderr,"%d\n",a);
    else 
        printf("%d\n",a);

    c = incn(a,b);

    return retorno;
}