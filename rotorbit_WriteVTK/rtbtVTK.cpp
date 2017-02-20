#include "rtbtVTK.h"

c_VTK::c_VTK(int num_nodes, float *x, float *y, float *z, int num_cells, int node_per_cell, int **cellConnectivity, int varSize, float **varMatrix, int mpi_rank, int mpi_size){

//  Related to Points
    _num_nodes = num_nodes;
    _x = new float[_num_nodes];
    _y = new float[_num_nodes];
    _z = new float[_num_nodes];
    _x = x;
    _y = y;
    _z = z;
//  Related to Cells
    _num_cells = num_cells;
    _node_per_cell = node_per_cell;

    _cellConnectivity = new int *[_num_cells];
    for(int i =0; i<_num_cells; i++){
     _cellConnectivity[i] = new int [_node_per_cell];
    }
    _cellConnectivity = cellConnectivity;
//  Related to CellCenterData
    _varSize = varSize;
    _varName = new char*[_varSize];
    for(int i=0; i<_varSize;i++){
//      _varName[i]=varName[i];
    }

    _cellCenterData = new vtkSmartPointer<vtkDoubleArray>[_varSize];

//  Related to Variable Matrix
     _varMatrix = new float*[_varSize];
     for(int i=0; i<_varSize;i++){
       _varMatrix[i] = new float [_num_cells];
     }
     _varMatrix = varMatrix;

    _mpi_rank = mpi_rank;
    _mpi_size = mpi_size;

}

c_VTK::~c_VTK(){
  
    delete [] _x;
    _x = NULL;

    delete [] _y;
    _y = NULL;

    delete [] _z;
    _z = NULL;

    for(int i=0; i<_num_cells; i++){
        delete []  _cellConnectivity[i];
        _cellConnectivity[i] = NULL;
    }
    delete [] _cellConnectivity;
    _cellConnectivity = NULL;

    delete [] _varName;
    _varName = NULL;

    for(int i=0; i<_varSize; i++){
        delete []  _varMatrix[i];
        _varMatrix[i] = NULL;
    }
    delete [] _varMatrix;
    _varMatrix = NULL;


}

void c_VTK::createPoints(){

    _points = vtkSmartPointer<vtkPoints>::New();
    for(int i=0; i<_num_nodes; i++){
       _points->InsertNextPoint(_x[i], _y[i], _z[i]);
    }

    cout << "Within VTK points are created." << _num_nodes << '\n';

}

void c_VTK::createCells(){

//  Allocate Cells
    _voxel = new vtkSmartPointer<vtkVoxel>[_num_cells];
    for(int i=0; i<_num_cells; i++){
    _voxel[i] = vtkSmartPointer<vtkVoxel>::New();
    }

//    _cellConnectivity = new int *[_num_cells];
//    for(int i =0; i<_num_cells; i++){
//      _cellConnectivity[i] = new int [_node_per_cell];
//    }

    for(int i=0; i<_num_cells; i++){
      for(int j=0; j<_node_per_cell; j++){
        _voxel[i]->GetPointIds()->SetId(j, _cellConnectivity[i][j]);
      }
    }

    _cellArray = vtkSmartPointer<vtkCellArray>::New();
    for(int i=0; i<_num_cells; i++){
      _cellArray->InsertNextCell(_voxel[i]);
    }

}
void c_VTK::createCellCenterData(){

    for(int i=0; i<_varSize; i++){
      _cellCenterData[i] = vtkSmartPointer<vtkDoubleArray>::New();
    }

    _cellCenterData[0]->SetName("MPI_Rank");
    _cellCenterData[1]->SetName("Value");
    for(int i=0; i<_varSize; i++){
//      _cellCenterData[i]->SetName(_varName[i]);
      _cellCenterData[i]->SetNumberOfComponents(1);
      _cellCenterData[i]->SetNumberOfValues(_num_cells);
      for(int j=0; j<_num_cells; j++){
          _cellCenterData[i]->SetValue(j,_varMatrix[i][j]);
      }

    }

}

void c_VTK::createNodalData(){
}

void c_VTK::createGrid(){

    _unstructuredGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    _unstructuredGrid->SetPoints(_points);
    _unstructuredGrid->SetCells(VTK_VOXEL, _cellArray);
    for(int i=0; i<_varSize; i++){
      _unstructuredGrid->GetCellData()->AddArray(_cellCenterData[i]);
    }

}


const char* c_VTK::getIndividualFileName(){

    string f1, f2, f3, ff;
    const char *c_ff;

    f1 = "Voxel_";
    f2 = to_string(static_cast<long long>(_mpi_rank));
    f3 = ".vtu";
   
    ff = f1 + f2 +f3;
    c_ff = ff.c_str();
    return c_ff;

}

void c_VTK::writeFile(){

    _writer = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
    
    cout << "Within VTK I am proc " << _mpi_rank << '\n';

    const char *fileName = getIndividualFileName();
    cout << "Within2 VTK filename is " << fileName << '\n';
    _writer->SetFileName(fileName);

#if VTK_MAJOR_VERSION <= 5
  _writer->SetInput(_unstructuredGrid);
#else
  _writer->SetInputData(_unstructuredGrid);
#endif
  _writer->Write();

}

void c_VTK::parallelWriteFile(){
  
  if(_mpi_rank==0){
    _pwriter = vtkSmartPointer<vtkXMLPUnstructuredGridWriter>::New();

    _pwriter->SetFileName("Voxel.pvtu");
    _pwriter->SetNumberOfPieces(_mpi_size);
#if VTK_MAJOR_VERSION <= 5
    _pwriter->SetInput(_unstructuredGrid);
#else
    _pwriter->SetInputData(_unstructuredGrid);
#endif
    _pwriter->Write();
  }


}

void c_VTK::fileCreation(){

    createPoints();
    createCells();
    createCellCenterData();
    createGrid();
    writeFile();
    parallelWriteFile();

}
