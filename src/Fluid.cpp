#include "Fluid.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <random>
#include <cmath>
//#include <ngl/NGLInit.h>


Fluid::Fluid()
{

}

Fluid::~Fluid()
{

}

void Fluid::Initialize()
{
  m_total_num_particles = 100000;
  m_particle_emitter.Initialize(m_total_num_particles, ngl::Vec3(0, 0, 0), 30, ngl::Vec3(0, 0, 0), 9, 0.1, 0.3);
}

void Fluid::setFluidTimestep(float _dt)
{
  m_dt = _dt;
  m_particle_emitter.setTimestep(m_dt);
}

void Fluid::hashParticles(ngl::Vec3 _position, float _sl)
{
  //  This function performs the spacial hashing of particles to a multimap.
  //  _position is a particle position, and _sl is the smoothing length

  //std::cout<<"ngl Vec3 particle position: ("<<_position.m_x<<","<<_position.m_y<<","<<_position.m_z<<")"<<std::endl;
  ngl::Vec3 pos = _position;

  //  X(x) = ([Xx/l], [Xy/l], [Xz/l])
  pos /= _sl;
  //std::cout<<"particle position after / smoothing length: ("<<pos.m_x<<","<<pos.m_y<<","<<pos.m_z<<")"<<std::endl;

  //casting the (x,y,z) to integers rounds down to next integer
  int x = (int)pos.m_x;
  int y = (int)pos.m_y;
  int z = (int)pos.m_z;

  int table_size = 52438387;//findNextPrime(2 * m_total_num_particles);

  int p1 = 73856093;
  int p2 = 19349663;
  int p3 = 83492791;

  int hash_key = (x*p1 ^ y*p2 ^ z*p3)%table_size;

}

int Fluid::findNextPrime(int _num)
{
  int next_prime = _num;
  bool found = false;

  while(!found)
  {
    next_prime++;
    if(isPrime(next_prime))
    {
      found = true;
    }
  }

  return next_prime;
}

bool Fluid::isPrime(int _num)
{
  for(int i = 2; i <= _num/2; i++)
  {
    if(_num % i == 0)
      return false;
  }
  return true;
}

void Fluid::fillHashTable()
{
  #pragma omp parallel for
  for(int i = 0; i < m_total_num_particles; i++)
  {
    ngl::Vec3 pos = m_particle_emitter.m_particles[i].m_position;
    hashParticles(pos, 1);
  }
}

void Fluid::Delete()
{

}

void Fluid::setCell()
{

}


void Fluid::Update()
{
  m_particle_emitter.Update();
}

void Fluid::Reset()
{

}

void Fluid::setVAO()
{

}
void Fluid::Draw()
{
  m_particle_emitter.Draw();
}
