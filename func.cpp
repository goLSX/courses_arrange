#include "func.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "string.h"
#include <stack>
using namespace std;

extern VexNode result1[100];
extern VexNode result2[100];
extern VexNode result3[100];
extern VexNode result4[100];
extern Class_arrange_Graph G;

void mainmenu()
{
    char key;

    printf("\n\n\n\n");
    printf("		     	    ��ӭʹ�ÿγ̱���ϵͳ	               \n\n\n");
    printf("______________________________________________________________________\n");
    printf("			     1. �鿴�γ���Ϣ        			  \n");
    printf("______________________________________________________________________\n");
    printf("	 		     2. �޸Ŀγ���Ϣ                		  \n");
    printf("______________________________________________________________________                   20���������ѧ�뼼��1�� ��ʢ��\n");
    printf("        		     3. ���Ȱ��ſγ�                   		  \n");
    printf("______________________________________________________________________                              3120004707  \n");
    printf("        		     4. ���찲�ſγ�           			  \n");
    printf("______________________________________________________________________\n");
    printf("        		     5. �رճ���               			  \n");
    printf("______________________________________________________________________\n");
    printf("\n\n\n\n\t ") ;
    key=getch();
    key=key-'0';
    switch(key)
    {
	case 1:		system("cls");
			Print_message();
			break;

	case 2:		system("cls");
			Adjust_message();
			break;

	case 3:		system("cls");
			Arrange_Selete(1);
			break;

	case 4:		system("cls");
			Arrange_Selete(0);
			break;

	case 5:		exit(0);

	default :
			cout << "��ѡ����Ч,�밴����������˵�" << endl;
			key=getch();
			system("cls");
			break;
    }

	mainmenu();
}



int Locate(char* ch)		//��C1C2C3������ ��Ϊ0 1 2...     �γ̺Ŷ�Ӧ��λ��
{
	return (2 == strlen(ch)) ? ch[1] - '1' : (ch[1] - '0') * 10 + ch[2] - '1';
}



void Read_file()
{
	FILE* fp = fopen("./����.txt", "r");
	if (NULL == fp)
	{
		printf("δ�ҵ��ļ�,�����ļ�·�����󣡣���");
		exit(1);
	}

	G.mes=(Message*)malloc(sizeof(Message));

	fscanf(fp,"%d%d%d",&G.mes->term_num,&G.mes->max_credit,&G.VexNum); 	//��ȡѧ������ÿѧ�����ѧ�֣��γ�����
	if(G.VexNum > MaxClass || G.mes->term_num > MaxTerm || G.mes->max_credit > MaxCredit)
	{
		cout << "�γ�������ѧ����Ŀ��ÿѧ�����ѧ�ֳ�������" <<endl;
		fclose(fp);
		exit(1);
	}

	G.Vex = (VexNode*)malloc(sizeof(VexNode) * G.VexNum);
	int i=0;

	for(;i<G.VexNum;i++)
		G.Vex[i].FirstArc=nullptr;

	for (i = 0; i < G.VexNum; i++)		//��ȡ�γ���Ϣ
	{
		fscanf(fp, "%s%d", G.Vex[i].data,&G.Vex[i].credit);		//��ȡ�γ����ƺ�ѧ��

		while ('\n' != fgetc(fp)) {		//�������޿γ̽����ڽӱ���
			char str[4];
			int s;
			fscanf(fp, "%s", str);
			s = Locate(str);
			if (s < 0 || s > G.VexNum) {		//�жϿγ��Ƿ��д���
				printf("%s�γ̴��󣬱�רҵ�������޿γ̣�\n", G.Vex[i].data);
				fclose(fp);
				exit(1);
			}
			AdjVexNode* p = (AdjVexNode*)malloc(sizeof(AdjVexNode));		//�����ڽӱ���
			p->AdjVex = s;
			p->Next = G.Vex[i].FirstArc;
			G.Vex[i].FirstArc = p;
			G.ArcNum++;
		}
	}
	fclose(fp);

	AdjVexNode * p;
	for (i=0; i<G.VexNum; i++)		//��ʼ�����
		G.Vex[i].In_degree=0;
	for(i=0;i<G.VexNum;i++)
	{
		p=G.Vex[i].FirstArc;
		while(p!=nullptr)
		{
			G.Vex[p->AdjVex].In_degree++;
			p=p->Next;
		}
	}

}



