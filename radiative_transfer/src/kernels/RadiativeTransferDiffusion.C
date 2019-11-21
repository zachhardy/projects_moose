// Radiative Transfer Diffusion
// Author: Zachary Hardy

#include "RadiativeTransferDiffusion.h"
#include "MooseMesh.h"

registerMooseObject("RadiativeTransferApp", RadiativeTransferDiffusion);

defineLegacyParams(RadiativeTransferDiffusion);

InputParameters RadiativeTransferDiffusion::validParams()
{
  MooseEnum diffusion_type("heat radiation");
  InputParameters params = Diffusion::validParams();
  params.addRequiredCoupledVar("coupled_var", "Coupled variable.");
  params.addParam<MooseEnum>("diffusion_type", diffusion_type,
                             "The name of the diffusion parameter.");
  return params;
}

RadiativeTransferDiffusion::RadiativeTransferDiffusion(const InputParameters& parameters)
  : Diffusion(parameters),
    _is_temperature(getParam<MooseEnum>("diffusion_type") == "heat"),
    _v_var(coupled("coupled_var")),
    _grad_v(coupledGradient("coupled_var")),
  	_diffusivity(_is_temperature ?
                        getMaterialProperty<Real>("thermal_conductivity") :
                        getMaterialProperty<Real>("photon_diffusivity")),
    _diffusivity_du(_is_temperature ?
                        getMaterialProperty<Real>("thermal_conductivity_dT") :
                        getMaterialProperty<Real>("photon_diffusivity_dE")),
    _diffusivity_dv(_is_temperature ?
                        getMaterialProperty<Real>("thermal_conductivity_dE") :
                        getMaterialProperty<Real>("photon_diffusivity_dT"))  
{
}

Real RadiativeTransferDiffusion::computeQpResidual()
{
  return _diffusivity[_qp] * _grad_test[_i][_qp] * _grad_u[_qp];
}

Real RadiativeTransferDiffusion::computeQpJacobian()
{
  Real jac = _diffusivity[_qp] * _grad_test[_i][_qp] * _grad_phi[_j][_qp];
  jac += _diffusivity_du[_qp] * _phi[_j][_qp] * _grad_test[_i][_qp] * _grad_u[_qp];
  return jac;
}

Real RadiativeTransferDiffusion::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _v_var) {
    return _diffusivity_dv[_qp] * _phi[_j][_qp] * _grad_test[_i][_qp] * _grad_u[_qp] ;
  }
  else {
    return 0.0;
  }
}
