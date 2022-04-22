#include<iostream>
#include<cstring>
#include<fstream>
#include <string> 
#include<math.h>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> allCombinations;
bool isGoodNum = true;
string buffer = "";
unsigned long long int currentNum = 0;
short currentOperation = 0;
int operationCount = 0;
int goodNumsCount = 0;

//check num on attitude to Fibonachi
bool isFib(unsigned long long num)
{
  if(num == 0) return false;
  long double firstValue = sqrt(pow(num,2) * 5 -4);
  long double secondValue = sqrt(pow(num,2) * 5 +4);
  if(firstValue - (long)firstValue == 0 || secondValue - (long)secondValue == 0)
    return true;
  return false;
}

//find all combinations of num and write it in vector
void findCombinations(const string& str, int _iterator, string t = "")
{
  if(isGoodNum)
  {
    if (_iterator == str.size())
    {
      int val = atoi(t.c_str());
      allCombinations.push_back(val);   
      if(isFib(val)) 
        isGoodNum = false;
    }
    else
    {
      findCombinations(str, _iterator + 1, t);
      findCombinations(str, _iterator + 1, t + str[_iterator]);
    }
  }
}

int main()
{
  ifstream fileToRead;
  ofstream fileToWrite("output.txt");
  fileToWrite.clear();
  fileToWrite.close();
  fileToRead.open("input.txt", ios_base::in);

  //take nums count
  getline(fileToRead, buffer);
  operationCount = stoi(buffer);
  while(operationCount > currentOperation++)
  {
    unsigned long long int numLessThanCurrent = 0;
    goodNumsCount = 0;
    ofstream fileToWrite;
    getline(fileToRead, buffer);
    //take current num
    currentNum = stoll(buffer);
    //find good nums count
    while(currentNum >= numLessThanCurrent)
    {
      isGoodNum = true;
      allCombinations.clear();
      findCombinations(to_string(numLessThanCurrent),0);
      if(isGoodNum)
         goodNumsCount++;
      numLessThanCurrent++;
    }
    fileToWrite.open("output.txt", ios_base::out | ios_base::app);
    fileToWrite << goodNumsCount;
    fileToWrite << "\n";
    fileToWrite.close();
  }
  return 0;
}