//* MyHCMat Material for NUEN 618 Homework 6
//* Author: Zachary Hardy

#pragma once

#include "Material.h"

class MyHCMat;
class Function;

class MyHCMat : public Material
{
public:
  static InputParameters validParams();
  MyHCMat(const InputParameters& parameters);

protected:
  virtual void computeProperties();

  const bool _has_temperature;
  const VariableValue& _temperature;

  const Real _my_k;

  // material properties
  MaterialProperty<Real>& _k;
  MaterialProperty<Real>& _dk_dT;
  const Function* _k_function;
};
