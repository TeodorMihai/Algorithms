#include<stdio.h>

int main() {
	FILE *f = fopen("convertor.in","r");
	int l;
	fseek(f,0,2);
	l = ftell(f);
	rewind(f);

	int i;
	char c;

	for(i = 0; i < l; i++)
		fscanf(f,"%c",&c);
	
	fclose(f);
	return 0;
}
