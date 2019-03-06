#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX_LEN 10//最大名字长度
#define STU_NUM 30//最多的学生人数
#define COURSE_NUM 6//最多的课程数
//定义学生信息结构体
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
    //函数功能：打印学生信息
    //函数参数：
    //STU *studentpt[]:指向各个学生信息链表的指针数组
    //STU *head:链表头指针
    //int stu_num:输入的学生人数
    //int course_num:输入的课程人数
    //函数返回值：无
    int i,j;
    printf("姓名\t学号\t");
    for(i=0;i<course_num;i++)
        printf("第%d门课\t",i+1);
    printf("总分\n");
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
    //函数功能：打印菜单并返回用户选择的操作码
    //函数参数：无
    //函数返回值：返回操作码
    int opt;
    int flag;
    printf("\n");
    printf("学生成绩管理系统\n");
    printf("1.输入成绩\n");
    printf("2.计算每门课总成绩和平均成绩\n");
    printf("3.计算每个学生总成绩和平均成绩\n");
    printf("4.按照学生总成绩升序排名\n");
    printf("5.按照学生总成绩降序排名\n");
    printf("6.按照学号排名\n");
    printf("7.按照姓名排序\n");
    printf("8.通过姓名查找\n");
    printf("9.通过学号查找\n");
    printf("10.成绩分析\n");
    printf("11.将成绩保存到文件\n");
    printf("12.从文件读取成绩\n");
    printf("0.退出系统\n");
    printf("请输入对应操作码：");
    fflush(stdin);
        flag=scanf("%d",&opt);
        if(flag==1||flag==2)
            return opt;
        else
            return -1;


}
STU *ReadScore(int stu_num,int course_num)
{
    //函数功能：输入学生信息
    //函数参数：
    //int stu_num:输入的学生人数
    //int course_num:输入的课程人数
    //函数返回值：返回链表的头指针
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
            printf("请按顺序输入第%d个学生的学号、姓名、成绩（以空格为间隔符）：\n",1);
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
                printf("请按顺序输入第%d个学生的学号、姓名、成绩（以空格为间隔符）：\n",i+1);
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
    //函数功能：将学生的指针数组分别指向每个学生的信息链表，建立一个索引
    //函数参数：
    //STU *studentpt[]:指向各个学生信息链表的指针数组
    //STU *head:链表头指针
    //int stu_num:输入的学生人数
    //int course_num:输入的课程人数
    //函数返回值：无
    STU *pt=head;
    studentpt[0]=head;
   // printf("指针数组保存的地址%d\n",studentpt[0]);
    int i=1;
    while(pt!=NULL)
    {
        studentpt[i]=pt->next;
        //printf("指针数组保存的地址%d\n",studentpt[i]);
        pt=pt->next;
        i++;
    }

}
void AverSumofEveryStudent(STU *studentpt[],STU *head,int stu_num,int course_num)
{
    //函数功能：计算每个学生的的总成绩和平均成绩
    //函数参数：
    //STU *studentpt[]:指向各个学生信息链表的指针数组
    //STU *head:链表头指针
    //int stu_num:输入的学生人数
    //int course_num:输入的课程人数
    //函数返回值：无
    int i,j;
    for(i=0;i<stu_num;i++)
    {
        studentpt[i]->sum=0;
    }
    for(i=0;i<stu_num;i++)
    {
        for(j=0;j<course_num;j++)
            studentpt[i]->sum+=studentpt[i]->score[j];//求每个学生总成绩
        printf("第%d个学生总成绩：%.2f ",i+1,studentpt[i]->sum);
        studentpt[i]->aver=studentpt[i]->sum/course_num;
        printf("第%d个学生平均：%.2f\n",i+1,studentpt[i]->aver);
    }

}
void AverSumofEveryCourse(STU *studentpt[],STU *head,int stu_num,int course_num,float sumofcourse[],float averofcourse[])
{
    //函数功能：计算课程的总成绩和平均成绩
    //函数参数：
    //STU *studentpt[]:指向各个学生信息链表的指针数组
    //STU *head:链表头指针
    //int stu_num:输入的学生人数
    //int course_num:输入的课程人数
    //float sumofcourse[]:每一个课程总成绩
    //float averofcourse[]:每一个课程的平均成绩
    //函数返回值：无
    int i,j;
    for(i=0;i<course_num;i++)
    {
        for(j=0;j<stu_num;j++)
        {
            sumofcourse[i]+=studentpt[j]->score[i];
        }
        printf("第%d门课总成绩：%.2f\n",i+1,sumofcourse[i]);
        averofcourse[i]=sumofcourse[i]/stu_num;
        printf("第%d门课平均成绩：%.2f\n",i+1,averofcourse[i]);
    }
}
void SortByName(STU *studentpt[],STU *head,int stu_num,int course_num)
{
    //函数功能：按照学生姓名排序
    //函数参数：
    //STU *studentpt[]:指向各个学生信息链表的指针数组
    //STU *head:链表头指针
    //int stu_num:输入的学生人数
    //int course_num:输入的课程人数
    //函数返回值：无
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
    //函数功能：利用快排按照学生学号排序
    //函数参数：
    //STU *studentpt[]:指向各个学生信息链表的指针数组
    //STU *head:链表头指针
    //int stu_num:输入的学生人数
    //int course_num:输入的课程人数
    //函数返回值：无
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
    //函数功能：按照学生成绩进行升序排序
    //函数参数：
    //STU *studentpt[]:指向各个学生信息链表的指针数组
    //STU *head:链表头指针
    //int stu_num:输入的学生人数
    //int course_num:输入的课程人数
    //函数返回值：无
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
    //函数功能：按照学生成绩降序排序
    //函数参数：
    //STU *studentpt[]:指向各个学生信息链表的指针数组
    //STU *head:链表头指针
    //int stu_num:输入的学生人数
    //int course_num:输入的课程人数
    //函数返回值：无
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
    //函数功能：按照学生名字进行查找，使用了模糊查询算法
    //函数参数：
    //STU *studentpt[]:指向各个学生信息链表的指针数组
    //STU *head:链表头指针
    //int stu_num:输入的学生人数
    //int course_num:输入的课程人数
    //函数返回值：无
    char inputname[MAX_LEN+1];
    int i,j;
    int m,count1=0,count2=0;
    int flag=0;
    printf("请输入要查找的学生姓名（请用*代替未知字符）：");
    getchar();
    gets(inputname);
    printf("姓名\t学号\t");
            for(j=0;j<course_num;j++)
                printf("第%d门课\t",j+1);
            printf("总分\n");
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
    printf("没有此学生信息！\n");
}
void SearchByNum(STU *studentpt[],STU *head,int stu_num,int course_num)
{
    //函数功能：按照学生学号查询
    //函数参数：
    //STU *studentpt[]:指向各个学生信息链表的指针数组
    //STU *head:链表头指针
    //int stu_num:输入的学生人数
    //int course_num:输入的课程人数
    //函数返回值：无
    long inputnum;
    int i,j;
    int flag=0;
    printf("请输入要查找的学生学号：");
    scanf("%ld",&inputnum);
    printf("姓名\t学号\t");
            for(j=0;j<course_num;j++)
                printf("第%d门课\t",j+1);
            printf("总分\n");
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
    printf("没有此学生信息！\n");
}
void StatisticAnalysis(STU *studentpt[],STU *head,int stu_num,int course_num)
{
    //函数功能：对学生成绩进行分析
    //函数参数：
    //STU *studentpt[]:指向各个学生信息链表的指针数组
    //STU *head:链表头指针
    //int stu_num:输入的学生人数
    //int course_num:输入的课程人数
    //函数返回值：无
    int i,j,counter[6];
    for(i=0;i<course_num;i++)
    {
        printf("第%d门课：\t人数\t比例\n",i+1);
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
    //函数功能：将学生信息保存到文件
    //函数参数：
    //STU *studentpt[]:指向各个学生信息链表的指针数组
    //STU *head:链表头指针
    //int stu_num:输入的学生人数
    //int course_num:输入的课程人数
    //函数返回值：无
    FILE *stream;
    if((stream=fopen("学生成绩.txt","w+"))!=NULL)
    {
        fprintf(stream,"学生人数：%d ",stu_num);
        fprintf(stream,"课程门数：%d\n",course_num);
        int i,j;
        fprintf(stream,"姓名\t学号\t");
        for(i=0;i<course_num;i++)
            fprintf(stream,"第%d门课\t",i+1);
        fprintf(stream,"总分\n");
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
        printf("保存成功！");
    }
    else
        printf("保存失败！");
}
void ReadFromFile(STU *studentpt[],STU *head,int stu_num,int course_num)
{
    //函数功能：从文件读取成绩
    //函数参数：
    //STU *studentpt[]:指向各个学生信息链表的指针数组
    //STU *head:链表头指针
    //int stu_num:输入的学生人数
    //int course_num:输入的课程人数
    //函数返回值：无
    FILE *stream;
    char a[50][50]={0};
    if((stream=fopen("学生成绩.txt","r"))!=NULL)
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
        printf("保存失败！");
}
int main()
{
    //函数功能：从 Print函数的获得操作码并进行相应的函数调用
    //函数参数：无
    //函数返回值：无
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
                printf("请输入学生人数：");
                scanf("%d",&stu_num);
                printf("请输入课程门数：");
                scanf("%d",&course_num);
                head=ReadScore(stu_num,course_num);
                Connect(studentpt,head,stu_num,course_num);
                option[1]=1;
            break;
            case 2:
                if(option[1]==0)
                    printf("请先输入成绩！\n");
                else
                {
                    AverSumofEveryCourse(studentpt,head,stu_num,course_num,sumofcourse,averofcourse);
                    option[2]=1;
                }
            break;
            case 3:
                if(option[1]==0)
                    printf("请先输入成绩！\n");
                else
                {
                    AverSumofEveryStudent(studentpt,head,stu_num,course_num);
                    option[3]=1;
                }
            break;
            case 4:
                if(option[3]==0)
                    printf("请先执行操作3！\n");
                else
                SortByScoreUP(studentpt,head,stu_num,course_num);
            break;
            case 5:
                if(option[3]==0)
                    printf("请先执行操作3！\n");
                else
                SortByScoreDOWN(studentpt,head,stu_num,course_num);
            break;
            case 6:
                if(option[3]==0)
                    printf("请先执行操作3！\n");
                else
                {
                    SortByNum(studentpt,stu_num,0,stu_num-1);
                    Print(studentpt,head,stu_num,course_num);
                }
            break;
            case 7:
                if(option[3]==0)
                    printf("请先执行操作3！\n");
                else
                SortByName(studentpt,head,stu_num,course_num);
            break;
            case 8:
                if(option[3]==0)
                    printf("请先执行操作3！\n");
                else
                SearchByName(studentpt,head,stu_num,course_num);
            break;
            case 9:
                if(option[3]==0)
                    printf("请先执行操作3！\n");
                else
                SearchByNum(studentpt,head,stu_num,course_num);
            break;
            case 10:
                if(option[3]==0)
                    printf("请先执行操作3！\n");
                else
                StatisticAnalysis(studentpt,head,stu_num,course_num);
            break;
            case 11:
                if(option[3]==0)
                    printf("请先执行操作3！\n");
                else
                    {
                        option[11]=1;
                        SaveToFile(studentpt,head,stu_num,course_num);
                    }
                break;
            case 12:
                if(option[11]==0)
                    printf("请执行操作11！\n");
                else
                    ReadFromFile(studentpt,head,stu_num,course_num);
                break;
            case 0:printf("已退出\n");
            exit(0);
            case -1:printf("输入错误！\n");
            break;
            default:printf("输入错误！\n");
        }
    }
}
