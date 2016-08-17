#include "Boundary.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <random>
#include <omp.h>
//#include <ngl/NGLInit.h>


Boundary::Boundary()
{

}

Boundary::~Boundary()
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

void Boundary::Initialize(ngl::Vec3 _position, ngl::Real _width, ngl::Real _height, ngl::Real _depth)
{
  m_colour = ngl::Vec3(1.0,1.0,1.0);

  m_position = _position;
  m_width = _width;
  m_height = _height;
  m_depth = _depth;

  m_x_min = m_position.m_x - m_width/2;
  m_x_max = m_position.m_x + m_width/2;

  m_y_min = m_position.m_y - m_height/2;
  m_y_max = m_position.m_y + m_height/2;

  m_z_min = m_position.m_z - m_depth/2;
  m_z_max = m_position.m_z + m_depth/2;


}

void Boundary::Delete()
{
  std::cout<<"removing cell vaos"<<std::endl;
  cube_vao->removeVOA();
  delete cube_vao;
}

bool Boundary::checkForCollision(ngl::Vec3& _pos)
{
  return(_pos.m_x > m_x_max || _pos.m_x < m_x_min ||
         _pos.m_y > m_y_max || _pos.m_y < m_y_min ||
         _pos.m_z > m_z_max || _pos.m_z < m_z_min);
}

void Boundary::collisionResponse(ngl::Vec3& _pos, ngl::Vec3& _vel, float _damper)
{
  //std::cout<<"test position: "<<_pos.m_x<<std::endl;
  if(_pos.m_x > m_x_max)
  {
    _pos.m_x = m_x_max;
    _vel.m_x *= _damper;
  }
  else if(_pos.m_x < m_x_min)
  {
    _pos.m_x = m_x_min;
    _vel.m_x *= _damper;
  }
//  if(_pos.m_y > m_y_max)
//  {
//    _pos.m_y = m_y_max;
//    _vel.m_y *= _damper;
//  }
  if(_pos.m_y < m_y_min)
  {
    _pos.m_y = m_y_min;
    _vel.m_y *= _damper;
  }
  if(_pos.m_z > m_z_max)
  {
    _pos.m_z = m_z_max;
    _vel.m_z *= _damper;
  }
  else if(_pos.m_z < m_z_min)
  {
    _pos.m_z = m_z_min;
    _vel.m_z *= _damper;
  }
}

void Boundary::Update(float _timestep, float _time)
{

  if(_time >= 20.1f && counter < 4)
  {
    m_x_max += m_resize_bbox;
  }

  if(m_x_max < m_width/3.5f)
  {
    m_x_max = m_width/3.5f;
    m_resize_bbox *= -1.0f;
  }
  else if(m_x_max > m_width/2)
  {
    counter ++;
    m_x_max = m_width/2;
    m_resize_bbox *= -1.0f;
  }

}

void Boundary::Reset()
{

}

void Boundary::setVAO()
{

  //Setting up the points necessary to draw 1 cell
  std::vector<data> cube_points;
  ngl::Real half_width = m_width*0.5;
  ngl::Real half_height = m_height*0.5;
  ngl::Real half_depth = m_depth*0.5;

  data p;
  p.pos = ngl::Vec3(ngl::Vec3(m_position.m_x - half_width,
                              m_position.m_y + half_height,
                              m_position.m_z + half_depth));
  p.colour = m_colour;
  cube_points.push_back(p);

  data p1;
  p1.pos = ngl::Vec3(ngl::Vec3(m_position.m_x - half_width,
                               m_position.m_y + half_height,
                               m_position.m_z - half_depth));
  p1.colour = m_colour;
  cube_points.push_back(p1);

  data q;
  q.pos = ngl::Vec3(ngl::Vec3(m_x_max,
                              m_position.m_y + half_height,
                              m_position.m_z + half_depth));
  q.colour = m_colour;
  cube_points.push_back(q);

  data q1;
  q1.pos = ngl::Vec3(ngl::Vec3(m_x_max,
                               m_position.m_y + half_height,
                              m_position.m_z - half_depth));
  q1.colour = m_colour;
  cube_points.push_back(q1);

  data s;
  s.pos = ngl::Vec3(ngl::Vec3(m_x_max,
                              m_position.m_y - half_height,
                              m_position.m_z + half_depth));
  s.colour = m_colour;
  cube_points.push_back(s);

  data s1;
  s1.pos = ngl::Vec3(ngl::Vec3(m_x_max,
                               m_position.m_y - half_height,
                               m_position.m_z - half_depth));
  s1.colour = m_colour;
  cube_points.push_back(s1);

  data r;
  r.pos = ngl::Vec3(ngl::Vec3(m_position.m_x - half_width,
                              m_position.m_y - half_height,
                              m_position.m_z + half_depth));
  r.colour = m_colour;
  cube_points.push_back(r);

  data r1;
  r1.pos = ngl::Vec3(ngl::Vec3(m_position.m_x - half_width,
                               m_position.m_y - half_height,
                               m_position.m_z - half_depth));
  r1.colour = m_colour;
  cube_points.push_back(r1);

  const static GLubyte indices[]=  {
                                      0,1,3,2, //top
                                      4,5,3,2,
                                      4,6,0,2,
                                      0,1,7,6,
                                      7,5,4,6
                                   };

  ngl::VertexArrayObject* cube_vao=ngl::VertexArrayObject::createVOA(GL_LINE_LOOP);
  cube_vao->bind();
  cube_vao->setRawIndexedData(sizeof(data)*sizeof(cube_points),&cube_points[0],sizeof(indices),&indices[0],GL_UNSIGNED_BYTE,GL_STATIC_DRAW);
  cube_vao->setData(cube_points.size()*sizeof(data),cube_points[0].pos.m_x);
  cube_vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(data),0);
  cube_vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(data),3);
  cube_vao->setNumIndices(20);
  cube_vao->draw();
  cube_vao->unbind();
  cube_vao->removeVOA();
}


void Boundary::Draw()
{
  setVAO();
}


