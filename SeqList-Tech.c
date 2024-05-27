#include<stdio.h>
#define MAX_Length 100
#define OK 1
#define ERROR -1

typedef int status;


//�������Ա�ṹ��
struct SeqList{
    int data[MAX_Length];  //���ݴ洢�ռ�
    int length;     //��ǰ���Ա���
};
typedef struct SeqList SList;   //�������


//�����б�
status SeqInsert(SList *List, int Loc, int elem);   //������ĳһλ�ò�������
status SeqDelete(SList *List, int Loc); //ɾ��ɾ��ĳһλ��Ԫ��
status SeqUpdate(SList *List, int Loc, int elem);   //�ģ��޸�ĳһλ��Ԫ��
int SeqSearch(SList *List, int elem);   //�飺����ĳһԪ������λ�ã������ء���š�(���!=�Ǳ�)


//������ڡ�������
void main(){
    //��ʼ��һ�����Ա�����Ϊ������Ҫ��¼���������Щ�������¡�
    SList DateBook;
    DateBook.length = 0;

    //���뼸�����ݡ���8�š�9�����¡�
    if( SeqInsert(&DateBook,1,9) == ERROR || SeqInsert(&DateBook,1,8) == ERROR){
        printf("����ʧ�ܣ�\n");
    }
    else{
        printf("����ɹ�~\n");
    }

    //���ڽ��ڶ������µ�����ɾ����9����Ҫ�ճ���������ˡ�
    if( SeqDelete(&DateBook,2) == ERROR){
        printf("ɾ��ʧ�ܣ�\n");
    }
    else{
        printf("ɾ���ɹ�~\n");
    }

    //������Ҫ�ѵ�һ�����ڸ���Ϊ10��8�ŵ����鱻�ҵ�����10�š�
    if( SeqUpdate(&DateBook,1,10) == ERROR){
        printf("����ʧ�ܣ�\n");
    }
    else{
        printf("���ĳɹ�~\n");
    }

    //��������֪��10���ڵڼ���Ԫ�ء��Һ���10���ǵڼ������µ����ӡ�
    if( SeqSearch(&DateBook,10) == ERROR){   //�������û�г��������ҵ���Ŀ��Ԫ�أ���ô����ֵ�Ͳ�������ERROR(����-1)����һ���Ǵ��ڵ���1��
        printf("��ѯʧ�ܣ�����δ�ҵ�Ŀ�����ݣ�\n");
    }
    else{
        printf("��ѯ�ɹ������ڵ�%d��Ԫ�ص�λ��~\n",SeqSearch(&DateBook,10));
    }
}


//������ĳһλ�ò�������
status SeqInsert(SList *List, int Loc, int elem){
    //�жϺϷ���(�������Ա�ʧ�ܡ���λС��0����λ���ڵ�ǰ���Ա�ĳ���+1�����Ա�����)
    if( List==NULL || Loc<0 || Loc>List->length+1 || List->length==MAX_Length){
        return ERROR;
    }

    //ʵ���㷨
    if( List->length == 0){  //�����Ա�Ϊ�գ�ʵ�����
        List->data[0] = elem;
        List->length += 1;
        return OK;
    }
    else{   //�����Ա�Ϊ�գ������㷨
        for( int i = List->length-1; i >= Loc-1; i--){   //�Ӻ�ʼŲ���ݣ�Ϊ�˰ѵ�Loc�����ݵ�λ�ø��������
            List->data[i+1] = List->data[i];
        }
        List->data[Loc-1] = elem;   //����Ӧλ�ý��и�ֵ
        List->length += 1;  //�����ȼ�1
        return OK;
    }

    return ERROR;
}


//ɾ��ɾ��ĳһλ��Ԫ��
status SeqDelete(SList *List, int Loc){
    //�жϺϷ���(�������Ա�ʧ�ܡ���λС��0����λ���ڵ�ǰ���Ա�ĳ���)
    if( List==NULL || Loc<0 || Loc>List->length){
        return ERROR;
    }

    //�㷨ʵ��
    for( int i=Loc-1; i<List->length-1; i++){  //��Ӧ��length-1λ��Ҳ���ʸ�д�ģ�������������ѭ�������ַ���List->data[length-1+1]������������Ա�������ʱ������Խ����ʵ�����
        List->data[i] = List->data[i+1];
    }
    List->data[List->length-1] = '\0';  //����length-1λ�ø�дΪ'��'
    return OK;
}



//�ģ��޸�ĳһλ��Ԫ��
status SeqUpdate(SList *List, int Loc, int elem){
    //�жϺϷ���(�������Ա�ʧ�ܡ���λС��0����λ���ڵ�ǰ���Ա�ĳ���)
    if( List==NULL || Loc<0 || Loc>List->length){
        return ERROR;
    }

    //�㷨ʵ��
    List->data[Loc-1] = elem;
    return OK;
}



//�飺����ĳһԪ������λ�ã������ء���š�(���!=�Ǳ�)
int SeqSearch(SList *List, int elem){
    //�жϺϷ���(�������Ա�ʧ�ܡ����Ա�Ϊ��)
    if( List == NULL || List->length == 0){
        return ERROR;
    }

    for( int i=0; i<List->length-1; i++){
        if( List->data[i] == elem){
            return i+1; //ע�����⣬����˵���Ƿ�����ţ�Ҳ��˵�ǵڼ���Ԫ�أ����Ƿ����½Ǳ꣡
        }
    }

    return ERROR;   //��һ�������������ҵ��Ǹ�Ŀ��Ԫ�أ��ǲ����ߵ���һ�еģ��������ִ�е����˵��������
}