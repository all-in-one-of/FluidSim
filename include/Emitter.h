#ifndef EMITTER_H
#define EMITTER_H
#include <iostream>
#include <vector>
#include "Particle.h"

#include<Alembic/AbcGeom/All.h>
#include<Alembic/AbcCoreOgawa/All.h>


class Emitter
{
public:
  Emitter();
  void Initialize(float _num_particles,  ngl::Vec3 _initial_pos, float _range, ngl::Vec3 _initial_vel, float _lifespan, float _mass);
  void Emit();
  void Update();
  void Draw();
  void toggleExport(){ m_export^=true;}


  float getTimestep(){return m_dt;}
  void setTimestep(float _timestep){m_dt = _timestep;}

  std::vector<Particle> m_particles;

private:

  std::vector<Particle> m_active_particles;
  ngl::Vec3 m_gravity;
  float m_emission_rate=0.0f;
  float m_last_emission=0.0f;
  float m_dt;
  float m_current_time = 0.0;
  bool m_export = true;

  void exportFrame();
  std::unique_ptr <Alembic::AbcGeom::OArchive> m_archive;
  std::unique_ptr <Alembic::AbcGeom::OPoints> m_partsOut;
  std::unique_ptr <Alembic::AbcGeom::OC4fArrayProperty> m_rgbOut;


};

#endif // EMITTER_H
