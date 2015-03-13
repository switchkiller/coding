#include<stdio.h>

int main()
{
	char tt[1000];
	strcpy(tt,"Avi \
			Dullu \
			in \
			Hyderabad \
			");
	printf("%s\n",tt);return 0;
	FILE *fp = fopen("allInstr","r"), *fo = fopen("res.txt","w");
	char s[100000], s2[100000], s3[100000];
	FILE *f1 = fopen("Scan_init_embed.hpp","r");
	fscanf(f1,"%[^Z]",s);
	fscanf(f1,"%[^@]",s2);
	fscanf(fp,"%[^Q]",s3);
	fprintf(fo,"%s",s);
	fprintf(fo,"%s",s3);
	fprintf(fo,"%s",s2);
	fclose(fp);
	fclose(fo);
	fclose(f1);
	return 0;
}
