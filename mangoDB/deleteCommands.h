void swapAllUp(struct table *mango, int index)
{
	int j;
	for (j = index; j < mango->numberOfKeys - 1;j++)
	{ 
		struct table *temp;
		temp = mango->rows[j];
		mango->rows[j] = mango->rows[j + 1];
		mango->rows[j + 1] = temp;
	}
	mango->numberOfKeys--;
}

void deleteEntries(struct table *mango, char *que)
{
	int count = 0,i;
	char **query = split(que, &count);
	if (count == 2)
	{
		for (i = 0; i < mango->numberOfKeys; i++)
		{
			if (strcmp(mango->rows[i]->rowname, query[1]) == 0)
			{
				mango->rows[i] = NULL;
				swapAllUp(mango, i);
			}
		}
		return;
	}
	/*for (i = 0; i < mango->numberOfKeys; i++)
	{
		if (strcmp(mango->rows[i]->rowname, query[1]) == 0)
		{
			for (int j = 0; j < mango->rows[i]->columnCount; j++)
			{
				for (int k = 2; k < count; k++)
				{
					if (strcmp(getColumnAddress(mango->rows[i]->column, j)->name, query[k]) == 0)
					{
						struct row *temp = mango->rows[i];
						if (j != 0)
							getColumnAddress(temp,j)->nextColumn = getColumnAddress(mango->rows[i]->column, j)->nextColumn;
						else
							mango->rows[i]->column = getColumnAddress(mango->rows[i]->column, j)->nextColumn;
						mango->rows[i]->columnCount -= 1;
					}
				}
			}
		}
	}
	*/

}