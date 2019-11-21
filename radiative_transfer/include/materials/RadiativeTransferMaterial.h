// Radiative Transfer Material
// Author: Zachary Hardy

#pragma once

#include "Material.h"

class RadiativeTransferMaterial : public Material
{
public:
  static InputParameters validParams();
  RadiativeTransferMaterial(const InputParameters& parameters);

protected:
  virtual void computeProperties();

  const VariableValue& _temperature;
  const VariableValue& _radiation;
  const VariableGradient& _grad_radiation;

  const Real _atomic_mass;

  MaterialProperty<Real>& _thermal_conductivity;
  MaterialProperty<Real>& _thermal_conductivity_dT;
  MaterialProperty<Real>& _thermal_conductivity_dE;

  MaterialProperty<Real>& _photon_diffusivity;
  MaterialProperty<Real>& _photon_diffusivity_dT;
  MaterialProperty<Real>& _photon_diffusivity_dE;

  MaterialProperty<Real>& _photon_absorptivity;
  MaterialProperty<Real>& _photon_absorptivity_dT;
  MaterialProperty<Real>& _photon_absorptivity_dE;
};
