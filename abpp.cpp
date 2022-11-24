
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include<math.h>
#include <vector>
#include <map> 

using namespace std;

vector<vector<int> > location_of_cell;


int HPWL(int wires) 
{

    //using HPWL as an estimating factor, put bounding box then add (hay represento el width w el height) 
    int hpwl=0, Xmin, Ymin, Xmax,Ymax;

for (int i=0; i<wires; i++)
{
    Xmin=location_of_cell[wires[i][0]][0];
    Ymin=location_of_cell[wires[i][0]][1];
    Xmax=location_of_cell[wires[i][0]][0];
    Ymax=location_of_cell[wires[i][0]][1];

    for (int j=2; j<wire[i].size(); j++)
    {
        if (location_of_cell[wires[i][j]][0]<Xmin)
            Xmin=location_of_cell[wires[i][j]][0];
        if (location_of_cell[wire[si][j]][1]<Ymin)
            Ymin=location_of_cell[wires[i][j]][1];
        if (location_of_cell[wires[i][j]][0]>Xmax)
            Xmax=location_of_cell[wires[i][j]][0];
        if (location_of_cell[wires[i][j]][1]>Ymax)
            Ymax=location_of_cell[wires[i][j]][1];
    }
  
}


 hpwl= hpwl + (Xmax-Xmin) + (Ymax-Ymin);

 return hpwl;
}

//randomly placing the cells in the grid
void inital_random_placement(int cells,int x, int y, vector<vector<int> > &grid, int wires)
{
    
    int x1,y1,total_wire_length;

    for(int i=0; i<cells; i++)
    {
        //any random row and col
        x1=rand()%x;
        y1=rand()%y;
     
       bool used;
       used=false;
       
       //to fill my grid with the cells
       if (grid[x1][y1]!= -1)
           used=true;
        else 
        {
          grid[x1][y1]=i;
          //fill my location vector of vectors with the random row and col
            location_of_cell[i][0]=x1;
            location_of_cell[i][1]=y1;
          used=false;
        }


total_wire_length= HPWL(wires);
}

}




void swap_cells(int cells, vector<vector<int> > location_of_cells, vector<vector<int> > &grid, int choice)
{

if (choice==0) //get random cells and swap them 

    int r1,r2, temp;
    r1=rand()%cells;
    r2=rand()%cells;
  
  while (r1==r2) 
  {
    r2 = rand()%cells;
  }

grid[location_of_cells[r1][0]][location_of_cells[r1][1]] = r2;
grid[location_of_cells[r2][0]][location_of_cells[r2][1]] = r1;


        temp = location_of_cells[r1][0];
        location_of_cells[r1][0] = location_of_cells[r2][0];
        location_of_cells[r2][0] = temp;
        temp = location_of_cells[r1][1];
        location_of_cells[r1][1] = location_of_cells[r2][1];
        location_of_cells[r2][1] = temp;

else //go back to my original 
{

grid[location_of_cells[r1][0]][location_of_cells[r1][1]] = r2;
grid[location_of_cells[r2][0]][location_of_cells[r2][1]] = r1;
 temp = location_of_cells[r1][0];
        location_of_cells[r1][0] = location_of_cells[r2][0];
        location_of_cells[r2][0] = temp;
        temp = location_of_cells[r1][1];
        location_of_cells[r1][1] = location_of_cells[r2][1];
        location_of_cells[r2][1] = temp;

}


   

//value el gowa r1 hahoto fel temp w el gowa r2 hahoto fel r1 w el gowa temp hahoto fel r2



    for (int )
    
    r1= location_of_cell[r1][0];


    while (r1==r2)
    {
        r2=rand()%cells;
    }


 

}

void simulated_annealing_placer(int cells,int x, int y, vector<vector<int> > &grid, int wires)
{

    int total_wire_length,c; //the original one i calculated before the swap
    total_wire_length= inital_random_placement(cells, x, y, grid, wires); 

    double init_temp,final_temperature,temperature, next_temp;
    int moves_temp, new_wire_length;

    //the given values
    init_temp= 500*total_wire_length;
    final_temperature = 5 * pow(10,-6) * total_wire_length / conections;
    temperature = init_temp;
    moves_temp= 10 * cells;

while (temperature > final_temperature)
{
    for (int i=0; i<moves_temp; i++) {

                c=0; 
                swap_cells(cells, vector<vector<int> > &location_of_cells, grid, c);
                new_wire_length = HPWL(wires);
                if (new_wire_length < total_wire_length) {
                    total_wire_length = new_wire_length;
                } else {
                    
                    double probability = 1 - exp( (total_wire_length - new_wire_length) / temperature );
                    double result = (double)rand() / RAND_MAX;
                    if (result > probability) {
                        total_wire_length = new_wire_length;
                    } else {
                        c=1;
                        swap_cells(cells, vector<vector<int> > &location_of_cells, grid,c);

                    }
                }
}
// cooling down 
next_temp= temperature * 0.95;
}

display_result(x,y,grid,total_wire_length);

}


display_result(int x, int y, vector<vector<int> > &grid, int total_wire_length)
{
    for(int i=0; i<x; i++){
        for (int j=0; j<y; j++)
        if(grid[i][j]!=-1)
            cout<<grid[i][j]<<"\t";
        else 
        cout<<"--"<<"\t";

        cout<<endl;
    }
    cout<<"total wire length is: "<<total_wire_length<<endl;
}


class allocating{

public:
    int cells, wires, x, y, key;
    vector<int> cell;
    map<int, vector<int> > val;
};


void readfile(string filename, allocating &a,vector<vector<int> > rows)
{
    ifstream file;
    file.open(filename);
// if the file does not open, print an error message
    if (!file.is_open())
    {
        cout << "Error opening file" << endl;
        exit(1);
    }

    //read first line, which has my cells, components, rows, and columns
    file>>a.cells>>a.wires>>a.x>>a.y;

    // a.cells is the number of rows
    // read file which is tab seperated and line seperated (the lines after the first one)

    int i=1;
    while(!file.eof())
    {
        file>>a.key;
        int col = a.key;
        a.cell.push_back(a.key);
        for(int j=0; j<col; j++)
        {
            file>>a.key;
            a.cell.push_back(a.key);
        }
        a.val[i]=a.cell;
        a.cell.clear();
        i++;
    }

   

    // printing the vector according to size of row and column (for checking)
    for(int i=0; i<a.cells; i++)
    {
        for(int j=0; j<a.val[i].size(); j++)
        {
            cout<<a.val[i][j]<<" ";
        }
        cout<<endl;
    }

   

}

int main() {


    //test readfile with a file d1.txt
    allocating a;
    vector<vector<int> > rows;

    //parse through the file to be able to decode the netlist components
    readfile("d1.txt",a,rows);
    //initlize my grid to be later filled
    vector<vector<int> > grid(a.x,vector<int>(a.y,-1));

location_of_cell.resize(200);
for(int i=0; i<10; i++)
{
    location_of_cell[i].resize(100);
}
    
    simulated_annealing_placer(inFile.cells, inFile.x ,inFile.y, grid,inFile.wires);

    return 0;
    
}
    
    
    

