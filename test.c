#include<stdio.h>
void b(){
	int *p = NULL;
      *p = 0;
      return 0;

}
void a(){
	b();
}
int main()
{
	a();
      return 0;
}
