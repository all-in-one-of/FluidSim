#ifndef GRID_H
#define GRID_H

#include <ngl/Vec3.h>
#include <vector>
#include <iostream>
#include "Cell.h"

class Grid
{
public:
  Grid();
  void Initialize(float _size, int _divisions);
  void setCellForces(std::vector<Cell> _cells, float _size);
  void Update(float _timestep);
  void Reset();
  void Draw();
  void Delete();
  std::vector<Cell> m_cells;

private:

  int m_size;
  std::vector<Cell> boarder_cells;
  std::vector<Cell> visable_cells;

};

#endif // GRID_H

