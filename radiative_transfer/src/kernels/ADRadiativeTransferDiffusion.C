// Radiative Transfer AD Diffusion
// Author: Zachary Hardy

#include "ADRadiativeTransferDiffusion.h"

registerADMooseObject("RadiativeTransferApp", ADRadiativeTransferDiffusion);

defineADLegacyParams(ADRadiativeTransferDiffusion);

template<ComputeStage compute_stage>
InputParameters
ADRadiativeTransferDiffusion<compute_stage>::validParams()
{
  InputParameters params = ADDiffusion<compute_stage>::validParams();
  params.addCoupledVar("coupled_var", "Coupled variable to this kernel.");
  return params;
}

template<ComputeStage compute_stage>
ADRadiativeTransferDiffusion<compute_stage>::ADRadiativeTransferDiffusion(const InputParameters& parameters)
  : ADDiffusion<compute_stage>(parameters),
    _diffusivity(getADMaterialProperty<Real>("thermal_conductivity")),
    _grad_v(isCoupled("coupled_var") ? adCoupledGradient("coupled_var") : _grad_u)
{}

template<ComputeStage compute_stage>
ADRealVectorValue
ADRadiativeTransferDiffusion<compute_stage>::precomputeQpResidual()
{
  return _diffusivity[_qp] * _grad_v[_qp];
}
