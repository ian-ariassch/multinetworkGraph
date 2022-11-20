#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void writeToFile(string file, string value)
{
    cout.flush();
    ofstream dataFile;
    dataFile.open(file, ios_base::app);
    dataFile << value;
    dataFile.close();
}