#include <iostream>
#include <string.h>
using namespace std;

#define EXIT_FAITURE 1
#define EXIT_SUCCESS 0
typedef int dataType;

class  Node
{
public:
     dataType data;
     Node *next;
};

class Slink
{
public:
    ~Slink();
    void insertDataBack(dataType x); //尾插法建表
    void insertDataFront(dataType x); //头插法建表
    void deleteData(dataType x); //删除指定元素
    void test();
    int lenSlink(); //计算链表长度
    void reverseOne(); //逆序倒置
    void showData();
private:
	Node *head;
};


Slink::~Slink() {
	delete head;
}

void Slink::insertDataBack(dataType  x) {
    Node *p,*q;
    p=head;
    q=new Node;
    q->data=x;
    q->next=NULL;

    if(head==NULL) {
        head=new Node;
        head->next=q;
    }
    else {
        while(p->next!=NULL) {
            p=p->next;
        }
        p->next=q;
    }
}

void Slink::insertDataFront(dataType x) {
    Node *p,*q;
    p=head;
    q=new Node;
    if(head==NULL) {
        head->data=x;
        head->next=NULL;
    }
    else {
        q->data=p->data;
        q->next=p->next;
        head->data=x;
        head->next=q;
    }
}
void Slink::showData() {
    Node *p;
    p=head->next;
    while(p!=NULL) {
        cout<<"data is "<<p->data<<endl;
        p=p->next;
    }
}

void Slink::deleteData(dataType x) {
    Node *p,*q;
    p=head;
    if(head==NULL) {
        exit(1);
    }
    else {
        while(p->next !=NULL) {
            if(p->next->data==x) {
                q=p->next;
                p->next=q->next;
                delete q;
            }
            p=p->next;
        }
    }
}

int Slink::lenSlink() {
    Node *p;
    p=head;
    int i=0;
    while(p!=NULL) {
        i++;
        p=p->next;
    }
    return i;
}

void Slink::reverseOne() { //头结点中不存放数据
    Node *p,*q;
    p=head->next;
    head->next=NULL;
    while(p!=NULL) {
       q=p;
       p=p->next;
       q->next=head->next;
       head->next=q;
      
    }
}
void Slink::test() {
    Node *p;
    cout<<head->data<<endl;
    cout<<head->next->data<<endl;
    cout<<head->next->next->data<<endl;
}
int main() {
    Slink *cur=new Slink();
    cur->insertDataBack(2);
    cur->insertDataBack(3);
    cur->insertDataBack(4);
    cur->showData();
    cout<<"reverse"<<endl;
    cur->reverseOne();
    cur->showData();
    return 0;
}