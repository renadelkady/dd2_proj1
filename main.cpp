//
//  main.cpp
//  proj1
//
//  Created by Renad Elkady on 17/11/2022.
//
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include<math.h>
#include <vector>
#include <map>
using namespace std;

class allocating{
public:
    int cells, wires, x, y, key;
    vector<int> cell;
    map<int, vector<int>> val;
};

int main() {
    fstream parce1;
    parce1.open("/Users/renadelkady/Desktop/DD2/annealing/proj1/inputs/parce1.txt",ios::in);
    if (parce1.is_open())  {
        cout << "File is open."<<endl;
    }
    else {
       // cout << "File created.";
        parce1.close();
    }
    
    allocating inFile;
    //int cells, wires, x, y ;
    parce1>> inFile.cells >> inFile.wires >> inFile.x >> inFile.y;
    cout << inFile.cells << "\t" << inFile.wires << "\t" << inFile.x << "\t" << inFile.y <<endl;
    
    for (int i = 0; i < inFile.wires; i++)
    {
        parce1 >> inFile.key;
        for (int j = 0; j < inFile.key; j++)
        {
            inFile.cell.resize(inFile.key);
            parce1 >> inFile.cell[j];
        }//updating the vector with the new read size of the row/column
        inFile.val.insert(pair < int, vector < int > > (inFile.key, inFile.cell)); //writing the new values
    }
    return 0;
}
