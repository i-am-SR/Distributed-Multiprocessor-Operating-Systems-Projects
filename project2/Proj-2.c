#include<stdio.h>
#include<stdlib.h>
#include "q.h" 

int main()
{
	struct q_elem* head=NewQueue();
	/*char reply;
	int pl;
	printf("Do you want to add nodes to the queue (y/n)? :\n");
	scanf("%c",&reply);
	while(reply=='y')
	{
	printf("Enter the payload value: \n");
	scanf("%d",&pl);
	struct q_elem* item=NewItem();
	item->payload=pl;
	AddQueue(&head, item);
	printf("Do you want to add nodes to the queue (y/n)? :\n");
	scanf("%c",&reply);
	}*/
	
	struct q_elem* item1=NewItem();
	item1->payload=1;
	AddQueue(&head, item1);
	struct q_elem* item2=NewItem();
	item2->payload=2;
	AddQueue(&head, item2);
	struct q_elem* item3=NewItem();
	item3->payload=3;
	AddQueue(&head, item3);
	struct q_elem* item4=NewItem();
	item4->payload=4;
	AddQueue(&head, item4);
	struct q_elem* item5=NewItem();
	item5->payload=5;
	AddQueue(&head, item5);
	struct q_elem* item6=NewItem();
	item6->payload=6;
	AddQueue(&head, item6);
	struct q_elem* item7=NewItem();
	item7->payload=7;
	AddQueue(&head, item7);
	PrintQ(&head);
	printf("Deleting the head of the queue!!\n");
	struct q_elem* deleted1=DelQueue(&head);
	printf("The deleted node is : %d\n",deleted1->payload);
	PrintQ(&head);
	printf("Deleting the head of the queue!!\n");
	struct q_elem* deleted2=DelQueue(&head);
	printf("The deleted node is : %d\n",deleted2->payload);
	PrintQ(&head);
	printf("=======================Rotating the head of the queue!!\n");
	AddQueue(&head, DelQueue(&head));
	PrintQ(&head);
	printf("Deleting the head of the queue!!\n");
	struct q_elem* deleted3=DelQueue(&head);
	printf("The deleted node is : %d\n",deleted3->payload);
	PrintQ(&head);
	printf("Deleting the head of the queue!!\n");
	struct q_elem* deleted4=DelQueue(&head);
	printf("The deleted node is : %d\n",deleted4->payload);
	PrintQ(&head);
	printf("================ADDING TO the end of the queue!!\n");	
	struct q_elem* item8=NewItem();
	item8->payload=999;
	AddQueue(&head, item8);
	PrintQ(&head);
	printf("Deleting the head of the queue!!\n");
	struct q_elem* deleted5=DelQueue(&head);
	printf("The deleted node is : %d\n",deleted5->payload);
	PrintQ(&head);
	printf("Deleting the head of the queue!!\n");
	struct q_elem* deleted6=DelQueue(&head);
	printf("The deleted node is : %d\n",deleted6->payload);
	PrintQ(&head);
	printf("Deleting the head of the queue!!\n");
	struct q_elem* deleted7=DelQueue(&head);
	printf("The deleted node is : %d\n",deleted7->payload);
	PrintQ(&head);
	
	return 0;
}
