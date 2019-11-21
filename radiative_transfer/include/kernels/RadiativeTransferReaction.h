// Radiative Transfer Reaction
// Author: Zachary Hardy

#pragma once

#include "Reaction.h"

class RadiativeTransferReaction : public Reaction
{
public:
  static InputParameters validParams();
  RadiativeTransferReaction(const InputParameters& parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  const bool _is_temperature;
  unsigned int _v_var;
  const VariableValue& _v;

  const MaterialProperty<Real>& _reactivity;
  const MaterialProperty<Real>& _reactivity_du;
  const MaterialProperty<Real>& _reactivity_dv;
};
