#define MaxWidth 40
#define MaxSize 30
int m = MaxSize;
typedef char datatype; 
typedef struct treenode
{
	datatype name[10];
	struct treenode *left_child,*right_sibling;
} *BTree;
//name对应的树
BTree find_own(BTree p,char own_name[])
{
	BTree bt;
	if(p==NULL) //根树不为空
		return(NULL);
	else
	{
		if(strcmp(p->name,own_name)==0)
			return(p);
		else
		{
			bt=find_own(p->left_child,own_name);

			if(bt!=NULL) 
				return(bt);
			else 
				return(find_own(p->right_sibling,own_name));
		}
	}
}
// 通过儿子找父亲（由上到下遍历树）xm当为第一个根点时，返回的是第一课树
BTree find_father(BTree p,char kid_name[])
{
	BTree bt; //存子节点
	p;//存父节点
	if(p==NULL) 
		return(NULL);
	else
	{
		bt=p->left_child;//暂时进入下一层
		if(bt!=NULL)
		{
			do
			{
				if(strcmp(bt->name,kid_name)==0)
					return(p);
				bt=bt->right_sibling;
			}while(bt!=NULL);
		}
		bt=find_father(p->left_child,kid_name);// 变量进入下一层
		if(bt!=NULL) // 触底反弹
			return(bt);
		else 
			return(find_father(p->right_sibling,kid_name));
	}
}
//找到链接自身的前一位，并返回链接他的树
BTree find_prirc(BTree father,BTree own)
{
	 BTree g;
	 if(father->left_child==own)//找链接他的树，为第一课子树
		return(father);
	else
	{
		g=father->left_child;
		while(g->right_sibling!=own)//找链接他的树
			  g=g->right_sibling;
		return(g);
	}
}
//树找到链接子树节点的位置，并返回(返回树与输入树相同时，其链接位是left_child,不同则是返回树的right_sibling)
BTree find_kid_NULL(BTree own)
{
	BTree g; //过度变量
	g=own->left_child;
	if(g==NULL)
		return(own);
	else
	{
		while(g->right_sibling!=NULL)
			g=g->right_sibling;
		return(g);
	}		
}
//链接树（添加）
void add_data(BTree father,BTree son)
{
	if(father!=NULL&&son!=NULL)
	{
		BTree l;//储存返回的链接位置
		l=find_kid_NULL(father);
		if(l==father)
			l->left_child=son;
		else
			l->right_sibling=son;
	}
}
//界面
int interface()
{
	int xz;
    printf("\t------------------------ - - -\n");
	printf("\t+家谱(树)管理（作者：曾俊宇）+\n");
	printf("\t------------------------ - - -\n");
	printf("\t******************************\n");
	printf("\t   1.添加成员                 \n");
	printf("\t   2.找父亲                   \n");
	printf("\t   3.找儿子                   \n");
	printf("\t   4.删除                     \n");
	printf("\t   5.改名字                   \n");
	printf("\t   6.过继                     \n");
	printf("\t   7:退出系统                 \n");
	printf("\t******************************\n");
	printf("请输入你的选择：");
	scanf("%d",&xz);
	return(xz);
}
//建树
BTree creatree(BTree btree)
{
	int contin=1;  //first是判断树是不是从根节点建立的变量
	char father_name[10];
	BTree father,son;
	while(contin)
	{
		int n;
		if(btree==NULL) //first==1表示為根節點
		{
			printf("\n建立一个家谱树（父亲为空格结束添加)：\n");
			btree=(BTree)malloc(sizeof(struct treenode));  //malloc是分配內存
			printf("\t家谱第一人姓名：");
			gets(btree->name);
			btree->right_sibling=btree->left_child=NULL;
		}
		else
		{
			printf("\n添加一个家族成员（父亲为空格结束添加)：\n");
			printf("\t输入你要添加成员的父亲和姓名\n");
			printf("\t父亲：");
 			gets(father_name);
			if(strcmp(father_name," ")==0)
				contin=0;
			else
			{	
				father=find_own(btree,father_name);//找到父树
				if(father==NULL)//判断父亲是否存在
				{
					printf("不存在这样的父结点！\n");
					continue;
				}
					son=(BTree)malloc(sizeof(struct treenode));//分配空间创建一颗树，储存信息
					son->right_sibling=son->left_child=NULL;
					printf("\t姓名：");
					gets(son->name);
					add_data(father,son);//添加族人
			}	
		}
	}
    return(btree);	
}
//显示树
void disptree(BTree BT)
{	
	BTree bt;
	if(BT!=NULL)
	{
		for(int i=1;i<=m;i++)
			printf("━");
		printf("%s",BT->name);
		printf("\n");
		m--;
		bt=BT->left_child;
		disptree(bt);
		m++;
		if((BT->right_sibling)!=NULL)
		{
			bt=BT->right_sibling;
			disptree(bt);
		}
	}
}
//找儿子
void findson(BTree bt)
{
	char xm[10];
	BTree p;
	printf("\n查找指定父亲的所有儿子\n");
	printf("父亲：");
	gets(xm);
	p=find_own(bt,xm);
	if(p==NULL)
		printf("不存在%s的父亲！\n",xm);
	else
	{
		p=p->left_child;
		if(p==NULL)
			printf("%s没有儿子!\n",xm);
		else
		{
			printf("%s有以下儿子!\n\t",xm);
			while(p!=NULL)
			{
				printf("%8s  ",p->name);
				p=p->right_sibling;
			}
		}
	}
}
//通过儿子找父亲
void findFatherInSon(BTree BT)
{
	char xm[10];
	BTree p;  //储存找到的父亲
	printf("\n查找指定儿子的父亲\n");
	printf("儿子：");
	gets(xm);
	p=find_father(BT,xm);
	if(p==NULL||strcmp((BT->name),xm)==0)//xm当为第一个根点时，返回的是第一课树
		printf("%s没有父亲!\n",xm);
	else
	{
		printf("%s的父亲!\n\t",xm);
		printf("%8s  ",p->name);
	}
}
//删除
void del_data(BTree BT)
{
	int i=0;// 确定是第几个儿子
	char del_name[10];
	BTree del;//储存要删除的节点
	BTree prirc; //储存要删除的链接树
	BTree father; //储存要删除的父节点
huishu:
	printf("逐出家门的名字：");
	gets(del_name);
	if(strcmp(del_name,BT->name)==0)
	{
		printf("不可以把老祖宗逐出家门,请重新输入");	
		goto huishu;
	}
	del=find_own(BT,del_name);//找到自己
	father=find_father(BT,del_name);//找到父树
	prirc=find_prirc(father,del);//找到链接它的树
	if(prirc==father)//删除的树是第一个儿子
	{
		add_data(del->right_sibling,del->left_child);//过继
		prirc->left_child=del->right_sibling;//跨过删除人	
	}
	else
	{
		add_data(prirc,del->left_child);//过继
		prirc->right_sibling=del->right_sibling;//跨过删除人
	}	
}
//改姓名
void alter_name(BTree BT)
{
	BTree own;
	char name[10];
	printf("\n请输入你要修改的姓名：");
	gets(name);
	own=find_own(BT,name);//找到人
	printf("\n请输入你要修改的姓名：");
	gets(own->name);
}
//过继
void alter_son(BTree BT)
{
	BTree own,father_o,father_n,prirc;
	char son_name[10],father_n_name[10];
	printf("请输入你要过继人的姓名：");
	gets(son_name);	
	printf("请输入你要过继到谁的名下：");
	gets(father_n_name);
	own=find_own(BT,son_name);//找到要过继的人
	father_n=find_own(BT,father_n_name);//找到过继到哪	
	father_o=find_father(BT,son_name);//找到过继人原来的父亲
	prirc=find_prirc(father_o,own);//链接过继人的链接点
	if(prirc==father_o)//删除的树是第一个儿子
		prirc->left_child=own->right_sibling;//跨过删除人
	else
		prirc->right_sibling=own->right_sibling;//跨过删除人
	if(find_father(BT,father_n_name)==NULL)//如果是同一直系亲属，老辈过继给后辈（老爹过继给儿子），这样会形成循环树，而脱离主树
	{  
    printf("同一直系亲属，不可以老辈过继给后辈！！！！\n");
	if(prirc==father_o)//删除的树是第一个儿子
		prirc->left_child=own;//链接回删除的人
	else
		prirc->right_sibling=own;//链接回删除的人   	 
	}	
	else
	{
		own->right_sibling=NULL;//斩断被驱逐人与兄弟的联系，不然会带着兄弟一起，过继
		add_data(father_n,own);//把人过继过去（添加过去），应该最后加（因为其会改变树的结构）
	}
}
//读取文件
BTree read_data()
{
	FILE *f=fopen("家谱.txt","r");
	BTree btree,s1,father;//根
	char s2[10];//存父亲名字
	btree=(BTree)malloc(sizeof(struct treenode));  //malloc是分配內存
	fread(btree->name,sizeof(btree->name),1,f);
	fclose(f);
	btree->right_sibling=btree->left_child=NULL;

	FILE *p=fopen("家谱.txt","r");
	s1=(BTree)malloc(sizeof(struct treenode));//分配空间创建一颗树，储存信息
	    s1->right_sibling=s1->left_child=NULL;
		fread(s2,sizeof(btree->name),1,p);
		father=find_own(btree,s2);
		fread(s1->name,sizeof(btree->name),1,p);
	while(!feof(p))
	{
		add_data(father,s1);//添加族人
		s1=(BTree)malloc(sizeof(struct treenode));//分配空间创建一颗树，储存信息
	    s1->right_sibling=s1->left_child=NULL;
		fread(s2,sizeof(btree->name),1,p);
		father=find_own(btree,s2);
		fread(s1->name,sizeof(btree->name),1,p);
	}
	fclose(p);//!feof(p)判断到文件结尾，会给多付一个值,以上方法已解决
	return(btree);
}
//保存文件
void write(BTree BT)
{
	BTree g;
	if(BT!=NULL)
	{
		
		if(BT->left_child!=NULL)
		{
			FILE *p=fopen("家谱.txt","a");
			fwrite(BT->name,sizeof(g->name),1,p);
			fwrite((BT->left_child)->name,sizeof(g->name),1,p);
			g=BT->left_child;
			while(g->right_sibling!=NULL)
			{
				g=g->right_sibling;
				fwrite(BT->name,sizeof(g->name),1,p);
				fwrite(g->name,sizeof(g->name),1,p);
				
			}
			fclose(p);
		    write(BT->left_child);
		 
		}
		write(BT->right_sibling);	
	}
	
}