void Print_message()
{
	printf("ѧ������ :  %d \t",G.mes->term_num);
	printf("ÿѧ�����ѧ�� �� %d \t",G.mes->max_credit);
	printf("���޿γ����� ��   %d \n",G.VexNum);

	cout << "\n\t\t\t��רҵ�ṩ�γ̣�\n";
	for(int i=0;i<G.VexNum;i++)		//ѭ����ͣ
	{	printf("______________________________________________________________________\n");
		printf("�γ̺ţ�C%d\t\tѧ�� �� %d\t\t���޿γ̣� ",i+1,G.Vex[i].credit);
		for (AdjVexNode* p = G.Vex[i].FirstArc; p!=nullptr; p = p->Next)
			printf("C%d  ",p->AdjVex+1);
		printf("\n");
	}

	cout << "\n\t\t\t\t������������˵�" <<endl;
	getch();
	system("cls");
	mainmenu();
}


void Adjust_message()
{
	printf("�����޸ĵ�������: 1.ѧ������  2.����ÿѧ�����ѧ�� ");
	printf("\n\n��ѡ��Ҫ�޸ĵ����� ,��������ȡ���޸�\n\n");
	char key=getch();
	key=key-'0';

	if(key==1)
	{	int term;
		printf("������ѧ��������");
		scanf("%d",&term);
		if(term > MaxTerm || term < 1)
		{
			cout << "\n�����ѧ�������Ϸ� (������������ѧ���� �� С��1 �� ����������)\n" <<endl;
			cout<< "�밴����������˵�"<< endl;
			getch();
			system("cls");
			mainmenu();
		}
		G.mes->term_num=term;
		cout << "\n�޸ĳɹ�\n" <<endl;
		cout << "������������˵�" <<endl;
		File_Update();
		getch();
	}
	else if(key==2)
	{
		int credit;
		printf("���������ÿѧ�����ѧ�֣�");
		scanf("%d",&credit);
		if( credit < 1 || credit > MaxCredit)
		{
			cout << "\n�����ѧ�������Ϸ� (С��1�����30)\n" <<endl;
			cout<< "�밴����������˵�"<< endl;
			getch();
			system("cls");
			mainmenu();
		}

		G.mes->max_credit=credit;
		cout << "\n�޸ĳɹ�\n" <<endl;
		cout << "������������˵�" <<endl;
		File_Update();
		getch();
	}

		system("cls");
		mainmenu();

}



void File_Update()
{
	ofstream ofs;
	ofs.open("./����.txt",ios::in | ios::out | ios::binary);

	ofs << G.mes->term_num << " "<< G.mes->max_credit << " " << G.VexNum << "\n" ;
	ofs.close();
}


void Arrange_Selete(int choice)
{
	Top_Sort(result1,0);
	Top_Sort(result2,1);
	Top_Sort(result3,2);
	Top_Sort(result4,3);
	Print_Top_Sort_Result();
	cout << "\n\n\n��������ѡ��Ŀγ̰����Ⱥ�˳��";
	char key=getch();

	if(key=='1')
		Arrange(result1,choice);
	else if(key=='2')
		Arrange(result2,choice);
	else if(key=='3')
		Arrange(result3,choice);
	else if(key=='4')
		Arrange(result4,choice);

	else
	{
		cout<<"ѡ�������밴����������˵�";
		getch();
		mainmenu();
	}

}


void Arrange(VexNode *result,int choice)
{
	system("cls");
	FILE *fp=fopen("./��ѧ�ڿγ̰��Ž��.txt","w");
	int i=0,j,k,course_num,per_max_num,Sumcredit,tag;

	if(choice==0)
		per_max_num=G.VexNum;
	else
	{	if(G.VexNum % G.mes->term_num == 0 || G.VexNum % G.mes->term_num <  G.mes->term_num/2 )
			per_max_num = G.VexNum/G.mes->term_num;
		else
			per_max_num = (G.VexNum/G.mes->term_num+1);
	}

	VexNode this_term_courses[G.VexNum];
	AdjVexNode* p;
	for(k=0;k<G.VexNum;k++)
	{
		if(i==G.VexNum)	break;

		fprintf(fp, "\n��%d��ѧ�ڵĿγ�Ϊ��", k+1);
		printf("\n��%d��ѧ�ڵĿγ�Ϊ��", k + 1);
		Sumcredit=0;       //��ѧ�ڰ��ſγ̵���ѧ��
		course_num=0;	 //��ѧ�ڰ��ſγ̵�����
		p=result[i].FirstArc;  //���޿�ָ��
		tag=0;          //��־��ѧ���Ƿ��иÿγ̵����޿γ�
		while(Sumcredit + result[i].credit <= G.mes->max_credit  && tag==0 && course_num<per_max_num)
		{
			while(p!=nullptr && tag==0)
			{
				for(j=0;j<course_num;j++)
				{
					if(p->AdjVex == Locate(this_term_courses[j].data) )
					{
						tag=1;
						break;
					}
				}
				p=p->Next;
			}

			if(tag==1) break;

			fprintf(fp, " %s ", result[i].data);
			printf( " %s ", result[i].data);
			Sumcredit+=result[i].credit;
			this_term_courses[course_num]=result[i];
			if(i==G.VexNum)	break;
			i++;
			course_num++;
			p=result[i].FirstArc;
		}

	}

	fclose(fp);

	if(k>G.mes->term_num)
	{
		fp=fopen("./��ѧ�ڿγ̰��Ž��.txt","w");
		fprintf(fp,"%s","�ÿγ̰����Ⱥ�˳���£��˲����޽�,��Ϊ��������ѧ�����������ѧ����");
		fclose(fp);
		cout << "\n\n\n�ÿγ̰����Ⱥ�˳���£��˲����޽�,��Ϊ��������ѧ�����������ѧ����\n\n\n";
		cout <<"�밴����������˵�" <<endl;
		getch();
		system("cls");
		mainmenu();
	}

	cout << "\n\n\n �γ̰�����Ϣ�Ѿ����뵱ǰĿ¼�£�����ѧ�ڿγ̰��Ž��.txt�� \n\n�밴����������˵�";
	getch();
	system("cls");
	mainmenu();

}




