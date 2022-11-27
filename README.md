# dd2_proj1
# Simulated-Annealing Cell Placement Tool 
# CSCE 3304 Digital Design II
# The American University in Cairo
# Fall 2022
# Renad ElKady-900191378, Alaa AlKady-900191122

# Problem Definition:
  The aim of the optimization is to reduce the half-perimeter of the smallest bounding box that contains all of the pins for each net, added together for all nets. Each cell in a circuit is given a specific position by the device. Create a straightforward placer based on simulated annealing that reduces the overall wirelength. There was also a need to research the effect of different cooling rates. This is a version of a tool for placing standard cells during simulated annealing.
  
# Objective:
  The main goal behind this project is to develop a simple simulated annealing-based placer that minimizes the total wirelength.
  
# Assumptions:
1. HPWL (half-perimeter of the smallest bounding box containing all pins for a net) is used to estimate the wirelength of any net
2. The core area is an 2D array of empty squares (sites)
3. Each cell is a square and matches the site size.
4. The site size is 1x1.
5. No site is assigned more than one cell.
6. The distance between two cells is measured from the center of one cell to the center of the other.

# Example Netlist:
```
24 16 4 8
3 0 10 17 
9 1 15 7 8 12 22 9 6 23 
9 2 15 7 8 12 22 9 6 23 
3 18 10 17 
3 4 10 17 
3 5 10 17 
2 15 16 
2 7 13 
2 8 3 
2 12 11 
2 22 20 
2 9 21 
2 6 14 
2 23 19 
5 10 15 8 22 6 
5 17 7 12 9 23 
```

# Cooling Schedule:
. Initial Temperature = 500 x Initial Cost
• Final Temperature = 5x10-6 x (Initial Cost) / (Number of Nets)
• Next Temperature = 0.95 x Current Temperature
• Moves/Temperature = 10 x (Number of cells)

 

