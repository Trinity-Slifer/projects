#include <cmath>
#include <vector>

class Galton {
 private:
  std::vector<int> matrix_{};
  int col_{};

 public:
  Galton(std::vector<int> mat, int col);
  std::vector<int> getMatrix() const;
  int getCol() const;
  int Get_ij(int i, int j);
};

class Simulation
{
private:
 int number_{};
 int col_{};

public:
 Simulation(std::vector<int> mat, int col);
 int sgetCol() const;
 int sGet_ij(int i, int j);
 void evolve(Galton g);
};

