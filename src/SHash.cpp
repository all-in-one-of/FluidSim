#include "SHash.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <random>
#include <cmath>

namespace shash {



int createHashKey(ngl::Vec3 _position, ngl::Real _sl, int _hashtable_size)
{
  //  This function performs the spacial hashing of particles to a multimap.
  //  _position is a particle position, and _sl is the smoothing length

  ngl::Vec3 pos = _position;

  //  X(x) = ([Xx/l], [Xy/l], [Xz/l])
  pos /= _sl;

  //casting the (x,y,z) to integers rounds down to next integer
  int x = (int)pos.m_x;
  int y = (int)pos.m_y;
  int z = (int)pos.m_z;

  int p1 = 73856093;
  int p2 = 19349663;
  int p3 = 83492791;

  int hash_key = abs((x*p1 ^ y*p2 ^ z*p3)%_hashtable_size);

  return hash_key;
}

int findNextPrime(int _num)
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

bool isPrime(int _num)
{
  for(int i = 2; i <= _num/2; i++)
  {
    if(_num % i == 0)
      return false;
  }

  return true;
}

void fillHashTable(std::multimap<int,Particle> _hash_table, int _total_num_particles, std::vector<Particle> _particles, ngl::Real _sl)
{
  for(int i = 0; i < _total_num_particles; i++)
  {
    ngl::Vec3 pos = _particles[i].m_position;
    int hashtable_size = findNextPrime(2 * _total_num_particles);
    int hash_key = createHashKey(pos, _sl, hashtable_size);
    _hash_table.insert(std::pair<int, Particle>(hash_key, _particles[i]));
  }

//   std::cout<<"Map size = "<<_hash_table.size()<<std::endl;
//   std::multimap<int, Particle>::iterator it = _hash_table.begin();
//   while(it != _hash_table.end())
//   {
//     std::cout<<"Key = "<<it->first<<"    Value = ("<<it->second.m_position.m_x<<", "<<it->second.m_position.m_y<<", "<<it->second.m_position.m_z<<")"<<std::endl;
//     it++;
//   }
}

void emptyHashTable(std::multimap<int,Particle> _hash_table)
{
  while (!_hash_table.empty())
  {
    _hash_table.erase(_hash_table.begin());
  }
}

}

