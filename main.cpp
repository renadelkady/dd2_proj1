#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <string>
#include <vector>
using namespace std::chrono;
using namespace std;
vector<vector<int>> location_of_cell;
vector<vector<int>> components;

class allocating {
public:
  int cells, wires, x, y, key;

  vector<int> cell;
  map<int, vector<int>> val;
};

int HPWL(int wires, int x, int y) {

  // using HPWL as an estimating factor, put bounding box then add (hay
  // represento el width w el height)
  int hpwl = 0, Xmax = 0, Ymax = 0, Xmin, Ymin;
  // Xmin = x, Ymin = y,
  int sum = 0;

  // int z;

  for (int i = 0; i < wires; i++) {
    // hpwl for each net

    Xmin = location_of_cell[components[i][0]][1];
    Ymin = location_of_cell[components[i][0]][0];
    Xmax = location_of_cell[components[i][0]][1];
    Ymax = location_of_cell[components[i][0]][0];

    for (int j = 1; j < components[i].size(); j++) {
      if (location_of_cell[components[i][j]][1] < Xmin)
        Xmin = location_of_cell[components[i][j]][1];
      if (location_of_cell[components[i][j]][0] < Ymin)
        Ymin = location_of_cell[components[i][j]][0];
      if (location_of_cell[components[i][j]][1] > Xmax)
        Xmax = location_of_cell[components[i][j]][1];
      if (location_of_cell[components[i][j]][0] > Ymax)
        Ymax = location_of_cell[components[i][j]][0];
    }
    // cout<<"the max and min values are:"<<endl;
    //  cout<<Xmax<<" "<<Xmin<<" "<<Ymax<<" "<< Ymin<<endl;
    hpwl = abs(Xmax - Xmin) + abs(Ymax - Ymin);
    sum = sum + hpwl;
    // cout<<sum<<endl;
  }
  // cout<<hpwl<<endl;

  // cout<<Xmax<<" "<<Xmin<<" "<<Ymax<<" "<< Ymin<<endl;
  // cout<<"the first hpwl "<<sum<<endl; // call it in simulated annealing

  return sum;
}

void swap_cells(int cells, vector<vector<int>> &grid, int choice, int x, int y,
                int rx1, int ry1, int rx2, int ry2) {

  int temp;

  // if (choice == 0)
  // {

  // grid[location_of_cells[r1][0]][location_of_cells[r1][1]] = r2;
  // grid[location_of_cells[r2][0]][location_of_cells[r2][1]] = r1;

  // cout << rx1 << " " << ry1 << " " << rx2 << " " << ry2 << " " << endl;
  temp = grid[ry1][rx1];
  grid[ry1][rx1] = grid[ry2][rx2];
  grid[ry2][rx2] = temp;

  // cout << "Ay haga";
  // after swapping
  if (grid[ry1][rx1] >= 0) {
    location_of_cell[grid[ry1][rx1]][0] = ry1;
    location_of_cell[grid[ry1][rx1]][1] = rx1;
  }

  if (grid[ry2][rx2] >= 0) {
    location_of_cell[grid[ry2][rx2]][0] = ry2;
    location_of_cell[grid[ry2][rx2]][1] = rx2;
  }
}

// else // if choice=1
// {

//     //cout << rx1 << " " << ry1 << " " << rx2 << " " << ry2 << " " << endl;
//     // grid[location_of_cells[r1][0]][location_of_cells[r1][1]] = r2;
//     // grid[location_of_cells[r2][0]][location_of_cells[r2][1]] = r1;
//     temp = grid[ry1][rx1];
//     grid[ry1][rx1] = grid[ry2][rx2];
//     grid[ry2][rx2] = temp;
//     temp = grid[ry1][rx1];
//     grid[ry1][rx1] = grid[ry2][rx2];
//     grid[ry1][rx1] = temp;

//     // after swapping
//     if (grid[ry1][rx1] >= 0)
//     {
//         location_of_cell[grid[ry1][rx1]][0] = rx1;
//         location_of_cell[grid[ry1][rx1]][1] = ry1;
//     }

