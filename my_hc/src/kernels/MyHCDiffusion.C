//* MyHC Kernel for NUEN 618 Homework 6
//* Author: Zachary Hardy

#include "MyHCDiffusion.h"
#include "MooseMesh.h"

registerMooseObject("MyHCApp", MyHCDiffusion);

defineLegacyParams(MyHCDiffusion);

InputParameters MyHCDiffusion::validParams()
{
  InputParameters params = Diffusion::validParams();
  params.addClassDescription("Diffusion for heat conduction.");
  params.addParam<MaterialPropertyName>(
    "thermal_conductivity",
    "thermal_conductivity",
    "Property name of the thermal conductivity.");
  params.addParam<MaterialPropertyName>(
    "thermal_conductivity_dT",
    "thermal_conductivity_dT",
    "Property name for the temperature derivative of the thermal conductivity.");
  return params;
}

MyHCDiffusion::MyHCDiffusion(const InputParameters& parameters)
  : Diffusion(parameters),
    _thermal_conductivity(getMaterialProperty<Real>("thermal_conductivity")),
    _thermal_conductivity_dT(getMaterialProperty<Real>("thermal_conductivity_dT"))
  {}

Real MyHCDiffusion::computeQpResidual()
{
  return _thermal_conductivity[_qp] * Diffusion::computeQpResidual();
}

Real MyHCDiffusion::computeQpJacobian()
{
  Real jac = _thermal_conductivity[_qp] * Diffusion::computeQpJacobian();
  jac += (_thermal_conductivity_dT)[_qp] * _phi[_j][_qp] * Diffusion::computeQpResidual();
  return jac;
}
