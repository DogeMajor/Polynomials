#ifndef POLY_H
#define POLY_H

#include <vector>
#include <math.h>
#include <iostream>
#include <algorithm>
using namespace std;
//template class of polynomes with arbitrary coefficients (T1) and elements (T2) as parameters x in p(x)
//The "product" of T1 and T2 must be well defined, i.e. a*b must be a member of T2 when a belongs to T1 and b belongs to T2

template <class T1, class T2>
class Poly{
    
private:
    int degree;//You can have a polynomial consisting of several zeros, i.e. it can happen that coeff.size()!=degree
    unsigned int length;
    vector <T1> coeff;

public:
    Poly();
    Poly(int l);
    ~Poly();
    
    void add(T1 a);
    void set_coeff(vector <T1> c);
    void update();
    T2 calc(T2 x) const;
    void show() const;
    
    T1 operator[](unsigned int i) const;
    Poly operator+(const Poly b) const;
    Poly operator-(const Poly b) const;
    Poly operator*(const Poly b) const;
    Poly operator*(const T1 b) const;
    
    friend Poly<T1,T2> operator*(const T1 a, const Poly b){
            return b*a;//Has to be defined inside the class brackets!!!
            //Refers to the overloaded operator Op*(const T1 a)
    }
    

    
};

//Template class member functions

template <class T1, class T2>
Poly<T1,T2>::Poly(){

    degree=-1;//Degree of the polynome p(x)=0
    length=1;
    vector <T2> temp(length);
    coeff=temp;
}
//OK

template <class T1, class T2>
Poly<T1,T2>::Poly(int l){
    degree=-1;
    length=l;
    vector <T2> temp(length);
    coeff=temp;
}
//OK! Only works with temp vector being initialized first.
//Degree is always one less than the lengt of the polynomial vector coeff; except for when p(x)=0, then degree(p)=-1

template <class T1, class T2>
Poly<T1,T2>::~Poly(){
    
}
//OK

template <class T1, class T2>
void Poly<T1,T2>::add(T1 a){
    if(degree!=-1){
        coeff.push_back(a);
        length++;
        }
    else{
        coeff[0]=a;
        }
    update();
}
//OK

template <class T1, class T2>
void Poly<T1,T2>::set_coeff(vector <T1> c){
    coeff=c;
    //degree=coeff.size()-1;
    //length=coeff.size();
    update();
}
//OK

template <class T1, class T2>
void Poly<T1,T2>::update(){
    int i=coeff.size();
    degree=i-1;
    length=coeff.size();
    for(int j=length-1;j>0;j--){
        if(coeff[j]!=0){
            degree=j; 
            break;
            }
        }
    //Resets the coeff vector to proper lenght.
    if(degree!=-1){
    vector <T1> temp(degree+1);
    for(int j=0; j<degree+1; j++){
        temp[j]=coeff[j];
        }
    coeff=temp;
    length=coeff.size();//Not necessarily needed!
    }
    else{
        vector <T1> temp(1);
        coeff=temp;
        length=1;
        }
}
//OK

template <class T1, class T2>
T2 Poly<T1,T2>::calc(T2 x) const{
    T2 result=0;
    for(unsigned int i=0; i<coeff.size(); i++){
        result+=coeff[i]*pow(x,i);
        }
    return result;
}
//OK

template <class T1, class T2>
void Poly<T1,T2>::show() const{
    cout<<"Length, degree and coefficients from a_(n-1) to a_0"<<endl;
    cout<<length<<endl;
    cout<<degree<<endl;
    for(unsigned int i=0; i<coeff.size(); i++){
        cout<<coeff[i]<<" ";
        }
    cout<<endl;
}
//OK

//Overloaded operators
template <class T1, class T2>
T1 Poly<T1,T2>::operator[](unsigned int i) const{
    if(i>coeff.size()){
        cerr<<"operator[]: Wrong dimension!";
        exit(1);
    }
    else {
        return coeff[i];
        }
}
//OK

template <class T1, class T2>
Poly<T1,T2> Poly<T1,T2>::operator+(const Poly b) const{
    
    int mini = min(degree,b.degree);
    int maxi = max(degree,b.degree);
    Poly Result(maxi+1);
    
    for(int i=0; i<mini+1;i++){
        Result.coeff[i]=coeff[i]+b.coeff[i];
        }
    for(int i=mini+1; i<maxi+1;i++){
        Result.coeff[i]=(degree>b.degree ? coeff[i] : b.coeff[i]) ;
        }//To make sure random elements of vectors coeff and b.coeff outside of range are not added!
    Result.update();
    return Result;
}
//OK

template <class T1, class T2>
Poly<T1,T2> Poly<T1,T2>::operator-(const Poly b) const{
    
    int mini = min(degree,b.degree);
    int maxi = max(degree,b.degree);
    Poly Result(maxi+1);
    
    for(int i=0; i<mini+1;i++){
        Result.coeff[i]=coeff[i]-b.coeff[i];
        }
    for(int i=mini+1; i<maxi+1;i++){
        Result.coeff[i]=(degree>b.degree ? -coeff[i] : -b.coeff[i]) ;
        }//To make sure random elements of vectors coeff and b.coeff outside of range are not added!
    Result.update();
    return Result;
}
//OK

template <class T1, class T2>
Poly<T1,T2> Poly<T1,T2>::operator*(const Poly b) const{
    Poly A=*this;
    Poly B=b;
    
    int da =A.degree+1;
    int db = B.degree+1;
    int size = A.degree+B.degree+2;
    B.coeff.insert(B.coeff.begin()+db,size-db,0);//Insert zeros to make the multiplication easier in the sum expressions
    A.coeff.insert(A.coeff.begin()+da,size-da,0);

    switch(da!=0 && db!=0){
        case(true): {
            Poly Result(size-1);
            for(int n=0; n<size-1;n++){
                for(int i=0; i<=n;i++){
                    Result.coeff[n]+=A.coeff[i]*B.coeff[n-i];
                    }
                }
            Result.update();
            return Result; 
            break;
            }
        case(false): {
            Poly Result(1);
            Result.coeff[0]=0;
            Result.update(); 
            return Result;
            break;
            }
        }
}
//OK

template <class T1, class T2>
Poly<T1,T2> Poly<T1,T2>::operator*(const T1 b) const{
    Poly B;
    B.add(b);
    Poly A=*this;
    return A*B;
}
//OK

#endif