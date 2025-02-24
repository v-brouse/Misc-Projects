
  class Matrix
  {
	public:
	  Matrix(int rows=1, int cols=1);
	  
	  int getRow()const{return rows;}
      int getColumn()const{return cols;}
	 
	  ~Matrix();
	
	  Matrix(const Matrix& target);
	
	 void operator=(const Matrix& target);
	
	 void setEntry(int i, int j, double entry);
	 
	 Matrix subMatrix(int i, int j)const;
	 
	 friend std::ostream& operator<<(std::ostream& out, const Matrix& a)
	 {
		 for(int i=0; i<a.rows; i++)
		 {
			 out<<"| ";
			 for(int j=0; j<a.cols; j++)
				 out<<std::setw(10)<<a.matrix[i][j];
		     out<<std::setw(5)<<"|\n";
		 }
		 return out;
	 }
	 
	private:
	  double** matrix;
	  int rows;
	  int cols;
   };
	