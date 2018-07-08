#include <iostream>
#include <math.h>
#include <ctime>
#include <cstdlib>
using namespace std;
#define EXIT_FAITURE 1
#define EXIT_SUCCESS 0
#define length 20

typedef int dataType;
class sequeList
{
public:
	sequeList();
	~sequeList();
	void insertdata(dataType x,int l);
	void deletedata(dataType x);
	void deleteManyEqual(dataType x);
	void reverse();
	void showNow();
private:
	int lenNow;
	dataType seqList[length];
};

sequeList::sequeList() {
	lenNow=0;
	for(int i=0;i<10;i++) {
		seqList[i]=2*i;
		lenNow++;
	}
	seqList[4]=4;
}
void sequeList::insertdata(dataType x,int l) {
	if(l>lenNow)
		exit(1);
	for(int i=lenNow;i>=l-1;i--) {
		seqList[i+1]=seqList[i];
	}
	seqList[l-1]=x;
	lenNow++;
}

void sequeList::deletedata(dataType x) {
	for(int i=0;i<lenNow;i++) {
		if(seqList[i]==x) {
			for(int j=i;j<lenNow;j++) {
				seqList[j]=seqList[j+1];
			}
			break;
		}
	}
	lenNow--;
}
void sequeList::deleteManyEqual(dataType x) {
	for(int i=0;i<lenNow;i++) {
		if(seqList[i]==x) {
			seqList[i]=seqList[lenNow-1];
			lenNow--;
		}
	}
}
void sequeList::reverse() {
	for(int i=0;i<lenNow/2;i++) {
		int temp=seqList[lenNow-i-1];
		seqList[lenNow-i-1]=seqList[i];
		seqList[i]=temp;
	}
}
void sequeList::showNow() {
	for(int i=0;i<lenNow;i++)
		cout<<"i:"<<seqList[i]<<"\t";
	cout<<endl;
}
int main() 
{
	sequeList *cur=new sequeList();
	cur->showNow();
	cur->deleteManyEqual(4);
	cur->showNow();
	/*cur->insertdata(25,2);
	cur->showNow();
	cur->deletedata(25);
	cur->showNow();*/
}
