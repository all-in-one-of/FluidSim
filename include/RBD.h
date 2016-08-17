#ifndef RBD_H
#define RBD_H

#include <ngl/Vec3.h>
#include <vector>
#include <iostream>
#include "ngl/VertexArrayObject.h"
#include "Particle.h"

class RBD
{
public:
  RBD();
  ~RBD();
  void Initialize(ngl::Vec3 _position, ngl::Real _radius);
  void Update(float _timestep, float _time);
  void Delete();
  void Reset();

  ngl::Vec3 getPosition(){return m_position;}
  void setPosition(ngl::Vec3 _position){m_position = _position;}

  bool checkForCollision(ngl::Vec3& _pos, ngl::Vec3& _vel);
  void collisionResponse(ngl::Vec3& _pos, ngl::Vec3& _vel, float _damper);

  struct data
  {
    ngl::Vec3 pos;
    ngl::Vec3 colour;
  };

private:
  ngl::Vec3 m_position;
  float m_radius;
};
#endif // RBD_H

