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

void Particle::ApplyExternalForces(float _timestep)
{
  m_velocity += m_gravity * _timestep;
}

void Particle::CalculateViscosity(float _timestep, float _h)
{
  for(int i = 0; i < m_neighbours.size(); i++)
  {

    ngl::Vec3 distance = m_neighbours[i]->m_position - m_position;
    float length = distance.length();

    ngl::Vec3 normal = distance/length;

    //inward radial velocity
    float u = (m_velocity - m_neighbours[i]->m_velocity).dot(normal);

    if(u > 0.0f)
    {
      float q = 1.0f - length/_h;
      ngl::Vec3 impulse = 0.5 * _timestep * q * (k_linear_viscosity * u + k_quadratic_viscosity * u * u) * normal;
      if(abs(impulse.m_x) > 10000.0f)
      {
        impulse.m_x /= 10000.0f;
      }
      if(abs(impulse.m_y) > 10000.0f)
      {
        impulse.m_y /= 10000.0f;
      }
      if(abs(impulse.m_z) > 10000.0f)
      {
        impulse.m_z /= 10000.0f;
      }
      m_velocity -= impulse;
      m_neighbours[i]->m_velocity += impulse;
    }
  }
}

void Particle::AdvanceParticles(float _timestep)
{
  m_prev_pos = m_position;
  m_position += m_velocity * _timestep;
//  m_position.m_z = 0;
//  m_velocity.m_z = 0;
}

void Particle::DoubleDensityRelaxation(float _timestep, float _h)
{
  //clear density and near density
  m_density = 0.0f;
  m_near_density = 0.0f;

  for(int i = 0; i < m_neighbours.size(); i++)
  {
    //calculate density and near density

    //  rij = xj - xi
    ngl::Vec3 distance = m_neighbours[i]->m_position - m_position;

    // |rij|
    float q  = 1.0f - distance.length() / _h;

    //density kernel =  (1 - r/h)^2
    m_density += q * q;

    //near density kernel = (1 - r/h)^3
    m_near_density += q * q * q;
  }

  // calculate pressure and near pressure

  //Pi = k(pi - p0)
  m_pressure = k_pressure * (m_density - m_rest_density);

  // Pi_near = k_near * pi_near
  m_near_pressure = k_near_pressure * m_near_density;

  if (m_pressure + m_near_pressure < 0.000001f || m_pressure + m_near_pressure > 1000000.0f)
  {
    m_pressure = 0;
    m_near_pressure = 0;
  }

  ngl::Vec3 dx = ngl::Vec3(0,0,0);

  for(int i = 0; i < m_neighbours.size(); i++)
  {
    // rij = xj - xi
    ngl::Vec3 distance = m_neighbours[i]->m_position - m_position;

    if(distance != ngl::Vec3(0,0,0))
    {

      // |rij|
      float magnitude = distance.length();

      // q = rij / h
      float q = 1.0f - magnitude/_h;

      //apply displacements

      // D = /\t^2 (P(1 - q) + P_near(1 - q)^2)rij   rij = unit normal
      //ngl::Vec3 displacement = 0.5f * (_timestep*_timestep) * (m_pressure * q + m_near_pressure * q * q) * distance/magnitude;

      ngl::Vec3 displacement = (_timestep * _timestep) * (m_pressure * q + m_near_pressure * (q * q)) * distance/magnitude;

      m_neighbours[i]->m_position += displacement/2;

      dx -= displacement/2;
    }
  }
  m_position += dx;

}

void Particle::UpdateVelocity(float _timestep)
{
  m_velocity = (m_position - m_prev_pos) / _timestep;
}

ngl::Vec3 pressureKernel(ngl::Vec3 r, float _sl)
{
  float PI = 3.141592f;


//  __
//  \/Wpressure(r, h) =  45/PI h ^6 r/mag_r (h - mag_r)^2
  float mag_r = r.length();
  return -45.0f/(PI * pow(_sl, 6)) * (r/mag_r) * ((_sl-mag_r) * (_sl-mag_r));

}

void Particle::calculateDensityPressure()
{
  m_density = 0;
  m_pressure = 0;
  for(int i = 0; i < m_neighbours.size(); i++)
  {
    ngl::Vec3 distance_vector =  m_position - m_neighbours[i]->m_position;
    float distance = distance_vector.lengthSquared();
    m_density +=  m_neighbours[i]->m_mass * WDefault(distance, 1);
  }
  m_pressure = k_pressure*(m_density - m_rest_density);
  int i = 0;
}

void Particle::calculateForce()
{
  for(int i = 0; i < m_neighbours.size(); i++)
  {

    ngl::Vec3 distance_vector =  m_position - m_neighbours[i]->m_position;

    float distance = distance_vector.length();
    float volume = m_neighbours[i]->m_mass / m_neighbours[i]->m_density;

    float temp_force = volume * (m_pressure + m_neighbours[i]->m_pressure)/2 * spiky(distance, 1);
    m_pressure_force += -distance_vector * temp_force/distance;
  }
  //std::cout<<"particle pressure: "<<m_pressure_force.m_x<<", "<<m_pressure_force.m_y<<", "<<m_pressure_force.m_z<<std::endl;

}

void Particle::Update(float _timestep)
{
    calculateDensityPressure();
    //std::cout<<"density: "<<m_density.m_x<<","<<m_density.m_y<<","<<m_density.m_z<<std::endl;
    calculateForce();
    m_force += m_pressure_force;
    //std::cout<<"particle force: "<<m_force.m_x<<", "<<m_force.m_y<<", "<<m_force.m_z<<std::endl;

    m_force += m_gravity;
    //m_force += -0.6f * m_velocity;
    //drag

    ngl::Vec3 acc;
    acc = m_force / (m_mass);
    m_position += m_velocity * _timestep;
    m_velocity += _timestep * acc;
    m_lifeleft -= _timestep;
    m_force = ngl::Vec3(0,0,0);
    m_pressure_force = ngl::Vec3(0,0,0);
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

