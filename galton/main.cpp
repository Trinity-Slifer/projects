#include "main.hpp"

#include <cmath>
#include <iostream>
#include <vector>

#include "TRandom.h"

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

Simulation::Simulation(int number, int col) : number_{number}, col_{col} {};
int Simulation::sgetCol() const { return col_; }
int Simulation::sGet_ij(int i, int j) {
  if (j < col_) {
    return matrix_[Sum(j) + i];
  } else {
    return matrix_[Sum(col_) + (j - col_) * col_ + i];
  }
}
void Simulation::evolve(Galton g){
std::vector<int> matrix_;
matrix_.reserve(g.getMatrix().size());
for (size_t i = 0; i < g.getMatrix().size() ; i++)
{
  int row = (g.getMatrix().size() - Sum(g.getCol())) / (Sum(g.getCol())) +
            Sum(g.getCol());
 for (int i = 0; i < row; i++) {
    for (int j = 0; j < i; j++)
    {
        if (g.Get_ij(j,i) != 0)
        {
          for (size_t k = 0; k < matrix_[Sum(i) + j]; k++) {
            double x = gRandom->Rndm();
             if (x <= g.Get_ij(j, i)/2) {
               matrix_[Sum(i) + i + j]+=1; 
             }else{
               matrix_[Sum(i) + i + j + 1] += 1;
             }
            matrix_[Sum(i)+j]=0;
          }
        }
    }
  }
}
for (size_t i = 0; i < g.getCol(); i++)
{
  int n = g.getMatrix.size();
 std::cout << matrix_[g.getCol() - n + i] << 
}
int main(){
std::vector<int> g = {1,1,1,1,1,1};
}
};