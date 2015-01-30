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

// .NAME vtkSlicerTablesLogic -
// Interface with tables methods and provides additionnal support
// .SECTION Description
// The table logic is in charge of interfacing with the tables nodes and
// is used for convience methods on tube objects.

#ifndef __vtkSlicerTablesLogic_h
#define __vtkSlicerTablesLogic_h

#include <vtkSlicerModuleLogic.h>

#include "vtkSlicerTablesLogic.h"
#include "vtkSlicerTablesModuleLogicExport.h"

class vtkMRMLTableNode;

class VTK_SLICER_TABLES_MODULE_LOGIC_EXPORT vtkSlicerTablesLogic
 : public vtkSlicerModuleLogic
{
public:
  static vtkSlicerTablesLogic *New( void );
  vtkTypeMacro(vtkSlicerTablesLogic, vtkSlicerModuleLogic);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Create a table node from a filename
  vtkMRMLTableNode* AddTableNodeFromCSV(const char *fileName);

protected:
  vtkSlicerTablesLogic( void );
  ~vtkSlicerTablesLogic( void );
  vtkSlicerTablesLogic(const vtkSlicerTablesLogic&);
  void operator=(const vtkSlicerTablesLogic&);

}; // End class vtkSlicerTablesLogic

#endif // End !defined(__vtkSlicerTablesLogic_h)
