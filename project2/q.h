
typedef struct q_elem
{
int payload;
struct q_elem* next;
struct q_elem* prev;
}q_elem;

q_elem* NewItem()
{
struct q_elem* new_q=(struct q_elem*)malloc(sizeof(struct q_elem));
return new_q;
}

q_elem* NewQueue()
{
struct q_elem* head=NULL;
return head;
}

void AddQueue(struct q_elem** head, struct q_elem* item)
{
if(*head == NULL)
{
	item->next=item;
	item->prev=item;
	*head=item;
}
else
{
	struct q_elem* first=*head;
	item->prev=first->prev;
	item->next=*head;
	first->prev->next=item;
	first->prev=item;
}
return;
}

q_elem* DelQueue(struct q_elem** head)
{
if(*head==NULL)
{
	printf("ERROR***** The queue is empty!!!\n");
	return *head;
}
else
{
	struct q_elem* removed=*head;
	if(removed->next==removed)
	{
		*head=NULL;
	}
	else
	{
	struct q_elem* first=removed->next;
	*head=first;
	removed->prev->next=first;
	first->prev=removed->prev;
	}
	removed->next=NULL;
	removed->prev=NULL; 
	return removed;
}
}

void PrintQ(struct q_elem** head)
{
printf("Printing the queue: -\n");
if(*head==NULL)
{
	printf("The queue is empty!!!\n");
}
else
{
	struct q_elem* node=*head;
	struct q_elem* curr=*head;
	printf("%d->",node->payload);
	while(node->next!=curr)
	{
		node=node->next;		
		printf("%d->",node->payload);
	}
	printf("%d",curr->payload);
	printf("\n");
}
}





















