#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <cmath>

#include "doctest.h"

class Complex{
    private:
    double r_; 
    double i_;
    public: 
    Complex (double x = 0. , double y = 0. ) : r_{x}, i_{y} {}
    double real () const { return r_; }
    double imag () const { return i_; } 


};

void Print(Complex const& c) {
    std::cout << c.real() << " + i" << c.imag() << "." << std::endl;
}

void PrintPolar(Complex const& c){
    double rr = sqrt((c.real() * c.real())  + (c.imag() * c.imag()));
    double ang = atan(c.imag() / c.real());
    ang = ang / 3.141592;
    std::cout << rr << "(cos(" << ang << " π) + i sin(" << ang << " π))." <<  std::endl;
} 

double norm2(Complex const& c){
    return c.real() * c.real() + c.imag() * c.imag();
}

Complex const conj(Complex const& c){
    return {c.real(), - c.imag()} ;
}



bool operator==(Complex const& c1, Complex const& c2){
    return c1.real() == c2.real() && c1.imag() == c2.imag();
}

Complex operator+(Complex const& c1, Complex const& c2){
    return {c1.real() + c2.real(), c1.imag() + c2.imag()};
}

Complex operator-(Complex const& c1, Complex const& c2){
    return {c1.real() - c2.real(), c1.imag() - c2.imag()};
}

Complex operator*(Complex const& c1, Complex const& c2){
    double r = (c1.real() * c2.real() + -1 * (c1.imag() * c2.imag()) );
    double i = (c1.real() * c2.imag() + c1.imag() * c2.real());
    return Complex{r, i};
}

auto operator/(Complex const& c1, Complex const& c2){
    Complex const& c3= {0., 0.};
    Complex comif = {0., 0.};
    if (c2 == c3){
        throw std::runtime_error {"Denominator is zero."};
        return comif;
    }
    Complex d = c1 * (conj(c2));
    double den = norm2(c2);
    Complex res = {d.real() / den, d.imag() / den};
    return res;
}

Complex pow (Complex const& c1, int exp){
    if(!(std::cin.good())){
        throw std::runtime_error{"Non int exponential."};
    }
    if (exp == 0){
        return Complex{1.0, 0.0};
    }
    Complex r = {1.0, 0.0};
    if (exp < 0){
        exp = -exp;
        for (int i = 1; i <= exp; ++i){
            r = r * c1;
        }
        Complex c = Complex{1.0, 0.0} / r;
        return c;
    }
    else{
        for (int i = 1; i <= exp; ++i){
            r = r * c1;
        }
        return r;
    }
}

TEST_CASE("Testing Complex class"){

    SUBCASE("norm2"){ 
        Complex a{1.0, -1.0};
        CHECK(norm2(a) == 2);

        Complex b{-2., 3.};
        CHECK(norm2(b) == 13);

        Complex c{-3., -4.};
        CHECK(norm2(c) == 25);
    }

    SUBCASE("operator+"){
        Complex a{1.0, -3.0};
        Complex b{-3.0, 4.0};
        CHECK(a + b == Complex{-2.0, 1.0});
    }

    SUBCASE("operator+"){
        Complex a{1.0, -3.0};
        Complex b{-3.0, 4.0};
        CHECK(a - b == Complex{4.0, -7.0});
    }

    SUBCASE("operator*"){
        Complex a{1.0, -3.0};
        Complex b{-3.0, 4.0};
        CHECK(a * b == Complex{9., 13.});
    }

    SUBCASE("operator/"){
        Complex c{1.0, -3.0};
        Complex d{0.0, 0.0};
        CHECK_THROWS_WITH_AS(c / d , "Denominator is zero.", std::runtime_error);

        Complex a{1.0, -3.0};
        Complex b{-3.0, 4.0};
        CHECK(a / b == Complex{- 3.0 / 5.0, 1.0 / 5.0});

        Complex e{1.0, 0.0};
        Complex f{-7., 24.};
        CHECK(e / f == Complex{-7. / 625., -24. / 625.});
    }

    SUBCASE("operator=="){
        Complex a{1.0, -3.0};
        Complex b{-3.0, 4.0};  
        CHECK(!(a == b));

        Complex c{1.0, 4.0};
        Complex d{1.0, 4.0};
        CHECK(c == d);     
    }

    SUBCASE("pow function"){
        Complex a{-3.0, 4.0};
        int exp1 = 3;
        CHECK(pow (a, exp1) == Complex{117, 44});

        Complex b{3.0, 4.0};
        int exp2 = 0;
        CHECK(pow (b, exp2)== Complex{1.0, 0.0});

        int exp3 = -2;
        CHECK(pow (a, exp3)== Complex{-7.0 / 625.0, 24.0 / 625.0});
    }
}