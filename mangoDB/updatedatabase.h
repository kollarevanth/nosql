void insert(struct table *mango, char *query, int flag)
{
	int i, noqs;
	mango->rows = (struct row **)realloc(mango->rows, sizeof(struct row)*(mango->numberOfKeys + 1));
	mango->rows[mango->numberOfKeys] = (struct row *)malloc(sizeof(struct row));
	mango->rows[mango->numberOfKeys]->columnCount = 0;
	mango->rows[mango->numberOfKeys]->column = NULL;
	mango->rows[mango->numberOfKeys]->commitVersion = 1;

	char **querySplit = split(query, &noqs);
	if (flag)
		noqs--;
	mango->rows[mango->numberOfKeys]->rowname = querySplit[1];
	for (i = 2; i<noqs - 1; i += 2)
	{
		struct column *temp = mango->rows[mango->numberOfKeys]->column;
		if (temp == NULL){
			mango->rows[mango->numberOfKeys]->columnCount += 1;
			mango->rows[mango->numberOfKeys]->column = getColumn();
			mango->rows[mango->numberOfKeys]->column->nextColumn = NULL;
			mango->rows[mango->numberOfKeys]->column->nextVersion = NULL;
			mango->rows[mango->numberOfKeys]->column->version = 1;
			mango->rows[mango->numberOfKeys]->column->data = querySplit[i + 1];
			mango->rows[mango->numberOfKeys]->column->name = querySplit[i];
		}
		else{
			mango->rows[mango->numberOfKeys]->columnCount += 1;
			while (temp != NULL&&temp->nextColumn != NULL)
				temp = temp->nextColumn;
			temp->nextColumn = getColumn();
			temp = temp->nextColumn;
			temp->data = querySplit[i + 1];
			temp->nextColumn = NULL;
			temp->nextVersion = NULL;
			temp->version = 1;
			temp->name = querySplit[i];

		}

	}

}

void appendFirst(struct row *row, struct column *col, int j)
{
	struct column *prev = NULL;
	struct column *next = NULL;
	struct column *current = NULL;
	if (j == 0)
	{
		current = getColumnAddress(row->column, j);
		next = getColumnAddress(row->column, j)->nextColumn;
		row->column = col;
		col->nextColumn = next;
		row->column->nextVersion = current;
	}
	else
	{
		current = getColumnAddress(row, j);
		next = getColumnAddress(row, j)->nextColumn;
		prev = getColumnAddress(row, j - 1);
		prev->nextColumn = col;
		col->nextColumn = next;
		row->column->nextVersion = current;
	}
}

void updateColumnsForRow(struct row *row, char **query,int *count1)
{
	int j,k,flag=0;
	struct column *prev = NULL;
	for (j = 0; j < row->columnCount; j++)
	{
		for (k = 0; k < *count1-1; k++)
		{
			int count = 1;
			if (strcmp(getColumnAddress(row->column, j)->name, query[k]) == 0){
				struct column *temp = getColumnAddress(row->column, j);				
					if (temp == NULL)
					{
						if (row->commitVersion == getInt(query[*count1 - 1]))
							getColumnAddress(row->column, j)->nextVersion = getColumn();
						else
							return;
						prev = getColumnAddress(row->column, j);
						temp = getColumnAddress(row->column, j)->nextVersion;
						count++;
					}
					else
					{
						while (temp->nextVersion != NULL)
						{
							temp = temp->nextVersion;
							count++;
						}
						if (row->commitVersion == getInt(query[*count1 - 1]) || getInt(query[*count1 - 1])<=0)
							temp->nextVersion = getColumn();
						else
							return;
						prev=temp;
						temp = temp->nextVersion;
						flag = 1;
					}
					row->commitVersion += 1;temp->name = query[k];
					if (strcmp(query[0], "followers") == 0){
						query[k + 1] = concat(getColumnAddress(row->column,j)->data, query[3]);
						temp->data = query[k + 1];temp->nextColumn = NULL; temp->nextVersion = NULL;
						temp->version = count+1;
						prev->nextVersion = NULL;
						appendFirst(row, temp, j);
						return;
					}
					prev->nextVersion = NULL;
					temp->data = query[k + 1];
					temp->nextColumn = NULL;temp->nextVersion = NULL;
					temp->version = count+1;	
					appendFirst(row, temp, j);
			}
		}
	}
}



void changeFollowers(struct table *mango, char *que)
{
	int i;
	char **queries = split(que, &i);
	for (i = 0; i < mango->numberOfKeys; i++)
	{
		if (strcmp(mango->rows[i]->rowname, queries[1])==0)
			mango->rows[i]->column->data = concat(mango->rows[i]->column->data, queries[2]);
	}
}


void updateFollowings(struct table *mango, char *que)
{
	int i, j;
	for (i = 0; i < mango->numberOfKeys; i++)
	{

	}
}



void updateDatabase(struct table *mango, char *que)
{
	int count = 0,i,flag=1;
	char **query = split(que,&count);
	for (i = 0; i < mango->numberOfKeys; i++)
	{
		if (strcmp(mango->rows[i]->rowname, query[1]) == 0)
		{
			updateColumnsForRow(mango->rows[i], query,&count);
			if (strcmp(query[0], "followers") == 0)
				updateFollowings(mango, que);
			flag = 0;
		}
	}
	if (flag == 1){
		insert(mango, que, 1);
		mango->numberOfKeys += 1;
	}
}