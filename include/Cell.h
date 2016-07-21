#ifndef CELL_H
#define CELL_H
#include <ngl/Vec3.h>
#include <vector>
#include <iostream>
#include "ngl/VertexArrayObject.h"

class Cell
{
public:
  Cell();
  ~Cell();
  void Initialize();
  void Update(float _timestep);
  void Delete();
  void Reset();
  void setCell();
  void Draw();

  ngl::Vec3 getPosition(){return m_position;}
  void setPosition(ngl::Vec3 _position){m_position = _position;}

  ngl::Vec3 getVelocity(){return m_velocity;}
  void setVelocity(ngl::Vec3 _velocity){m_velocity = _velocity;}

  ngl::Vec3 getInitVelocity(){return m_init_velocity;}
  void setInitVelocity(ngl::Vec3 _velocity){m_init_velocity = _velocity;}

  ngl::Vec3 getGravity(){return m_gravity;}
  void setGravity(ngl::Vec3 _gravity){ m_gravity = _gravity;}

  ngl::Real getSize(){return m_size;}
  void setSize(ngl::Real _size){ m_size = _size;}

  ngl::Vec3 getColour(){return m_colour;}
  void setColour(ngl::Vec3 _colour){m_colour = _colour;}

  void setCellForces(float _size);

  void setVAO();

  struct data
  {
    ngl::Vec3 pos;
    ngl::Vec3 colour;
  };

private:
  ngl::Vec3 m_position;
  ngl::Vec3 m_velocity;
  ngl::Vec3 m_init_velocity;
  ngl::Vec3 m_gravity;
  ngl::Vec3 m_colour;
  ngl::Vec3 m_state_colour;
  float m_pressure;
  ngl::Real m_size;

  ngl::VertexArrayObject *cube_vao;
  ngl::VertexArrayObject *state_vao;

};
#endif // CELL_H

