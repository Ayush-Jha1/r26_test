#include "planning.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

Planner::Planner(const vector<vector<bool>> &grid) : grid(grid) {
  rows = grid.size();
  cols = grid[0].size();
}

bool Planner::isvalid(int x, int y) const {
  return (x >= 0 && x < rows && y >= 0 && y < cols && !grid[x][y]);
}

double Planner::heuristic(int x1, int y1, int x2, int y2) const {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

vector<pair<int, int>> Planner::pathplanning(pair<int, int> start,
                                             pair<int, int> goal) {
  vector<pair<int, int>> path; // store final path 
			       
  /* Implement Path Planning logic here */
  
  // A* algorithm implementation
  vector<vector<double>> gCost(rows, vector<double>(cols, INFINITY));
  vector<vector<double>> fCost(rows, vector<double>(cols, INFINITY));
  vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));
  vector<vector<bool>> visited(rows, vector<bool>(cols, false));
  
  // Priority queue for A* (min heap based on fCost)
  vector<pair<double, pair<int, int>>> openSet;
  
  // Initialize start position
  gCost[start.first][start.second] = 0.0;
  fCost[start.first][start.second] = heuristic(start.first, start.second, goal.first, goal.second);
  openSet.push_back({fCost[start.first][start.second], start});
  
  // 8-directional movement (including diagonals)
  vector<pair<int, int>> directions = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
  
  while (!openSet.empty()) {
    // Find node with minimum f cost
    int minIdx = 0;
    for (size_t i = 1; i < openSet.size(); i++) {
      if (openSet[i].first < openSet[minIdx].first) {
        minIdx = i;
      }
    }
    
    auto current = openSet[minIdx].second;
    openSet.erase(openSet.begin() + minIdx);
    
    // Mark as visited
    visited[current.first][current.second] = true;
    
    // Check if we reached the goal
    if (current.first == goal.first && current.second == goal.second) {
      // Reconstruct path
      pair<int, int> curr = goal;
      while (curr.first != -1 && curr.second != -1) {
        path.push_back(curr);
        curr = parent[curr.first][curr.second];
      }
      reverse(path.begin(), path.end());
      break;
    }
    
    // Explore neighbors
    for (auto& dir : directions) {
      int nx = current.first + dir.first;
      int ny = current.second + dir.second;
      
      if (!isvalid(nx, ny) || visited[nx][ny]) {
        continue;
      }
      
      // Calculate movement cost (diagonal moves cost more)
      double moveCost = (abs(dir.first) + abs(dir.second) == 2) ? sqrt(2.0) : 1.0;
      double tentativeGCost = gCost[current.first][current.second] + moveCost;
      
      if (tentativeGCost < gCost[nx][ny]) {
        parent[nx][ny] = current;
        gCost[nx][ny] = tentativeGCost;
        fCost[nx][ny] = gCost[nx][ny] + heuristic(nx, ny, goal.first, goal.second);
        
        // Add to open set if not already there
        bool inOpenSet = false;
        for (auto& node : openSet) {
          if (node.second.first == nx && node.second.second == ny) {
            inOpenSet = true;
            break;
          }
        }
        if (!inOpenSet) {
          openSet.push_back({fCost[nx][ny], {nx, ny}});
        }
      }
    }
  }

  return path;
}
