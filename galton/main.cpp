#include "main.hpp"

#include <cmath>
#include <vector>

int Sum(int& j){
int k = 0;
for (size_t i = 0; i < j; i++)
{
    k +=i;
}
return k;
};


Galton::Galton(std::vector<int> mat, int col) : matrix_{mat}, col_{col} {};
std::vector<int> Galton::getMatrix() const {return matrix_;};
int Galton::getCol() const {return col_;}
int Galton::Get_ij(int i, int j) {if (j < col_)
{
    return matrix_[Sum(j) + i];
}else{
return matrix_[Sum(col_) + (j - col_)* col_ + i];
}
}

Simulation::Simulation(std::vector<int> mat, int col) : matrix_{mat}, col_{col} {};
int Simulation::sgetCol() const { return col_; }
int Simulation::sGet_ij(int i, int j) {
  if (j < col_) {
    return matrix_[Sum(j) + i];
  } else {
    return matrix_[Sum(col_) + (j - col_) * col_ + i];
  }
}
void Simulation::evolve(Galton g){
for (size_t i = 0; i < ; i++)
{
    
}

};
