#include<stdio.h>
#include<stdlib.h>

#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int listMaxSize; //current maximum size of list
int * list;
int length;

void initializeList()
{
	listMaxSize = LIST_INIT_SIZE;
	list = (int*)malloc(sizeof(int)*listMaxSize) ;
	length = 0 ;
}

int getLength(int *list)
{
    int i = 0;
    while(i < length) i++;
    return i;
}

int shrink()
{
    if(length==LIST_INIT_SIZE) return NULL_VALUE;
    if(length<=(listMaxSize/2)){
        int *templist;
        listMaxSize = listMaxSize/2 ;
		templist = (int*) malloc (listMaxSize*sizeof(int)) ;
        for(int i = 0; i < length ; i++)
        {
            templist[i] = list[i] ;
        }
        free(list) ;
        list = templist ;
	}
    return SUCCESS_VALUE ;
}

int insertItemAt(int pos,int item)
{
    int *templist;
    if(pos>=length) return NULL_VALUE;
    if(length==listMaxSize)
    {
        listMaxSize = 2 * listMaxSize;
        templist = (int *) malloc (listMaxSize * sizeof(int));
        for(int i = 0; i < length ; i++ )
        {
            templist[i] = list[i];
        }
        free(list);
        list=templist;
    }
    list[length]=list[pos-1];
    list[pos-1]=item;
    length++;
    return SUCCESS_VALUE;
}

int searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

int insertItem(int newitem)
{
	if(*list==0) list=(int *)malloc(LIST_INIT_SIZE*sizeof(int));
	int *tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = (int *) malloc (listMaxSize*sizeof(int)) ;

        for(int i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	}

	list[length] = newitem ; //store new item
	length++ ;
	return SUCCESS_VALUE ;
}


int deleteItemAt(int position) //version 2, do not preserve order of items
{
	if ( position >= length ) return NULL_VALUE;
	list[position] = list[length-1] ;
	length-- ;
	shrink();
	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return NULL_VALUE;
	deleteItemAt(position);
	shrink();
	return SUCCESS_VALUE ;
}

int deleteLast()
{
    int a = list[length-1];
    length--;
    shrink();
    return a;
}

void deleteAll()
{
    length=0;
    free(list);
    list = (int *)malloc(LIST_INIT_SIZE*sizeof(int));
    listMaxSize=LIST_INIT_SIZE;
}
int Clear()
{
    free(list);
    *list=0;
    listMaxSize=LIST_INIT_SIZE;
    length=0;
}
void printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Insert item with Position. 3. Delete item at. \n4. Delete item.");
        printf("5. Get Length. 6. Print. \n7. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int item;
            int pos;
            scanf("%d %d",&item,&pos);
            insertItemAt(pos,item);
        }
        else if(ch==3)
        {
            int pos;
            scanf("%d", &pos);
            deleteItemAt(pos);
        }
        else if(ch==4)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==5)
        {
            int i;
            i=getLength(list);
            printf("Length of the list=%d\n",i);
        }
        else if(ch==6)
        {
            printList();
        }
        else if(ch==7)
        {
            deleteAll();
        }
    }

}
/*
int main()
{
    initializeList();
    int i=0;
    char dig[15];
    scanf("%s",dig);
    while(dig[i]!='\0')
    {
        if((dig[i]!='+')&&(dig[i]!='-')&&(dig[i]!='*')&&(dig[i]!='/')){
            int k = dig[i]-48;
            printf("%d\n",k);
            insertItem(k);
        }
        else{
            if(dig[i]=='+'){
                int a = deleteLast();
                int b = deleteLast();
                insertItem(a+b);
            }
            else if(dig[i]=='-'){
                int a = deleteLast();
                int b = deleteLast();
                insertItem(a-b);
            }
            else if(dig[i]=='*'){
                int a = deleteLast();
                int b = deleteLast();
                insertItem(a*b);
            }
            else if(dig[i]=='/'){
                int a = deleteLast();
                int b = deleteLast();
                insertItem(a/b);
            }
        }
        i++;
    }
    printf("%d", deleteLast());

    Clear();

    return 0;
}

*/
