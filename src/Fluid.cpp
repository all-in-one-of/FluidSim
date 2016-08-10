#include "Fluid.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <random>
#include <cmath>
#include <algorithm>
#include <omp.h>

#include <SHash.h>


Fluid::Fluid()
{

}

Fluid::~Fluid()
{

}

void Fluid::Initialize()
{

  m_bbox.Initialize(ngl::Vec3(0,0,0), 20);
  m_total_num_particles = 40000;

  m_particle_emitter.Initialize(m_total_num_particles, ngl::Vec3(-10, 0, 0), 10, ngl::Vec3(0, 0, 0), 999999, 0.1);
    m_hashtable_size = findNextPrime(2* m_particle_emitter.m_particles.size());
  //m_particle_emitter.Emit();
  //shash::fillHashTable(m_hash_table, m_total_num_particles, m_particle_emitter.m_particles, m_sl);
  fillHashTable();
  findNeighbours();
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

  for(int i = 0; i < m_particle_emitter.m_particles.size(); i++)
  {
    if(m_particle_emitter.m_particles[i].getActive())
    {
      ngl::Vec3 pos = m_particle_emitter.m_particles[i].m_position;
      int hash_key = createHashKey(pos);
      m_particle_emitter.m_particles[i].setID(hash_key);
      m_hash_table.insert(std::pair<int, Particle*>(hash_key, &m_particle_emitter.m_particles[i]));
    }
  }

   //std::cout<<"Map size = "<<m_hash_table.size()<<std::endl;
//   std::multimap<int, Particle*>::iterator it = m_hash_table.begin();
//   while(it != m_hash_table.end())
//   {
//     std::cout<<"Key = "<<it->first<<"    Value = ("<<it->second->m_position.m_x<<", "
//                                                    <<it->second->m_position.m_y<<", "
//                                                    <<it->second->m_position.m_z<<")"<<std::endl;
//     //std::cout<<"Key = "<<it->first<<std::endl;
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
  std::vector<Particle*> neighbours;
  ngl::Vec3 smooth_length = ngl::Vec3(m_sl, m_sl, m_sl)*ngl::Vec3(m_sl, m_sl, m_sl);
  //std::cout<<"smooth length: ("<<smooth_length.m_x<<", "<<smooth_length.m_y<<", "<<smooth_length.m_z<<")"<<std::endl;

  #pragma omp parallel for
  for(int i = 0; i < m_particle_emitter.m_particles.size(); i++)
  {
    if(m_particle_emitter.m_particles[i].getActive())
    {
      m_particle_emitter.m_particles[i].m_neighbours.clear();
      neighbours.clear();

      ngl::Vec3 bmin = m_particle_emitter.m_particles[i].m_position - smooth_length;
      ngl::Vec3 bmax = m_particle_emitter.m_particles[i].m_position + smooth_length;

      for(ngl::Real x = bmin.m_x; x < bmax.m_x; x += m_sl)
      {
        for(ngl::Real y = bmin.m_y; y < bmax.m_y; y += m_sl)
        {
          for(ngl::Real z = bmin.m_z; z < bmax.m_z; z += m_sl)
          {
            ngl::Vec3 test_pos = ngl::Vec3(x,y,z);
            int test_key = createHashKey(test_pos);

            std::pair<std::multimap<int,Particle*>::iterator, std::multimap<int,Particle*>::iterator> ii;
            std::multimap<int, Particle*>::iterator it;
            ii = m_hash_table.equal_range(test_key);

            for(it = ii.first; it != ii.second; ++it)
            {
              bool inlist = false;

              for(int j = 0; j < m_particle_emitter.m_particles[i].m_neighbours.size(); j++)
              {
                if(it->second == m_particle_emitter.m_particles[i].m_neighbours[j])
                {
                  inlist = true;
                  j = m_particle_emitter.m_particles[i].m_neighbours.size();
                }
              }
              if(!inlist)
              {
                float INF  = 0.001f;
                ngl::Vec3 direction = m_particle_emitter.m_particles[i].m_position - it->second->m_position;
                float distance = direction.lengthSquared(); //sqrt((distance.m_x*distance.m_x) + (distance.m_y*distance.m_y) + (distance.m_z*distance.m_z));
                if(distance < (m_sl*m_sl) && &m_particle_emitter.m_particles[i] != it->second && distance > INF)
                {
                  m_particle_emitter.m_particles[i].m_neighbours.push_back(it->second);
                }
              }
            }

          }
        }
      }
    }
  }

//  std::cout<<"key: "<<m_particle_emitter.m_particles[50].getID()<<std::endl;
//  std::cout<<"num of neighbours: "<<m_particle_emitter.m_particles[50].m_neighbours.size()<<std::endl;
//  std::cout<<"Particle position: "<<m_particle_emitter.m_particles[50].m_position.m_x<<", "
//                                  <<m_particle_emitter.m_particles[50].m_position.m_y<<", "
//                                  <<m_particle_emitter.m_particles[50].m_position.m_z<<", "<<std::endl;
//  for(int i = 0; i < m_particle_emitter.m_particles[50].m_neighbours.size(); i++)
//  {
//      std::cout<<"( "<<m_particle_emitter.m_particles[50].m_neighbours[i]->m_position.m_x<<", "
//                     <<m_particle_emitter.m_particles[50].m_neighbours[i]->m_position.m_y<<", "
//                     <<m_particle_emitter.m_particles[50].m_neighbours[i]->m_position.m_z<<" )"<<std::endl;
//  }
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

  m_particle_emitter.Update();

  #pragma omp parallel for
  for(int i = 0; i < m_particle_emitter.m_particles.size(); i++)
  {
    if(m_particle_emitter.m_particles[i].getActive())
      m_particle_emitter.m_particles[i].ApplyExternalForces(m_dt);
  }

  #pragma omp parallel for
  for(int i = 0; i < m_particle_emitter.m_particles.size(); i++)
  {
    if(m_particle_emitter.m_particles[i].getActive())
      m_particle_emitter.m_particles[i].CalculateViscosity(m_dt, m_sl);
  }

  #pragma omp parallel for
  for(int i = 0; i < m_particle_emitter.m_particles.size(); i++)
  {
    if(m_particle_emitter.m_particles[i].getActive())
    m_particle_emitter.m_particles[i].AdvanceParticles(m_dt);
  }

  emptyHashTable();
  fillHashTable();
  findNeighbours();

  #pragma omp parallel for
  for(int i = 0; i < m_particle_emitter.m_particles.size(); i++)
  {
    if(m_particle_emitter.m_particles[i].getActive())
    m_particle_emitter.m_particles[i].DoubleDensityRelaxation(m_dt, m_sl);
  }

  #pragma omp parallel for
  for(int i = 0; i < m_particle_emitter.m_particles.size(); i++)
  {
    if(m_particle_emitter.m_particles[i].getActive())
    m_particle_emitter.m_particles[i].UpdateVelocity(m_dt);
  }

  #pragma omp parallel for
  for(int i = 0; i < m_particle_emitter.m_particles.size(); i++)
  {
    if(m_particle_emitter.m_particles[i].getActive() && m_particle_emitter.m_particles[i].m_ghost == false)
    m_bbox.collisionResponse(m_particle_emitter.m_particles[i].m_position,
                             m_particle_emitter.m_particles[i].m_velocity, -0.6);
  }


}

void Fluid::Reset()
{

}

void Fluid::setVAO()
{

}
void Fluid::Draw()
{
  m_bbox.Draw();
  m_particle_emitter.Draw();
}
