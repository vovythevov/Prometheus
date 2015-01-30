/*=========================================================================

Library:   TubeTK

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

#include "vtkSlicerTortuosityLogic.h"

// ITK includes
#include "itkVesselTubeSpatialObject.h"
#include "itktubeTortuositySpatialObjectFilter.h"

// Slicer includes
#include <vtkMRMLScene.h>

// VesselView includes
#include "vtkMRMLSpatialObjectsNode.h"
#include "vtkMRMLTableNode.h"
#include "vtkSlicerTablesLogic.h"

// VTK includes
#include "vtkObjectFactory.h"
#include "vtkDelimitedTextWriter.h"
#include "vtkDoubleArray.h"
#include "vtkIntArray.h"
#include "vtkMath.h"
#include "vtkNew.h"
#include "vtkPointData.h"
#include "vtkPolyData.h"
#include "vtkTable.h"

#include <math.h>

//------------------------------------------------------------------------------
vtkStandardNewMacro(vtkSlicerTortuosityLogic);

//------------------------------------------------------------------------------
vtkCxxSetObjectMacro(vtkSlicerTortuosityLogic, TablesLogic, vtkSlicerTablesLogic);

//------------------------------------------------------------------------------
vtkSlicerTortuosityLogic::vtkSlicerTortuosityLogic( void )
{
  this->FlagToArrayNames[DistanceMetric] = "DistanceMetric";
  this->FlagToArrayNames[InflectionCountMetric] = "InflectionCountMetric";
  this->FlagToArrayNames[InflectionPoints] = "InflectionPoints";
  this->FlagToArrayNames[SumOfAnglesMetric] = "SumOfAnglesMetric";
}

//------------------------------------------------------------------------------
vtkSlicerTortuosityLogic::~vtkSlicerTortuosityLogic( void )
{
}

//------------------------------------------------------------------------------
void vtkSlicerTortuosityLogic::PrintSelf(ostream& os, vtkIndent indent)
{
}

//------------------------------------------------------------------------------
bool vtkSlicerTortuosityLogic::UniqueMeasure(int flag)
{
  return flag == vtkSlicerTortuosityLogic::DistanceMetric ||
    flag == vtkSlicerTortuosityLogic::InflectionCountMetric ||
    flag == vtkSlicerTortuosityLogic::InflectionPoints ||
    flag == vtkSlicerTortuosityLogic::SumOfAnglesMetric;
}

//------------------------------------------------------------------------------
vtkDoubleArray* vtkSlicerTortuosityLogic
::GetDistanceMetricArray(vtkMRMLSpatialObjectsNode* node, int flag)
{
  return this->GetOrCreateArray(
    node, flag & vtkSlicerTortuosityLogic::DistanceMetric);
}

//------------------------------------------------------------------------------
vtkDoubleArray* vtkSlicerTortuosityLogic
::GetInflectionCountMetricArray(vtkMRMLSpatialObjectsNode* node, int flag)
{
  return this->GetOrCreateArray(
    node, flag & vtkSlicerTortuosityLogic::InflectionCountMetric);
}

//------------------------------------------------------------------------------
vtkDoubleArray* vtkSlicerTortuosityLogic
::GetInflectionPointsArray(vtkMRMLSpatialObjectsNode* node, int flag)
{
  return this->GetOrCreateArray(
    node, flag & vtkSlicerTortuosityLogic::InflectionPoints);
}

//------------------------------------------------------------------------------
vtkDoubleArray* vtkSlicerTortuosityLogic
::GetSumOfAnglesMetricArray(vtkMRMLSpatialObjectsNode* node, int flag)
{
  return this->GetOrCreateArray(
    node, flag & vtkSlicerTortuosityLogic::SumOfAnglesMetric);
}

//------------------------------------------------------------------------------
vtkDoubleArray* vtkSlicerTortuosityLogic
::GetOrCreateArray(vtkMRMLSpatialObjectsNode* node, int flag)
{
  if (!flag || !this->UniqueMeasure(flag))
    {
    return NULL;
    }

  std::string name = this->FlagToArrayNames[flag];
  vtkDoubleArray* metricArray =
    this->GetOrCreateArray<vtkDoubleArray>(node, name.c_str());
  if (!metricArray)
    {
    return NULL;
    }

  // If it's new, make it the correct size
  vtkDoubleArray* ids = this->GetArray<vtkDoubleArray>(node, "TubeIDs");
  assert(ids);
  if (metricArray->GetSize() != ids->GetSize());
    {
    metricArray->SetNumberOfValues(ids->GetSize());
    }
  return metricArray;
}

//------------------------------------------------------------------------------
template<typename T> T* vtkSlicerTortuosityLogic
::GetArray(vtkMRMLSpatialObjectsNode* node, const char* name)
{
  vtkPolyData* polydata = node->GetPolyData();
  if (!polydata)
    {
    return NULL;
    }
  vtkPointData* pointData = polydata->GetPointData();
  if (!pointData)
    {
    return NULL;
    }

  return T::SafeDownCast(pointData->GetArray(name));
}

//------------------------------------------------------------------------------
template<typename T> T* vtkSlicerTortuosityLogic
::GetOrCreateArray(vtkMRMLSpatialObjectsNode* node, const char* name)
{
  T* metricArray = this->GetArray<T>(node, name);
  if (!metricArray)
    {
    vtkPolyData* polydata = node->GetPolyData();
    if (!polydata)
      {
      return NULL;
      }
    vtkPointData* pointData = polydata->GetPointData();
    if (!pointData)
      {
      return NULL;
      }

    vtkNew<T> newMetricArray;
    newMetricArray->SetName(name);
    pointData->AddArray(newMetricArray.GetPointer());
    return newMetricArray.GetPointer();
    }
  return metricArray;
}

//------------------------------------------------------------------------------
bool vtkSlicerTortuosityLogic
::RunDistanceMetric(vtkMRMLSpatialObjectsNode* node)
{
  return this->RunMetrics(
    node, vtkSlicerTortuosityLogic::DistanceMetric);
}

//------------------------------------------------------------------------------
bool vtkSlicerTortuosityLogic
::RunInflectionCountMetric(vtkMRMLSpatialObjectsNode* node)
{
  return this->RunMetrics(
    node, vtkSlicerTortuosityLogic::InflectionCountMetric);
}

//------------------------------------------------------------------------------
bool vtkSlicerTortuosityLogic
::RunInflectionPoints(vtkMRMLSpatialObjectsNode* node)
{
  return this->RunMetrics(
    node, vtkSlicerTortuosityLogic::InflectionPoints);
}

//------------------------------------------------------------------------------
bool vtkSlicerTortuosityLogic
::RunSumOfAnglesMetric(vtkMRMLSpatialObjectsNode* node)
{
  return this->RunMetrics(
    node, vtkSlicerTortuosityLogic::SumOfAnglesMetric);
}

//------------------------------------------------------------------------------
bool vtkSlicerTortuosityLogic
::RunMetrics(vtkMRMLSpatialObjectsNode* node, int flag)
{
  if (!node)
    {
    return false;
    }

  // 1 - Get the metric arrays
  vtkDoubleArray* dm = this->GetDistanceMetricArray(node, flag);
  vtkDoubleArray* icm = this->GetInflectionCountMetricArray(node, flag);
  vtkDoubleArray* ip = this->GetInflectionPointsArray(node, flag);
  vtkDoubleArray* soam = this->GetSumOfAnglesMetricArray(node, flag);

  if (!dm && !icm && !ip && !soam)
    {
    std::cerr<<"Tortuosity flag mode unknown."<<std::endl;
    return false;
    }

  // Rewrite number of points array everytime
  vtkIntArray* nop = this->GetOrCreateArray<vtkIntArray>(node, "NumberOfPoints");

  // 2 - Fill the metric arrays
  typedef vtkMRMLSpatialObjectsNode::TubeNetType                    TubeNetType;
  typedef itk::VesselTubeSpatialObject<3>                           VesselTubeType;
  typedef itk::tube::TortuositySpatialObjectFilter<VesselTubeType>  FilterType;

  TubeNetType* spatialObject = node->GetSpatialObject();

  char childName[] = "Tube";
  TubeNetType::ChildrenListType* tubeList =
    spatialObject->GetChildren(spatialObject->GetMaximumDepth(), childName);

  size_t totalNumberOfPointsAdded = 0;
  for(TubeNetType::ChildrenListType::iterator tubeIt = tubeList->begin();
        tubeIt != tubeList->end(); ++tubeIt)
    {
    VesselTubeType* currTube =
      dynamic_cast<VesselTubeType*>((*tubeIt).GetPointer());
    if (!currTube)
      {
      continue;
      }

    if (currTube->GetNumberOfPoints() < 2)
      {
      std::cerr<<"Error, vessel #"<<currTube->GetId()
        <<" has less than 2 points !"<<std::endl
        <<"Skipping the vessel."<<std::endl;
      continue;
      }

    // Update filter
    FilterType::Pointer filter = FilterType::New();
    filter->SetMeasureFlag(flag);
    filter->SetInput(currTube);
    filter->Update();

    if (filter->GetOutput()->GetId() != currTube->GetId())
      {
      std::cerr<<"Error while running filter on tube."<<std::endl;
      return false;
      }

    // Fill the arrays
    size_t numberOfPoints = currTube->GetPoints().size();
    for(size_t filterIndex = 0, tubeIndex = totalNumberOfPointsAdded;
      filterIndex < numberOfPoints; ++filterIndex, ++tubeIndex)
      {
      if (dm)
        {
        dm->SetValue(tubeIndex, filter->GetDistanceMetric());
        }
      if (icm)
        {
        icm->SetValue(tubeIndex, filter->GetInflectionCountMetric());
        }
      if (soam)
        {
        soam->SetValue(tubeIndex, filter->GetSumOfAnglesMetric());
        }
      if (ip)
        {
        ip->SetValue(tubeIndex, filter->GetInflectionPointValue(filterIndex));
        }

      nop->InsertNextValue(numberOfPoints);
      }

    totalNumberOfPointsAdded += numberOfPoints;
    }

  return true;
}

//------------------------------------------------------------------------------
std::vector<std::string> vtkSlicerTortuosityLogic::GetNamesFromFlag(int flag)
{
  std::vector<std::string> names;
  for (int compareFlag = vtkSlicerTortuosityLogic::DistanceMetric;
    compareFlag <= vtkSlicerTortuosityLogic::SumOfAnglesMetric;
    compareFlag = compareFlag << 1)
    {
    if (flag & compareFlag)
      {
      names.push_back(this->FlagToArrayNames[compareFlag]);
      }
    }
  return names;
}

//------------------------------------------------------------------------------
vtkMRMLTableNode* vtkSlicerTortuosityLogic
::UpdateTableNodeFromMeasures(vtkMRMLSpatialObjectsNode* node,
                              vtkMRMLTableNode* tableNode,
                              int flag)
{
  if (!node)
    {
    return false;
    }

  if (!tableNode)
    {
    tableNode = vtkMRMLTableNode::SafeDownCast(
        this->GetMRMLScene()->AddNode(vtkMRMLTableNode::New()));
    }

  // Get the metric arrays
  std::vector<vtkDoubleArray*> metricArrays;
  std::vector<std::string> names = this->GetNamesFromFlag(flag);
  for (std::vector<std::string>::iterator it = names.begin();
    it != names.end(); ++it)
    {
    vtkDoubleArray* metricArray =
      this->GetArray<vtkDoubleArray>(node, it->c_str());
    if (metricArray)
      {
      metricArrays.push_back(metricArray);
      }
    }

  // Make sure we have everything we need for export
  if (metricArrays.size() <= 0)
    {
    std::cout<<"No array found for given flag: "<<flag<<std::endl;
    return tableNode;
    }

  vtkIntArray* numberOfPointsArray =
    this->GetArray<vtkIntArray>(node, "NumberOfPoints");
  if (!numberOfPointsArray)
    {
    std::cerr<<"Expected ''NumberOfPoints'' array on the node point data."
      <<std::endl<<"Cannot proceed."<<std::endl;
    return tableNode;
    }

  // Create  the table. Each column has only one value per vessel
  // instead of one value per each point of the vessel.
  int wasModifying = tableNode->StartModify();
  for (int j = 0; j < tableNode->GetTable()->GetNumberOfColumns(); ++j)
    {
    tableNode->GetTable()->RemoveColumn(j);
    }

  for(std::vector<vtkDoubleArray*>::iterator it = metricArrays.begin();
    it != metricArrays.end(); ++it)
    {
    vtkNew<vtkDoubleArray> newArray;
    newArray->SetName((*it)->GetName());

    for (int j = 0; j < numberOfPointsArray->GetNumberOfTuples(); j += numberOfPointsArray->GetValue(j))
      {
      newArray->InsertNextValue((*it)->GetValue(j));
      }

    tableNode->GetTable()->AddColumn(newArray.GetPointer());
    }
  this->EndModify(wasModifying);

  return tableNode;
}

//------------------------------------------------------------------------------
bool vtkSlicerTortuosityLogic
::SaveAsCSV(vtkMRMLSpatialObjectsNode* node, const char* filename, int flag)
{
  if (!node || !filename)
    {
    return false;
    }

  vtkMRMLTableNode* tableNode =
    this->UpdateTableNodeFromMeasures(node, NULL, flag);
  return this->GetTablesLogic()->SaveTableNodeToCSV(tableNode, filename);
}
