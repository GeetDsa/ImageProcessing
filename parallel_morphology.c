#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
int IMG[3002][3002],IMG2[3002][3002],IMG3[3002][3002],IMGR[3002][3002];
void dialation();
void erosion();
void morphology();
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

	for(i=1;i<=3000;i++)
		for(j=1;j<=3000;j++)
		{
			fscanf(fp,"%d",&IMG[i][j]);
		}

	//padding for dialation
	
	for(i=0;i<3002;i++)
	{
		IMG[0][i]=0;
		IMG[3001][i]=0;
		IMG[i][0]=0;
		IMG[i][3001]=0;
	}
	
	dialation();

	//padding for erosion
	for(i=0;i<3002;i++)
        {
                IMG[0][i]=255;
                IMG[3001][i]=255;
                IMG[i][0]=255;
                IMG[i][3001]=255;
        }
	erosion();

	//morphology
	morphology();

	for(i=1;i<=3000;i++)
        {
                for(j=1;j<=3000;j++)
                {
                        fprintf(fp2,"%d ",IMGR[i][j]);
                }
                fprintf(fp2,"\n");
        }


	fclose(fp);
	fclose(fp2);
}
void erosion()
{
	int i,j;
	omp_set_dynamic(0);     // Explicitly disable dynamic teams
	omp_set_num_threads(16);
	#pragma omp parallel private(i,j)
	{
	for(i=1;i<=3000;i++)
		for(j=1;j<=3000;j++)
			IMG3[i][j]=min(i,j);
	}
}
void dialation()
{
	int i,j;
	omp_set_dynamic(0);     // Explicitly disable dynamic teams
        omp_set_num_threads(16);
        #pragma omp parallel private(i,j)
        {
        for(i=1;i<=3000;i++)
                for(j=1;j<=3000;j++)
                        IMG2[i][j]=max(i,j);
	}
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
void morphology()
{
	int i,j;
	 omp_set_dynamic(0);     // Explicitly disable dynamic teams
        omp_set_num_threads(16);
        #pragma omp parallel private(i,j)
	{
        for(i=1;i<=3000;i++)
                for(j=1;j<=3000;j++)
                        IMGR[i][j]=IMG2[i][j]-IMG3[i][j];
	}
}
