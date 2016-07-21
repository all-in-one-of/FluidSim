#include "Cell.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <random>
//#include <ngl/NGLInit.h>


Cell::Cell()
{

}

Cell::~Cell()
{

  //this resulted in a crash.

  /*std::cout<<"removing cell vaos"<<std::endl;
  cube_vao->removeVOA();
  delete cube_vao;

  pressure_vao->removeVOA();
  delete pressure_vao;

  velocity_vao->removeVOA();
  delete velocity_vao;*/
}

void Cell::Initialize()
{
  setVAO();
}

void Cell::Delete()
{
  std::cout<<"removing cell vaos"<<std::endl;
  cube_vao->removeVOA();
  delete cube_vao;

  state_vao->removeVOA();
  delete state_vao;
}

void Cell::setCellForces(float _grid_size)
{

}


void Cell::setCell()
{

}


void Cell::Update(float _timestep)
{

}

void Cell::Reset()
{

}

void Cell::setVAO()
{

  //Setting up the points necessary to draw 1 cell
  std::vector<data> cube_points;
  ngl::Real half_size = m_size*0.5;

  data p;
  p.pos = ngl::Vec3(ngl::Vec3(m_position.m_x - half_size,
                              m_position.m_y + half_size,
                              m_position.m_z + half_size));
  p.colour = m_colour;
  cube_points.push_back(p);

  data p1;
  p1.pos = ngl::Vec3(ngl::Vec3(m_position.m_x - half_size,
                               m_position.m_y + half_size,
                               m_position.m_z - half_size));
  p1.colour = m_colour;
  cube_points.push_back(p1);

  data q;
  q.pos = ngl::Vec3(ngl::Vec3(m_position.m_x + half_size,
                              m_position.m_y + half_size,
                              m_position.m_z + half_size));
  q.colour = m_colour;
  cube_points.push_back(q);

  data q1;
  q1.pos = ngl::Vec3(ngl::Vec3(m_position.m_x + half_size,
                               m_position.m_y + half_size,
                              m_position.m_z - half_size));
  q1.colour = m_colour;
  cube_points.push_back(q1);

  data s;
  s.pos = ngl::Vec3(ngl::Vec3(m_position.m_x + half_size,
                              m_position.m_y - half_size,
                              m_position.m_z + half_size));
  s.colour = m_colour;
  cube_points.push_back(s);

  data s1;
  s1.pos = ngl::Vec3(ngl::Vec3(m_position.m_x + half_size,
                               m_position.m_y - half_size,
                               m_position.m_z - half_size));
  s1.colour = m_colour;
  cube_points.push_back(s1);

  data r;
  r.pos = ngl::Vec3(ngl::Vec3(m_position.m_x-half_size,
                              m_position.m_y-half_size,
                              m_position.m_z + half_size));
  r.colour = m_colour;
  cube_points.push_back(r);

  data r1;
  r1.pos = ngl::Vec3(ngl::Vec3(m_position.m_x-half_size,
                               m_position.m_y-half_size,
                               m_position.m_z - half_size));
  r1.colour = m_colour;
  cube_points.push_back(r1);

  const static GLubyte indices[]=  {
                                      0,1,3,2, //top
                                      4,5,3,2,
                                      4,6,0,2,
                                      0,1,7,6,
                                      7,5,4,6
                                   };

  cube_vao=ngl::VertexArrayObject::createVOA(GL_LINE_LOOP);
  cube_vao->bind();
  cube_vao->setRawIndexedData(sizeof(data)*sizeof(cube_points),&cube_points[0],sizeof(indices),&indices[0],GL_UNSIGNED_BYTE,GL_STATIC_DRAW);
  cube_vao->setData(cube_points.size()*sizeof(data),cube_points[0].pos.m_x);
  cube_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(data),0);
  cube_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(data),3);
  cube_vao->setNumIndices(20);
  cube_vao->unbind();


  //setting up the points to display where the pressure is stored in this cell
  std::vector<data> state_points;
  ngl::Vec3 pressure_colour = ngl::Vec3(0.0,1.0,0.0);

  data state1;
  state1.pos = ngl::Vec3((m_position.m_x + (m_size/20)), m_position.m_y, m_position.m_z);
  state1.colour = pressure_colour;
  state_points.push_back(state1);

  data state2;
  state2.pos = ngl::Vec3((m_position.m_x - (m_size/20)), m_position.m_y, m_position.m_z);
  state2.colour = pressure_colour;
  state_points.push_back(state2);

  data state3;
  state3.pos = ngl::Vec3(m_position.m_x, (m_position.m_y + (m_size/20)), m_position.m_z);
  state3.colour = pressure_colour;
  state_points.push_back(state3);

  data state4;
  state4.pos = ngl::Vec3(m_position.m_x, (m_position.m_y - (m_size/20)), m_position.m_z);
  state4.colour = pressure_colour;
  state_points.push_back(state4);

  data state5;
  state5.pos = ngl::Vec3(m_position.m_x, m_position.m_y , (m_position.m_z + (m_size/20)));
  state5.colour = pressure_colour;
  state_points.push_back(state5);

  data state6;
  state6.pos = ngl::Vec3(m_position.m_x, m_position.m_y, (m_position.m_z - (m_size/20)));
  state6.colour = pressure_colour;
  state_points.push_back(state6);

  state_vao = ngl::VertexArrayObject::createVOA(GL_LINES);
  state_vao->bind();
  state_vao->setData(state_points.size()*sizeof(data),state_points[0].pos.m_x);
  state_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(data),0);
  state_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(data),3);
  state_vao->setNumIndices(state_points.size());
  state_vao->unbind();
}


void Cell::Draw()
{

  cube_vao->bind();
  cube_vao->draw();
  cube_vao->unbind();

  state_vao->bind();
  state_vao->draw();
  state_vao->unbind();

}
