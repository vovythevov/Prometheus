/*=========================================================================

  Program: Bender

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

#ifndef __qSlicerTablesIO_h
#define __qSlicerTablesIO_h

// SlicerQt includes
#include "qSlicerFileReader.h"
class qSlicerTablesIOPrivate;
class vtkSlicerTablesLogic;

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_Tables
class qSlicerTablesIO : public qSlicerFileReader
{
  Q_OBJECT
public:
  typedef qSlicerFileReader Superclass;
  qSlicerTablesIO(vtkSlicerTablesLogic* logic = 0, QObject* parent = 0);
  virtual ~qSlicerTablesIO();

  void setTablesLogic(vtkSlicerTablesLogic* logic);
  vtkSlicerTablesLogic* tablesLogic()const;

  virtual QString description()const;
  virtual IOFileType fileType()const;
  virtual QStringList extensions()const;

  virtual bool load(const IOProperties& properties);

protected:
  QScopedPointer<qSlicerTablesIOPrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(qSlicerTablesIO);
  Q_DISABLE_COPY(qSlicerTablesIO);
};

#endif
