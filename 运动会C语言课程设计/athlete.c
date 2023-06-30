#define _CRT_SECURE_NO_WARNINGS  1
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<string.h>
#include<time.h>
#include<Windows.h>

typedef struct Athlete   /*定义运动员管理信息的结构体。typedef用来指定新的类型名来代替已有的类型名*/
{
	char name[10];//姓名
	char sex[4];//性别
	char school[10];//学院
	int number;//学号
	int age;//年龄
	int score[3];//800m,跳高，跳远三门成绩
	float aver;
}athtype;

typedef struct Athletenode   /*使用链表录入运动员数据athtype data*/
{
	athtype data;
	struct Athletenode* next;
}Listnode;
Listnode* Head = NULL;
Listnode list;

void Welcome()
{
	printf("*****运动员管理系统*****\n");
	system("pause");//便于观察程序的执行结果
	system("cls");//清屏
}
void Goodbye()
{
	system("cls");
	printf("*****谢谢使用*****");
	exit(0);
}
void Menu()
{
	printf("*****************************************\n");
	printf("                                         \n");
	printf("        0.退出系统                       \n");
	printf("        1.添加运动员信息                 \n");
	printf("        2.浏览运动员信息                 \n");
	printf("        3.修改运动员信息                 \n");
	printf("        4.删除运动员信息                 \n");
	printf("        5.查询运动员信息                 \n");
	printf("        6.保存运动员信息                 \n");
	printf("        7.统计运动员成绩                 \n");
	printf("        8.运动员成绩排序                 \n");
	printf("                                         \n");
	printf("*****************************************\n");
}
void Add()
{
	int i;
	system("cls");
	Listnode* New = (Listnode*)malloc(sizeof(Listnode));
	New->next = NULL;
	printf("输入运动员姓名：\n");
	scanf("%s", New->data.name);
	printf("输入运动员性别：\n");
	scanf("%s", New->data.sex);
	printf("输入运动员学院：\n");
	scanf("%s", New->data.school);
	printf("输入运动员学号：\n");
	scanf("%d", &New->data.number);
	printf("输入运动员年龄：\n");
	scanf("%d", &New->data.age);
	printf("输入运动员800m,跳高，跳远成绩信息:\n");
	for(i=0;i<3;i++)
	{
	scanf("%d",&New->data.score[i]);
    }
	if (Head == NULL)
	{
		Head = New;
	}
	else
	{
		New->next = Head;
		Head = New;
	}
	printf("*****添加运动员成功*****");
	system("pause");
	system("cls");
}
void CalAver() //统计运动员总成绩
{
	int s=0;
		printf("输入要统计的运动员名字：\n");
	char name[10];
	scanf("%s", &name);
	Listnode* p = (Listnode*)malloc(sizeof(Listnode));
	p = Head;
	while (p)
	{
		if (strcmp(p->data.name, name) != 0)
		{
			p = p->next;
		}
		
		else
		{
			printf("**********统计成功**********\n");
			printf("#姓名\t\t性别\t\t学院\t\t学号\t\t年龄\t\t800m\t跳高\t跳远#\n");

		printf("#%s\t\t%s\t\t%s\t\t%d\t\t%d\t\t",
			p->data.name,
			p->data.sex,
			p->data.school,
			p->data.number,
			p->data.age
		);
			for(int i=0;i<3;i++)
			{
				printf("%d\t",p->data.score[i]);
			
	
		s+=p->data.score[i];
	
			 }
			 printf("\n该运动员的总成绩为：%d",s);
			 printf("\n");
		p = p->next;

			system("pause");
			system("cls");
			break;
		}
		}
		if (p == NULL)
			printf("**********此运动员不存在**********\n");
		system("pause");
		system("cls");
	


}



