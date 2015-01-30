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

#ifndef __vtkMRMLTableCSVStorageNode_h
#define __vtkMRMLTableCSVStorageNode_h

// Armatures includes
#include <vtkMRMLStorageNode.h>
#include "vtkSlicerTablesModuleMRMLCoreExport.h"

/// \brief Loads CSV files
///
class VTK_SLICER_TABLES_MRML_CORE_EXPORT vtkMRMLTableCSVStorageNode
  : public vtkMRMLStorageNode
{
public:
  static vtkMRMLTableCSVStorageNode *New();
  vtkTypeMacro(vtkMRMLTableCSVStorageNode, vtkMRMLStorageNode);
  void PrintSelf(ostream& os, vtkIndent indent);

  virtual vtkMRMLNode* CreateNodeInstance();

  ///
  /// Get node XML tag name (like Storage, Model)
  virtual const char* GetNodeTagName()  {return "TableCSVStorage";};

  /// Return a default file extension for writting
  virtual const char* GetDefaultWriteFileExtension();

  /// Return true if the reference node can be read in
  virtual bool CanReadInReferenceNode(vtkMRMLNode *refNode);

protected:
  vtkMRMLTableCSVStorageNode();
  ~vtkMRMLTableCSVStorageNode();
  vtkMRMLTableCSVStorageNode(const vtkMRMLTableCSVStorageNode&);
  void operator=(const vtkMRMLTableCSVStorageNode&);

  /// Initialize all the supported read file types
  virtual void InitializeSupportedReadFileTypes();

  /// Initialize all the supported write file types
  virtual void InitializeSupportedWriteFileTypes();

  /// Read data and set it in the referenced node
  virtual int ReadDataInternal(vtkMRMLNode *refNode);

  /// Write data from a  referenced node
  virtual int WriteDataInternal(vtkMRMLNode *refNode);
};
#endif
