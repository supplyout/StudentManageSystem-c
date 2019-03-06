#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX_LEN 10//������ֳ���
#define STU_NUM 30//����ѧ������
#define COURSE_NUM 6//���Ŀγ���
//����ѧ����Ϣ�ṹ��
typedef struct student
{
    long number;
    char name[MAX_LEN];
    float score[COURSE_NUM];
    float sum;
    float aver;
    struct student *next;
}STU;
STU *ReadScore(int stu_num,int course_num);
void Connect(STU *studentpt[],STU *head,int stu_num,int course_num);
void AverSumofEveryStudent(STU *studentpt[],STU *head,int stu_num,int course_num);
void AverSumofEveryCourse(STU *studentpt[],STU *head,int stu_num,int course_num,float sumofcourse[],float averofcourse[]);
void SortByName(STU *studentpt[],STU *head,int stu_num,int course_num);
void SortByNum(STU *studentpt[],int stu_num,int low,int high);
void SortByScoreUP(STU *studentpt[],STU *head,int stu_num,int course_num);
void SortByScoreDOWN(STU *studentpt[],STU *head,int stu_num,int course_num);
void SearchByName(STU *studentpt[],STU *head,int stu_num,int course_num);
void SearchByNum(STU *studentpt[],STU *head,int stu_num,int course_num);
void StatisticAnalysis(STU *studentpt[],STU *head,int stu_num,int course_num);
void Print(STU *studentpt[],STU *head,int stu_num,int course_num);
char Menu(void);
void SaveToFile(STU *studentpt[],STU *head,int stu_num,int course_num);
void ReadFromFile(STU *studentpt[],STU *head,int stu_num,int course_num);
int option[12]={0};
void Print(STU *studentpt[],STU *head,int stu_num,int course_num)
{
    //�������ܣ���ӡѧ����Ϣ
    //����������
    //STU *studentpt[]:ָ�����ѧ����Ϣ�����ָ������
    //STU *head:����ͷָ��
    //int stu_num:�����ѧ������
    //int course_num:����Ŀγ�����
    //��������ֵ����
    int i,j;
    printf("����\tѧ��\t");
    for(i=0;i<course_num;i++)
        printf("��%d�ſ�\t",i+1);
    printf("�ܷ�\n");
    for(i=0;i<stu_num;i++)
    {
        printf("%s\t%ld\t",studentpt[i]->name,studentpt[i]->number);
        for(j=0;j<course_num;j++)
        {
            printf("%.2f\t",studentpt[i]->score[j]);
        }
        printf("%.2f\n",studentpt[i]->sum);
    }
}
char Menu(void)
{
    //�������ܣ���ӡ�˵��������û�ѡ��Ĳ�����
    //������������
    //��������ֵ�����ز�����
    int opt;
    int flag;
    printf("\n");
    printf("ѧ���ɼ�����ϵͳ\n");
    printf("1.����ɼ�\n");
    printf("2.����ÿ�ſ��ܳɼ���ƽ���ɼ�\n");
    printf("3.����ÿ��ѧ���ܳɼ���ƽ���ɼ�\n");
    printf("4.����ѧ���ܳɼ���������\n");
    printf("5.����ѧ���ܳɼ���������\n");
    printf("6.����ѧ������\n");
    printf("7.������������\n");
    printf("8.ͨ����������\n");
    printf("9.ͨ��ѧ�Ų���\n");
    printf("10.�ɼ�����\n");
    printf("11.���ɼ����浽�ļ�\n");
    printf("12.���ļ���ȡ�ɼ�\n");
    printf("0.�˳�ϵͳ\n");
    printf("�������Ӧ�����룺");
    fflush(stdin);
        flag=scanf("%d",&opt);
        if(flag==1||flag==2)
            return opt;
        else
            return -1;


}
STU *ReadScore(int stu_num,int course_num)
{
    //�������ܣ�����ѧ����Ϣ
    //����������
    //int stu_num:�����ѧ������
    //int course_num:����Ŀγ�����
    //��������ֵ�����������ͷָ��
    STU *pt,*prept,*head;
    int i,j;
    int count1=0,count2=0,flag=0;
    pt=(STU*)malloc(sizeof(STU));
    do
    {
        if(pt!=NULL)
        {
            count1=0;
            count2=0;
            printf("�밴˳�������%d��ѧ����ѧ�š��������ɼ����Կո�Ϊ���������\n",1);
            fflush(stdin);
            count1=scanf("%ld%s",&pt->number,pt->name);
            for(j=0;j<course_num;j++)
            {
                flag=scanf("%f",&pt->score[j]);
                count2+=flag;
            }
            printf("\n");
            head=pt;
            prept=pt;
        }
        else
        {
            printf("Error!");
            exit(0);
        }
    }while(count1!=2||count2!=course_num);
    for(i=1;i<stu_num;i++)
    {
        pt=(STU*)malloc(sizeof(STU));
        do
        {
            count1=0;
            count2=0;
            if(pt!=NULL)
            {
                printf("�밴˳�������%d��ѧ����ѧ�š��������ɼ����Կո�Ϊ���������\n",i+1);
                fflush(stdin);
                count1=scanf("%ld%s",&pt->number,pt->name);
                for(j=0;j<course_num;j++)
                {
                    flag=0;
                    flag=scanf("%f",&pt->score[j]);
                    count2+=flag;
                }
                printf("\n");
                prept->next=pt;
                prept=pt;
            }
            else
            {
                printf("Error!");
                exit(0);
            }
        }while(count1!=2||count2!=course_num);
    }
    fflush(stdin);
    prept->next=NULL;
    return head;

}
void Connect(STU *studentpt[],STU *head,int stu_num,int course_num)
{
    //�������ܣ���ѧ����ָ������ֱ�ָ��ÿ��ѧ������Ϣ��������һ������
    //����������
    //STU *studentpt[]:ָ�����ѧ����Ϣ�����ָ������
    //STU *head:����ͷָ��
    //int stu_num:�����ѧ������
    //int course_num:����Ŀγ�����
    //��������ֵ����
    STU *pt=head;
    studentpt[0]=head;
   // printf("ָ�����鱣��ĵ�ַ%d\n",studentpt[0]);
    int i=1;
    while(pt!=NULL)
    {
        studentpt[i]=pt->next;
        //printf("ָ�����鱣��ĵ�ַ%d\n",studentpt[i]);
        pt=pt->next;
        i++;
    }

}
void AverSumofEveryStudent(STU *studentpt[],STU *head,int stu_num,int course_num)
{
    //�������ܣ�����ÿ��ѧ���ĵ��ܳɼ���ƽ���ɼ�
    //����������
    //STU *studentpt[]:ָ�����ѧ����Ϣ�����ָ������
    //STU *head:����ͷָ��
    //int stu_num:�����ѧ������
    //int course_num:����Ŀγ�����
    //��������ֵ����
    int i,j;
    for(i=0;i<stu_num;i++)
    {
        studentpt[i]->sum=0;
    }
    for(i=0;i<stu_num;i++)
    {
        for(j=0;j<course_num;j++)
            studentpt[i]->sum+=studentpt[i]->score[j];//��ÿ��ѧ���ܳɼ�
        printf("��%d��ѧ���ܳɼ���%.2f ",i+1,studentpt[i]->sum);
        studentpt[i]->aver=studentpt[i]->sum/course_num;
        printf("��%d��ѧ��ƽ����%.2f\n",i+1,studentpt[i]->aver);
    }

}
void AverSumofEveryCourse(STU *studentpt[],STU *head,int stu_num,int course_num,float sumofcourse[],float averofcourse[])
{
    //�������ܣ�����γ̵��ܳɼ���ƽ���ɼ�
    //����������
    //STU *studentpt[]:ָ�����ѧ����Ϣ�����ָ������
    //STU *head:����ͷָ��
    //int stu_num:�����ѧ������
    //int course_num:����Ŀγ�����
    //float sumofcourse[]:ÿһ���γ��ܳɼ�
    //float averofcourse[]:ÿһ���γ̵�ƽ���ɼ�
    //��������ֵ����
    int i,j;
    for(i=0;i<course_num;i++)
    {
        for(j=0;j<stu_num;j++)
        {
            sumofcourse[i]+=studentpt[j]->score[i];
        }
        printf("��%d�ſ��ܳɼ���%.2f\n",i+1,sumofcourse[i]);
        averofcourse[i]=sumofcourse[i]/stu_num;
        printf("��%d�ſ�ƽ���ɼ���%.2f\n",i+1,averofcourse[i]);
    }
}
void SortByName(STU *studentpt[],STU *head,int stu_num,int course_num)
{
    //�������ܣ�����ѧ����������
    //����������
    //STU *studentpt[]:ָ�����ѧ����Ϣ�����ָ������
    //STU *head:����ͷָ��
    //int stu_num:�����ѧ������
    //int course_num:����Ŀγ�����
    //��������ֵ����
    int i,j;
    STU *temp=NULL;
    for(i=0;i<stu_num-1;i++)
    {
        for(j=i+1;j<stu_num;j++)
        {
            if(strcmp(studentpt[i]->name,studentpt[j]->name)>0)
            {
                temp=studentpt[i];
                studentpt[i]=studentpt[j];
                studentpt[j]=temp;

            }
        }
    }
    Print(studentpt,head,stu_num,course_num);
}
void SortByNum(STU *studentpt[],int stu_num,int low,int high)
{
    //�������ܣ����ÿ��Ű���ѧ��ѧ������
    //����������
    //STU *studentpt[]:ָ�����ѧ����Ϣ�����ָ������
    //STU *head:����ͷָ��
    //int stu_num:�����ѧ������
    //int course_num:����Ŀγ�����
    //��������ֵ����
    int left=low,right=high;
    STU *temp;
    STU *temp1=studentpt[low];
    if(low>=high)
        return;
    while(left!=right)
        {
            while(left<right&&studentpt[right]->number>=temp1->number)
                right--;
            while(left<right&&studentpt[left]->number<=temp1->number)
                left++;
            if(left<right)
            {
                temp = studentpt[left];
                studentpt[left] = studentpt[right];
                studentpt[right] = temp;
            }

        }
        studentpt[low]=studentpt[left];
        studentpt[left]=temp1;
        SortByNum(studentpt,stu_num,low,left-1);
        SortByNum(studentpt,stu_num,left+1,high);
}
void SortByScoreUP(STU *studentpt[],STU *head,int stu_num,int course_num)
{
    //�������ܣ�����ѧ���ɼ�������������
    //����������
    //STU *studentpt[]:ָ�����ѧ����Ϣ�����ָ������
    //STU *head:����ͷָ��
    //int stu_num:�����ѧ������
    //int course_num:����Ŀγ�����
    //��������ֵ����
    int i,j;
    STU *temp=NULL;
    for(i=0;i<stu_num-1;i++)
    {
        for(j=i+1;j<stu_num;j++)
        {
            if(studentpt[i]->sum>studentpt[j]->sum)
            {
                temp=studentpt[i];
                studentpt[i]=studentpt[j];
                studentpt[j]=temp;

            }
        }
    }
    Print(studentpt,head,stu_num,course_num);
}
void SortByScoreDOWN(STU *studentpt[],STU *head,int stu_num,int course_num)
{
    //�������ܣ�����ѧ���ɼ���������
    //����������
    //STU *studentpt[]:ָ�����ѧ����Ϣ�����ָ������
    //STU *head:����ͷָ��
    //int stu_num:�����ѧ������
    //int course_num:����Ŀγ�����
    //��������ֵ����
    int i,j;
    STU *temp=NULL;
    for(i=0;i<stu_num-1;i++)
    {
        for(j=i+1;j<stu_num;j++)
        {
            if(studentpt[i]->sum<studentpt[j]->sum)
            {
                temp=studentpt[i];
                studentpt[i]=studentpt[j];
                studentpt[j]=temp;

            }
        }
    }
    Print(studentpt,head,stu_num,course_num);
}
void SearchByName(STU *studentpt[],STU *head,int stu_num,int course_num)
{
    //�������ܣ�����ѧ�����ֽ��в��ң�ʹ����ģ����ѯ�㷨
    //����������
    //STU *studentpt[]:ָ�����ѧ����Ϣ�����ָ������
    //STU *head:����ͷָ��
    //int stu_num:�����ѧ������
    //int course_num:����Ŀγ�����
    //��������ֵ����
    char inputname[MAX_LEN+1];
    int i,j;
    int m,count1=0,count2=0;
    int flag=0;
    printf("������Ҫ���ҵ�ѧ������������*����δ֪�ַ�����");
    getchar();
    gets(inputname);
    printf("����\tѧ��\t");
            for(j=0;j<course_num;j++)
                printf("��%d�ſ�\t",j+1);
            printf("�ܷ�\n");
    for(i=0;i<stu_num;i++)
    {
        count1=0;
        count2=0;
        for(m=0;inputname[m]!='\0';m++)
        {
            if(inputname[m]=='*')
            {
                count1++;
                continue;
            }
            if(inputname[m]==studentpt[i]->name[m])
            count2++;
        }
        if(count1+count2==strlen(inputname))
        {
            flag=1;
            printf("%s\t%ld\t",studentpt[i]->name,studentpt[i]->number);
            for(j=0;j<course_num;j++)
            {
                printf("%.2f\t",studentpt[i]->score[j]);
            }
            printf("%.2f\n",studentpt[i]->sum);
        }
    }
    if(flag==0)
    printf("û�д�ѧ����Ϣ��\n");
}
void SearchByNum(STU *studentpt[],STU *head,int stu_num,int course_num)
{
    //�������ܣ�����ѧ��ѧ�Ų�ѯ
    //����������
    //STU *studentpt[]:ָ�����ѧ����Ϣ�����ָ������
    //STU *head:����ͷָ��
    //int stu_num:�����ѧ������
    //int course_num:����Ŀγ�����
    //��������ֵ����
    long inputnum;
    int i,j;
    int flag=0;
    printf("������Ҫ���ҵ�ѧ��ѧ�ţ�");
    scanf("%ld",&inputnum);
    printf("����\tѧ��\t");
            for(j=0;j<course_num;j++)
                printf("��%d�ſ�\t",j+1);
            printf("�ܷ�\n");
    for(i=0;i<stu_num;i++)
    {
        if(inputnum==studentpt[i]->number)
        {
            flag=1;
            printf("%s\t%ld\t",studentpt[i]->name,studentpt[i]->number);
            for(j=0;j<course_num;j++)
            {
                printf("%.2f\t",studentpt[i]->score[j]);
            }
            printf("%.2f\n",studentpt[i]->sum);
        }
    }
    if(flag==0)
    printf("û�д�ѧ����Ϣ��\n");
}
void StatisticAnalysis(STU *studentpt[],STU *head,int stu_num,int course_num)
{
    //�������ܣ���ѧ���ɼ����з���
    //����������
    //STU *studentpt[]:ָ�����ѧ����Ϣ�����ָ������
    //STU *head:����ͷָ��
    //int stu_num:�����ѧ������
    //int course_num:����Ŀγ�����
    //��������ֵ����
    int i,j,counter[6];
    for(i=0;i<course_num;i++)
    {
        printf("��%d�ſΣ�\t����\t����\n",i+1);
        memset(counter,0,sizeof(counter));
        for(j=0;j<stu_num;j++)
        {
            if(studentpt[j]->score[i]<60&&studentpt[j]->score[i]>=0) counter[0]++;
            else if(studentpt[j]->score[i]<70) counter[1]++;
            else if(studentpt[j]->score[i]<80) counter[2]++;
            else if(studentpt[j]->score[i]<90) counter[3]++;
            else if(studentpt[j]->score[i]<100) counter[4]++;
            else if(studentpt[j]->score[i]==100) counter[5]++;
        }
        printf("0~59\t\t%d\t%.2f%%\n",counter[0],(float)counter[0]*100/stu_num);
        printf("60~69\t\t%d\t%.2f%%\n",counter[1],(float)counter[1]*100/stu_num);
        printf("70~79\t\t%d\t%.2f%%\n",counter[2],(float)counter[2]*100/stu_num);
        printf("80~89\t\t%d\t%.2f%%\n",counter[3],(float)counter[3]*100/stu_num);
        printf("90~99\t\t%d\t%.2f%%\n",counter[4],(float)counter[4]*100/stu_num);
        printf("100\t\t%d\t%.2f%%\n",counter[5],(float)counter[5]*100/stu_num);
    }
}
void SaveToFile(STU *studentpt[],STU *head,int stu_num,int course_num)
{
    //�������ܣ���ѧ����Ϣ���浽�ļ�
    //����������
    //STU *studentpt[]:ָ�����ѧ����Ϣ�����ָ������
    //STU *head:����ͷָ��
    //int stu_num:�����ѧ������
    //int course_num:����Ŀγ�����
    //��������ֵ����
    FILE *stream;
    if((stream=fopen("ѧ���ɼ�.txt","w+"))!=NULL)
    {
        fprintf(stream,"ѧ��������%d ",stu_num);
        fprintf(stream,"�γ�������%d\n",course_num);
        int i,j;
        fprintf(stream,"����\tѧ��\t");
        for(i=0;i<course_num;i++)
            fprintf(stream,"��%d�ſ�\t",i+1);
        fprintf(stream,"�ܷ�\n");
        for(i=0;i<stu_num;i++)
        {
            fprintf(stream,"%s\t%ld\t",studentpt[i]->name,studentpt[i]->number);
            for(j=0;j<course_num;j++)
            {
                fprintf(stream,"%.2f\t",studentpt[i]->score[j]);
            }
            fprintf(stream,"%.2f\n",studentpt[i]->sum);
        }
        fclose(stream);
        printf("����ɹ���");
    }
    else
        printf("����ʧ�ܣ�");
}
void ReadFromFile(STU *studentpt[],STU *head,int stu_num,int course_num)
{
    //�������ܣ����ļ���ȡ�ɼ�
    //����������
    //STU *studentpt[]:ָ�����ѧ����Ϣ�����ָ������
    //STU *head:����ͷָ��
    //int stu_num:�����ѧ������
    //int course_num:����Ŀγ�����
    //��������ֵ����
    FILE *stream;
    char a[50][50]={0};
    if((stream=fopen("ѧ���ɼ�.txt","r"))!=NULL)
    {
        int i;
        for(i=0;i<stu_num+2;i++)
        {
            fgets(a[i],50,stream);
        }
        for(i=0;i<stu_num+2;i++)
        {
            fputs(a[i],stdout);
        }
        fclose(stream);
    }
    else
        printf("����ʧ�ܣ�");
}
int main()
{
    //�������ܣ��� Print�����Ļ�ò����벢������Ӧ�ĺ�������
    //������������
    //��������ֵ����
    int stu_num;
    int course_num;
    float sumofcourse[COURSE_NUM]={0};
    float averofcourse[COURSE_NUM]={0};
    STU *head;
    STU *studentpt[STU_NUM];
    char opt;
    while(1)
    {
        opt=Menu();
        switch(opt)
        {
            case 1:
                printf("������ѧ��������");
                scanf("%d",&stu_num);
                printf("������γ�������");
                scanf("%d",&course_num);
                head=ReadScore(stu_num,course_num);
                Connect(studentpt,head,stu_num,course_num);
                option[1]=1;
            break;
            case 2:
                if(option[1]==0)
                    printf("��������ɼ���\n");
                else
                {
                    AverSumofEveryCourse(studentpt,head,stu_num,course_num,sumofcourse,averofcourse);
                    option[2]=1;
                }
            break;
            case 3:
                if(option[1]==0)
                    printf("��������ɼ���\n");
                else
                {
                    AverSumofEveryStudent(studentpt,head,stu_num,course_num);
                    option[3]=1;
                }
            break;
            case 4:
                if(option[3]==0)
                    printf("����ִ�в���3��\n");
                else
                SortByScoreUP(studentpt,head,stu_num,course_num);
            break;
            case 5:
                if(option[3]==0)
                    printf("����ִ�в���3��\n");
                else
                SortByScoreDOWN(studentpt,head,stu_num,course_num);
            break;
            case 6:
                if(option[3]==0)
                    printf("����ִ�в���3��\n");
                else
                {
                    SortByNum(studentpt,stu_num,0,stu_num-1);
                    Print(studentpt,head,stu_num,course_num);
                }
            break;
            case 7:
                if(option[3]==0)
                    printf("����ִ�в���3��\n");
                else
                SortByName(studentpt,head,stu_num,course_num);
            break;
            case 8:
                if(option[3]==0)
                    printf("����ִ�в���3��\n");
                else
                SearchByName(studentpt,head,stu_num,course_num);
            break;
            case 9:
                if(option[3]==0)
                    printf("����ִ�в���3��\n");
                else
                SearchByNum(studentpt,head,stu_num,course_num);
            break;
            case 10:
                if(option[3]==0)
                    printf("����ִ�в���3��\n");
                else
                StatisticAnalysis(studentpt,head,stu_num,course_num);
            break;
            case 11:
                if(option[3]==0)
                    printf("����ִ�в���3��\n");
                else
                    {
                        option[11]=1;
                        SaveToFile(studentpt,head,stu_num,course_num);
                    }
                break;
            case 12:
                if(option[11]==0)
                    printf("��ִ�в���11��\n");
                else
                    ReadFromFile(studentpt,head,stu_num,course_num);
                break;
            case 0:printf("���˳�\n");
            exit(0);
            case -1:printf("�������\n");
            break;
            default:printf("�������\n");
        }
    }
}
