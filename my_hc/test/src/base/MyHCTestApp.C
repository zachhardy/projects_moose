//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "MyHCTestApp.h"
#include "MyHCApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

InputParameters
MyHCTestApp::validParams()
{
  InputParameters params = MyHCApp::validParams();
  return params;
}

MyHCTestApp::MyHCTestApp(InputParameters parameters) : MooseApp(parameters)
{
  MyHCTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

MyHCTestApp::~MyHCTestApp() {}

void
MyHCTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  MyHCApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"MyHCTestApp"});
    Registry::registerActionsTo(af, {"MyHCTestApp"});
  }
}

void
MyHCTestApp::registerApps()
{
  registerApp(MyHCApp);
  registerApp(MyHCTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
MyHCTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  MyHCTestApp::registerAll(f, af, s);
}
extern "C" void
MyHCTestApp__registerApps()
{
  MyHCTestApp::registerApps();
}
