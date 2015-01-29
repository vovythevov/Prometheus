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

#ifndef __qSlicerTablesModule_h
#define __qSlicerTablesModule_h

// SlicerQt includes
#include "qSlicerLoadableModule.h"

#include "qSlicerTablesModuleExport.h"

class qSlicerTablesModulePrivate;

/// \ingroup Slicer_QtModules_Tables
class Q_SLICER_QTMODULES_TABLES_EXPORT qSlicerTablesModule :
  public qSlicerLoadableModule
{
  Q_OBJECT
  Q_INTERFACES(qSlicerLoadableModule);

public:

  typedef qSlicerLoadableModule Superclass;
  explicit qSlicerTablesModule(QObject *parent=0);
  virtual ~qSlicerTablesModule();

  qSlicerGetTitleMacro(QTMODULE_TITLE);
  
  /// Help to use the module
  virtual QString helpText()const;

  /// Return acknowledgements
  virtual QString acknowledgementText()const;

  /// Return the authors of the module
  virtual QStringList  contributors()const;

  /// Return a custom icon for the module
  virtual QIcon icon()const;

  /// Return the categories for the module
  virtual QStringList categories()const;

  /// Return the dependencies for the module
  virtual QStringList dependencies()const;

protected:

  /// Initialize the module. Register the volumes reader/writer
  virtual void setup();

  /// Create and return the widget representation associated to this module
  virtual qSlicerAbstractModuleRepresentation * createWidgetRepresentation();

  /// Create and return the logic associated to this module
  virtual vtkMRMLAbstractLogic* createLogic();

protected:
  QScopedPointer<qSlicerTablesModulePrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(qSlicerTablesModule);
  Q_DISABLE_COPY(qSlicerTablesModule);

};

#endif
