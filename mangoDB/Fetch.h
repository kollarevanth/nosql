struct row
{
	int columnCount;
	char *rowname;
	int commitVersion;
	struct column *column;
};
struct column
{
	int version;
	char *data, *name;
	struct column *nextColumn;
	struct column *nextVersion;
};
struct table
{
	int numberOfKeys;
	char *name;
	struct row **rows;
	struct table *nextTable;
};



struct column *getColumn()
{
	struct column *temp = (struct column *)malloc(sizeof(struct column));
	return temp;
}
char *concat(char *a, char *b)
{
	char *res=NULL;
	if (a == NULL)
		return b;
	int l = strlen(a);
	res = (char *)malloc( sizeof(char)*l + 1);
	for (int i=0; i < l; i++)
		res[i] = a[i];

	res[l] = ',';
	if (b == NULL)
		return a;
	int j;
	for (j = 0; b[j] != '\0'; j++)
	{
		res = (char *)realloc(res, sizeof(char)*l + 2 + j);
		res[l + j + 1] = b[j];
	}
	res[l + j + 1] = '\0';
	return res;
}
char *getName(char *query)
{
	char *res = NULL;
	int i;
	for (i = 0; query[i] != ' '&&query[i] != '\0'; i++)
	{
		res = (char *)realloc(res, sizeof(char)*(i + 1));
		res[i] = query[i];
	}
	res[i] = '\0';
	return res;
}
int strlen(char *a)
{
	int i = 0;
	for (i = 0; a[i] != '\0'; i++)
	{

	}
	return i;
}
char *strcat1(char *a, char *b)
{
	char *res = (char *)malloc(sizeof(char)*(strlen(a)+strlen(b)));
	int i, j;
	for (i = 0; a[i] != '\0'; i++)
		res[i] = a[i];
	for (j = 0; b[j] != '\0'; j++)
		res[i + j] = b[j];
	res[i + j] = '\0';
	return res;
}
char **split(char *query, int *nows)
{
	char **res = NULL;
	int i, j, count = 0;
	for (i = 0; i<strlen(query); i++)
	{
		count++;
		res = (char **)realloc(res, sizeof(char *)*(count + 1));
		res[count - 1] = getName(query + i);
		i += strlen(res[count - 1]);
	}
	*nows = count;
	res[count] = NULL;
	return res;
}
int getInt(char *a)
{
	int i = 0,sum=0;
	if (a[i] == '-')
		i++;
	while (a[i] != '\0'){
		sum = sum * 10 + (a[i] - '0');
		i++;
	}
	if (a[0] == '-')
		return -1 * sum;
	else
		return sum;
}
struct column *getColumnAddress(struct column *s, int j)
{
	int i;
	for (i = 0; i < j; i++)
		s = s->nextColumn;
	return s;
}

char **getDetails(struct table *mango, char *query,int *count1)
{
	int count = 0,resCount=0;
	char **splits = split(query, &count);
	char **res = NULL;
	int i,j;


	if (count == 2)
	{
		for (i = 0; i < mango->numberOfKeys;i++)
			if (strcmp(mango->rows[i]->rowname, splits[1]) == 0)
			{
				for (j = 0; j < (mango->rows[i]->columnCount); j++)
				{
					res = (char **)realloc(res, sizeof(char *)*(j+1));
					struct column *temp = getColumnAddress(mango->rows[i]->column, j);
					/*while (temp->nextVersion != NULL)
						temp = temp->nextVersion;*/
					res[j] = temp->data;
				}
				*count1 = j;
				return res;

			}
	}
	/*for (i = 0; i < (mango->numberOfKeys); i++)
	{
		if (strcmp(mango->rows[i]->rowname, splits[1]) == 0)		//To Compare Row Name
		{
			for (j = 0; j < mango->rows[i]->columnCount; j++)	//To compare column name
			{
				for (int k = 2; k < count; k+=1)					//To compare column with query
				{
					if (strcmp(getColumnAddress(mango->rows[i]->column, j)->name, splits[k]) == 0)
					{
						res = (char **)realloc(res, sizeof(char *)*(resCount + 1));
						struct column *temp = getColumnAddress(mango->rows[i]->column,j);
						while (temp->nextVersion != NULL)
							temp = temp->nextVersion;
						res[j] = temp->data;
						resCount++;
					}
				}
			}
			*count1 = resCount;
			return res;
		}
	}*/
}