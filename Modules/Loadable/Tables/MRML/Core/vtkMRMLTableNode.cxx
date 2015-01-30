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

// MRML includes
#include "vtkMRMLTableNode.h"

// VTK includes
#include <vtkCallbackCommand.h>
#include <vtkObjectFactory.h>
#include <vtkTable.h>

//----------------------------------------------------------------------------
static void MRMLTableNodeCallback(vtkObject* vtkNotUsed(caller),
                                 long unsigned int eventId,
                                 void* clientData,
                                 void* vtkNotUsed(callData))
{
  if (eventId == vtkCommand::ModifiedEvent)
    {
    vtkMRMLTableNode* node = reinterpret_cast<vtkMRMLTableNode*>(clientData);
    if (node)
      {
      node->Modified();
      }
    }
}

//----------------------------------------------------------------------------
vtkMRMLNodeNewMacro(vtkMRMLTableNode);

//----------------------------------------------------------------------------
vtkMRMLTableNode::vtkMRMLTableNode()
{
  this->Table = vtkTable::New();

  this->Callback = vtkCallbackCommand::New();
  this->Callback->SetCallback(MRMLTableNodeCallback);
  this->Callback->SetClientData(this);
  this->Table->AddObserver(vtkCommand::ModifiedEvent, this->Callback);
}

//----------------------------------------------------------------------------
vtkMRMLTableNode::~vtkMRMLTableNode()
{
  this->Table->Delete();
  this->Callback->Delete();
}

//----------------------------------------------------------------------------
const char* vtkMRMLTableNode::GetNodeTagName()
{
  return "Table";
}

//----------------------------------------------------------------------------
// Copy the node's attributes to this object.
// Does NOT copy: ID, FilePrefix, Name, ID
void vtkMRMLTableNode::Copy(vtkMRMLNode *anode)
{
  int disabledModify = this->StartModify();

  Superclass::Copy(anode);
  vtkMRMLTableNode *node = vtkMRMLTableNode::SafeDownCast(anode);
  if (!node)
    {
    return;
    }

  this->Table->DeepCopy(node->GetTable());

  this->EndModify(disabledModify);

}

//----------------------------------------------------------------------------
void vtkMRMLTableNode::PrintSelf(ostream& os, vtkIndent indent)
{
  Superclass::PrintSelf(os,indent);
  this->Table->PrintSelf(os, indent);
}
