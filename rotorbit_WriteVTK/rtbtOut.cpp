#include "rtbtOut.h"

using namespace std;

void rtbtOut(const char* fileName, char* gridName, char* gridType, char* topoName,int cellNum, int nodePerCell, int nodeNum, int varSize, char** varName, char** varType, float** varMatrix, float *x, float *y, float *z, int** cellConMatrix,  MPI_Info &info,  MPI_Comm &comm){

Output *output1=NULL;
output1 = new Output();

////// set all the input parameters correctly
output1->setNames(fileName,gridName, gridType,topoName);
output1->setGeometryValues(cellNum,nodePerCell,nodeNum,x, y, z, cellConMatrix);
output1->setVariables(varSize, varName, varType, varMatrix);
output1->parSetParameters(info, comm);
output1->createVTKObject();

delete output1;

}

Output::~Output(){

  delete [] _varMatrix;
  delete [] _cellConMatrix;

}

void Output::parSetParameters(MPI_Info &info,  MPI_Comm &comm){

     _info = info;
     _comm = comm;

}

void Output::setNames(const char *fileName, char *gridName, char *gridType, char *topoType){

  _fileName=fileName;
  _gridName=gridName;
  _gridType=gridType;
  _topoType=topoType;
}

void Output::setVariables( int varSize, char** varName, char** varType, float** varMatrix){

  _varSize=varSize;
    _temp_varMatrix = varMatrix; 

}

void Output::_2DMatrixto1DArray(int **cellConMatrix){

   _cellConMatrix = new int [_cellNum*_nodePerCell];

   for(int i =0; i<_cellNum; i++){
     for(int j =0; j<_nodePerCell; j++){
       _cellConMatrix[i*_nodePerCell+j] = cellConMatrix[i][j];
     }
   }

}

void Output::setGeometryValues(int cellNum, int nodePerCell, int nodeNum, float *x, float *y, float *z, int **cellConMatrix){
  _cellNum=cellNum;
  _nodePerCell=nodePerCell;
  _nodeNum=nodeNum;
  _x = x;
  _y = y;
  _z = z;

  _2DMatrixto1DArray(cellConMatrix);
  _actualCellConMatrix = cellConMatrix ;

}

void Output::createVTKObject(){

    int local_mpi_rank;
    int local_mpi_size;
    MPI_Comm_rank(_comm, &local_mpi_rank);
    MPI_Comm_size(_comm, &local_mpi_size);
    VTK = new c_VTK(_nodeNum, _x, _y, _z, _cellNum, _nodePerCell, _actualCellConMatrix, _varSize, _temp_varMatrix, local_mpi_rank, local_mpi_size);
    VTK->fileCreation();

}

