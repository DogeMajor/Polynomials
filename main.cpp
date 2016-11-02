#include <iostream>
#include "Poly.h"
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
int main()
{
    //Some tests regarding the polynomials, can be omitted
    vector <double> v1;
    v1.push_back(1);
    v1.push_back(2);
    Poly <double,double> P1;
    P1.add(2);
    
    cout<<P1[0]<<endl;
    cout<<P1.calc(1)<<endl;
    
    P1.show();
    vector <double> v2;
    v2.push_back(1);
    v2.push_back(2);
    Poly <double,double> P2(1);
    P2.set_coeff(v2);
    //
    P2.add(3);
    P2.add(4);
    P2.show();
    Poly <double,double> P3=P1*P2;
    P3.show();
    Poly <double,double> P4(4);
    P4.update();
    P4.show();
    Poly <double,double> P5(2);
    P5=P2*P2;
    //P5=P2*2.0;
    
    P5.show();
    cout<<P1.calc(-1)<<endl;
    cout<<P2.calc(-1)<<endl;
    cout<<P3.calc(-1)<<endl;
    cout<<P4.calc(-1)<<endl;
    cout<<P5.calc(-1)<<endl;

return 0;
}
