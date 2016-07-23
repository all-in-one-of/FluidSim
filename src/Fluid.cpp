#include "Fluid.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <random>
#include <cmath>
#include <SHash.h>


Fluid::Fluid()
{

}

Fluid::~Fluid()
{

}

void Fluid::Initialize()
{

  m_total_num_particles = 100;
  m_hashtable_size = findNextPrime(2* m_total_num_particles);
  m_particle_emitter.Initialize(m_total_num_particles, ngl::Vec3(0, 0, 0), 30, ngl::Vec3(0, 0, 0), 1.0, 0.1, 0.3);
  //shash::fillHashTable(m_hash_table, m_total_num_particles, m_particle_emitter.m_particles, m_sl);
  fillHashTable();
  //findNeighbours();
}

void Fluid::setFluidTimestep(float _dt)
{
  m_dt = _dt;
  m_particle_emitter.setTimestep(m_dt);
}

int Fluid::createHashKey(ngl::Vec3 _position)
{
  //  This function performs the spacial hashing of particles to a multimap.
  //  _position is a particle position, and _sl is the smoothing length

  ngl::Vec3 pos = _position;

  //  X(x) = ([Xx/l], [Xy/l], [Xz/l])
  pos /= m_sl;

  //casting the (x,y,z) to integers rounds down to next integer
  int x = (int)pos.m_x;
  int y = (int)pos.m_y;
  int z = (int)pos.m_z;

  int p1 = 73856093;
  int p2 = 19349663;
  int p3 = 83492791;

  int hash_key = abs((x*p1 ^ y*p2 ^ z*p3)%m_hashtable_size);

  return hash_key;
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
  for(int i = 0; i < m_total_num_particles; i++)
  {
    ngl::Vec3 pos = m_particle_emitter.m_particles[i].m_position;
    int hash_key = createHashKey(pos);
    m_hash_table.insert(std::pair<int, Particle>(hash_key, m_particle_emitter.m_particles[i]));
  }

   //std::cout<<"Map size = "<<m_hash_table.size()<<std::endl;
//   std::multimap<int, Particle>::iterator it = m_hash_table.begin();
//   while(it != m_hash_table.end())
//   {
//     std::cout<<"Key = "<<it->first<<"    Value = ("<<it->second.m_position.m_x<<", "
//                                                    <<it->second.m_position.m_y<<", "
//                                                    <<it->second.m_position.m_z<<")"<<std::endl;
//     it++;
//   }
}

void Fluid::emptyHashTable()
{
  while (!m_hash_table.empty())
  {
    m_hash_table.erase(m_hash_table.begin());
  }
}

void Fluid::findNeighbours()
{
  ngl::Vec3 smooth_length = ngl::Vec3(m_sl, m_sl, m_sl)*ngl::Vec3(m_sl, m_sl, m_sl);
  //std::cout<<"smooth length: ("<<smooth_length.m_x<<", "<<smooth_length.m_y<<", "<<smooth_length.m_z<<")"<<std::endl;
  for(int i = 0; i < m_total_num_particles; i++)
  {
    ngl::Vec3 bmin = m_particle_emitter.m_particles[i].m_position - smooth_length;
    ngl::Vec3 bmax = m_particle_emitter.m_particles[i].m_position + smooth_length;

    for(ngl::Real i = bmin.m_x; i < bmax.m_x; i + m_sl)
    {
      for(ngl::Real j = bmin.m_y; j < bmax.m_y; j + m_sl)
      {
        for(ngl::Real k = bmin.m_z; k < bmax.m_z; k + m_sl)
        {
          ngl::Vec3 test_pos = ngl::Vec3(i,j,k);
          int test_key = createHashKey(test_pos);
          //std::cout<<"test key: "<<test_key<<std::endl;
          //std::cout<<"num neighbours in key: "<<m_hash_table.count(test_key)<<std::endl;
        }
      }
    }

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
  //shash::emptyHashTable(m_hash_table);
  //shash::fillHashTable(m_hash_table, m_total_num_particles, m_particle_emitter.m_particles, m_sl);

  emptyHashTable();
  fillHashTable();
  //findNeighbours();
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
