// Radiative Transfer Material
// Author: Zachary Hardy

#include "RadiativeTransferMaterial.h"
#include "libmesh/quadrature.h"
#include <cmath>

registerMooseObject("RadiativeTransferApp", RadiativeTransferMaterial);

InputParameters RadiativeTransferMaterial::validParams()
{
  InputParameters params = Material::validParams();
  params.addRequiredParam<Real>("atomic_mass", "Material atomic mass.");
  params.addRequiredCoupledVar("temperature", "Coupled temperature");
  params.addRequiredCoupledVar("radiation", "Coupled radiation energy");
  return params;
}

RadiativeTransferMaterial::RadiativeTransferMaterial(const InputParameters& parameters)
  : Material(parameters),
    _temperature(coupledValue("temperature")),
    _radiation(coupledValue("radiation")),
    _grad_radiation(coupledGradient("radiation")),

    _atomic_mass(getParam<Real>("atomic_mass")),

    _thermal_conductivity(declareProperty<Real>("thermal_conductivity")),
    _thermal_conductivity_dT(declareProperty<Real>("thermal_conductivity_dT")),
    _thermal_conductivity_dE(declareProperty<Real>("thermal_conductivity_dE")),

    _photon_diffusivity(declareProperty<Real>("photon_diffusivity")),
    _photon_diffusivity_dT(declareProperty<Real>("photon_diffusivity_dT")),
    _photon_diffusivity_dE(declareProperty<Real>("photon_diffusivity_dE")),

    _photon_absorptivity(declareProperty<Real>("photon_absorptivity")),
    _photon_absorptivity_dT(declareProperty<Real>("photon_absorptivity_dT")),
    _photon_absorptivity_dE(declareProperty<Real>("photon_absorptivity_dE"))
{
}

void RadiativeTransferMaterial::computeProperties()
{
  for (unsigned int qp(0); qp < _qrule->n_points(); ++qp)
  {
    Real qp_temperature = _temperature[qp];
    Real qp_radiation = _radiation[qp];
    Real qp_grad_radiation_norm = _grad_radiation[qp].norm();

    // const auto centroid = _current_elem->centroid();
    // int index = 2;
    // for (unsigned int i; i<_coupled_moose_vars.size(); ++i) {
    //   if (_coupled_moose_vars[i]->name() == "radition") {
    //     index = i;
    //   }
    // }
    // auto _myvar = _coupled_moose_vars[index];
    // auto centroid_radiation = _subproblem.getSystem(
    //   _myvar->name()).point_value(_myvar->number(),centroid,_current_elem);


    Real sigma_a = std::pow(_atomic_mass, 3) / std::pow(qp_temperature, 3);
    Real Dr = 1.0 / (3.0*sigma_a + qp_grad_radiation_norm/qp_radiation);

    _thermal_conductivity[qp] = 0.01 * std::pow(qp_temperature, 5/2);
    _thermal_conductivity_dT[qp] = 0.025 * std::pow(qp_temperature, 3/2);
    _thermal_conductivity_dE[qp] = 0.0;

    _photon_absorptivity[qp] = sigma_a;
    _photon_absorptivity_dT[qp] = -3.0 * sigma_a / qp_temperature;
    _photon_absorptivity_dE[qp] = 0.0;

    _photon_diffusivity[qp] = Dr;
    _photon_diffusivity_dT[qp] = 9.0 * sigma_a / qp_temperature * Dr * Dr;
    _photon_diffusivity_dE[qp] = 0.0;
  } // for qp
}
