#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jiapu.h"
void main()
{
	BTree btree=NULL;//储存根节点
	// btree=(BTree)malloc(sizeof(struct treenode));  //malloc是分配內存
	// btree->right_sibling=btree->left_child=NULL;
	int xz;
	do
	{
		char ch;
		FILE *t=fopen("家谱.txt","r");
		ch=fgetc(t);
		fclose(t);
		if(ch!=-1)//判断文件是否为空
		{
			 btree=read_data();
			 printf("\n\n\n\t家谱图\n");
			 disptree(btree);
		}
		xz=interface();
		//清除缓存区的内容
		fflush(stdin);
	    if(ch==-1&&xz!=7)
		{
			printf("家谱为空，请先添加\n");
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
		   FILE *p=fopen("家谱.txt","w");
		   fclose(p);//清空文件
		   write(btree);
		}
	}while(xz!=7);
}