//     if (grid[ry2][rx2] >= 0)
//     {
//         location_of_cell[grid[ry2][rx2]][0] = rx2;
//         location_of_cell[grid[ry2][rx2]][1] = ry2;
//     }
// cout<<"Swapped back"<<endl;

//}

// cout<<"loco after swapping"<<endl;

//  for (int i=0; i<cells+1; i++)
//     {
//         cout<<location_of_cell[i][0]<<" ";
//         cout<<location_of_cell[i][1];

//         cout<<endl;
//     }
//}

void inital_random_placement(int cells, int x, int y, vector<vector<int>> &grid,
                             int wires) {

  // cout<<"here2"<<endl;

  int x1, y1, total_wire_length;
  bool used;
  used = false;
  srand((unsigned)time(0));
  // srand(5);

  for (int i = 0; i < cells; i++) {

    // any random row and col
    x1 = rand() % x;
    y1 = rand() % y;

    // to fill my grid with the cells
    while (grid[x1][y1] != -1) {
      x1 = rand() % x;
      y1 = rand() % y;
    }
    grid[x1][y1] = i;
    // fill my location vector of vectors with the random row and col
    location_of_cell[i][0] = y1;
    location_of_cell[i][1] = x1;
  }

  cout << "the initial random placement" << endl;
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      cout << grid[i][j] << " ";
    }
    cout << endl;
  }

  // // to print loco of cells
  // for (int i=0; i<cells+1; i++)
  // {
  //     cout<<location_of_cell[i][0]<<" ";
  //     cout<<location_of_cell[i][1];

  //     cout<<endl;
  // }

  // to output my grid after filling randomly

  // total_wire_length= HPWL(wires);
  // cout<<total_wire_length;
}

void simulated_annealing_placer(int cells, int x, int y,
                                vector<vector<int>> &grid, int wires) {

  // create a csv file to write the results in it
  ofstream myfile;
  myfile.open("d3_0.7.csv");

  int rx1, ry1, rx2, ry2;
  int total_wire_length,
      c; // the original one i calculated before the swap, choice
  auto start = high_resolution_clock::now();
  // cout<<"here"<<endl;
  inital_random_placement(cells, x, y, grid, wires);

  total_wire_length = HPWL(wires, x, y);
  auto stop = high_resolution_clock::now();

  // Get duration. Substart timepoints to
  // get duration. To cast it to proper unit
  // use duration cast method
  auto duration = duration_cast<microseconds>(stop - start);

  // cout << "Time taken by function: " << duration.count() << " microseconds"
  //      << endl;
  // cout << "the inital total wire length is: " << total_wire_length << endl;

  // total_wire_length= inital_random_placement(cells, x, y, grid, wires);

  double init_temp, final_temperature, temperature;
  int moves_temp, new_wire_length;

  // the given values
  init_temp = 500 * total_wire_length;
  final_temperature = 5 * pow(10, -6) * total_wire_length / wires;
  temperature = init_temp;
  moves_temp = 10 * cells;

  while (temperature > final_temperature) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < moves_temp; i++) {
      c = 0;
      rx1 = rand() % y;
      ry1 = rand() % x;

      rx2 = rand() % y;
      ry2 = rand() % x;

      while ((rx1 == rx2) && (ry1 == ry2)) {
        rx2 = rand() % y;
        ry2 = rand() % x;
      }

      swap_cells(cells, grid, c, x, y, rx1, ry1, rx2, ry2);

      //              cout<<"to see swap "<<endl;
      //     for (int i = 0; i < x; i++)
      // {
      //     for (int j = 0; j < y; j++)
      //     {
      //         cout << grid[i][j] << " ";
      //     }
      //     cout << endl;
      // }
      new_wire_length = HPWL(wires, x, y);
      // cout<<"the wire length after swap is:  ";
      // cout << new_wire_length << endl;
      if (new_wire_length < total_wire_length) {
        total_wire_length = new_wire_length;
        // cout<<"the wire length became smaller"<<endl;
      }

      else {

        double ex =
            (((double)(total_wire_length - new_wire_length)) / temperature);
        double probability = 1 - exp(ex);

        float result =
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        // cout<<total_wire_length-new_wire_length<<endl;
        // cout<<"ex "<<ex<<endl;
        // cout << result << " " << probability << endl;

        if (result > probability)
          total_wire_length = new_wire_length;
        else {
          c = 1;
          swap_cells(cells, grid, c, x, y, rx1, ry1, rx2, ry2);
          //                 cout<<"to see swap back "<<endl;

          //     for (int i = 0; i < x; i++)
          // {
          //     for (int j = 0; j < y; j++)
          //     {
          //         cout << grid[i][j] << " ";
          //     }
          //     cout << endl;
          // }
        }
      }
    }

    // cooling down
    temperature = temperature * 0.7;

    // append temperature and wire length to the csv file
    myfile << temperature << "," << total_wire_length << endl;
  }
  cout << "the new TWL " << total_wire_length << endl;

  // display_result(x,y,grid,total_wire_length);
}

