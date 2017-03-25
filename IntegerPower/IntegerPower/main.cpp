#include <iostream>
using namespace std;

bool g_InvalidInput = false;    // 用于区分是否输入的值有错误

bool equal(double n1, double n2){
    
    if(n1 - n2 > -0.0000001 && n1 - n2 < 0.0000001)
        
        return true;
    
    else
    
        return false;
}

double PowerWithUnsignedExponent(double base, unsigned int exponent){
    
    double result = 1.0;
    
    for(int i = 1; i <= exponent; i++)
        
        result *= base;
    
    return result;

}

double PowerWithUnsignedExponent1(double base, int exponent){
    
    if(exponent == 0)
        
        return 1;
    
    if(exponent == 1)
        
        return base;
    
    double result = PowerWithUnsignedExponent1(base, exponent>>1);
    
    result *= result;
    
    if(exponent & 0x1)
        
        result *= base;
    
    return result;

}

double Power(double base, double exponent){
    
    if(equal(base,0.0) && exponent < 0){
        
        g_InvalidInput = true;
        
        return 0.0;
    }
    
    unsigned int absExponent = (unsigned int) exponent;
    
    if(exponent < 0)
        
        absExponent = (unsigned int) -exponent;
    
    double result = PowerWithUnsignedExponent1(base, absExponent);
    
    if(exponent < 0)
        
        return 1.0 / result;
    
    return result;
}





int main(int argc, const char * argv[]) {
    
    double result = Power(2, -3);
    
    double result1 = Power(0, 0);
    
    if(g_InvalidInput == true)
        
        cout<<"您输入的数值有误"<<endl;
    
    else
    
        cout<<result;
    
    return 0;
}
