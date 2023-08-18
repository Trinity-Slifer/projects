#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>


bool gen(){
std::vector<int> ace;
std::vector<int> two;
std::vector<int> three;
std::vector<int> deck;
int k = 0; 
for (size_t i = 1; i < 41; i++) {
    deck.push_back(i);
  }


std::random_device rd;
std::mt19937 g(rd());

std::shuffle(deck.begin(), deck.end(), g);

for (size_t i = 0; i < 39; i+= 3)
{
    ace.push_back(deck[i]);
    two.push_back(deck[i + 1]);
    three.push_back(deck[i + 2]); 
}
ace.push_back(deck[39]);

for (int n : {1, 11, 21, 31})
    (std::find(ace.begin(), ace.end(), n) == std::end(ace))
        ? k=k 
        : k++ ;
for (int n : {2, 12, 22, 32})
    (std::find(two.begin(), two.end(), n) == std::end(two)) ? k=k : k++;

for (int n : {3, 13, 23, 33})
    (std::find(three.begin(), three.end(), n) == std::end(three)) ? k=k : k++;

if (k == 0 )
{
 return true;
}else { 
return false; }
}

int main(){
int n = 0;

for (size_t i = 0; i < 1000000; i++)
{
    if(gen() == true){ n+=1 ; };  
}
std::cout << n << std::endl; 
return n;
}



