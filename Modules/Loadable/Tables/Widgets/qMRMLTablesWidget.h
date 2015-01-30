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
#ifndef __qMRMLTablesWidget_h
#define __qMRMLTablesWidget_h

// CTK includes
#include <ctkVTKObject.h>

// Slicer includes
#include <qMRMLWidget.h>

// Tables includes

#include "qSlicerTablesModuleWidgetsExport.h"

class vtkMRMLNode;
class vtkMRMLTableNode;
class qMRMLTablesWidgetPrivate;

/// \ingroup Slicer_QtModules_Volumes
class Q_SLICER_QTMODULES_TABLES_WIDGETS_EXPORT qMRMLTablesWidget
  : public qMRMLWidget
{
  Q_OBJECT
  QVTK_OBJECT
  Q_PROPERTY(QString tableNodeID READ tableNodeID WRITE setTableNodeID NOTIFY tableNodeIDChanged)

public:
  /// Constructors
  typedef qMRMLWidget Superclass;
  explicit qMRMLTablesWidget(QWidget* parent=0);
  virtual ~qMRMLTablesWidget();

  Q_INVOKABLE vtkMRMLTableNode* tableNode() const;
  QString tableNodeID() const;

public slots:
  void setTableNode(vtkMRMLNode* node);
  void setTableNode(vtkMRMLTableNode* node);
  void setTableNodeID(QString id);

signals:
  void tableNodeChanged(vtkMRMLTableNode* node);
  void tableNodeIDChanged(const QString& id);

protected slots:
  void updateWidgetFromMRML();

protected:
  QScopedPointer<qMRMLTablesWidgetPrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(qMRMLTablesWidget);
  Q_DISABLE_COPY(qMRMLTablesWidget);
};

#endif
