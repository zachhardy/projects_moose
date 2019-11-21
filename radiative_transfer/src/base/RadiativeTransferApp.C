#include "RadiativeTransferApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
RadiativeTransferApp::validParams()
{
  InputParameters params = MooseApp::validParams();
  return params;
}

RadiativeTransferApp::RadiativeTransferApp(InputParameters parameters) : MooseApp(parameters)
{
  RadiativeTransferApp::registerAll(_factory, _action_factory, _syntax);
}

RadiativeTransferApp::~RadiativeTransferApp() {}

void
RadiativeTransferApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAll(f, af, s);
  Registry::registerObjectsTo(f, {"RadiativeTransferApp"});
  Registry::registerActionsTo(af, {"RadiativeTransferApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
RadiativeTransferApp::registerApps()
{
  registerApp(RadiativeTransferApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
RadiativeTransferApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  RadiativeTransferApp::registerAll(f, af, s);
}
extern "C" void
RadiativeTransferApp__registerApps()
{
  RadiativeTransferApp::registerApps();
}
