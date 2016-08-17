#ifndef BOUNDARY_H
#define BOUNDARY_H
#include <ngl/Vec3.h>
#include <vector>
#include <iostream>
#include "ngl/VertexArrayObject.h"
#include "Particle.h"

class Boundary
{
public:
  Boundary();
  ~Boundary();
  void Initialize(ngl::Vec3 _position, ngl::Real _width, ngl::Real _height, ngl::Real _depth);
  void Update(float _timestep, float _time);
  void Delete();
  void Reset();
  void setCell();
  void Draw();

  ngl::Vec3 getPosition(){return m_position;}
  void setPosition(ngl::Vec3 _position){m_position = _position;}

  ngl::Vec3 getColour(){return m_colour;}
  void setColour(ngl::Vec3 _colour){m_colour = _colour;}

  bool checkForCollision(ngl::Vec3& _pos);
  void collisionResponse(ngl::Vec3& _pos, ngl::Vec3& _vel, float _damper);

  void setVAO();

  struct data
  {
    ngl::Vec3 pos;
    ngl::Vec3 colour;
  };

private:
  ngl::Vec3 m_position;
  ngl::Vec3 m_colour;
  ngl::Real m_width;
  ngl::Real m_height;
  ngl::Real m_depth;
  ngl::Real m_x_min;
  ngl::Real m_x_max;

  ngl::Real m_y_min;
  ngl::Real m_y_max;

  ngl::Real m_z_min;
  ngl::Real m_z_max;
  float m_resize_bbox = -0.03;
  int counter = 0;

  ngl::VertexArrayObject *cube_vao;
};
#endif // BOUNDARY_H

