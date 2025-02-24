#include<iomanip>
#include"Matrix.h"
#include<cstring>
#include<string>
#include<math.h>

	
	 Matrix::Matrix(int rows, int cols)
	  {
		  this->rows=rows;
		  this->cols=cols;
		  this->matrix=new double*[rows];
		  for(int i=0; i<rows; i++)
			  this->matrix[i]=new double[cols];
	  }
	 
	  Matrix::~Matrix()
	  {
		  for(int i=0; i<rows; i++)
			  delete [] matrix[i];
		  delete [] matrix;
	  }
	  
	  Matrix::Matrix(const Matrix& target)
	  {  
		 this->rows=rows;
		  this->cols=cols;
		  this->matrix=new double*[target.rows];
		  for(int i=0; i<rows; i++)
			  this->matrix[i]=new double[target.cols];
         for(int i=0; i<target.rows; i++)
           for(int j=0; j<target.cols; j++)
            this->matrix[i][j]=target.matrix[i][j];	
       		
	  }
	
	 void Matrix::operator=(const Matrix& target)
	 {
		 if(matrix!=NULL)
		 {
		  for(int i=0; i<rows; i++)
			  delete [] matrix[i];
		  delete [] matrix;
		 }
		  this->rows=rows;
		  this->cols=cols;
		  this->matrix=new double*[target.rows];
		  for(int i=0; i<rows; i++)
			  this->matrix[i]=new double[target.cols];
         for(int i=0; i<target.rows; i++)
           for(int j=0; j<target.cols; j++)
            this->matrix[i][j]=target.matrix[i][j];	  
	 }
	 
	 
	 void Matrix::setEntry(int i, int j, double entry)
	 {
		this->matrix[i][j]=entry;
     }	

     Matrix Matrix::subMatrix(int r, int c)const
	 { 
	   Matrix m(this->rows-1, this->cols-1);
	   for(int i=0; i<rows-1; i++)
		   for(int j=0; j<cols-1;j++)
		   {
			  if(i<r &&j<c) 
		        m.matrix[i][j]=this->matrix[i][j];
			  if(i<r &&j>=c)
		        m.matrix[i][j]=this->matrix[i][j+1];
			  if(i>=r && j<c)
				m.matrix[i][j]=this->matrix[i+1][j];  
			  if(i>=r && j>=c)
				m.matrix[i][j]=this->matrix[i+1][j+1];
		   }
	   return m;
	 }
	

	 
