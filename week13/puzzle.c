#include <stdio.h>
#include <stdbool.h>
void inputpuzzle()
{
    int a[10][10];
    int n=3,m=3;

	printf("Nha cac gia tri cho puzzle :");
	for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
	
	int checked = true;
	int sum = 0;
	for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            sum += a[i][j];
			if(a[i][j] > 8) {
				checked = false;
				break;
            }
        }
	    if(  checked =false){
		    printf("nha sai du lieu vui long  lai");
		    return inputpuzzle();
	    }
    }
    printf("trang thai ban dau:\n");
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    inputpuzzle();
    return 0;
}

