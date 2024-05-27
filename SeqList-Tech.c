#include<stdio.h>
#define MAX_Length 100
#define OK 1
#define ERROR -1

typedef int status;


//定义线性表结构体
struct SeqList{
    int data[MAX_Length];  //数据存储空间
    int length;     //当前线性表长度
};
typedef struct SeqList SList;   //定义别名


//函数列表
status SeqInsert(SList *List, int Loc, int elem);   //增：在某一位置插入数据
status SeqDelete(SList *List, int Loc); //删：删除某一位置元素
status SeqUpdate(SList *List, int Loc, int elem);   //改：修改某一位置元素
int SeqSearch(SList *List, int elem);   //查：查找某一元素所在位置，并返回【序号】(序号!=角标)


//程序入口、主函数
void main(){
    //初始化一个线性表，举例为【我需要记录下这个月哪些日子有事】
    SList DateBook;
    DateBook.length = 0;

    //插入几个数据【我8号、9号有事】
    if( SeqInsert(&DateBook,1,9) == ERROR || SeqInsert(&DateBook,1,8) == ERROR){
        printf("插入失败！\n");
    }
    else{
        printf("插入成功~\n");
    }

    //现在将第二个有事的日期删除【9号我要空出来陪对象了】
    if( SeqDelete(&DateBook,2) == ERROR){
        printf("删除失败！\n");
    }
    else{
        printf("删除成功~\n");
    }

    //现在我要把第一个日期更改为10【8号的事情被我调到了10号】
    if( SeqUpdate(&DateBook,1,10) == ERROR){
        printf("更改失败！\n");
    }
    else{
        printf("更改成功~\n");
    }

    //现在我想知道10是在第几个元素【我好奇10号是第几个有事的日子】
    if( SeqSearch(&DateBook,10) == ERROR){   //如果函数没有出错，并且找到了目标元素，那么返回值就不可能是ERROR(数字-1)，它一定是大于等于1的
        printf("查询失败，或是未找到目标数据！\n");
    }
    else{
        printf("查询成功！它在第%d个元素的位置~\n",SeqSearch(&DateBook,10));
    }
}


//增：在某一位置插入数据
status SeqInsert(SList *List, int Loc, int elem){
    //判断合法性(传入线性表失败、定位小于0、定位大于当前线性表的长度+1、线性表已满)
    if( List==NULL || Loc<0 || Loc>List->length+1 || List->length==MAX_Length){
        return ERROR;
    }

    //实现算法
    if( List->length == 0){  //若线性表为空，实现最简单
        List->data[0] = elem;
        List->length += 1;
        return OK;
    }
    else{   //若线性表不为空，常规算法
        for( int i = List->length-1; i >= Loc-1; i--){   //从后开始挪数据，为了把第Loc个数据的位置给空余出来
            List->data[i+1] = List->data[i];
        }
        List->data[Loc-1] = elem;   //对相应位置进行赋值
        List->length += 1;  //将长度加1
        return OK;
    }

    return ERROR;
}


//删：删除某一位置元素
status SeqDelete(SList *List, int Loc){
    //判断合法性(传入线性表失败、定位小于0、定位大于当前线性表的长度)
    if( List==NULL || Loc<0 || Loc>List->length){
        return ERROR;
    }

    //算法实现
    for( int i=Loc-1; i<List->length-1; i++){  //理应将length-1位置也访问覆写的，但如果放在这个循环里，会出现访问List->data[length-1+1]的情况，若线性表已满的时候会出现越界访问的问题
        List->data[i] = List->data[i+1];
    }
    List->data[List->length-1] = '\0';  //将将length-1位置覆写为'空'
    return OK;
}



//改：修改某一位置元素
status SeqUpdate(SList *List, int Loc, int elem){
    //判断合法性(传入线性表失败、定位小于0、定位大于当前线性表的长度)
    if( List==NULL || Loc<0 || Loc>List->length){
        return ERROR;
    }

    //算法实现
    List->data[Loc-1] = elem;
    return OK;
}



//查：查找某一元素所在位置，并返回【序号】(序号!=角标)
int SeqSearch(SList *List, int elem){
    //判断合法性(传入线性表失败、线性表为空)
    if( List == NULL || List->length == 0){
        return ERROR;
    }

    for( int i=0; i<List->length-1; i++){
        if( List->data[i] == elem){
            return i+1; //注意审题，这里说的是返回序号，也就说是第几个元素，不是返回下角标！
        }
    }

    return ERROR;   //若一切正常，且能找到那个目标元素，是不会走到这一行的，如果程序执行到这就说明出错了
}