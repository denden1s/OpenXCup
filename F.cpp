#include<iostream>
#include<cstring>
#include<fstream>
#include<math.h>
using namespace std;

fstream file;
string buffer = "";
long long int firstNum = 0;
long long int secondNum = 0;
unsigned long long result = 0;

int main()
{
  //read from file
  file.open("input.txt", ios_base::in);
  getline(file,buffer);
  file.close();

  // convert data to needed format
  char *dataInChar = new char[buffer.length() + 1];
  strcpy(dataInChar, buffer.c_str());
  char *splitData = strtok(dataInChar, " ");
  firstNum = atol(splitData);
  splitData = strtok(NULL, " ");
  secondNum = atol(splitData);

  file.open("output.txt", ios_base::out);
  //find sum
  if(secondNum > 0 && firstNum > 0)
  {
    result = firstNum + secondNum;
    file << result;
    file.close();
  }
  else if (secondNum < 0 && firstNum < 0)
  {
    result = abs(firstNum) + abs(secondNum);
    file << "-";
    file <<result;
  }
  else
  {
    firstNum += secondNum;
    file << firstNum;
  }
  file.close();
  return 0;
}