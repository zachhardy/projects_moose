//* MyHC Kernel for NUEN 618 Homework 6
//* Author: Zachary Hardy

#pragma once

#include "Diffusion.h"
#include "Material.h"

class MyHCDiffusion : public Diffusion
{
public:
  static InputParameters validParams();
  MyHCDiffusion(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

  const MaterialProperty<Real>& _thermal_conductivity;
  const MaterialProperty<Real>& _thermal_conductivity_dT;
};
