#include <iostream>
#include <vector>
namespace zich{

    class Matrix{
    private:
        unsigned int row{};
        unsigned int col{};
        std::vector<double> mat;
    public:
        // Constructor getting array and number of rows and cols
        Matrix(std::vector<double> matrix,int row,int col);
        Matrix(std::vector<double> matrix,unsigned int row,unsigned int col);
        Matrix(double value,unsigned int row,unsigned int col);
        Matrix();
        // destructor getting an array and number of rows and cols
        ~Matrix();
        // operator ++ overloading
        Matrix  operator ++(int ind);
        // ++operator overloading
        Matrix& operator ++();
        // + another matrix and double
        Matrix operator +(const Matrix& matrix);
        Matrix operator +(double add);
        // += operator for matrix
        Matrix operator +=(const Matrix& matrix);
        Matrix operator +=(double add);
        [[nodiscard]] double get_ind(unsigned int i,unsigned int j) const;
        void set(unsigned int i,unsigned int j,double value);
        // operator multiplication
        Matrix operator *(const Matrix& matrix) const;
        Matrix operator *(double mult);
        //
        Matrix operator *=(double mult);
        Matrix operator *=(const Matrix& matrix);

        Matrix operator ()(const Matrix& matrix) const;
        Matrix operator ()(double mult);
        // operator -- overloading
        Matrix operator --(int sub);
        // --operator overloading
        Matrix& operator --();
        // + another matrix and double
        Matrix operator -(const Matrix &matrix);
        Matrix operator -(double sub);
        // += operator for matrix
        Matrix operator -=(const Matrix& matrix);
        Matrix operator -=(double sub);

        bool operator >(const Matrix& matrix) const;
        bool operator <(const Matrix& matrix) const;
        bool operator ==(const Matrix& matrix) const;
        bool operator !=(const Matrix& matrix) const;

        bool operator >=(const Matrix& matrix) const;
        bool operator <=(const Matrix& matrix) const;

        [[nodiscard]] double sum() const;

        double operator [](unsigned int i);

        friend std::ostream& operator<<(std::ostream& os,const Matrix &matrix);
        friend std::istream& operator>> (std::istream& stream, Matrix &matrix);

        friend Matrix operator-(Matrix &matrix);
        friend Matrix operator+(Matrix &matrix);
        friend Matrix operator*(double mult,Matrix &matrix);



    };
}
