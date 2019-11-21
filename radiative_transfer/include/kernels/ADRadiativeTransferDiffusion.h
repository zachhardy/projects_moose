// Radiative Transfer AD Diffusion
// Author: Zachary Hardy

#pragma once

#include "ADDiffusion.h"

template <ComputeStage>
class ADRadiativeTransferDiffusion;

declareADValidParams(ADRadiativeTransferDiffusion);

template<ComputeStage compute_stage>
class ADRadiativeTransferDiffusion : public ADDiffusion<compute_stage>
{
public:
  static InputParameters validParams();
  ADRadiativeTransferDiffusion(const InputParameters& parameters);

protected:
  virtual ADRealVectorValue precomputeQpResidual() override;

  const ADMaterialProperty(Real)& _diffusivity;
  const ADVariableGradient& _grad_v;
  usingKernelGradMembers;
};
