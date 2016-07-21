#ifndef EMITTER_H
#define EMITTER_H
#include <iostream>
#include <vector>
#include "Particle.h"


class Emitter
{
public:
  Emitter();
  void Initialize(float _num_particles,  ngl::Vec3 _initial_pos, float _range, ngl::Vec3 _initial_vel, float _lifespan, float _mass, float _variance);
  void Emit();
  void Update();
  void Draw();

  float getTimestep(){return m_dt;}
  void setTimestep(float _timestep){m_dt = _timestep;}

  std::vector<Particle> getParticleList(){return m_particles;}
  std::vector<Particle> m_particles;

private:

  std::vector<Particle> m_active_particles;
  ngl::Vec3 m_gravity;
  float m_emission_rate=0.0f;
  float m_last_emission=0.0f;
  float m_dt;
  float m_current_time = 0.0;

};

#endif // EMITTER_H
