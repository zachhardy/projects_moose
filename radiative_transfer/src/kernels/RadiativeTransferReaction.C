// Radiative Transfer Reaction
// Author: Zachary Hardy

#include "RadiativeTransferReaction.h"
#include "MooseMesh.h"

registerMooseObject("RadiativeTransferApp", RadiativeTransferReaction);

defineLegacyParams(RadiativeTransferReaction);

InputParameters RadiativeTransferReaction::validParams()
{
  MooseEnum source_type("material radiation");
  InputParameters params = Reaction::validParams();
  params.addRequiredCoupledVar("coupled_var", "Coupled variable.");
  params.addParam<MooseEnum>("source_type", source_type,
                             "The type of source this is, a.k.a. which "
                             "equation this kernel corresponds to.");
  return params;
}

RadiativeTransferReaction::RadiativeTransferReaction(const InputParameters& parameters)
  : Reaction(parameters),
    _is_temperature(getParam<MooseEnum>("source_type") == "material"),
    _v_var(coupled("coupled_var")),
    _v(coupledValue("coupled_var")),

    _reactivity(getMaterialProperty<Real>("photon_absorptivity")),
    _reactivity_du(_is_temperature ?
                        getMaterialProperty<Real>("photon_absorptivity_dT") :
                        getMaterialProperty<Real>("photon_absorptivity_dE")),
    _reactivity_dv(_is_temperature ?
                        getMaterialProperty<Real>("photon_absorptivity_dE") :
                        getMaterialProperty<Real>("photon_absorptivity_dT"))
{
}

Real RadiativeTransferReaction::computeQpResidual()
{
  if (_is_temperature) {
    return _reactivity[_qp] * _test[_i][_qp] * (std::pow(_u[_qp], 4) - _v[_qp]);
  }
  else {
    return _reactivity[_qp] * _test[_i][_qp] * (_u[_qp] - std::pow(_v[_qp], 4));
  }
}

Real RadiativeTransferReaction::computeQpJacobian()
{
  Real jac = 0.0;
  if (_is_temperature) {
    jac += 4.0 * std::pow(_u[_qp], 3) * _reactivity[_qp] * _test[_i][_qp] * _phi[_j][_qp];
    jac += _reactivity_du[_qp] * _phi[_j][_qp] * _test[_i][_qp] * (std::pow(_u[_qp], 4) - _v[_qp]);
  }
  else {
    jac += _reactivity[_qp] * _test[_i][_qp] * _phi[_j][_qp];
    jac += _reactivity_du[_qp] * _phi[_j][_qp] * _test[_i][_qp] * (_u[_qp] - std::pow(_v[_qp], 4));
  }
  return jac;
}

Real RadiativeTransferReaction::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _v_var) {
    if (_is_temperature) {
      return _reactivity_dv[_qp] * _phi[_j][_qp] * _test[_i][_qp] * (std::pow(_u[_qp], 4) - _v[_qp]);
    }
    else {
      return _reactivity_dv[_qp] * _phi[_j][_qp] * _test[_i][_qp] * (_u[_qp] - std::pow(_v[_qp], 4));
    }
  }
  else {
    return 0.0;
  }

}
