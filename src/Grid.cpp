
#include <math.h>
#include "Grid.h"

Grid::Grid()
{

}

void Grid::Initialize(float _size, int _divisions)
{
  Cell c;

  //_divisions = _divisions+2;

  std::cout << "divisions " << _divisions<<std::endl;
  ngl::Real cell_size = _size/_divisions;

  for(int i = 0; i < _divisions; i ++)
  {
    for(int j = 0; j < _divisions; j++)
    {
      for(int k = 0; k < _divisions; k++)
      {
        c.setPosition(ngl::Vec3(((k*cell_size)+cell_size*0.5),
                                ((j*cell_size)+cell_size*0.5),
                                ((i*cell_size)+cell_size*0.5)));
        c.setSize(cell_size);
        c.setColour(ngl::Vec3(0.8,0.8,0.8));

        c.Initialize();

        if(i == 0 || j == 0 || k == 0 ||i == _divisions-1 || j == _divisions-1 || k == _divisions-1)
        {
          boarder_cells.push_back(c);
        }
        else
        {
          visable_cells.push_back(c);
        }

        m_cells.push_back(c);
      }
    }
  }
}

void Grid::Delete()
{
  for(int i = 0; i < m_cells.size(); i++)
  {
    m_cells[i].Delete();
  }
}

void Grid::Draw()
{
  for(int i = 0; i < visable_cells.size(); i++)
  {
    visable_cells[i].Draw();
  }

//  for(int i = 0; i < boarder_cells.size(); i++)
//  {
//      boarder_cells[i].Draw();
//  }


//  m_cells[0].Draw();
//  m_cells[1].Draw();
//  m_cells[4].Draw();
//  m_cells[16].Draw();
}
