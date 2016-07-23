#ifndef SHASH
#define SHASH

#include <ngl/Vec3.h>
#include <vector>
#include <iostream>
#include <map>
#include "ngl/VertexArrayObject.h"
#include "Particle.h"

namespace shash {

  int createHashKey(ngl::Vec3 _position, ngl::Real _sl, int _hashtable_size);
  int findNextPrime(int _num);
  bool isPrime(int _num);
  void fillHashTable(std::multimap<int,Particle> _hash_table, int _total_num_particles, std::vector<Particle> _particle, ngl::Real _sl);
  void emptyHashTable(std::multimap<int,Particle> _hash_table);
};

#endif // SHASH

