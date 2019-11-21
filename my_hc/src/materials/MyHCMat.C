//* MyHCMat Material for NUEN 618 Homework 6
//* Author: Zachary Hardy

#include "MyHCMat.h"
#include "Function.h"
#include "libmesh/quadrature.h"


registerMooseObject("MyHCApp", MyHCMat);

InputParameters MyHCMat::validParams()
{
  InputParameters params = Material::validParams();
  params.addCoupledVar("temperature", "Coupled temperature");

  params.addParam<Real>("thermal_conductivity", "Thermal conductivity value.");
  params.addParam<FunctionName>("thermal_conductivity_function",
                                "",
                                "Thermal conductivity function.");
  return params;
}

MyHCMat::MyHCMat(const InputParameters& parameters)
  : Material(parameters),
    _has_temperature(isCoupled("temperature")),
    _temperature(_has_temperature ? coupledValue("temperature") : _zero),

    _my_k(
      isParamValid("thermal_conductivity") ? getParam<Real>("thermal_conductivity") : 0),

    _k(declareProperty<Real>("thermal_conductivity")),
    _dk_dT(declareProperty<Real>("thermal_conductivity_dT")),
    _k_function(
      getParam<FunctionName>("thermal_conductivity_function") != ""
        ? &getFunction("thermal_conductivity_function") : NULL)
  {
    if (_k_function && !_has_temperature) {
      mooseError("Must couple with temperature if using thermal conductivity function.");
    }
    if (!_k_function && _has_temperature) {
      mooseError("Must have a thermal conductivity function if coupling to temperature.");
    }
    if (isParamValid("thermal_conductivity") &&  _k_function) {
      mooseError("Ambiguous specifications for thermal conductivity."
                 "Both a constant and function were supplied.");
    }
  }

void MyHCMat::computeProperties()
{
  for (unsigned int qp(0); qp < _qrule->n_points(); ++qp)
  {
    Real qp_temperature = _temperature[qp];

    if (_k_function && _has_temperature)
    {
      Point p;
      _k[qp] = _k_function->value(qp_temperature, p);
      _dk_dT[qp] = _k_function->timeDerivative(qp_temperature, p);
    }
    else
    {
      _k[qp] = _my_k;
      _dk_dT[qp] = 0.0;
    }
  }
}