void readfile(string filename, allocating &a) {

  ifstream file;
  file.open(filename);
  // if the file does not open, print an error message
  if (!file.is_open()) {
    cout << "Error opening file" << endl;
    exit(1);
  }

  // read first line, which has my cells, components, rows, and columns
  file >> a.cells >> a.wires >> a.x >> a.y;

  // a.cells is the number of rows
  // read file which is tab seperated and line seperated (the lines after the
  // first one)

  int i = 0, col;

  while (!file.eof()) {

    int value;
    file >> value;
    a.key = value;
    col = a.key;
    a.cell.push_back(a.key);

    components[i].resize(value);
    for (int j = 0; j < value; j++) {
      file >> components[i][j];
      a.cell.push_back(components[i][j]);
    }
    a.val[i] = a.cell;
    a.cell.clear();
    i++;
  }

  // cout<<a.cells<<" "<<a.wires<<" "<<a.x<<" "<<a.y<<endl;// first line

  // cout<<"my components are: "<<endl;
  // for (int i = 0; i < components.size(); i++)
  // {

  //     for (int j = 0; j < components[i].size(); j++)
  //     {
  //         cout << components[i][j] << " ";
  //     }

  //     cout << endl;
  // }
}

int main() {

  cout << "hello" << endl;
  allocating a;
  // vector<vector<int> > rows;

  components.resize(1271);

  // for(int i=0; i<17; i++)
  // {
  // components[i].resize(10);
  // }

  readfile("d0", a);

  vector<vector<int>> grid(a.x, vector<int>(a.y, -1));

  cout << "the initial grid" << endl;
  for (int i = 0; i < a.x; i++) {
    for (int j = 0; j < a.y; j++) {
      cout << grid[i][j];
    }

    cout << endl;
  }

  cout << endl;

  location_of_cell.resize(1290);
  for (int i = 0; i < 1290; i++) {
    location_of_cell[i].resize(2);
  }

  // Call the function, here sort()

  // Get ending timepoint

  simulated_annealing_placer(a.cells, a.x, a.y, grid, a.wires);

  // final display!
  // for (int i = 0; i < a.x; i++)
  // {
  //     for (int j = 0; j < a.y; j++)
  //     {
  //         cout << grid[i][j] << " ";
  //     }
  //     cout << endl;
  // }
  // cout << endl;

  cout << "the display in 0's and 1's" << endl;
  for (int i = 0; i < a.x; i++) {
    for (int j = 0; j < a.y; j++) {
      if (grid[i][j] == -1)
        cout << 1 << " ";
      else
        cout << 0 << " ";
    }
    cout << endl;
  }

  cout << "annealing done" << endl;

  // inital_random_placement(a.cells, a.x ,a.y, grid,a.wires);
  // HPWL(a.wires, a.x, a.y);
}
