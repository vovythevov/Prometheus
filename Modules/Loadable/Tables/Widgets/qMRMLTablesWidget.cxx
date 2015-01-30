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

// QT includes
#include <QDebug>

// SlicerQT includes
#include "qMRMLTablesWidget.h"
#include "Ui_qMRMLTablesWidget.h"

// MRML includes
#include "vtkMRMLScene.h"
#include <vtkMRMLTableNode.h>

// VTK includes
#include <vtkTable.h>

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_Volumes
class qMRMLTablesWidgetPrivate : public Ui_qMRMLTablesWidget
{
  Q_DECLARE_PUBLIC(qMRMLTablesWidget);

protected:
  qMRMLTablesWidget* const q_ptr;

public:
  qMRMLTablesWidgetPrivate(qMRMLTablesWidget& object);
  void init();
  void populateWidget();
  void clearWidget();

  vtkMRMLTableNode* TableNode;
};

// --------------------------------------------------------------------------
qMRMLTablesWidgetPrivate::qMRMLTablesWidgetPrivate(
  qMRMLTablesWidget& object)
  : q_ptr(&object)
{
  this->TableNode = 0;
}

// --------------------------------------------------------------------------
void qMRMLTablesWidgetPrivate::init()
{
  Q_Q(qMRMLTablesWidget);
  this->setupUi(q);
}

// --------------------------------------------------------------------------
void qMRMLTablesWidgetPrivate::clearWidget()
{
  Q_Q(qMRMLTablesWidget);
  this->tableWidget->clear();
}

// --------------------------------------------------------------------------
void qMRMLTablesWidgetPrivate::populateWidget()
{
  Q_Q(qMRMLTablesWidget);

  vtkTable* table = this->TableNode ? NULL : this->TableNode->GetTable();
  if (!table)
    {
    this->clearWidget();
    }

  this->tableWidget->setRowCount(table->GetNumberOfRows());
  this->tableWidget->setColumnCount(table->GetNumberOfColumns());
  for (int j = 0; j < table->GetNumberOfColumns(); ++j)
    {
    QTableWidgetItem* header = this->tableWidget->horizontalHeaderItem(j);
    if (!header)
      {
      header = new QTableWidgetItem;
      this->tableWidget->setHorizontalHeaderItem(j, header);
      }
    header->setText(table->GetColumnName(j));

    for (int i = 0; i < table->GetNumberOfRows(); ++i)
      {
      QTableWidgetItem* item = this->tableWidget->item(i, j);
      if (!item)
        {
        item = new QTableWidgetItem;
        this->tableWidget->setItem(i, j, item);
        }
      QVariant data(table->GetValue(i,j).ToString().c_str());
      item->setData(Qt::DisplayRole, data);
      }
    }
}

// --------------------------------------------------------------------------
// qMRMLTablesWidget
// --------------------------------------------------------------------------
qMRMLTablesWidget::qMRMLTablesWidget(QWidget* parentWidget)
  : Superclass(parentWidget)
  , d_ptr(new qMRMLTablesWidgetPrivate(*this))
{
  Q_D(qMRMLTablesWidget);
  d->init();
}

// --------------------------------------------------------------------------
qMRMLTablesWidget::~qMRMLTablesWidget()
{
}

// --------------------------------------------------------------------------
vtkMRMLTableNode* qMRMLTablesWidget::tableNode() const
{
  Q_D(const qMRMLTablesWidget);
  return d->TableNode;
}

// --------------------------------------------------------------------------
QString qMRMLTablesWidget::tableNodeID() const
{
  return this->tableNode() ? this->tableNode()->GetID() : "";
}

// --------------------------------------------------------------------------
void qMRMLTablesWidget::setTableNode(vtkMRMLNode* node)
{
  this->setTableNode(vtkMRMLTableNode::SafeDownCast(node));
}

// --------------------------------------------------------------------------
void qMRMLTablesWidget::setTableNode(vtkMRMLTableNode* tableNode)
{
  Q_D(qMRMLTablesWidget);
  if (d->TableNode == tableNode)
    {
    return;
    }
  d->TableNode = tableNode;
  this->qvtkReconnect(d->TableNode, vtkCommand::ModifiedEvent,
    this, SLOT(updateWidgetFromMRML()));
  this->updateWidgetFromMRML();

  emit this->tableNodeChanged(this->tableNode());
  emit this->tableNodeIDChanged(this->tableNodeID());
}

// --------------------------------------------------------------------------
void qMRMLTablesWidget::setTableNodeID(QString id)
{
  if (!this->mrmlScene())
    {
    qCritical() << "No mrml scene !";
    }

  this->setTableNode(this->mrmlScene()->GetNodeByID(id.toAscii()));
}

// --------------------------------------------------------------------------
void qMRMLTablesWidget::updateWidgetFromMRML()
{
  Q_D(qMRMLTablesWidget);
  d->populateWidget();
}
