#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jiapu.h"
void main()
{
	BTree btree=NULL;//������ڵ�
	// btree=(BTree)malloc(sizeof(struct treenode));  //malloc�Ƿ���ȴ�
	// btree->right_sibling=btree->left_child=NULL;
	int xz;
	do
	{
		char ch;
		FILE *t=fopen("����.txt","r");
		ch=fgetc(t);
		fclose(t);
		if(ch!=-1)//�ж��ļ��Ƿ�Ϊ��
		{
			 btree=read_data();
			 printf("\n\n\n\t����ͼ\n");
			 disptree(btree);
		}
		xz=interface();
		//���������������
		fflush(stdin);
	    if(ch==-1&&xz!=7)
		{
			printf("����Ϊ�գ��������\n");
			xz=1;
		}
		switch(xz)
		{
		case 1:
			btree=creatree(btree);
			break;
		case 2:
			findFatherInSon(btree);
			break;
		case 3:
				findson(btree);
			break;
		case 4:
			del_data(btree);
			break;
		case 5:
			alter_name(btree);
			break;
		case 6:
			alter_son(btree);
			break;
		}
		if(btree!=NULL)
		{
		   FILE *p=fopen("����.txt","w");
		   fclose(p);//����ļ�
		   write(btree);
		}
	}while(xz!=7);
}
