#include<iostream>
#include<fstream>
#include <string> 
#include<cstring>
#include<math.h>
#include <vector>
using namespace std;

ifstream fileToRead;
ofstream fileToWrite;
unsigned long long *lambsCount;
unsigned long long *lambHousesCount;
unsigned long long *lambs;
const unsigned long long mod = 1000000007;
unsigned long long minutes = 0;
unsigned long long linesInFile = -1;
unsigned long long allPlaces = 0;
string buffer = "";
unsigned long long avg = 0;
bool flag = true;
unsigned long long lastIndexInSorting = 0;

int main()
{
  //read file  
  fileToRead.open("input.txt", ios_base::in);
  getline(fileToRead, buffer);
  linesInFile = stoi(buffer);
  lambsCount = new unsigned long long[linesInFile];
  lambHousesCount = new unsigned long long[linesInFile];
  int indexForTemp = 0;
  while(getline(fileToRead, buffer))
  {
    char *dataInChar = new char[buffer.length() + 1];
    strcpy(dataInChar, buffer.c_str());
    char *splitData = strtok(dataInChar, " ");
    allPlaces += splitData[0] - 48;
    lambHousesCount[indexForTemp] = splitData[0] - 48;
    splitData = strtok(NULL, " ");
    lambsCount[indexForTemp++] = splitData[0] - 48;
  }
  fileToRead.close();

  //setup lambs array
  lambs = new unsigned long long[allPlaces];
  indexForTemp = 0;
  for (size_t i = 0; i < allPlaces;)
  {
    unsigned long long countsForAdd = lambHousesCount[indexForTemp];
    size_t j;
    for (j = i; j < i+countsForAdd; j++)
    {
      lambs[j] = lambsCount[indexForTemp];
      avg+= lambs[j];
    }
    i+= countsForAdd;
    indexForTemp++;
  }
  //заполнили массив

    avg = avg / allPlaces;
    //нашли среднее значение по которому будем ориентироваться

  while(flag)
  {     
    //check sorting       
    bool isSorted = true;
    for (unsigned long long i = 0; i < allPlaces; i++)
    {
      if(lambs[i] != avg)
      {
        isSorted = false;
        i = allPlaces;
      }
    }

    if(!isSorted)
    {
      //start sorting
      //start from limit values
      if(lambs[allPlaces-1] > avg || lambs[0] > avg)
      {
        if(lambs[allPlaces-1] >= lambs[0])
        {
          lambs[allPlaces-1]--;
          lambs[allPlaces-2]++;
        }
        else
        {
          lambs[0]--;
          lambs[1]++;
        }
      }
      else
      {
        //go to center principle 
        for (size_t i = lastIndexInSorting; i < allPlaces-1; i++)
        {
          if(lambs[i] > avg)
          {
            lastIndexInSorting = i - 1;
            if(lambs[i-1] < lambs[i+1] && lambs[i-1] < avg)
            {
              lambs[i]--;
              lambs[i-1]++;
              i = allPlaces;
            }
            else
            {
              lambs[i]--;
              lambs[i+1]++;
              i = allPlaces;
            }
          }
        }
      }
      minutes++;
    }
    else
    {
      flag = false;
    }
  }
  minutes = (minutes % mod);
  fileToWrite.open("output.txt");
  fileToWrite << minutes;
  fileToWrite.close();
  return 0;
}