#include "Particle.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

Particle::Particle(bool _active)
{
  m_active = _active;
  m_gravity = ngl::Vec3(0, -9.81, 0);

  ngl::Real r = 0.2 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/0.8f);
  ngl::Real g = 0.2 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/0.8f);
  ngl::Real b = 0.2 + static_cast <float>(rand())/static_cast<float> (RAND_MAX/0.8f);
  m_colour = ngl::Vec3(r,g,b);
  m_colour = ngl::Vec3(0.0,0.5,1.0);
}

void Particle::calculateDensity()
{
  for(int i = 0; i < m_neighbours.size(); i++)
  {
    ngl::Vec3 distance_vector =  m_position - m_neighbours[i]->m_position;
    float distance = distance_vector.lengthSquared();
    m_density +=  m_neighbours[i]->m_mass * WDefault(distance, 1.0f);

    m_pressure = k_pressure*(m_density - m_rest_density);
  }
}

void Particle::calculatePressure()
{
  for(int i = 0; i < m_neighbours.size(); i++)
  {
    ngl::Vec3 distance_vector =  m_position - m_neighbours[i]->m_position;
    float distance = distance_vector.lengthSquared();
    m_pressure_force += m_neighbours[i]->m_mass * ((m_pressure + m_neighbours[i]->m_pressure)/(2 * m_neighbours[i]->m_density)) * pressureKernel(distance, 1);
  }
}

void Particle::Update(float _timestep)
{
    calculateDensity();
    //std::cout<<"density: "<<m_density.m_x<<","<<m_density.m_y<<","<<m_density.m_z<<std::endl;
    calculatePressure();
    m_force += m_pressure_force;
    m_force += m_gravity;
    //m_force += -0.6f * m_velocity;
    //drag

    ngl::Vec3 acc;
    acc = m_force / (m_mass);
    m_position += m_velocity * _timestep;
    m_velocity += _timestep * acc;
    m_lifeleft -= _timestep;
    m_force = ngl::Vec3(0,0,0);
    if (m_lifeleft <= 0)
    {
      m_active = false;
    }
}

void Particle::addForce(ngl::Vec3 _force)
{
  m_force += _force;
}

void Particle::Reset()
{
  m_position = m_init_position;

  m_velocity = m_init_velocity;
  m_lifeleft = m_lifespan;
}

