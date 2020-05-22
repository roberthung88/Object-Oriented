#include <stdexcept>
#include "rational.h"
#include "stdio.h"
#include <string.h>
#include <string>
#include <cmath>

Rational::Rational()
{
    n = 0;
    d = 1;
}
Rational::Rational(int num, int denom)
{
    if (denom == 0) throw std::invalid_argument("Can't have denom = 0");
    n = num;
    d = denom;
    this->reduce();
    this->normalize0();
}

void Rational::normalize0()
{
    if (n == 0 && d != 1) d = 1;
}

void Rational::reduce(){
    int div = Rational::gcd(n, d);
    n /= div;
    d /= div;
}

//Rational + Rational
Rational Rational::operator+(const Rational &rhs){
    Rational temp;
    temp.n = (Rational::lcm(d, rhs.d) / d) * n + (Rational::lcm(d, rhs.d) / rhs.d) * rhs.n;
    temp.d = Rational::lcm(d, rhs.d);
    temp.reduce();
    temp.normalize0();
    return temp;
}

//int + Rational
Rational operator+(const int& lhs, const Rational &rhs){
    Rational temp(lhs, 1);
    return temp + rhs;
}

//Rational + int
Rational operator+(const Rational& lhs, const int& rhs){
    Rational temp(rhs,1);
    return temp + lhs;
}

//Rational * Rational
Rational Rational::operator*(const Rational &rhs){
    Rational temp;
    temp.n = n * rhs.n;
    temp.d = d * rhs.d;
    temp.reduce();
    temp.normalize0();
    return temp;
}
//int * Rational
Rational operator*(const int& lhs, const Rational &rhs){
    Rational temp(lhs,1);
    return temp * rhs;
}
//Rational * int
Rational operator*(const Rational& lhs, const int& rhs){
    Rational temp(rhs,1);
    return temp * lhs;
}

//^
Rational operator^(const Rational& lhs, const int& rhs){
    Rational temp;
    if(rhs > 0){
        temp.n = pow(lhs.n, rhs);
        temp.d = pow(lhs.d, rhs);
    }else{
        temp.n = pow(lhs.d, rhs*-1);
        temp.d = pow(lhs.n, rhs*-1);
    }
    temp.reduce();
    temp.normalize0();
    return temp;
}

//==
bool operator==(const Rational&lhs, const Rational& rhs){
    Rational temp(lhs.n,lhs.d);
    Rational temp1(rhs.n,rhs.d);
    temp.reduce();
    temp.normalize0();
    temp1.reduce();
    temp1.normalize0();
    if(temp.n == temp1.n && temp.d == temp1.d){
        return true;
    }else{
        return false;
    }
}

//!=
bool operator!=(const Rational&lhs, const Rational& rhs){
    Rational temp(lhs.n,lhs.d);
    Rational temp1(rhs.n,rhs.d);
    temp.reduce();
    temp.normalize0();
    temp1.reduce();
    temp1.normalize0();
    if(temp.n != temp1.n || temp.d != temp1.d){
        return true;
    }else{
        return false;
    }
}

//<
bool operator<(const Rational&lhs, const Rational& rhs){
    double temp = lhs.n*1.0/lhs.d*1.0;
    double temp1 = rhs.n*1.0/rhs.d*1.0;
    if(temp < temp1){
        return true;
    }else{
        return false;
    }
}

//+=
Rational Rational::operator+=(const Rational &rhs){
    Rational temp(n,d);
    temp = temp + rhs;
    n = temp.n;
    d = temp.d;
    return temp;
}
Rational Rational::operator+=(const int& lhs){
    Rational temp(n,d);
    temp = temp + lhs;
    n = temp.n;
    d = temp.d;
    return temp;
}

//*=
Rational Rational::operator*=(const Rational &rhs){
    Rational temp(n,d);
    temp = temp * rhs;
    n = temp.n;
    d = temp.d;
    return temp;
}
Rational Rational::operator*=(const int& lhs){
    Rational temp(n,d);
    temp = temp * lhs;
    n = temp.n;
    d = temp.d;
    return temp;
}

std::ostream& operator<<(std::ostream& ostr, const Rational& r){
    if((r.n * 1.0 / r.d * 1.0) >= 0){
        ostr << std::abs(r.n) << "/" << std::abs(r.d);
    }else{
        ostr << "-" << std::abs(r.n) << "/" << std::abs(r.d);
    }
    return ostr;
}

std::istream& operator>>(std::istream& istr, Rational& r){
    std::string input;
    std::string second;
    std::string third;
    int tempint = 0;
    
    istr >> input;
    if (input.find('/') != std::string::npos){
            //found '/'
            int pos = input.find('/');
            if (pos == 0){
                //invalid position
                r.n = 0;
                r.d = 1;
                r.reduce();
                r.normalize0();
                return istr;
                
            }else if(pos != int(input.size() - 1)){
                //not at the end
            
                try{
                    std::string temp = input.substr(0, pos);
                    tempint = std::stoi(temp);
                }
                catch (const std::invalid_argument& ia){
                    //invalid format so set Rational to 0/1
                    r.n = 0;
                    r.d = 1;
                    r.reduce();
                    r.normalize0();
                    return istr;
                }
                //code reaches here only if numerator is valid
                r.n = tempint;
                try{
                    std::string temp = input.substr(pos + 1);
                    tempint = std::stoi(temp);
                }
                catch (const std::invalid_argument& ia){
                    //invalid format so set Rational to 0/1
                    r.n = 0;
                    r.d = 1;
                    r.reduce();
                    r.normalize0();
                    return istr;
                }
                //denominator is valid
                r.d = tempint;
                r.reduce();
                r.normalize0();
                return istr;
            }
    }else{
        // '/' not found
        try{
            tempint = std::stoi(input);
        }
        catch (const std::invalid_argument& ia){
            //first input invalid
            r.n = 0;
            r.d = 1;
            r.reduce();
            r.normalize0();
            return istr;
        }
        r.n = tempint;
        istr >> second;
        if(second.find('/') == std::string::npos){
            //invalid rational number
            r.n = 0;
            r.d = 1;
            r.reduce();
            r.normalize0();
            return istr;
        }else{
            if(second.find('/') == second.size() - 1){
                //read next number to see it it's a proper integer
                istr >> third;
                try{
                    tempint = std::stoi(third);
                }
                catch (const std::invalid_argument& ia){
                    //third input invalid
                    r.n = 0;
                    r.d = 1;
                    r.reduce();
                    r.normalize0();
                    return istr;
                }
                //denominator is valid
                r.d = tempint;
                r.reduce();
                r.normalize0();
                return istr;
            }else{
                third = second.substr(second.find('/') + 1);
                tempint = stoi(third);
                r.d = tempint;
                r.reduce();
                r.normalize0();
                return istr;
            }
            
        }
    }
        r.reduce();
        r.normalize0();
        return istr;
}
