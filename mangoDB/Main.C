#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include"Fetch.h"
#include"deleteCommands.h"
#include"updatedatabase.h"
#include"createTable.h"
#include"memoryToFile.h"





void print(char **res, int count)
{
	int i;
	for (i = 0; i < count; i++)
		printf("%s ", res[i]);
	printf("\n");
}

void main()
{
	char query[100], **res;
	struct table *mango = (struct table *)malloc(sizeof(struct table));
	struct table *temp;
	mango->numberOfKeys = 0;
	mango->rows = NULL;
	mango->name = NULL; mango->nextTable = NULL;
	int count = 0;
	while (1)
	{
		gets(query);
		res = split(query,&count);
		if (strcmp(res[0], "create") == 0)
			createTable(mango, query);
		else if (strcmp(res[0], "insert") == 0){
			temp = getRequiredTable(mango, res[1]);
			insert(temp, query+strlen(res[0])+1,0);
			temp->numberOfKeys += 1;
		}
		else if (strcmp(res[0], "update") == 0)
		{
			temp = getRequiredTable(mango, res[1]);
			updateDatabase(temp, query + strlen(res[0]) + 1);
		}
		else if (strcmp(res[0], "delete") == 0)
		{
			temp = getRequiredTable(mango, res[1]);
			deleteEntries(temp, query + strlen(res[0]) + 1);
		}
		else if (strcmp(res[0], "dump") == 0)
		{
			temp = getRequiredTable(mango, res[1]);
			dumpIntoFile(temp);
		}
		else
		{
			temp = getRequiredTable(mango, res[1]);
			res = getDetails(temp, query + strlen(res[0]) + 1, &count);

			print(res, count);

		}
	}
}