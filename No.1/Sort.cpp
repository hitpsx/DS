#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream> 
using namespace std;

#define lengh 20

typedef int dataType;

class Sort
{
public:
	Sort();
	~Sort();
	void bubbleSort();
	void selectSort();
	void insertSort();
	void shellSort();
	void swap(dataType *a,dataType *b);
	void show();
private:
	dataType seqList[lengh];
};

Sort::Sort() {
	ifstream infile;
	int temp;
	int i=0;
	infile.open("data.txt");
	if(!infile.is_open())
		cout<<"false"<<endl;
	string s;
	while(getline(infile,s)) {
		istringstream iss(s);
		int num;
		while(iss>>num)
			seqList[i++]=num;
	}
	infile.close();
}
void Sort::swap(dataType *a,dataType *b) {
	dataType temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
void Sort::bubbleSort() {
	int i,j;
	int a,b;
	for(int i=0;i<lengh;i++) {
		for(int j=lengh-1;j>i;j--) {
			if(seqList[j]<seqList[j-1])
				swap(&seqList[j-1],&seqList[j]);
		}
	}
}
void Sort::selectSort() {
	int i,j;
	int mx=0;
	for(i=0;i<lengh;i++) {
		j=i;

		for(j=i+1;j<lengh;j++) {        //choice the mx location after i (because before i all is sorted)
			if(seqList[j]<seqList[mx])
				mx=j;
		}

		if(mx!=i) //then exchange
			swap(&seqList[i],&seqList[mx]);
	}
}

void Sort::insertSort() {
	int i,j;
	for(i=0;i<lengh;i++){
		j=i;
		while(seqList[j]<seqList[j-1] && j!=0){
			swap(&seqList[j],&seqList[j-1]);
			j--;
		}
	}
}

void Sort::show() {
	for(int i=0;i<lengh;i++)
		cout<<seqList[i]<<"\t";
}
int main(){
	Sort *my=new Sort();
	//my->bubbleSort();
	//my->selectSort();
	//my->insertSort();
	my->show();
}