void Top_Sort(VexNode* result,int choice)
{
	int tag=0,i;
	AdjVexNode *  p;
	stack<VexNode> S;
	stack <AdjVexNode*> S1;
	Read_file();
	if(choice==0)

		while(tag==0)
		{
			tag=1;
			for(i=G.VexNum-1;i>=0;i--)
				if(G.Vex[i].In_degree==0)
				{
					S.push(G.Vex[i]);
					G.Vex[i].In_degree--;
					p=G.Vex[i].FirstArc;
					S1.push(p);
					tag=0;
				}

			while(S1.empty()==false)
			{	p=S1.top();
				S1.pop();

				while(p!=nullptr)
				{
					G.Vex[p->AdjVex].In_degree--;
					p=p->Next;
				}
			}
		}



	else if(choice==1)

		while(tag==0)
		{
			tag=1;
			for(i=0;i<G.VexNum;i++)
				if(G.Vex[i].In_degree==0)
				{
					S.push(G.Vex[i]);
					G.Vex[i].In_degree--;
					p=G.Vex[i].FirstArc;
					S1.push(p);
					tag=0;
				}

			while(S1.empty()==false)
			{	p=S1.top();
				S1.pop();

				while(p!=nullptr)
				{
					G.Vex[p->AdjVex].In_degree--;
					p=p->Next;
				}
			}
		}



	else if(choice==2)

		for(i=G.VexNum-1;i>=0;i--)
		{
			if(G.Vex[i].In_degree==0)
			{
				S.push(G.Vex[i]);
				G.Vex[i].In_degree--;
				p=G.Vex[i].FirstArc;
				while(p!=nullptr)
				{
					G.Vex[p->AdjVex].In_degree--;
					p=p->Next;
				}

				i=G.VexNum-1;
			}
		}



	else

		for(i=0;i<G.VexNum;i++)
		{
			if(G.Vex[i].In_degree==0)
			{
				S.push(G.Vex[i]);
				G.Vex[i].In_degree--;
				p=G.Vex[i].FirstArc;
				while(p!=nullptr)
				{
					G.Vex[p->AdjVex].In_degree--;
					p=p->Next;
				}

				i=-1;
			}
		}




	i=S.size();

	if(i <G.VexNum)
	{
		cout<< "��������ʧ�ܣ��γ����޹�ϵ���ܴ��ڻ�·���밴����������˵�\n";
		getch();
		system("cls");
		mainmenu();
	}

	for(i=0;i<G.VexNum;i++)
	{
		if(S.empty()==false)
		{
			result[i]=S.top();
			S.pop();
		}
		else
		{
			cout << "��������ջʧ��,�밴����������˵�" << endl;
			getch();
			mainmenu();
		}

	}
}



void Print_Top_Sort_Result()
{
	printf("���γ̰����Ⱥ�˳��Ϊ:\n");
	cout << "ѡ��1��" ;
	for(int i=0;i<G.VexNum;i++)
	{
		cout<< result1[i].data<< "  " ;
	}

	cout << "\n\nѡ��2��" ;
	for(int i=0;i<G.VexNum;i++)
	{
		cout<< result2[i].data<< "  " ;
	}

	cout << "\n\nѡ��3��" ;
	for(int i=0;i<G.VexNum;i++)
	{
		cout<< result3[i].data<< "  " ;
	}

	cout << "\n\nѡ��4��" ;
	for(int i=0;i<G.VexNum;i++)
	{
		cout<< result4[i].data<< "  " ;
	}

}


