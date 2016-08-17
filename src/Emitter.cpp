#include "Emitter.h"
#include <ngl/NGLInit.h>
#include <random>
#include <cstdlib>
#include<ngl/RibExport.h>

namespace AbcG = Alembic::AbcGeom;

Emitter::Emitter()
{

}


void Emitter::Initialize(float _num_particles,  ngl::Vec3 _initial_pos, float _range, ngl::Vec3 _initial_vel, float _lifespan, float _mass)
{
  //int boundary_particles = 10;
//  float count = 0.6f/2;
//  float half_size = 20.0f/2.0f;

//  for(float i = -half_size; i <= half_size; i +=count)
//  {
//    for(float j = -half_size; j <= half_size; j +=count)
//    {

//      Particle p(true);
//      p.setGhost(true);
//      p.setColour(ngl::Vec3(1,0,0));
//      p.setPosition(ngl::Vec3(i, j, half_size));
//      p.setInitPosition(ngl::Vec3(i, j, half_size));
//      p.setLifespan(_lifespan);
//      p.setMass(_mass);
//      p.setVelocity(_initial_vel);
//      p.setInitVelocity(_initial_vel);
//      m_particles.push_back(p);
//    }
//  }
  //std::cout<<"num ghost particles: "<< m_particles.size()<<std::endl;

//  for(int i = 0; i < boundary_particles; i ++)
//  {
//    float size_rand = -10 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/(20));
//    int half_size = 20/2;
//    Particle p(true);
//    p.setGhost(true);
//    p.setPosition(ngl::Vec3(size_rand, -half_size, -half_size));
//    p.setInitPosition(ngl::Vec3(size_rand, -half_size, -half_size));
//    p.setLifespan(_lifespan);
//    p.setMass(_mass);
//    p.setVelocity(_initial_vel);
//    p.setInitVelocity(_initial_vel);
//    m_particles.push_back(p);
//  }

//  for(int i = 0; i < boundary_particles; i ++)
//  {
//    float size_rand = -10 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/(20));
//    int half_size = 20/2;
//    Particle p(true);
//    p.setGhost(true);
//    p.setPosition(ngl::Vec3(half_size, -half_size, size_rand));
//    p.setInitPosition(ngl::Vec3(half_size, -half_size, size_rand));
//    p.setLifespan(_lifespan);
//    p.setMass(_mass);
//    p.setVelocity(_initial_vel);
//    p.setInitVelocity(_initial_vel);
//    m_particles.push_back(p);
//  }

//  for(int i = 0; i < boundary_particles; i ++)
//  {
//    float size_rand = -10 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/(20));
//    int half_size = 20/2;
//    Particle p(true);
//    p.setGhost(true);
//    p.setPosition(ngl::Vec3(-half_size, -half_size, size_rand));
//    p.setInitPosition(ngl::Vec3(-half_size, -half_size, size_rand));
//    p.setLifespan(_lifespan);
//    p.setMass(_mass);
//    p.setVelocity(_initial_vel);
//    p.setInitVelocity(_initial_vel);
//    m_particles.push_back(p);
//  }

//  for(int i = 0; i < boundary_particles; i ++)
//  {
//    float size_rand = -10 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/(20));
//    int half_size = 20/2;
//    Particle p(true);
//    p.setGhost(true);
//    p.setPosition(ngl::Vec3(half_size, size_rand, half_size));
//    p.setInitPosition(ngl::Vec3(half_size, size_rand, half_size));
//    p.setLifespan(_lifespan);
//    p.setMass(_mass);
//    p.setVelocity(_initial_vel);
//    p.setInitVelocity(_initial_vel);
//    m_particles.push_back(p);
//  }


//  for(int i = 0; i < boundary_particles; i ++)
//  {
//    float size_rand = -10 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/(20));
//    int half_size = 20/2;
//    Particle p(true);
//    p.setGhost(true);
//    p.setPosition(ngl::Vec3(-half_size, size_rand, -half_size));
//    p.setInitPosition(ngl::Vec3(-half_size, size_rand, -half_size));
//    p.setLifespan(_lifespan);
//    p.setMass(_mass);
//    p.setVelocity(_initial_vel);
//    p.setInitVelocity(_initial_vel);
//    m_particles.push_back(p);
//  }


//  for(int i = 0; i < boundary_particles; i ++)
//  {
//    float size_rand = -10 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/(20));
//    int half_size = 20/2;
//    Particle p(true);
//    p.setGhost(true);
//    p.setPosition(ngl::Vec3(-half_size, size_rand, half_size));
//    p.setInitPosition(ngl::Vec3(-half_size, size_rand, half_size));
//    p.setLifespan(_lifespan);
//    p.setMass(_mass);
//    p.setVelocity(_initial_vel);
//    p.setInitVelocity(_initial_vel);
//    m_particles.push_back(p);
//  }


//  for(int i = 0; i < boundary_particles; i ++)
//  {
//    float size_rand = -10 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/(20));
//    int half_size = 20/2;
//    Particle p(true);
//    p.setGhost(true);
//    p.setPosition(ngl::Vec3(half_size, size_rand, -half_size));
//    p.setInitPosition(ngl::Vec3(half_size, size_rand, -half_size));
//    p.setLifespan(_lifespan);
//    p.setMass(_mass);
//    p.setVelocity(_initial_vel);
//    p.setInitVelocity(_initial_vel);
//    m_particles.push_back(p);
//  }



  for(int i = 0; i < _num_particles; i++)
  {
     ngl::Real theta_rand = 0 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/(M_PI*2));
     ngl::Real y_theta_rand = 0 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/(M_PI*2));

     float x_radius_rand =  static_cast <float>(rand())/static_cast<float> (RAND_MAX/(_range/2));
     float y_radius_rand =  static_cast <float>(rand())/static_cast<float> (RAND_MAX/(_range*1.2));
     float z_radius_rand =  -_range + static_cast <float>(rand())/static_cast<float> (RAND_MAX/(_range/2));


     ngl::Real x = ((float)cos(theta_rand))*x_radius_rand;
     ngl::Real z = ((float)sin(theta_rand))*x_radius_rand;
     ngl::Real y = ((float)cos(y_theta_rand))*x_radius_rand;
     ngl::Vec3 init_pos = ngl::Vec3(_initial_pos.m_x + x, _initial_pos.m_y+y_radius_rand, _initial_pos.m_z + z);

    Particle p(false);
    p.setGhost(false);
    p.setPosition(init_pos);
    p.setPrevPosition(init_pos);
    p.setInitPosition(init_pos);
    p.setLifespan(_lifespan);
    p.setMass(_mass);
    p.setVelocity(_initial_vel);
    p.setInitVelocity(_initial_vel);
    m_particles.push_back(p);
  }
  //std::cout<<"num of particles: "<< m_particles.size()<<std::endl;
  m_last_emission = m_current_time;


  m_archive.reset(new AbcG::OArchive(Alembic::AbcCoreOgawa::WriteArchive(), "particlesOut.abc"));

  AbcG::TimeSampling ts(1.0f/24.0f, 0.0f);
  AbcG::OObject topObj(*m_archive.get(), AbcG::kTop);
  Alembic::Util::uint32_t tsidx = topObj.getArchive().addTimeSampling(ts);
  m_partsOut.reset(new AbcG::OPoints(topObj, "FluidSim", tsidx));
  m_rgbOut.reset(new AbcG::OC4fArrayProperty(m_partsOut->getSchema(), ".colour", false, AbcG::kVertexScope, tsidx));
}


