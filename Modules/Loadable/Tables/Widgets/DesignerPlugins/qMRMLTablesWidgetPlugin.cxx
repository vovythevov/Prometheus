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

#include "qMRMLTablesWidgetPlugin.h"
#include "qMRMLTablesWidget.h"

//------------------------------------------------------------------------------
qMRMLTablesWidgetPlugin::qMRMLTablesWidgetPlugin(QObject *_parent)
  : QObject(_parent)
{

}

//------------------------------------------------------------------------------
QWidget *qMRMLTablesWidgetPlugin::createWidget(QWidget *_parent)
{
  qMRMLTablesWidget* _widget 
    = new qMRMLTablesWidget(_parent);
  return _widget;
}

//------------------------------------------------------------------------------
QString qMRMLTablesWidgetPlugin::domXml() const
{
  return "<widget class=\"qMRMLTablesWidget\" \
          name=\"MRMLTablesWidget\">\n"
          "</widget>\n";
}

//------------------------------------------------------------------------------
QString qMRMLTablesWidgetPlugin::includeFile() const
{
  return "qMRMLTablesWidget.h";
}

//------------------------------------------------------------------------------
bool qMRMLTablesWidgetPlugin::isContainer() const
{
  return false;
}

//------------------------------------------------------------------------------
QString qMRMLTablesWidgetPlugin::name() const
{
  return "qMRMLTablesWidget";
}
