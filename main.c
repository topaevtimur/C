#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv) {
	int n;
	scanf("%d", &n);
	int **a;
	a = malloc(sizeof(int) * n);
	for(int i = 0; i < n; i++)
		a[i] = malloc(sizeof(int) * n);  	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			a[i][j] = (j + 1) * (i + 1);
	int x1,y1,x2,y2;
	while(scanf("%d", &x1)) {
		if(x1 == 0) {
			for(int i = 0; i < n; i++)
				free(a[i]);
			free(a);
			return 0;		
		}
		scanf("%d%d%d", &y1,&x2,&y2);
		for(int i = x1-1;i < x2; i++) {
			for(int j = y1-1;j < y2; j++)
				printf("%d ", a[i][j]);
			printf("\n");
		}
	}                           	
	
}
