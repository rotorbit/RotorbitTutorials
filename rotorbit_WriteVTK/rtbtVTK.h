#include <iostream>
#include <string>

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkTetra.h>
#include <vtkVoxel.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkDataSetMapper.h>
#include <vtkActor.h>
#include <vtkXMLPUnstructuredGridWriter.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkUnstructuredGrid.h>
#include <vtkPointData.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkDoubleArray.h>

#include "mpi.h"

using namespace std;

class c_VTK{

public:
    int _num_nodes;
    int _num_cells;
    int _node_per_cell;
    int _varSize;
    char **_varName;
    float *_x;
    float *_y;
    float *_z;
    vtkSmartPointer<vtkPoints> _points;
    vtkSmartPointer<vtkVoxel> *_voxel; 
    vtkSmartPointer<vtkCellArray> _cellArray;
    vtkSmartPointer<vtkDoubleArray> *_cellCenterData;
    vtkSmartPointer<vtkUnstructuredGrid> _unstructuredGrid;
    vtkSmartPointer<vtkXMLUnstructuredGridWriter> _writer;
    vtkSmartPointer<vtkXMLPUnstructuredGridWriter> _pwriter;
    int **_cellConnectivity;

    float **_varMatrix;

    int _mpi_rank;
    int _mpi_size;
    
public:
    c_VTK(int num_nodes, float *x, float *y, float *z, int num_cells, int node_per_cell, int **cellConnectivity, int varSize, float **varMatrix, int mpi_rank, int mpi_size);
    ~c_VTK();
    void createPoints();
    void createCells();
    void createCellCenterData();
    void createNodalData();
    void createGrid();
    void writeFile();
      const char* getIndividualFileName();
    void parallelWriteFile();

    void fileCreation();

};
