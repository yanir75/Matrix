#include "Matrix.hpp"
#include <stdexcept>

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
    for(unsigned int i=0;i<mat.size();i++){
        ans.mat[i]+=matrix.mat[i];
    }
    return ans;
}

zich::Matrix zich::Matrix::operator+(double add) {
    zich::Matrix ans(mat,row,col);
    for(double &i:ans.mat){
        i+=add;
    }
    return ans;
}

zich::Matrix &zich::Matrix::operator++() {
    *this = *this+1;
    return *this;
}

const zich::Matrix zich::Matrix::operator++(int ind) {
    const zich::Matrix ans(mat,row,col);
    ++*this;
    return ans;
}

zich::Matrix zich::Matrix::operator+=(const zich::Matrix& matrix) {
    *this = *this+matrix;
    return *this;
}

zich::Matrix zich::Matrix::operator+=(double add) {
    *this = *this+add;
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
    for(unsigned int i=0;i<mat.size();i++){
        ans.mat[i]-=matrix.mat[i];
    }
    return ans;
}

zich::Matrix &zich::Matrix::operator--() {
    *this = *this -1;
    return *this;
}

const zich::Matrix zich::Matrix::operator--(int sub) {
    zich::Matrix ans(mat,row,col);
    *this=*this-1;
    return ans;
}

zich::Matrix zich::Matrix::operator-=(const zich::Matrix& matrix) {
    *this = *this-matrix;
    return *this;
}

zich::Matrix zich::Matrix::operator-=(double sub) {
    *this = *this-sub;
    return *this;
}
/**
 * [1,2,3] [1,2]
 * [1,2,3] [1,2]
 * [1,2,3] [1,2]
 * @param matrix
 * @return
 */
zich::Matrix zich::Matrix::operator*(const zich::Matrix &matrix) {
    if(col!=matrix.row){
        throw std::invalid_argument("mat size is different");
    }
    // 3x3 3x2 3x2
    double res=0;
    zich::Matrix ans(0,row,matrix.col);
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

double zich::Matrix::get_ind(unsigned int i, unsigned int j) const {
    return mat[i*col+j];
}

void zich::Matrix::set(unsigned int i, unsigned int j,double value) {
    mat[i*col+j]=value;
}

zich::Matrix zich::Matrix::operator*(double mult) {
    zich::Matrix ans(mat,row,col);
    for(double &i:ans.mat){
        i=i*mult;
    }
    return ans;
}

zich::Matrix zich::Matrix::operator()(const zich::Matrix &matrix) {
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
    *this =*this*mult;
    return *this;
}


zich::Matrix::~Matrix() = default;





