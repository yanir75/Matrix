#include "Matrix.hpp"
#include <stdexcept>
#include <iostream>
#include <string>


zich::Matrix::Matrix(std::vector<double> matrix, unsigned int row, unsigned int col) :mat(row*col) {
    if(matrix.size()!= row*col){
        throw std::invalid_argument("Matrix size is not right");
    }
    this->row = row;
    this->col = col;
    for(unsigned int i=0;i<matrix.size();i++){
        mat[i]=matrix[i];
    }
}

zich::Matrix::Matrix(double value, unsigned int row, unsigned int col): mat(row*col) {
    this->row = row;
    this->col = col;
    for(unsigned int i=0;i<row*col;i++){
        mat[i]=value;
    }

}


zich::Matrix zich::Matrix::operator+(const zich::Matrix &matrix) {
    if(row!=matrix.row || col!=matrix.col){
        throw std::invalid_argument("mat size is different");
    }
    zich::Matrix ans(mat,row,col);
    ans+=matrix;
    return ans;
}

zich::Matrix zich::Matrix::operator+(double add) {
    zich::Matrix ans(mat,row,col);
    ans+=add;
    return ans;
}

zich::Matrix &zich::Matrix::operator++() {
    *this +=1;
    return *this;
}

zich::Matrix zich::Matrix::operator++(int ind) {
    const zich::Matrix ans(mat,row,col);
    ++*this;
    return ans;
}

zich::Matrix zich::Matrix::operator+=(const zich::Matrix& matrix) {

    if(row!=matrix.row || col!=matrix.col){
        throw std::invalid_argument("mat size is different");
    }
    for(unsigned int i=0;i<mat.size();i++){
        mat[i]+=matrix.mat[i];
    }
    return *this;
}

zich::Matrix zich::Matrix::operator+=(double add) {
    for(double &i:mat){
        i+=add;
    }
    return *this;
}

zich::Matrix zich::Matrix::operator-(double sub) {
    zich::Matrix ans=*this+-sub;
    return ans;
}


zich::Matrix zich::Matrix::operator-(const zich::Matrix &matrix) {
    if(row!=matrix.row || col!=matrix.col){
        throw std::invalid_argument("mat size is different");
    }
    zich::Matrix ans(mat,row,col);
    ans-=matrix;
    return ans;
}

zich::Matrix &zich::Matrix::operator--() {
    *this += -1;
    return *this;
}

zich::Matrix zich::Matrix::operator--(int sub) {
    zich::Matrix ans(mat,row,col);
    *this+=-1;
    return ans;
}

zich::Matrix zich::Matrix::operator-=(const zich::Matrix& matrix) {
    if(row!=matrix.row || col!=matrix.col){
        throw std::invalid_argument("mat size is different");
    }
    for(unsigned int i=0;i<mat.size();i++){
        mat[i]-=matrix.mat[i];
    }
    return *this;
}

zich::Matrix zich::Matrix::operator-=(double sub) {
    *this+=-sub;
    return *this;
}
/**
 * [1,2,3] [1,2]
 * [1,2,3] [1,2]
 * [1,2,3] [1,2]
 * @param matrix
 * @return
 */
zich::Matrix zich::Matrix::operator*(const zich::Matrix &matrix) const {
    if(col!=matrix.row){
        throw std::invalid_argument("mat size is different");
    }
    // 3x3 3x2 3x2
    zich::Matrix ans(0,row,matrix.col);
    ans*=matrix;
    return ans;
}

double zich::Matrix::get_ind(unsigned int i, unsigned int j) const {
    return mat[i*col+j];
}

void zich::Matrix::set(unsigned int i, unsigned int j,double value) {
    mat[i*col+j]=value;
}

zich::Matrix zich::Matrix::operator*(double mult) {
    zich::Matrix ans(mat,row,col);
    ans*=mult;
    return ans;
}

zich::Matrix zich::Matrix::operator()(const zich::Matrix &matrix) const {
    return *this*matrix;
}

zich::Matrix zich::Matrix::operator()(double mult) {
    return *this*mult;
}

std::ostream &zich::operator<<(std::ostream &os, const zich::Matrix &matrix) {
    for(unsigned int i=0;i<matrix.row;i++){
        os << '[';
        for (unsigned int j = 0; j < matrix.col; j++) {
            os << matrix.get_ind(i,j) << " ";
        }
        os << "]\n";
    }
    return os;
}

zich::Matrix zich::operator-(zich::Matrix &matrix) {
    return matrix *-1;
}

zich::Matrix zich::operator*(double mult, zich::Matrix &matrix) {
    return matrix*mult;
}


zich::Matrix zich::Matrix::operator*=(double mult) {

    for(double &i:mat){
        i=i*mult;
    }
    return *this;
}

double zich::Matrix::sum() const {
    double sum=0;
    for(double i:mat){
        sum+=i;
    }
    return sum;
}

bool zich::Matrix::operator>(const zich::Matrix &matrix) const {
    return this->sum() > matrix.sum();
}

bool zich::Matrix::operator<(const zich::Matrix &matrix) const {
    return this->sum() < matrix.sum();
}

bool zich::Matrix::operator==(const zich::Matrix &matrix) const{
    if(col !=matrix.col || row != matrix.row){
        return false;
    }
    for(unsigned int i=0;i<mat.size();i++){
        if(mat[i]!=matrix.mat[i]){
            return false;
        }
    }
    return true;
}

bool zich::Matrix::operator>=(const zich::Matrix &matrix) const {
    return *this == matrix || *this > matrix;
}

bool zich::Matrix::operator<=(const zich::Matrix &matrix) const {
    return *this < matrix || *this >matrix;
}

zich::Matrix zich::operator+(zich::Matrix &matrix) {
    return {matrix.mat, matrix.row, matrix.col};
}

double zich::Matrix::operator[](unsigned int i) {
    return mat[i];
}
std::vector<std::string> split(std::string s, char delim){
    std::vector<std::string> splited;
    std::string add;
    for(unsigned int i=0;i<s.length();i++){
        if(s[i]!=delim){
            if(s[i]!='[' && s[i]!=']') {
                add += s[i];
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


std::istream &zich::operator>>(std::istream &stream, zich::Matrix &matrix) {
    std::string s;
    char ch=stream.get();
    while(ch!='\n'){
        s+=ch;
        ch=stream.get();
    }
    std::vector<std::string > sa = split(s, ',');
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

zich::Matrix zich::Matrix::operator*=(const zich::Matrix &matrix) {
    if(col!=matrix.row){
        throw std::invalid_argument("mat size is different");
    }
    // 3x3 3x2 3x2
    double res=0;
    for (unsigned int k = 0; k <matrix.col ;k++) {
        for (unsigned int i = 0; i < row; i++) {
            for (unsigned int j = 0; j < col; j++) {
                res+= get_ind(i,j)*matrix.get_ind(j,k);
            }
            set(i,k,res);
            res=0;
        }
    }
    return *this;
}


zich::Matrix::Matrix() = default;


zich::Matrix::~Matrix() = default;




