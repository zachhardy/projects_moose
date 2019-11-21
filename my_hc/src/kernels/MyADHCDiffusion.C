//* MyADHC Kernel for NUEN 618 Homework 6
//* Author: Zachary Hardy

#include "MyADHCDiffusion.h"

registerADMooseObject("MyHCApp", MyADHCDiffusion);

defineADLegacyParams(MyADHCDiffusion);

template <ComputeStage compute_stage>
InputParameters MyADHCDiffusion<compute_stage>::validParams()
{
  InputParameters params = ADDiffusion<compute_stage>::validParams();
  params.addParam<MaterialPropertyName>("thermal_conductivity",
                                        "thermal_conductivity",
                                        "the name of the thermal conductivity material property");
  return params;
}

template <ComputeStage compute_stage>
MyADHCDiffusion<compute_stage>::MyADHCDiffusion(const InputParameters & parameters)
  : ADDiffusion<compute_stage>(parameters),
    _thermal_conductivity(getADMaterialProperty<Real>("thermal_conductivity"))
{
}

template <ComputeStage compute_stage>
ADRealVectorValue MyADHCDiffusion<compute_stage>::precomputeQpResidual()
{
  return _thermal_conductivity[_qp] * ADDiffusion<compute_stage>::precomputeQpResidual();
}
