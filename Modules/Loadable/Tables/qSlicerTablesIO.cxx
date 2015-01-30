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
#include <QDebug>
#include <QFileInfo>

// SlicerQt includes
#include "qSlicerTablesIO.h"

// MRML includes
#include "vtkMRMLTableNode.h"
#include "vtkSlicerTablesLogic.h"

// VTK includes
#include <vtkNew.h>
#include <vtkSmartPointer.h>

//-----------------------------------------------------------------------------
class qSlicerTablesIOPrivate
{
public:
  vtkSmartPointer<vtkSlicerTablesLogic> TablesLogic;
};

//-----------------------------------------------------------------------------
qSlicerTablesIO::qSlicerTablesIO(vtkSlicerTablesLogic* logic, QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerTablesIOPrivate)
{
  this->setTablesLogic(logic);
}

//-----------------------------------------------------------------------------
qSlicerTablesIO::~qSlicerTablesIO()
{
}

//-----------------------------------------------------------------------------
void qSlicerTablesIO::setTablesLogic(vtkSlicerTablesLogic* logic)
{
  Q_D(qSlicerTablesIO);
  d->TablesLogic = logic;
}

//-----------------------------------------------------------------------------
vtkSlicerTablesLogic* qSlicerTablesIO::tablesLogic()const
{
  Q_D(const qSlicerTablesIO);
  return d->TablesLogic;
}

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_Armatures

//-----------------------------------------------------------------------------
QString qSlicerTablesIO::description()const
{
  return "Table";
}

//-----------------------------------------------------------------------------
qSlicerIO::IOFileType qSlicerTablesIO::fileType()const
{
  return "TableFile";
}

//-----------------------------------------------------------------------------
QStringList qSlicerTablesIO::extensions()const
{
  return QStringList()
    << "CSV (*.csv)";
}

//-----------------------------------------------------------------------------
bool qSlicerTablesIO::load(const IOProperties& properties)
{
  Q_D(qSlicerTablesIO);
  Q_ASSERT(properties.contains("fileName"));
  QString fileName = properties["fileName"].toString();

  this->setLoadedNodes(QStringList());
  if (d->TablesLogic.GetPointer() == 0)
    {
    return false;
    }

  if (fileName.endsWith(".csv"))
    {
    vtkMRMLTableNode* tableNode =
      d->TablesLogic->AddTableNodeFromCSV(fileName.toLatin1());
    if (!tableNode)
      {
      return false;
      }

    this->setLoadedNodes(QStringList(tableNode->GetID()));
    return true;
    }

  return false;
}
