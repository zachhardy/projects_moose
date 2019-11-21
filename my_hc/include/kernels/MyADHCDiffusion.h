//* MyADHCDiffusion Kernel for NUEN 618 Homework 6
//* Author: Zachary Hardy

#pragma once

#include "ADDiffusion.h"

template <ComputeStage>
class MyADHCDiffusion;

declareADValidParams(MyADHCDiffusion);

template <ComputeStage compute_stage>
class MyADHCDiffusion : public ADDiffusion<compute_stage>
{
public:
  static InputParameters validParams();
  MyADHCDiffusion(const InputParameters & parameters);

protected:
  virtual ADRealVectorValue precomputeQpResidual() override;

  const ADMaterialProperty(Real)& _thermal_conductivity;

  usingKernelGradMembers;
};
