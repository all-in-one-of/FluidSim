#ifndef PARTICLE_H
#define PARTICLE_H

#include <ngl/Vec3.h>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>

class Particle
{
public:
  Particle(bool _active);
  void Update(float _timestep);
  void addForce(ngl::Vec3);
  void Reset();
  int findIntegerPosition(ngl::Vec3 _position, float _cell_size);
  void hashFunction();

  boost::tuple<int,int,int> test();

  ngl::Vec3 getPosition(){return m_position;}
  void setPosition(ngl::Vec3 _position){m_position = _position;}

  ngl::Vec3 getInitPosition(){return m_init_position;}
  void setInitPosition(ngl::Vec3 _position){m_init_position = _position;}

  ngl::Vec3 getVelocity(){return m_velocity;}
  void setVelocity(ngl::Vec3 _velocity){m_velocity = _velocity;}

  ngl::Vec3 getInitVelocity(){return m_init_velocity;}
  void setInitVelocity(ngl::Vec3 _velocity){m_init_velocity = _velocity;}

  ngl::Vec3 getColour(){return m_colour;}
  void setColour(ngl::Vec3 _colour){m_colour = _colour;}

  float getMass(){return m_mass;}
  void setMass(float _mass){m_mass = _mass;}

  float getLifespan(){return m_lifespan;}
  void setLifespan(float _lifespan){m_lifespan = _lifespan;}

  float getLifeleft(){return m_lifeleft;}
  void setLifeleft(float _lifeleft){m_lifeleft = _lifeleft;}

  bool getActive(){return m_active;}
  void setActive(float _active){m_active = _active;}

    ngl::Vec3 m_position;

private:


  ngl::Vec3 m_velocity;
  ngl::Vec3 m_force;
  ngl::Vec3 m_init_position;
  ngl::Vec3 m_init_velocity;
  ngl::Vec3 m_gravity;
  ngl::Vec3 m_colour;
  float m_mass;
  float m_lifespan;
  float m_lifeleft;
  bool m_active;

};
#endif // PARTICLE_H

