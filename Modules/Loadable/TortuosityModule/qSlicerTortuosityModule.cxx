/*=========================================================================

Library:   TubeTK

Copyright 2010 Kitware Inc. 28 Corporate Drive,
Clifton Park, NY, 12065, USA.

All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

=========================================================================*/

// Qt includes
#include <QtPlugin>

// SlicerQt includes
#include <qSlicerCoreApplication.h>
#include <qSlicerIOManager.h>
#include <qSlicerModuleManager.h>
#include <qSlicerNodeWriter.h>

// Tortuosity Logic includes
#include "vtkSlicerTablesLogic.h"
#include "vtkSlicerTortuosityLogic.h"

// Tortuosity QTModule includes
#include "qSlicerTortuosityModule.h"
#include "qSlicerTortuosityModuleWidget.h"

//------------------------------------------------------------------------------
Q_EXPORT_PLUGIN2(qSlicerTortuosityModule, qSlicerTortuosityModule);

//------------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_Tortuosity
class qSlicerTortuosityModulePrivate
{};

//------------------------------------------------------------------------------
qSlicerTortuosityModule::qSlicerTortuosityModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerTortuosityModulePrivate)
{}

//------------------------------------------------------------------------------
qSlicerTortuosityModule::~qSlicerTortuosityModule()
{}

//------------------------------------------------------------------------------
QString qSlicerTortuosityModule::helpText() const
{
  QString help = QString("Run tortuosity metrics on spatial objects.");

  return help;
}

//------------------------------------------------------------------------------
QString qSlicerTortuosityModule::acknowledgementText() const
{
  QString acknowledgement = QString("");

  return acknowledgement;
}

//------------------------------------------------------------------------------
QStringList qSlicerTortuosityModule::contributors() const
{
  QStringList moduleContributors;
  moduleContributors << QString("Johan Andruejol (Kitware)");

  return moduleContributors;
}

//------------------------------------------------------------------------------
QIcon qSlicerTortuosityModule::icon()const
{
  return QIcon(":/Icons/Tortuosity.png");
}

//------------------------------------------------------------------------------
QStringList qSlicerTortuosityModule::categories() const
{
  return QStringList() << "TubeTK";
}

//------------------------------------------------------------------------------
QStringList qSlicerTortuosityModule::dependencies() const
{
  QStringList moduleDependencies;
  moduleDependencies << "SpatialObjects" << "Tables";

  return moduleDependencies;
}

//------------------------------------------------------------------------------
void qSlicerTortuosityModule::setup()
{
  this->Superclass::setup();

  vtkSlicerTortuosityLogic* tortuosityLogic =
    vtkSlicerTortuosityLogic::SafeDownCast(this->logic());
  qSlicerAbstractCoreModule* tablesModule =
    qSlicerCoreApplication::application()->moduleManager()->module("Tables");
  if (tablesModule)
    {
    vtkSlicerTablesLogic* tablesLogic =
      vtkSlicerTablesLogic::SafeDownCast(tablesModule->logic());
    tortuosityLogic->SetTablesLogic(tablesLogic);
    }
}

//------------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation*
qSlicerTortuosityModule::createWidgetRepresentation()
{
  return new qSlicerTortuosityModuleWidget;
}

//------------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerTortuosityModule::createLogic()
{
  return vtkSlicerTortuosityLogic::New();
}
