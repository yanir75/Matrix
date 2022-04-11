#include "Matrix.hpp"
#include <stdexcept>
#include <iostream>
#include <string>

/**
 * Constructor that receives an int and builds a matrix according to the given vector
 * @param matrix
 * @param row
 * @param col
 */
zich::Matrix::Matrix(std::vector<double> matrix,  int row,  int col) :mat((unsigned int)row*(unsigned int)col) {
    if(matrix.size()!= row*col || row<0 || col <0){
        throw std::invalid_argument("Matrix size is not right");
    }
    this->row = (unsigned int) row;
    this->col = (unsigned int) col;
    for(unsigned int i=0;i<matrix.size();i++){
        mat[i]=matrix[i];
    }
}
/**
 * Constructs a matrix from vector and unsigned ints
 * @param matrix
 * @param row
 * @param col
 */
zich::Matrix::Matrix(std::vector<double> matrix,  unsigned int row,  unsigned int col) :mat(row*col) {
    if(matrix.size()!= row*col){
        throw std::invalid_argument("Matrix size is not right");
    }
    this->row = row;
    this->col = col;
    for(unsigned int i=0;i<matrix.size();i++){
        mat[i]=matrix[i];
    }
}
/**
 * Constructs a matrix with a given value and resets the matrix to the given value
 * @param value
 * @param row
 * @param col
 */
zich::Matrix::Matrix(double value, unsigned int row, unsigned int col): mat(row*col) {
    this->row = row;
    this->col = col;
    for(unsigned int i=0;i<row*col;i++){
        mat[i]=value;
    }

}

/**
 * receives a matrix of the same size and adds it this to the given matrix
 * @param matrix
 * @return
 */
zich::Matrix zich::Matrix::operator+(const zich::Matrix &matrix) {
    if(row!=matrix.row || col!=matrix.col){
        throw std::invalid_argument("mat size is different");
    }
    zich::Matrix ans(mat,row,col);
    ans+=matrix;
    return ans;
}
/**
 * receives a double and adds it to all the matrix
 * @param add
 * @return
 */
zich::Matrix zich::Matrix::operator+(double add) {
    zich::Matrix ans(mat,row,col);
    ans+=add;
    return ans;
}
/**
 * adds 1 to all the matrix returns the matrix after added 1
 * @return
 */
zich::Matrix &zich::Matrix::operator++() {
    *this +=1;
    return *this;
}
/**
 * Adds one to all and returns a copy of the matrix before adding 1
 * @param ind
 * @return
 */
zich::Matrix zich::Matrix::operator++(int ind) {
    const zich::Matrix ans(mat,row,col);
    ++*this;
    return ans;
}
/**
 * Adds the matrix to the given matrix and returns the matrix
 * @param matrix
 * @return
 */
zich::Matrix zich::Matrix::operator+=(const zich::Matrix& matrix) {

    if(row!=matrix.row || col!=matrix.col){
        throw std::invalid_argument("mat size is different");
    }
    for(unsigned int i=0;i<mat.size();i++){
        mat[i]+=matrix.mat[i];
    }
    return *this;
}
/**
 * adds the parameter to all the values in the matrix
 * @param add
 * @return
 */
zich::Matrix zich::Matrix::operator+=(double add) {
    for(double &i:mat){
        i+=add;
    }
    return *this;
}
/**
 * subtracts the value from the matrix
 * @param sub
 * @return
 */
zich::Matrix zich::Matrix::operator-(double sub) {
    zich::Matrix ans=*this+-sub;
    return ans;
}

/**
 * Subtracts a matrix from the given matrix of the same size and returns a copy
 * @param matrix
 * @return
 */
zich::Matrix zich::Matrix::operator-(const zich::Matrix &matrix) {
    if(row!=matrix.row || col!=matrix.col){
        throw std::invalid_argument("mat size is different");
    }
    zich::Matrix ans(mat,row,col);
    ans-=matrix;
    return ans;
}
/**
 * Subtracts 1 from all the matrix and returns the reference of the matrix after we removed 1
 * @return
 */
zich::Matrix &zich::Matrix::operator--() {
    *this += -1;
    return *this;
}
/**
 * Returns a copy of the matrix before subtracting 1 from all the values
 * @param sub
 * @return
 */
zich::Matrix zich::Matrix::operator--(int sub) {
    zich::Matrix ans(mat,row,col);
    *this+=-1;
    return ans;
}
/**
 * Subtracts 2 matrix of the same size
 * @param matrix
 * @return
 */
