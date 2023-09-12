#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
 
typedef struct Node
{
	int data;
	struct Node* next;
} Node;
int Create(Node** joseph,int num)
{
	if (joseph == NULL || num < 1)
	{
		return ERROR;
	}
	//创建头结点
	Node* head = (Node*)malloc(sizeof(Node));
	head->next = NULL;
 
	//移动的指针，开始指向头结点
	Node* p = head;
	//创建约瑟夫结点,采用尾插法，每次创建的结点放到链表尾部
	for (size_t i = 1; i <= num; i++)
	{
		//创建新结点，并且赋值
		Node* node = (Node*)malloc(sizeof(Node));
		node->data = i;
        //新节点的next指针设置为头结点是为了构建循环链表的闭环结构
		node->next = head;
		p->next = node;
		p = node;
	}
	//头结点去掉，整个环剩下约瑟夫结点
	p->next = head->next;
	free(head);
	//约瑟夫环，循环链表中头指针指向环第一个结点
	*joseph = p->next;
	return OK;
}
int Length(Node* joseph)
{
	if (joseph == NULL)
	{
		return 0;
	}
	Node* target = joseph;//开始target指向第一个结点
	int length = 1;
	for (; target->next!=joseph; target = target->next)
	{
		length++;
	}
	return length;
}

int Kill(Node* joseph,int n)
{
	if (joseph == NULL)
	{
		return ERROR;
	}
	int num = Length(joseph);
	//skip为杀第n个人要跨越的人数
	int skip = n-1;
	Node* p = joseph;
	Node* begin = p;//begin指向开始数的第1个人
	while (1)
	{
		begin = p;
		//找到自杀人的前一个位置
		for (size_t i = 0; i < skip-1; i++)
		{
			p = p->next;
		}
 
		//最后剩2个人时，依次自杀
		//temp == p->next 时剩下最后2个人！
		if (begin == p->next)
		{
			printf("->%d", begin->data);
			printf("->%d", begin->next->data);
			free(begin);
			free(p);
			begin = NULL;
			p = NULL;
			break;
		}
 
 
		//循环完，p 指向自杀前面一个人
		//p->next 进行自杀，实质上就是将p->next结点从循环链表中干掉
		Node* kill = p->next;
		printf("-->%d", kill->data);
		//将kill移除结点
		p->next = kill->next;
		free(kill);
		kill = NULL;
 
		//p移动到后面3个人的第1个人的位置 
		p = p->next;
		
	}
	printf("\n");
	return OK;
}
 
int main(int argc, char *argv[])
{
	Node* joseph = NULL;
	int num = 1;
    int m=0;
 
	while (num)
	{
		printf("请输入约瑟夫环人数(输入0退出):");
		scanf("%d", &num);
        if (!num)
		{
			break;
		}
        printf("请输入数到第几个人自杀:");
		scanf("%d", &m);


		printf("约瑟夫环死亡顺序:\n");
		joseph = NULL;
		Create(&joseph,num);
		Kill(joseph, m);
	}
	return 0;
}