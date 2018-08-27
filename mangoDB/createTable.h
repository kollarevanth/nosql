struct table *getRequiredTable(struct table *mango, char *tablename)
{
	struct table *temp = mango;
	while (strcmp(temp->name, tablename) != 0)
		temp = temp->nextTable;
	return temp;

}



void createTable(struct table *mango, char *que)
{
	int j = 0;
	char **query = split(que,&j);
	struct table *temp = mango;
	if (temp->name == NULL)
	{
		temp->name = query[1];
	}
	else
	{
		while (temp->nextTable != NULL)
			temp = temp->nextTable;
		temp->nextTable = (struct table *)malloc(sizeof(struct table));
		temp = temp->nextTable;
	}
	temp->name = query[1];
	temp->numberOfKeys = 0;
	temp->nextTable = NULL;
	temp->rows = NULL;
}