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

#include "vtkSlicerTablesLogic.h"

// Spatial object includes
#include "vtkMRMLTableNode.h"
#include "vtkMRMLTableCSVStorageNode.h"

// Slicer includes
#include <vtkMRMLScene.h>

// VTK includes
#include <vtkObjectFactory.h>
#include <vtkDelimitedTextReader.h>
#include <vtkNew.h>
#include <vtkTable.h>

//------------------------------------------------------------------------------
vtkStandardNewMacro(vtkSlicerTablesLogic);

//------------------------------------------------------------------------------
vtkSlicerTablesLogic::vtkSlicerTablesLogic( void )
{
}

//------------------------------------------------------------------------------
vtkSlicerTablesLogic::~vtkSlicerTablesLogic( void )
{
}

//------------------------------------------------------------------------------
void vtkSlicerTablesLogic::PrintSelf(ostream& os, vtkIndent indent)
{
}

//------------------------------------------------------------------------------
vtkMRMLTableNode* vtkSlicerTablesLogic::AddTableNodeFromCSV(const char* filename)
{
  if (!filename)
    {
    return NULL;
    }

  // make a storage node and fiducial node and set the file name
  vtkNew<vtkMRMLTableCSVStorageNode> storageNode;
  storageNode->SetFileName(filename);
  vtkNew<vtkMRMLTableNode> tableNode;

  // add the nodes to the scene and set up the observation on the storage node
  this->GetMRMLScene()->AddNode(storageNode.GetPointer());
  this->GetMRMLScene()->AddNode(tableNode.GetPointer());
  tableNode->SetAndObserveStorageNodeID(storageNode->GetID());

  // read the file
  storageNode->ReadData(tableNode.GetPointer());

  return tableNode.GetPointer();
}
