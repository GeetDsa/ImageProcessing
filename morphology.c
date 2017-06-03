#include<stdio.h>
#include<stdlib.h>
int IMG[258][258],IMG2[258][258],IMG3[258][258],IMGR[258][258];
void dialation();
void erosion();
int min(int,int);
int max(int,int);
void main()
{
	char ch;
	int i,j;
	FILE *fp,*fp2;

	//Use space separated pixel value in a *.txt file
	fp=fopen("<Enter the path of txt file here within the braces>","r");
	fp2=fopen("<Enter the path of the txt file here within the braces>","w");

	if(fp==NULL)
	{
		printf("Error retrieving the file\n");
		exit(1);
	}
	if(fp2==NULL)
	{
		printf("Error in write file\n");
		exit(2);
	}

	for(i=1;i<=256;i++)
		for(j=1;j<=256;j++)
		{
			fscanf(fp,"%d",&IMG[i][j]);
		}

	//padding for dialation
	
	for(i=0;i<258;i++)
	{
		IMG[0][i]=0;
		IMG[257][i]=0;
		IMG[i][0]=0;
		IMG[i][257]=0;
	}
	
	dialation();

	//padding for erosion
	for(i=0;i<258;i++)
        {
                IMG[0][i]=255;
                IMG[257][i]=255;
                IMG[i][0]=255;
                IMG[i][257]=255;
        }
	erosion();

	//morphology
	for(i=1;i<=256;i++)
                for(j=1;j<=256;j++)
                        IMGR[i][j]=IMG2[i][j]-IMG3[i][j];

	for(i=1;i<=256;i++)
	{
                for(j=1;j<=256;j++)
                {
                        fprintf(fp2,"%d ",IMGR[i][j]);
                }
                fprintf(fp2,"%c",'\n');
	}

	fclose(fp);
	fclose(fp2);
}
void erosion()
{
	int i,j;
	for(i=1;i<=256;i++)
		for(j=1;j<=256;j++)
			IMG3[i][j]=min(i,j);
}
void dialation()
{
	int i,j;
        for(i=1;i<=256;i++)
                for(j=1;j<=256;j++)
                        IMG2[i][j]=max(i,j);
}
int min(int i,int j)
{
	int a,b,m=999;
	for(a=i-1;a<=i+1;a++)
		for(b=j-1;b<=j+1;b++)
			if(IMG[a][b]<m)
				m=IMG[a][b];
	return m;
}
int max(int i,int j)
{
        int a,b,m=0;
        for(a=i-1;a<=i+1;a++)
                for(b=j-1;b<=j+1;b++)
                        if(IMG[a][b]>m)
                                m=IMG[a][b];
        return m;
}

