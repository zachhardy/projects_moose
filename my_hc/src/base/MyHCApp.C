#include "MyHCApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
MyHCApp::validParams()
{
  InputParameters params = MooseApp::validParams();
  return params;
}

MyHCApp::MyHCApp(InputParameters parameters) : MooseApp(parameters)
{
  MyHCApp::registerAll(_factory, _action_factory, _syntax);
}

MyHCApp::~MyHCApp() {}

void
MyHCApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAll(f, af, s);
  Registry::registerObjectsTo(f, {"MyHCApp"});
  Registry::registerActionsTo(af, {"MyHCApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
MyHCApp::registerApps()
{
  registerApp(MyHCApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
MyHCApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  MyHCApp::registerAll(f, af, s);
}
extern "C" void
MyHCApp__registerApps()
{
  MyHCApp::registerApps();
}
