// Radiative Transfer Diffusion
// Author: Zachary Hardy

#pragma once

#include "Diffusion.h"

class RadiativeTransferDiffusion : public Diffusion
{
public:
  static InputParameters validParams();
  RadiativeTransferDiffusion(const InputParameters& parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const bool _is_temperature;
  unsigned int _v_var;
  const VariableGradient& _grad_v;

  const MaterialProperty<Real>& _diffusivity;
	const MaterialProperty<Real>& _diffusivity_du;
  const MaterialProperty<Real>& _diffusivity_dv;
};
