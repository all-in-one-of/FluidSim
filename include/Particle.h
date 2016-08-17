#ifndef PARTICLE_H
#define PARTICLE_H

#include <ngl/Vec3.h>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>

class Particle
{
public:
  Particle(bool _active);

  void ApplyExternalForces(float _timestep);
  void CalculateViscosity(float _timestep, float _h);
  void AdvanceParticles(float _timestep);
  void DoubleDensityRelaxation(float _timestep, float _h);
  void UpdateVelocity(float _timestep);

  void Update(float _timestep);
  void addForce(ngl::Vec3);
  void Reset();
  float WDefault(float _r, float _sl){return 315.0f/(64.0f * PI * pow(_sl, 9)) * pow(_sl*_sl-_r, 3);}
  float spiky(float r, float _sl){ return -45.0f/(PI * pow(_sl, 6)) * (_sl-r) * (_sl-r); }
  void calculateDensityPressure();
  void calculateForce();


  int getID(){return m_ID;}
  void setID(int _ID){m_ID = _ID;}

  int getHashkey(){return m_hash_key;}
  void setHashkey(int _key){m_hash_key = _key;}

  ngl::Vec3 getPosition(){return m_position;}
  void setPosition(ngl::Vec3 _position){m_position = _position;}

  void setPrevPosition(ngl::Vec3 _position){m_prev_pos = _position;}

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

  void setGhost(float _ghost){m_ghost = _ghost;}

  ngl::Vec3 m_position;
  ngl::Vec3 m_velocity;
  float m_pressure;
  float m_near_pressure;
  float m_near_density;
  float m_density;
  std::vector<Particle*> m_neighbours;
  float PI = 3.141592f;

  bool m_active;
  bool m_ghost;
  ngl::Vec3 m_colour;

private:

  const float m_rest_density = 8.0f;
  const float k_pressure = 6.0f;
  const float k_near_pressure = 7.0f;
  const float k_linear_viscosity = 1.0f;
  const float k_quadratic_viscosity = 0.5f;

  int m_ID;
  int m_hash_key;

  ngl::Vec3 m_force;
  ngl::Vec3 m_prev_pos;
  ngl::Vec3 m_pressure_force;
  ngl::Vec3 m_init_position;
  ngl::Vec3 m_init_velocity;
  ngl::Vec3 m_gravity;

  ngl::Vec3 m_acceleration;


  float m_mass;
  float m_lifespan;
  float m_lifeleft;


};
#endif // PARTICLE_H