void show()
{
	system("cls");
	Listnode* p = Head;
	printf("****************************************************************************************************\n");
	printf("#姓名\t\t性别\t\t学院\t\t学号\t\t年龄\t\t800m\t跳高\t跳远#\n");
	while (p)
	{
		printf("#%s\t\t%s\t\t%s\t\t%d\t\t%d\t\t",
			p->data.name,
			p->data.sex,
			p->data.school,
			p->data.number,
			p->data.age
		);
			for(int i=0;i<3;i++)
			{
				printf("%d\t",p->data.score[i]);
			 }
			 printf("\n");
		p = p->next;
	}
	printf("****************************************************************************************************\n");
	system("pause");
	system("cls");
}
void Saveinformation()//保存信息
{
	system("cls");
	FILE* fp = fopen("./Stu.dat", "wb");
	Listnode* p = Head;
	while (p)
	{
		fwrite(&p->data, 1, sizeof(athtype), fp);
		p = p->next;
	}
	fclose(fp);
	p = NULL;
	printf("*****保存运动员信息成功*****\n");
	system("pause");
	system("cls");
}
void Readinformation()
{
	system("cls");
	FILE* fp = fopen("./Stu.dat", "rb");
	athtype data;
	while (fread(&data, 1, sizeof(athtype), fp))
	{
		Listnode* New = (Listnode*)malloc(sizeof(Listnode));
		New->next = NULL;
		New->data = data;
		if (Head == NULL)
		{
			Head = New;
		}
		else
		{
			New->next = Head;
			Head = New;
		}
	}
	fclose(fp);
	printf("***读取运动员成功***\n");
	system("pause");
	system("cls");
}
void change()
{
	printf("输入要修改信息的运动员姓名：\n");
	char name[10];
	scanf("%s", &name);
	Listnode* p = (Listnode*)malloc(sizeof(Listnode));
	p = Head;
	while (p)
	{
		if (strcmp(p->data.name, name) != 0)
		{
			p = p->next;
		}
		else
		{
			char name1[10];
			char sex1[4];
			char school1[10];
			int number1;
			int age1;
			printf("输入运动员姓名：\n");
			scanf("%s", name1);
			strcpy(p->data.name, name1);
			printf("输入运动员性别：\n");
			scanf("%s", sex1);
			strcpy(p->data.sex, sex1);
			printf("输入运动员学院：\n");
			scanf("%s", school1);
			strcpy(p->data.school, school1);
			printf("输入运动员学号：\n");
			scanf("%d", number1);
			p->data.number = number1;
			printf("输入运动员年龄：\n");
			scanf("%d", age1);
			p->data.age = age1;
			printf("***********修改运动员信息成功***********\n");
			system("pause");
			system("cls");
			break;
		}
		if (p == NULL)
		{
			printf("**********要修改信息的运动员不存在**********\n");
			system("pause");
			system("cls");
			break;
		}
	}

}
void shanchu()
{
	printf("输入要删除的运动员姓名：\n");
	char name[10];
	scanf("%s", &name);
	Listnode* p = (Listnode*)malloc(sizeof(Listnode));
	p = Head;
	while (p)
	{
		if (strcmp(p->data.name, name) != 0)
		{
			p = p->next;
		}
		else
		{
			Listnode* q = (Listnode*)malloc(sizeof(Listnode));
			q = Head;
			while (q)
			{
				if (q->next != p)
				{
					q = q->next;
				}
				else
				{
					q->next = p->next;
					p->next = NULL;
					free(p);
					printf("***********删除成功**********\n");
					break;
				}
			}
			system("pause");
			system("cls");
			break;
		}
	}
	if (p == NULL)
	{
		printf("***********要删除的学生不存在**********\n");
		system("pause");
		system("cls");
	}
}
void chaxun()
{
	printf("输入要查询的学生名字：\n");
	char name[10];
	scanf("%s", &name);
	Listnode* p = (Listnode*)malloc(sizeof(Listnode));
	p = Head;
	while (p)
	{
		if (strcmp(p->data.name, name) != 0)
		{
			p = p->next;
		}
		
		else
		{
			printf("**********查询成功**********\n");
			printf("#姓名\t\t性别\t\t学院\t\t学号\t\t年龄\t\t800m\t跳高\t跳远#\n");

		printf("#%s\t\t%s\t\t%s\t\t%d\t\t%d\t\t",
			p->data.name,
			p->data.sex,
			p->data.school,
			p->data.number,
			p->data.age
		);
			for(int i=0;i<3;i++)
			{
				printf("%d\t",p->data.score[i]);
			 }
			 printf("\n");
		p = p->next;

			system("pause");
			system("cls");
			break;
		}
		}
		if (p == NULL)
			printf("**********此运动员不存在**********\n");
		system("pause");
		system("cls");
	
}

