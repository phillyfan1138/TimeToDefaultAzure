#include "AutoDiff.h"

AutoDiff::AutoDiff(double stnd, double dl){
    standard=stnd;
    dual=dl;
}
AutoDiff::AutoDiff(){
    standard=0;
    dual=0;
}
AutoDiff::AutoDiff(double stnd){
    standard=stnd;
    dual=0;
}
double AutoDiff::getStandard() const{
    return standard;
}
double AutoDiff::getDual() const{
    return dual;
}
AutoDiff AutoDiff::add(const AutoDiff &val) const{
   return AutoDiff(standard+val.getStandard(), dual+val.getDual());
}
AutoDiff AutoDiff::add(double val) const{
   return AutoDiff(standard+val, dual);
}
AutoDiff AutoDiff::subtract(const AutoDiff &val) const{
   return AutoDiff(standard-val.getStandard(), dual-val.getDual());
}
AutoDiff AutoDiff::subtract(double val) const{
   return AutoDiff(standard-val, dual);
}
AutoDiff AutoDiff::multiply(const AutoDiff &val) const{
    return AutoDiff(standard*val.getStandard(), standard*val.getDual()+dual*val.getStandard());
}
AutoDiff AutoDiff::multiply(double val) const{
    return AutoDiff(standard*val, dual*val);
}
AutoDiff AutoDiff::recipricol() const{
    return AutoDiff(1.0/standard, -dual/(standard*standard));
}
void AutoDiff::setDual(double val){
    dual=val;
}
void AutoDiff::setStandard(double val){
    standard=val;
}

AutoDiff sin(const AutoDiff &val){
    return AutoDiff(sin(val.getStandard()), cos(val.getStandard())*val.getDual());
}
AutoDiff cos(const AutoDiff &val){
    return AutoDiff(cos(val.getStandard()), -sin(val.getStandard())*val.getDual());
}
AutoDiff exp(const AutoDiff &val){
    return AutoDiff(exp(val.getStandard()), exp(val.getStandard())*val.getDual());
}
AutoDiff log(const AutoDiff &val){
    return AutoDiff(log(val.getStandard()), val.getDual()/val.getStandard());
}
AutoDiff sqrt(const AutoDiff &val){
    double getsqrt=sqrt(val.getStandard());
    return AutoDiff(getsqrt, val.getDual()/(2*getsqrt));
}
AutoDiff erf(const AutoDiff &val){
    return AutoDiff(erf(val.getStandard()), (2.0/sqrt(M_PI))*exp(-val.getStandard()*val.getStandard())*val.getDual());
}
AutoDiff operator+(const AutoDiff &left, const AutoDiff &right){
    return left.add(right);
}
AutoDiff operator+(const AutoDiff &left, double right){
    return left.add(right);
}
AutoDiff operator+(double left, const AutoDiff &right){
    return right.add(left);
}
AutoDiff operator-(const AutoDiff &left, const AutoDiff &right){
    return left.subtract(right);
}
AutoDiff operator-(const AutoDiff &right){
    return AutoDiff(-right.getStandard(), -right.getDual());
}
AutoDiff operator-(const AutoDiff &left, double right){
    return left.subtract(right);
}
AutoDiff operator-(double left, const AutoDiff &right){
    return right.multiply(-1).add(left);
}
AutoDiff operator*(const AutoDiff &left, const AutoDiff &right){
    return left.multiply(right);
}
AutoDiff operator*(const AutoDiff &left, double right){
    return left.multiply(right);
}
AutoDiff operator*(double left, const AutoDiff &right){
    return right.multiply(left);
}
AutoDiff operator/(const AutoDiff &left, const AutoDiff &right){
    return left.multiply(right.recipricol());
}
AutoDiff operator/(const AutoDiff &left, double right){
    return left.multiply(1.0/right);
}
AutoDiff operator/(double left, const AutoDiff &right){
    return right.recipricol().multiply(left);
}
/*AutoDiff& AutoDiff::operator=(const AutoDiff &right){
    //return right;
    
    standard=right.getStandard();
    dual=right.getDual();
}*/
AutoDiff AutoDiff::operator=(double x){
    return AutoDiff(x, 0.0);
}
AutoDiff AutoDiff::operator+=(const AutoDiff &right){
    standard+=right.getStandard();
    dual+=right.getDual();
    return AutoDiff(standard, dual);
}
bool operator==(const AutoDiff &left, const AutoDiff &right){
    return left.getStandard()==right.getStandard() && left.getDual()==right.getDual();
}
bool operator==(double left, const AutoDiff &right){
    return left==right.getStandard();
}
bool operator==(const AutoDiff &left, double right){
    return left.getStandard()==right;
}
bool operator!=(const AutoDiff &left, const AutoDiff &right){
    return left.getStandard()!=right.getStandard() && left.getDual()!=right.getDual();
}
bool operator!=(double left, const AutoDiff &right){
    return left!=right.getStandard();
}
bool operator!=(const AutoDiff &left, double right){
    return left.getStandard()!=right;
}
bool operator>(const AutoDiff &left, const AutoDiff &right){
    return left.getStandard()>right.getStandard();
}
bool operator>(double left, const AutoDiff &right){
    return left>right.getStandard();
}
bool operator>(const AutoDiff &left, double right){
    return left.getStandard()>right;
}
bool operator<(const AutoDiff &left, const AutoDiff &right){
    return left.getStandard()<right.getStandard();
}
bool operator<(double left, const AutoDiff &right){
    return left<right.getStandard();
}
bool operator<(const AutoDiff &left, double right){
    return left.getStandard()<right;
}