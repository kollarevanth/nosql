#include<sys/stat.h>
#include<sys/types.h>
char *str(int j)
{
	char *res = (char *)malloc(100);
	int i=0;
	for (j; j != 0; j++)
	{
		res[i++] = (char)(j % 10+'0');
		j = j / 10;
		j--;
	}
	res[i] = '\0';
	return strrev(res);
}


char *getColumnsData(struct column *col,char *rowname)
{
	int i;
	char *res = NULL;
	res = strcat(rowname, "\0");
	while (col != NULL)
	{
		res = concat(res, str(col->version));
		res = concat(res, col->data);
		col = col->nextVersion;
	}
	
	return res;
}
void constChar(char *a, char *b)
{
	int i;
	for (i = 0; b[i] != '\0'; i++)
		a[i] = b[i];
	a[i] = '\0';
}

void dumpIntoFile(struct table *temp)
{
	int i, j;
	FILE *fp=NULL;
	mkdir(temp->name, 0777);
	char *path = strcat1(temp->name, "/");
	for (i = 0; i < temp->numberOfKeys; i++)
	{
		for (j = 0; j < temp->rows[i]->columnCount; j++)
		{
			fp = fopen(strcat1(path,strcat1(getColumnAddress(temp->rows[i]->column, j)->name,".txt")), "a+");
			char b[1000];
			constChar(b, getColumnsData(getColumnAddress(temp->rows[i]->column, j),temp->rows[i]->rowname));
			fprintf(fp, "%s\n", b);
			fclose(fp);
		}
	}
	fclose(fp);
}