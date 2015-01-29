/*=========================================================================

  Program: VesselView

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

// Qt includes
#include <QtPlugin>

// Tables includes
#include "qSlicerTablesModule.h"

//-----------------------------------------------------------------------------
Q_EXPORT_PLUGIN2(qSlicerTablesModule, qSlicerTablesModule);

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_Tables
class qSlicerTablesModulePrivate
{
public:
  qSlicerTablesModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerTablesModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerTablesModulePrivate::qSlicerTablesModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerTablesModule methods

//-----------------------------------------------------------------------------
qSlicerTablesModule::qSlicerTablesModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerTablesModulePrivate)
{
}

//-----------------------------------------------------------------------------
QStringList qSlicerTablesModule::categories()const
{
  return QStringList() << "";
}

//-----------------------------------------------------------------------------
qSlicerTablesModule::~qSlicerTablesModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerTablesModule::helpText()const
{
  QString help = "The Tables module allows you to handle table data.";
  return help;
}

//-----------------------------------------------------------------------------
QString qSlicerTablesModule::acknowledgementText()const
{
  QString acknowledgement = tr("TODO");
  return acknowledgement;
}

//-----------------------------------------------------------------------------
QStringList qSlicerTablesModule::contributors()const
{
  QStringList moduleContributors;
  moduleContributors
    << QString("Johan Andruejol (Kitware)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QStringList qSlicerTablesModule::dependencies()const
{
  return QStringList() << "Colors";
}

//-----------------------------------------------------------------------------
QIcon qSlicerTablesModule::icon()const
{
  return QIcon(":/Icons/Tables.png");
}

//-----------------------------------------------------------------------------
void qSlicerTablesModule::setup()
{
  this->Superclass::setup();
}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation * qSlicerTablesModule::createWidgetRepresentation()
{
  return NULL;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerTablesModule::createLogic()
{
  return NULL;
}