zich::Matrix zich::Matrix::operator-=(const zich::Matrix& matrix) {
    if(row!=matrix.row || col!=matrix.col){
        throw std::invalid_argument("mat size is different");
    }
    for(unsigned int i=0;i<mat.size();i++){
        mat[i]-=matrix.mat[i];
    }
    return *this;
}
/**
 * Subtracts a value from the matrix
 * @param sub
 * @return
 */
zich::Matrix zich::Matrix::operator-=(double sub) {
    *this+=-sub;
    return *this;
}
/**
 * [1,2,3] [1,2]
 * [1,2,3] [1,2]
 * [1,2,3] [1,2]
 * Using matrix multiplication algorithm to multiply two matrices
 * @param matrix
 * @return
 */
zich::Matrix zich::Matrix::operator*(const zich::Matrix &matrix) const {
    // verifies matrix size
    if(col!=matrix.row){
        throw std::invalid_argument("mat size is different");
    }
    // 3x3 3x2 3x2
    // create a 0 given matrix
    zich::Matrix ans(0,row,matrix.col);
    if(col!=matrix.row){
        throw std::invalid_argument("mat size is different");
    }
    // 3x3 3x2 3x2
    // multiply the matrix after and puts the answer in ans matrix
    double res=0;
    for (unsigned int k = 0; k <matrix.col ;k++) {
        for (unsigned int i = 0; i < row; i++) {
            for (unsigned int j = 0; j < col; j++) {
                res+= get_ind(i,j)*matrix.get_ind(j,k);
            }
            ans.set(i,k,res);
            res=0;
        }
    }
    return ans;
}
/**
 * Since I use one vector I created a function that  allows me to treat it like a 2 dimension array for convenience
 * @param i
 * @param j
 * @return
 */
double zich::Matrix::get_ind(unsigned int i, unsigned int j) const {
    return mat[i*col+j];
}
/**
 * Sets the value same as get just modifies the value
 * @param i
 * @param j
 * @param value
 */
void zich::Matrix::set(unsigned int i, unsigned int j,double value) {
    mat[i*col+j]=value;
}
/**
 * multiple all the parameters in the vector
 * @param mult
 * @return
 */
zich::Matrix zich::Matrix::operator*(double mult) {
    zich::Matrix ans(mat,row,col);
    ans*=mult;
    return ans;
}
/**
 * Multiply 2 matrices
 * @param matrix
 * @return
 */
zich::Matrix zich::Matrix::operator()(const zich::Matrix &matrix) const {
    return *this*matrix;
}

zich::Matrix zich::Matrix::operator()(double mult) {
    return *this*mult;
}
/**
 * A function to print the given matrices
 * @param os
 * @param matrix
 * @return
 */
std::ostream &zich::operator<<(std::ostream &os, const zich::Matrix &matrix) {
    for(unsigned int i=0;i<matrix.row;i++){
        os << "[";
        for (unsigned int j = 0; j < matrix.col; j++) {
            os << matrix.get_ind(i, j);
            if (j != matrix.col - 1) {
                os << " ";
            }
        }
        if(i!=matrix.row-1) {
            os << "]\n";
        }
        else{
            os << "]";
        }
    }
    return os;
}
/**
 * Returns a new matrix with the negative values of the given matrix
 * @param matrix
 * @return
 */
zich::Matrix zich::operator-(zich::Matrix &matrix) {
    return matrix *-1;
}
/**
 * Multiply double and matrix
 * @param mult
 * @param matrix
 * @return
 */
zich::Matrix zich::operator*(double mult, zich::Matrix &matrix) {
    return matrix*mult;
}

/**
 * Multiply double and a matrix and changes the given matrix
 * @param mult
 * @return
 */
zich::Matrix zich::Matrix::operator*=(double mult) {

    for(double &i:mat){
        i=i*mult;
    }
    return *this;
}
/**
 * Gets the sum of all the matrix values
 * @return
 */
double zich::Matrix::sum() const {
    double sum=0;
    for(double i:mat){
        sum+=i;
    }
    return sum;
}
/**
 * Check if one matrix is bigger than the other
 * @param matrix
 * @return
 */
bool zich::Matrix::operator>(const zich::Matrix &matrix) const {
    if(row!=matrix.row || col!=matrix.col){
        throw std::invalid_argument("not the same size");
    }
    return this->sum() > matrix.sum();
}
/**
 * Check if a matrix is smaller than the other
 * @param matrix
 * @return
 */
