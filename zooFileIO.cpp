//
// Created by bella on 3/8/2025.
//

#include "zooFileIO.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int zooFile() {
    string myText = "";
    string mypause = "";

// Open zooPopulation.txt
ifstream MyFile("C:/cpptxtfiles/zooPopulation.txt");

// Read zooPopulation.txt line by line
while (getline(MyFile, myText)){
    cout << myText;
    cin >> mypause;
}
// Close the file.
MyFile.close();
}