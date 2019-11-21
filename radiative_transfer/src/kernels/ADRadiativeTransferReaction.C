#include "ADRadiativeTransferReaction.h"

registerADMooseObject("RadiativeTransferApp", ADRadiativeTransferReaction);

defineADLegacyParams(ADRadiativeTransferReaction);

template<ComputeStage compute_stage>
InputParameters
ADRadiativeTransferReaction<compute_stage>::validParams()
{
  InputParameters params = ADKernel<compute_stage>::validParams();
  params.addCoupledVar("coupled_var", "Coupled variable to this kernel.");
  return params;
}

template<ComputeStage compute_stage>
ADRadiativeTransferReaction<compute_stage>::ADRadiativeTransferReaction(const InputParameters& parameters)
  : ADKernel<compute_stage>(parameters),
    _is_temperature(_var.name() == "temperature"),
    _reactivity(getADMaterialProperty<Real>("photon_absorptivity")),
    _v(isCoupled("coupled_var") ? adCoupledValue("coupled_var") : _u)
{}

template<ComputeStage compute_stage>
ADReal
ADRadiativeTransferReaction<compute_stage>::computeQpResidual()
{
  if (_is_temperature) {
    return _reactivity[_qp] * _test[_i][_qp] * (std::pow(_u[_qp], 4) - _v[_qp]);
  }
  else {
    return _reactivity[_qp] * _test[_i][_qp] * (_u[_qp] - std::pow(_v[_qp], 4));
  }
}
