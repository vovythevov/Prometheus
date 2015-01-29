/*=========================================================================

Library:   VesselView

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

#ifndef __vtkMRMLTableNode_h
#define __vtkMRMLTableNode_h

// MRML includes
#include <vtkMRMLStorableNode.h>
#include "vtkSlicerTablesModuleMRMLCoreExport.h"

// VTK includes
class vtkTable;
class vtkCallbackCommand;

/// \brief Node that contains a reference to a vtkTable
///
///
class VTK_SLICER_TABLES_MRML_CORE_EXPORT vtkMRMLTableNode :
  public vtkMRMLStorableNode
{
public:
  vtkTypeMacro(vtkMRMLTableNode,vtkMRMLStorableNode);
  void PrintSelf(ostream& os, vtkIndent indent);

  //--------------------------------------------------------------------------
  /// MRMLNode methods
  //--------------------------------------------------------------------------

  virtual vtkMRMLNode* CreateNodeInstance();

  virtual const char* GetNodeTagName();

  ///
  /// Copy the node's attributes to this object
  virtual void Copy(vtkMRMLNode *node);

  ///
  vtkGetObjectMacro(Table, vtkTable);

 protected:
  vtkMRMLTableNode();
  ~vtkMRMLTableNode();
  vtkMRMLTableNode(const vtkMRMLTableNode&);
  void operator=(const vtkMRMLTableNode&);

  vtkTable* Table;
  vtkCallbackCommand* Callback;
};

#endif
