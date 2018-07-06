#include <stdio.h>
#include <string.h>
using namespace std;

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
    Slink();
    ~Slink();
    void insertData(dataType x);
    void showData();
private:
	Node *head;
};

Slink::Slink() {
	head=new Node;
	head->data=0;
	head->next=NULL;
}

Slink::~Slink() {
	delete head;
}