/**
 * An example of how to write unit tests.
 * Use this as a basis to build a more complete Test.cpp file.
 *
 * IMPORTANT: Please write more tests - the tests here are only for example and are not complete.
 *
 * AUTHORS: <Please write your names here>
 *
 * Date: 2021-02
 */

#include "doctest.h"
#include "Matrix.hpp"
using namespace zich;


using namespace std;


vector<double> vector_gen(unsigned int num,double value=0){
    vector<double> mat(num);
    for(unsigned int i=0;i<num;i++) {
        mat[i] = value;
    }
    return mat;
}

TEST_CASE("Constructor") {
    for(unsigned int i=0;i<100;i++){
        CHECK_THROWS(Matrix({1,1},i,i));
    }
    for(unsigned int i=0;i<100;i++){
        CHECK_NOTHROW(Matrix(vector<double>(i*i),i,i));
    }
}



TEST_CASE("++ and --") {
    vector <double>mat_plus = vector_gen(1000);
    vector <double>mat_minus = vector_gen(1000);
    Matrix p(mat_plus,10,100);
    Matrix k(mat_minus,10,100);
    for(double i=1;i<11;i++){
        p++;
        k--;
        for(unsigned int j=0;j<1000;j++){
                    CHECK_EQ(p[j],i);
                    CHECK_EQ(k[j],-i);
        }
    }
    for(unsigned int i=0;i<1000;i++){
        mat_plus[i]=9;
    }
    Matrix l(mat_plus,10,100);
            CHECK_EQ(l,--p);
            CHECK_EQ(-l,++k);
}

TEST_CASE("check +double and +matrix") {
    vector<double> vec = vector_gen(1000);
    Matrix mat(vec,100,10);
    double ans=0;
        for(double i=0;i<1000;i++){
            mat+=i;
            ans+=i;
            for(unsigned int j=0;j<1000;j++){
                CHECK_EQ(mat[j],ans);
            }
        }

    vec = vector_gen(1000,5);
    mat=Matrix(vec,100,10);


    vec = vector_gen(1000,10);
    Matrix m1(vec,100,10);
    for(unsigned int i=1;i<100;i++){
        mat+=m1;
        mat = mat+m1;
        for(unsigned int j=0;j<1000;j++){
            CHECK_EQ(mat[j],5+i*20);
        }
    }


}


TEST_CASE("check -double and -matrix") {
    vector<double> vec = vector_gen(1000);
    Matrix mat(vec,100,10);
    double ans=0;
    for(double i=0;i<1000;i++){
        mat-=i;
        mat= mat -i;
        ans-=2*i;
        for(unsigned int j=0;j<1000;j++){
                    CHECK_EQ(mat[j],ans);
        }
    }

    vec = vector_gen(1000,5);
    mat=Matrix(vec,100,10);


    vec = vector_gen(1000,10);
    Matrix m1(vec,100,10);
    for(int i=1;i<100;i++){
        mat-=m1;
        mat = mat-m1;
        for(unsigned int j=0;j<1000;j++){
                    CHECK_EQ(mat[j],5+(-i*20));
        }
    }
}