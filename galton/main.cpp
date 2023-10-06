#include "main.hpp"

#include <cmath>
#include <iostream>
#include <random>
#include <vector>

int Sum(int j) {
  int k = 0;
  for (size_t i = 0; i < j; i++) {
    k += i;
  }
  return k;
};

Galton::Galton(std::vector<int> mat, int col) : matrix_{mat}, col_{col} {};
std::vector<int> Galton::getMatrix() const { return matrix_; };
int Galton::getCol() const { return col_; }
int Galton::Get_ij(int i, int j) {
  if (j < col_) {
    return matrix_[Sum(j) + i - 1];
  } else {
    return matrix_[Sum(col_) + (j - col_) * col_ + i - 1];
  }
}

Simulation::Simulation(int number, int col) : number_{number}, col_{col} {};
int Simulation::sgetCol() const { return col_; }
void Simulation::evolve(Galton g) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, 1);
  std::vector<int> mat;
  mat.reserve(g.getMatrix().size());
  mat.push_back(number_);
  for (size_t i = 1; i < g.getMatrix().size(); i++) {
    mat.push_back(0);
  }
  int row = (g.getMatrix().size() - Sum(g.getCol())) / (Sum(g.getCol())) +
            Sum(g.getCol());
  std::cout << row << std::endl;
  for (int i = 1; i < row; i++) {
    std::cout << std::endl;
    for (int j = 1; j <= i; j++) {
      if (g.Get_ij(j, i) != 0) {
        std::cout << mat[Sum(i) + j - 1] << " ";
        for (size_t k = 0; k < mat[Sum(i) + j - 1]; k++) {
          double x = distrib(gen);
          if (x <= g.Get_ij(j, i) / 2) {
          if (g.Get_ij(i + 1, j) = 0)
          {
            mat[Sum(i) + i + i + j] += 1;
          } else {
            mat[Sum(i) + i + j - 1] += 1;
          }
          } else {
            if (g.Get_ij(i + 1, j + 1) = 0) {
              mat[Sum(i) + i + i + j + 1] += 1;
            }else{
              mat[Sum(i) + i + j] += 1;
            }
          }
        }
        mat[Sum(i) + j - 1] = 0;
      }
    }
  }
};

int main() {
  std::vector<int> g = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  Galton galton(g, 3);
  Simulation sim(100000, 3);
  sim.evolve(galton);
}