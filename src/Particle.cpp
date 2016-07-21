#include "Particle.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

Particle::Particle(bool _active)
{
  m_active = _active;
  m_gravity = ngl::Vec3(0, -9.81, 0);

  ngl::Real r = 0.2 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/0.8f);
  ngl::Real g = 0.2 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/0.8f);
  ngl::Real b = 0.2 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/0.8f);
  m_colour = ngl::Vec3(r,g,b);
  m_colour = ngl::Vec3(0.0,0.5,1.0);
}

int Particle::findIntegerPosition(ngl::Vec3 _position, float _cell_size)
{
//  This function forms part of the spacial hashing algorithm,
//  it takes in a vec3 and returns the discretized x,y and z values:
//  X(x) = ([Xx/l], [Xy/l], [Xz/l])

  ngl::Vec3 pos = _position;
  pos /= _cell_size;

  int x = (int)pos.m_x;
  int y = (int)pos.m_y;
  int z = (int)pos.m_z;

  return x, y, z;
}

//void Particle::hashFunction(ngl::Vec3 _position, float _cell_size)
//{
//  //  This function forms part of the spacial hashing algorithm,
//  //  it takes in a vec3 and returns the discretized x,y and z values:
//  //  X(x) = ([Xx/l], [Xy/l], [Xz/l])

//    ngl::Vec3 pos = _position;
//    pos /= _cell_size;

//    int x = (int)pos.m_x;
//    int y = (int)pos.m_y;
//    int z = (int)pos.m_z;
//}

void Particle::Update(float _timestep)
{
    m_force += m_gravity;
    //m_force += -0.6f * m_velocity;
    //drag

    ngl::Vec3 acc;
    acc = m_force / (m_mass);
    m_position += m_velocity * _timestep;
    m_velocity += _timestep * acc;
    m_lifeleft -= _timestep;
    m_force = ngl::Vec3(0,0,0);
    if (m_lifeleft <= 0)
    {
      m_active = false;
    }
}

void Particle::addForce(ngl::Vec3 _force)
{
  m_force += _force;
}

void Particle::Reset()
{
  m_position = m_init_position;

  m_velocity = m_init_velocity;
  m_lifeleft = m_lifespan;
}

