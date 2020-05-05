#include <fstream>;
#include <iostream>;
#include <vector>
#include <algorithm> 
using namespace std;
// error message in case of txt file does not have required number of integers for making orthogonal pyramid
void Errormsg() {
    cout << "Please enter valid number to making orthogonal triangle" << endl;
    exit(0);
}
// checking if number is prime or not;
int notprime(int a) {
    int temp = 0;
    if (a != 1 && a!=2) {
        for (int i = 2; i < a; i++) {
            if (a % i == 0)
                temp = temp + 5;
        }  
    }
    else  if (a == 1 || a == 2)
        temp = 5;
    return temp;
}
// calculating line number of pyramid for making for dynamic programming
  int calculatelinenum(int x) {
    int c = -(x*2);
    double r1=0;
    double r2=0;
    r1 = (-1 + (sqrt(1 - 4 * c))) / 2 ;
    r2 = (-1 - (sqrt(1 - 4 * c))) / 2;
    if ((ceil(r1)-r1)>0.05 ) // checking number of integers in txt file in case of showing error
        Errormsg();
    if (r1 > 0)
        return ceil(r1);
    else
        return ceil(r2);
   }
  int main()
  {     
      char filename[10] = { "a.txt" };
      vector <int> triangle;
      int data=0;
      ifstream nums(filename);  // filling vector  from txt file
      while (nums >> data) {
          triangle.push_back(data);
      }
      nums.close();
      auto size = triangle.size();
      int arrsize = 0;
      arrsize = calculatelinenum(size);
      for (int i = 1; i < size; i++) {            // deleting prime numbers from vector to improve our search
          int compare = 0;
          compare = notprime(triangle[i]);
          if (compare <1) {
              triangle[i] = 0;
          }
      }       
      for (int i = arrsize -1; i > 0; i--)              
          for (int j = (i * (i - 1)) / 2; j < (i * (i + 1)) / 2; j++) {
        
              if (triangle[j] <1 || (triangle[i + j] <1 & triangle[i + j + 1] <1) )  // if both nodes below currently node is prime than for prevent miscalculation equalizing currently node to 0
                  triangle[j] = 0;  
              else
                  triangle[j] += max(triangle[i + j], triangle[i + j + 1]); // finally choosing biggest path for our top to bottom way
          }
      
      cout << triangle[0] << endl; // printing maximum path length
  }