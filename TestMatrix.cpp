#include"Matrix.cpp"
#include<iostream>

using namespace std;


int main()
{
	Matrix *m=new Matrix(3,5);
	for(int i=0; i<m->getRow(); i++)
		for(int j=0; j<m->getColumn(); j++)
	       m->setEntry(i, j, (i+1)*(j+1));
	cout<<*m<<endl;
	
	cout<<"\n\n"<<m->subMatrix(1, 2)<<endl;
	return 0;
}