void Emitter::Emit()
{
  float particlesPF = 80;
  if(m_current_time > m_last_emission + m_emission_rate)
  {
    int active_particles = 0;
    for(int i = 0; i < m_particles.size(); i ++)
    {

      if(m_particles[i].getActive() == false)
      {
        m_particles[i].setActive(true);
        active_particles += 1;
        m_particles[i].Reset();

        if(active_particles >= particlesPF)
        {
          break;
        }
        m_last_emission = m_current_time;
      }
    }
  }
}

void Emitter::Update()
{
  Emit();
//  for(int i = 0; i < m_particles.size(); i ++)
//  {
//    if(m_particles[i].getActive()==true)
//    {
//      m_particles[i].Update(m_dt);
//    }
//  }
  m_current_time += m_dt;
}

void Emitter::Draw()
{
  struct data
  {
    ngl::Vec3 pos;
    ngl::Vec3 colour;
  };

  std::vector<data> activeParticles;
  for(int i = 0; i < m_particles.size(); i ++)
  {
    if(m_particles[i].getActive() == true /*&& m_particles[i].m_ghost == false*/)
    {
      data p;
      p.pos = m_particles[i].getPosition();
      p.colour = m_particles[i].getColour();
      activeParticles.push_back(p);
    }
  }

  ngl::VertexArrayObject *vao=ngl::VertexArrayObject::createVOA(GL_POINTS);
  vao->bind();
  vao->setData(activeParticles.size()*sizeof(data),activeParticles[0].pos.m_x);
  vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(data),0);
  vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(data),3);
  vao->setNumIndices(activeParticles.size());
  vao->draw();
  vao->unbind();

  if(m_export==true)
  {
     //timer.restart();
     exportFrame();
  }



  vao->removeVOA();
  delete vao;
}

void Emitter::exportFrame()
{
  static int frame = 0;

  ++frame;

  std::vector<Imath::V3f>positions;

  std::vector<Alembic::Util::uint64_t> id;

  Imath::V3f data;

  Imath::C4f c;

  std::vector<Imath::C4f> colours;

  for(unsigned int i = 0; i < m_particles.size(); i++)
  {
    //std::cout<<Imath::V3f(m_particles[10].m_position.m_x, m_particles[i].m_position.m_y, m_particles[i].m_position.m_z )<<std::endl;
    //if(m_particles[i].m_ghost == false)
    //{
      positions.push_back(Imath::V3f(m_particles[i].m_position.m_x, m_particles[i].m_position.m_y, m_particles[i].m_position.m_z ));
      id.push_back(i);
      colours.push_back(Imath::C4f(m_particles[i].m_colour.m_x, m_particles[i].m_colour.m_y, m_particles[i].m_colour.m_z, 1.0f));
   // }
  }

  AbcG::V3fArraySample pos(positions);
  AbcG::UInt64ArraySample ids(id);
  AbcG::OPointsSchema::Sample psamp(pos, ids);

  m_partsOut->getSchema().set(psamp);
  AbcG::C4fArraySample colourArray(colours);
  m_rgbOut->set(colourArray);

}



