#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <numeric>
#include <cmath>

#include "doctest.h"

class Rational {
    int n_;
    int d_;

    public:
    Rational(int num = 0, int den = 1) : n_{num}, d_{den}
    {
        if (den == 0){
            throw std::runtime_error{"Denominator is zero"};
        }
    auto g = std::gcd(n_, d_);
    n_ /=g;
    d_ /=g;
    if (d_ < 0){
        n_ = -n_;
        d_ = -d_;
    }
    }

    int num() const {return n_; }
    int den() const {return d_; }

    void print() const {
        std::cout << '\n'
              << n_ << "\n- = " << num() / den() << '\n'
              << d_ << "\n\n";
    }
};

bool operator==(Rational const& r1, Rational const& r2){
    return (r1.num() == r2.num() && r1.den() ==r2.den());
}

Rational operator+(Rational const& r1, Rational const& r2){
    int den1 = std::lcm(r1.den(), r2.den());
    int num1 = (r1.den() * r2.num()) + (r1.num() * r2.den());
    return Rational {num1, den1};
}

Rational operator-(Rational const& r1, Rational const& r2){
    int den1 = std::lcm(r1.den(), r2.den());
    int num1 = - (r1.den() * r2.num()) + (r1.num() * r2.den());
    return Rational {num1, den1};
}

Rational operator*(Rational const& r1, Rational const& r2){
    return Rational {r1.num() * r2.num(), r1.den() * r2.den()}; //non serve controllare il denominatore, c'é giá il runtime error nella classe.
}

Rational operator/(Rational const& r1, Rational const& r2){
    return Rational {r1.num() * r2.den (), r1.den() * r2.num()};
}

Rational rpow (Rational const& r1, int exp){
    if(!(std::cin.good())){
        throw std::runtime_error{"Non int exponential."};
    }
    if (exp == 0){
        return Rational{1, 1};
    }
    Rational r = {1, 1};
     if (exp < 0){
        exp = -exp;
        for (int i = 1; i <= exp; ++i){
            r = r * r1;
        }
        Rational c = Rational{1, 1} / r;
        return c;
    }
    else{
        for (int i = 1; i <= exp; ++i){
            r = r * r1;
        }
        return r;
    }
}

TEST_CASE ("Testing Rational class"){

    SUBCASE("Null denominator"){ 
    CHECK_THROWS_WITH_AS(Rational (1, 0), "Denominator is zero", std::runtime_error);
    CHECK_THROWS_WITH_AS(Rational (1, -0), "Denominator is zero", std::runtime_error);
    }

    SUBCASE("Negative denominator"){
        Rational a{1, -1};
        CHECK(a.num() == -1);
        CHECK(a.den() == 1);

        Rational b{-1, -1};
        CHECK(b.num() == 1);
        CHECK(b.den() == 1);
    }

    SUBCASE("Reduced francion"){
        Rational a{48, 8};
        CHECK(a.num() == 6);
        CHECK(a.den() == 1);

        Rational b{6, 12};
        CHECK(b.num() == 1);
        CHECK(b.den() == 2);

        Rational c{0, 12};
        CHECK(c.num() == 0);
        CHECK(c.den() == 1);

        Rational d{0, -12};
        CHECK(d.num() == 0);
        CHECK(d.den() == 1);
    }

    SUBCASE("operator+"){
        Rational a{48, 8};
        Rational b{6, 12};
        CHECK(a + b == Rational {13, 2});
    }

    SUBCASE("operator-"){
        Rational a{48, 8};
        Rational b{6, 12};
        CHECK(a - b == Rational {11, 2});
    }

    SUBCASE("operator*"){
        Rational a{48, 8};
        Rational b{6, 12};
        CHECK(a * b == Rational {3, 1});
    }

    SUBCASE("operator/"){
        Rational a{48, 8};
        Rational b{6, 12};
        CHECK(a / b == Rational {12, 1});
    }

    SUBCASE("rpow function "){
        Rational a{2, 8};
        int exp = 3;
        CHECK(rpow (a, exp) == Rational {1, 64});

        Rational b{6, 12};
        int exp1 = -3;
        CHECK(rpow (b, exp1) == Rational {8, 1});

        int exp2 = 0;
        CHECK(rpow (b, exp2) == Rational {1, 1});
    }
}