void paixu1()//成绩排序
{
	system("cls");
	Listnode* cur = Head;
	Listnode dummy;dummy.next = Head;
	Listnode* prev = &dummy;
	Listnode* ter = NULL;
	while (cur != ter) {
		while (cur->next != ter) {
			if (cur->data.score[0] < cur->next->data.score[0])
			{
				prev = cur;
				cur = cur->next;
			}
			else {
				Listnode* tmp = cur->next;
				cur->next = tmp->next;
				tmp->next = cur;
				prev->next = tmp;
				prev = tmp;
			}
		}
		ter = cur;
		prev = &dummy;
		cur = dummy.next;
	}
	Head = dummy.next;
	printf("|------------------------------------------------------------------------|\n");
	printf("|************************************************************************|\n");
	printf("|*                                                                      *|\n");
	printf("|*                        **********                                    *|\n");
	printf("|*                        *排序成功*                                    *|\n");
	printf("|*                        **********                                    *|\n");
    printf("|************************************************************************|\n");
	printf("|------------------------------------------------------------------------|\n");
	system("pause");
	system("cls");
}
void paixu2()
{
	system("cls");
	Listnode* cur = Head;
	Listnode dummy;dummy.next = Head;
	Listnode* prev = &dummy;
	Listnode* ter = NULL;
	while (cur != ter) {
		while (cur->next != ter) {
			if (cur->data.score[0] > cur->next->data.score[0])
			{               
				prev = cur;
				cur = cur->next;
			}
			else {
				Listnode* tmp = cur->next;
				cur->next = tmp->next;
				tmp->next = cur;
				prev->next = tmp;
				prev = tmp;
			}
		}
		ter = cur;
		prev = &dummy;
		cur = dummy.next;
	}
	Head = dummy.next;
	printf("|------------------------------------------------------------------------|\n");
	printf("|************************************************************************|\n");
	printf("|*                                                                      *|\n");
	printf("|*                        **********                                    *|\n");
	printf("|*                        *排序成功*                                    *|\n");
	printf("|*                        **********                                    *|\n");
    printf("|************************************************************************|\n");
	printf("|------------------------------------------------------------------------|\n");
	system("pause");
	system("cls");
}
void paixu()
{
	system("cls");
	printf("----------------请选择排序方式------------------\n");
	printf("----------------升序排序请输入:1----------------\n");
	printf("----------------降序排序请输入:2----------------\n");
	char h = getch();
	switch (h)
	{
	case'1':
		paixu1();
		break;
	case'2':
		paixu2();
		break;
	}
}
int main()
{


	int n;
	athtype st[100];
	char ss[20];
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t请输入密码以进入系统：");
	scanf("%s", ss);
	if (strcmp(ss, "123456") == 0)	//密码
	{
		system("cls");
		Welcome();
		Readinformation();
		while (1)
		{
			Menu();
			char ch = getch();
			switch (ch)
			{
				case'0':
					Goodbye();
					break;
			case'1':
				Add();
				break;
			case'2':
				show();
				break;
			case'3':
				change();
				break;
			case'4':
				shanchu();
				break;
			case'5':
				chaxun();
				break;
			case'6':
				Saveinformation();
				break;
            case'7':
            	CalAver();
            	break;
			 case'8':
			 	paixu();
			 	break;
			}
		}
	}
	else
		printf("密码输入错误！系统已关闭！");
	return 0;
}
