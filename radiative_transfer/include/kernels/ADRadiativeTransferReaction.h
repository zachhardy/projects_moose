// Radiative Transfer AD Reaction
// Author: Zachary Hardy

#pragma once

#include "ADKernel.h"

template <ComputeStage>
class ADRadiativeTransferReaction;

declareADValidParams(ADRadiativeTransferReaction);

template<ComputeStage compute_stage>
class ADRadiativeTransferReaction : public ADKernel<compute_stage>
{
public:
  static InputParameters validParams();
  ADRadiativeTransferReaction(const InputParameters& parameters);

protected:
  virtual ADReal computeQpResidual() override;

  const bool _is_temperature;
  const ADMaterialProperty(Real)& _reactivity;
  const ADVariableValue& _v;
  usingKernelMembers;
};
