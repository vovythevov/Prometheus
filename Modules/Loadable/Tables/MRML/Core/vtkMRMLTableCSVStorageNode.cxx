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
#include "vtkMRMLTableCSVStorageNode.h"

// VTK includes
#include <vtkDelimitedTextReader.h>
#include <vtkDelimitedTextWriter.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>
#include <vtkStringArray.h>
#include <vtksys/SystemTools.hxx>
#include <vtkTable.h>

// MRML includes
#include <vtkMRMLNode.h>
#include "vtkMRMLTableNode.h"

// STD includes
#include <sstream>
#include <locale>

//----------------------------------------------------------------------------
vtkMRMLNodeNewMacro(vtkMRMLTableCSVStorageNode);

//----------------------------------------------------------------------------
vtkMRMLTableCSVStorageNode::vtkMRMLTableCSVStorageNode()
{
}

//----------------------------------------------------------------------------
vtkMRMLTableCSVStorageNode::~vtkMRMLTableCSVStorageNode()
{
}

//----------------------------------------------------------------------------
void vtkMRMLTableCSVStorageNode::PrintSelf(ostream& os, vtkIndent indent)
{
  Superclass::PrintSelf(os,indent);
}

//----------------------------------------------------------------------------
bool vtkMRMLTableCSVStorageNode::CanReadInReferenceNode(vtkMRMLNode *refNode)
{
  return refNode->IsA("vtkMRMLTableNode");
}

//----------------------------------------------------------------------------
int vtkMRMLTableCSVStorageNode::ReadDataInternal(vtkMRMLNode *refNode)
{
  vtkMRMLTableNode* tableNode = vtkMRMLTableNode::SafeDownCast(refNode);
  if (!tableNode)
    {
    return 0;
    }

  std::string fullName = this->GetFullNameFromFileName();
  if (fullName == std::string(""))
    {
    vtkErrorMacro("ReadDataInternal: File name not specified");
    return 0;
    }

  // check that the file exists
  if (vtksys::SystemTools::FileExists(fullName.c_str()) == false)
    {
    vtkErrorMacro("ReadDataInternal: model file '"
      << fullName.c_str() << "' not found.");
    return 0;
    }
      
  // compute file prefix
  std::string name(fullName);
  std::string::size_type loc = name.find_last_of(".");
  if( loc == std::string::npos )
    {
    vtkErrorMacro("ReadDataInternal: no file extension specified: "
      << name.c_str());
    return 0;
    }
  std::string extension = name.substr(loc);

  vtkDebugMacro("ReadDataInternal: extension = " << extension.c_str());

  if (extension == std::string(".csv"))
    {
    vtkNew<vtkDelimitedTextReader> reader;
    reader->SetFileName(fullName.c_str());
    reader->DetectNumericColumnsOn();
    reader->Update();

    tableNode->GetTable()->DeepCopy(reader->GetOutput());
    }
  else
    {
    vtkDebugMacro("Cannot read armature file '" << name.c_str()
      << "' (extension = " << extension.c_str() << ")");
    return 0;
    }

  return 1;
}

//------------------------------------------------------------------------------
int vtkMRMLTableCSVStorageNode::WriteDataInternal(vtkMRMLNode* refNode)
{
  vtkMRMLTableNode* tableNode = vtkMRMLTableNode::SafeDownCast(refNode);
  if (!tableNode)
    {
    return 0;
    }

  std::string fullName = this->GetFullNameFromFileName();
  if (fullName == std::string(""))
    {
    vtkErrorMacro("ReadDataInternal: File name not specified");
    return 0;
    }

  // Write out the table to file
  vtkNew<vtkDelimitedTextWriter> writer;
  writer->SetFileName(fullName.c_str());

#if (VTK_MAJOR_VERSION < 6)
  writer->SetInput(tableNode->GetTable());
#else
  writer->SetInputData(tableNode->GetTable());
#endif

  return writer->Write();
}

//----------------------------------------------------------------------------
void vtkMRMLTableCSVStorageNode::InitializeSupportedReadFileTypes()
{
  this->SupportedReadFileTypes->InsertNextValue(
    "Comma Separated Value (.csv)");
}

//----------------------------------------------------------------------------
void vtkMRMLTableCSVStorageNode::InitializeSupportedWriteFileTypes()
{
  this->SupportedWriteFileTypes->Reset();
  this->SupportedWriteFileTypes->SetNumberOfTuples(0);
}

//----------------------------------------------------------------------------
const char* vtkMRMLTableCSVStorageNode::GetDefaultWriteFileExtension()
{
  return "csv";
}