bool zich::Matrix::operator<(const zich::Matrix &matrix) const {
    if(row!=matrix.row || col!=matrix.col){
        throw std::invalid_argument("not the same size");
    }
    return this->sum() < matrix.sum();
}
/**
 * Check if a matrix is equal to the other
 * @param matrix
 * @return
 */
bool zich::Matrix::operator==(const zich::Matrix &matrix) const{
    if(row!=matrix.row || col!=matrix.col){
        throw std::invalid_argument("not the same size");
    }
    for(unsigned int i=0;i<mat.size();i++){
        if(mat[i]!=matrix.mat[i]){
            return false;
        }
    }
    return true;
}
/**
 * Check if matrix is bigger or equal to the other.
 * @param matrix
 * @return
 */
bool zich::Matrix::operator>=(const zich::Matrix &matrix) const {
    return *this == matrix || *this > matrix;
}
/**
 * Check if matrix is smaller or equal to the other
 * @param matrix
 * @return
 */
bool zich::Matrix::operator<=(const zich::Matrix &matrix) const {
    return *this < matrix || *this ==matrix;
}
/**
 * returns a deep copy of the matrix
 * @param matrix
 * @return
 */
zich::Matrix zich::operator+(zich::Matrix &matrix) {
    return {matrix.mat, matrix.row, matrix.col};
}
/**
 * Gets the value of the matrix in the i th place
 * @param i
 * @return
 */
double zich::Matrix::operator[](unsigned int i) {
    return mat[i];
}
/**
 * Split 2 strings based on a delimeter
 * @param s
 * @param delim
 * @return
 */
std::vector<std::string> split(std::string mat, char delim){
    std::vector<std::string> splited;
    std::string add;
    for(unsigned int i=0;i<mat.length();i++){
        if(mat[i]!=delim){
            if(mat[i]!='[' && mat[i]!=']') {
                add += mat[i];
            }
        }
        else{
            if(add.length()!=0) {
                splited.push_back(add);
                add = "";
            }
        }
    }
    if(add.length()!=0) {
        splited.push_back(add);
    }
    return splited;
}
/**
 * Validate that a cin string is according to the given format
 * @param mat
 */
void validate(std::string mat){
    bool t = true;
    for(unsigned int i=0;i<mat.length()-1;i++){
        if(mat[i]=='[' && (mat[i+1]<'0' || mat[i+1]>'9') && mat[i+1]!=' ' && t){
            throw std::invalid_argument("invalid string");
        }
        if(mat[i]==',' && mat[i+1]!=' '){
            throw std::invalid_argument("invalid string");
        }
        if(mat[i]==']' && mat[i+1]!=','){
            throw std::invalid_argument("invalid string");
        }
        if(mat[i]!=']' && mat[i]!='[' && mat[i]!=',' && mat[i]!=' ' && (mat[i]<'0' || mat[i]>'9') && mat[i]!='.'){
            throw std::invalid_argument("invalid string");
        }
    }
}
/**
 * changes a given matrix according to the given stream
 * @param stream
 * @param matrix
 * @return
 */
std::istream &zich::operator>>(std::istream &stream, zich::Matrix &matrix) {
    std::string mat;
    char ch=stream.get();
    matrix = Matrix();
    while(ch!='\n' && ch!=-1){
        mat+=ch;
        ch=stream.get();
    }
    validate(mat);
    std::vector<std::string > sa = split(mat, ',');
    unsigned int size=0;
    for(auto & i : sa){
        std::vector<std::string> sap = split(i,' ');
        if(size!=0 && sap.size()!=size){
            throw std::invalid_argument("col length does not match");
        }
        size=sap.size();
        for(auto & j : sap){
            matrix.mat.push_back(stod(j));
        }
    }
    matrix.row=sa.size();
    matrix.col=size;

    return stream;
}
/**
 * Operator *= multiply both matrices and changes the value of the first matrix returns a reference
 * @param matrix
 * @return
 */
zich::Matrix zich::Matrix::operator*=(const zich::Matrix &matrix) {
    if(col!=matrix.row){
        throw std::invalid_argument("mat size is different");
    }
    *this = *this * matrix;
    return *this;
}
/**
 * Operator not equal
 * @param matrix
 * @return
 */
bool zich::Matrix::operator!=(const zich::Matrix &matrix) const {
    return !(*this==matrix);
}

/**
 * Default empty constructor
 */
zich::Matrix::Matrix() = default;

/**
 * Default empty destructor
 */
zich::Matrix::~Matrix() = default;




