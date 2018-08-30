#define MaxWidth 40
#define MaxSize 30
int m = MaxSize;
typedef char datatype; 
typedef struct treenode
{
	datatype name[10];
	struct treenode *left_child,*right_sibling;
} *BTree;
//name��Ӧ����
BTree find_own(BTree p,char own_name[])
{
	BTree bt;
	if(p==NULL) //������Ϊ��
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
// ͨ�������Ҹ��ף����ϵ��±�������xm��Ϊ��һ������ʱ�����ص��ǵ�һ����
BTree find_father(BTree p,char kid_name[])
{
	BTree bt; //���ӽڵ�
	p;//�游�ڵ�
	if(p==NULL) 
		return(NULL);
	else
	{
		bt=p->left_child;//��ʱ������һ��
		if(bt!=NULL)
		{
			do
			{
				if(strcmp(bt->name,kid_name)==0)
					return(p);
				bt=bt->right_sibling;
			}while(bt!=NULL);
		}
		bt=find_father(p->left_child,kid_name);// ����������һ��
		if(bt!=NULL) // ���׷���
			return(bt);
		else 
			return(find_father(p->right_sibling,kid_name));
	}
}
//�ҵ����������ǰһλ������������������
BTree find_prirc(BTree father,BTree own)
{
	 BTree g;
	 if(father->left_child==own)//��������������Ϊ��һ������
		return(father);
	else
	{
		g=father->left_child;
		while(g->right_sibling!=own)//������������
			  g=g->right_sibling;
		return(g);
	}
}
//���ҵ����������ڵ��λ�ã�������(����������������ͬʱ��������λ��left_child,��ͬ���Ƿ�������right_sibling)
BTree find_kid_NULL(BTree own)
{
	BTree g; //���ȱ���
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
//����������ӣ�
void add_data(BTree father,BTree son)
{
	if(father!=NULL&&son!=NULL)
	{
		BTree l;//���淵�ص�����λ��
		l=find_kid_NULL(father);
		if(l==father)
			l->left_child=son;
		else
			l->right_sibling=son;
	}
}
//����
int interface()
{
	int xz;
    printf("\t------------------------ - - -\n");
	printf("\t+����(��)�������ߣ������+\n");
	printf("\t------------------------ - - -\n");
	printf("\t******************************\n");
	printf("\t   1.��ӳ�Ա                 \n");
	printf("\t   2.�Ҹ���                   \n");
	printf("\t   3.�Ҷ���                   \n");
	printf("\t   4.ɾ��                     \n");
	printf("\t   5.������                   \n");
	printf("\t   6.����                     \n");
	printf("\t   7:�˳�ϵͳ                 \n");
	printf("\t******************************\n");
	printf("���������ѡ��");
	scanf("%d",&xz);
	return(xz);
}
//����
BTree creatree(BTree btree)
{
	int contin=1;  //first���ж����ǲ��ǴӸ��ڵ㽨���ı���
	char father_name[10];
	BTree father,son;
	while(contin)
	{
		int n;
		if(btree==NULL) //first==1��ʾ������c
		{
			printf("\n����һ��������������Ϊ�ո�������)��\n");
			btree=(BTree)malloc(sizeof(struct treenode));  //malloc�Ƿ���ȴ�
			printf("\t���׵�һ��������");
			gets(btree->name);
			btree->right_sibling=btree->left_child=NULL;
		}
		else
		{
			printf("\n���һ�������Ա������Ϊ�ո�������)��\n");
			printf("\t������Ҫ��ӳ�Ա�ĸ��׺�����\n");
			printf("\t���ף�");
 			gets(father_name);
			if(strcmp(father_name," ")==0)
				contin=0;
			else
			{	
				father=find_own(btree,father_name);//�ҵ�����
				if(father==NULL)//�жϸ����Ƿ����
				{
					printf("�����������ĸ���㣡\n");
					continue;
				}
					son=(BTree)malloc(sizeof(struct treenode));//����ռ䴴��һ������������Ϣ
					son->right_sibling=son->left_child=NULL;
					printf("\t������");
					gets(son->name);
					add_data(father,son);//�������
			}	
		}
	}
    return(btree);	
}
//��ʾ��
void disptree(BTree BT)
{	
	BTree bt;
	if(BT!=NULL)
	{
		for(int i=1;i<=m;i++)
			printf("��");
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
//�Ҷ���
void findson(BTree bt)
{
	char xm[10];
	BTree p;
	printf("\n����ָ�����׵����ж���\n");
	printf("���ף�");
	gets(xm);
	p=find_own(bt,xm);
	if(p==NULL)
		printf("������%s�ĸ��ף�\n",xm);
	else
	{
		p=p->left_child;
		if(p==NULL)
			printf("%sû�ж���!\n",xm);
		else
		{
			printf("%s�����¶���!\n\t",xm);
			while(p!=NULL)
			{
				printf("%8s  ",p->name);
				p=p->right_sibling;
			}
		}
	}
}
//ͨ�������Ҹ���
void findFatherInSon(BTree BT)
{
	char xm[10];
	BTree p;  //�����ҵ��ĸ���
	printf("\n����ָ�����ӵĸ���\n");
	printf("���ӣ�");
	gets(xm);
	p=find_father(BT,xm);
	if(p==NULL||strcmp((BT->name),xm)==0)//xm��Ϊ��һ������ʱ�����ص��ǵ�һ����
		printf("%sû�и���!\n",xm);
	else
	{
		printf("%s�ĸ���!\n\t",xm);
		printf("%8s  ",p->name);
	}
}
//ɾ��
void del_data(BTree BT)
{
	int i=0;// ȷ���ǵڼ�������
	char del_name[10];
	BTree del;//����Ҫɾ���Ľڵ�
	BTree prirc; //����Ҫɾ����������
	BTree father; //����Ҫɾ���ĸ��ڵ�
huishu:
	printf("������ŵ����֣�");
	gets(del_name);
	if(strcmp(del_name,BT->name)==0)
	{
		printf("�����԰��������������,����������");	
		goto huishu;
	}
	del=find_own(BT,del_name);//�ҵ��Լ�
	father=find_father(BT,del_name);//�ҵ�����
	prirc=find_prirc(father,del);//�ҵ�����������
	if(prirc==father)//ɾ�������ǵ�һ������
	{
		add_data(del->right_sibling,del->left_child);//����
		prirc->left_child=del->right_sibling;//���ɾ����	
	}
	else
	{
		add_data(prirc,del->left_child);//����
		prirc->right_sibling=del->right_sibling;//���ɾ����
	}	
}
//������
void alter_name(BTree BT)
{
	BTree own;
	char name[10];
	printf("\n��������Ҫ�޸ĵ�������");
	gets(name);
	own=find_own(BT,name);//�ҵ���
	printf("\n��������Ҫ�޸ĵ�������");
	gets(own->name);
}
//����
void alter_son(BTree BT)
{
	BTree own,father_o,father_n,prirc;
	char son_name[10],father_n_name[10];
	printf("��������Ҫ�����˵�������");
	gets(son_name);	
	printf("��������Ҫ���̵�˭�����£�");
	gets(father_n_name);
	own=find_own(BT,son_name);//�ҵ�Ҫ���̵���
	father_n=find_own(BT,father_n_name);//�ҵ����̵���	
	father_o=find_father(BT,son_name);//�ҵ�������ԭ���ĸ���
	prirc=find_prirc(father_o,own);//���ӹ����˵����ӵ�
	if(prirc==father_o)//ɾ�������ǵ�һ������
		prirc->left_child=own->right_sibling;//���ɾ����
	else
		prirc->right_sibling=own->right_sibling;//���ɾ����
	if(find_father(BT,father_n_name)==NULL)//�����ͬһֱϵ�������ϱ����̸��󱲣��ϵ����̸����ӣ����������γ�ѭ����������������
	{  
    printf("ͬһֱϵ�������������ϱ����̸��󱲣�������\n");
	if(prirc==father_o)//ɾ�������ǵ�һ������
		prirc->left_child=own;//���ӻ�ɾ������
	else
		prirc->right_sibling=own;//���ӻ�ɾ������   	 
	}	
	else
	{
		own->right_sibling=NULL;//ն�ϱ����������ֵܵ���ϵ����Ȼ������ֵ�һ�𣬹���
		add_data(father_n,own);//���˹��̹�ȥ����ӹ�ȥ����Ӧ�����ӣ���Ϊ���ı����Ľṹ��
	}
}
//��ȡ�ļ�
BTree read_data()
{
	FILE *f=fopen("����.txt","r");
	BTree btree,s1,father;//��
	char s2[10];//�游������
	btree=(BTree)malloc(sizeof(struct treenode));  //malloc�Ƿ���ȴ�
	fread(btree->name,sizeof(btree->name),1,f);
	fclose(f);
	btree->right_sibling=btree->left_child=NULL;

	FILE *p=fopen("����.txt","r");
	s1=(BTree)malloc(sizeof(struct treenode));//����ռ䴴��һ������������Ϣ
	    s1->right_sibling=s1->left_child=NULL;
		fread(s2,sizeof(btree->name),1,p);
		father=find_own(btree,s2);
		fread(s1->name,sizeof(btree->name),1,p);
	while(!feof(p))
	{
		add_data(father,s1);//�������
		s1=(BTree)malloc(sizeof(struct treenode));//����ռ䴴��һ������������Ϣ
	    s1->right_sibling=s1->left_child=NULL;
		fread(s2,sizeof(btree->name),1,p);
		father=find_own(btree,s2);
		fread(s1->name,sizeof(btree->name),1,p);
	}
	fclose(p);//!feof(p)�жϵ��ļ���β������ึһ��ֵ,���Ϸ����ѽ��
	return(btree);
}
//�����ļ�
void write(BTree BT)
{
	BTree g;
	if(BT!=NULL)
	{
		
		if(BT->left_child!=NULL)
		{
			FILE *p=fopen("����.txt","a");
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