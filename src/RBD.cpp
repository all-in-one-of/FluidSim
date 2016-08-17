
#include "RBD.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <random>
#include <omp.h>
//#include <ngl/NGLInit.h>


RBD::RBD()
{

}

RBD::~RBD()
{

}

void RBD::Initialize(ngl::Vec3 _position, ngl::Real _radius)
{

  m_position = _position;
  m_radius = _radius;

}

void RBD::Delete()
{

}

bool RBD::checkForCollision(ngl::Vec3& _pos, ngl::Vec3& _vel)
{
  ngl::Vec3 x = m_position - _pos;
  if(x.lengthSquared() < (m_radius*m_radius))
  {
    ngl::Vec3 collision_normal = x;
    collision_normal.normalize();
    float x1 = collision_normal.dot(_vel);
    ngl::Vec3 v1x = collision_normal * x1;
    ngl::Vec3 v1y = _vel - v1x;
    _pos -= collision_normal * (m_radius - x.length());
    _vel = (-v1x + v1y)*0.85;
  }
}

void RBD::collisionResponse(ngl::Vec3& _pos, ngl::Vec3& _vel, float _damper)
{

}

void RBD::Update(float _timestep, float _time)
{


}

void RBD::Reset()
{

}

