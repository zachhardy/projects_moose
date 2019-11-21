//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "RadiativeTransferTestApp.h"
#include "RadiativeTransferApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

InputParameters
RadiativeTransferTestApp::validParams()
{
  InputParameters params = RadiativeTransferApp::validParams();
  return params;
}

RadiativeTransferTestApp::RadiativeTransferTestApp(InputParameters parameters) : MooseApp(parameters)
{
  RadiativeTransferTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

RadiativeTransferTestApp::~RadiativeTransferTestApp() {}

void
RadiativeTransferTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  RadiativeTransferApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"RadiativeTransferTestApp"});
    Registry::registerActionsTo(af, {"RadiativeTransferTestApp"});
  }
}

void
RadiativeTransferTestApp::registerApps()
{
  registerApp(RadiativeTransferApp);
  registerApp(RadiativeTransferTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
RadiativeTransferTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  RadiativeTransferTestApp::registerAll(f, af, s);
}
extern "C" void
RadiativeTransferTestApp__registerApps()
{
  RadiativeTransferTestApp::registerApps();
}
