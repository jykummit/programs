#include<stdio.h>
#include<stdlib.h>

struct node
{
int data;
struct node *next;
};


struct node *head;

void create_ll(int data)
{
struct node *tmp=(struct node*)malloc(sizeof(struct node));
struct node *tmp2;
if(tmp == NULL)
	return;

tmp->data=data;
if(head == NULL)
head = tmp;


else
{
tmp2=head;
while(tmp2->next != NULL)
	tmp2 =tmp2->next;
tmp2->next = tmp ;
}
}

void print_ll(void)
{
struct node *tmp = head;
while(tmp != NULL)
{
printf("%d--->",tmp->data);
tmp = tmp->next;
}
printf("NULL \n");
}

void main(void)
{
create_ll(1);
create_ll(2);
create_ll(3);
create_ll(4);
create_ll(5);
print_ll();
}



