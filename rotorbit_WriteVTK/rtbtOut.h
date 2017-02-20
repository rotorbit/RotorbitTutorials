#include <string>
//#include <string.h>
#include <iostream>
#include <fstream>

#include "mpi.h"
#include "rtbtVTK.h"

using namespace std;

void rtbtOut(const char*, char*, char*, char*,int,int,int,int, char**, char**, float**, float*, float*, float*, int**,  MPI_Info &, MPI_Comm &);

#ifndef output_h
#define output_h

class Output{
  /*!This is Output class

  */
   public:
/*! SetNames: smth stmh */
    void setNames(const char*, char*, char*,char*);
/*! SetVariables: smth stmh */
    void setVariables(int, char**, char**, float**);
    void setGeometryValues(int,int,int, float*, float*, float*, int**);   

    void parSetParameters(MPI_Info &,  MPI_Comm &);

    void createVTKObject();
    void parWriteVTK();
    void writePVTU();
//Constructor deconstrutor
    ~Output();  
  private:
    //methods
    void _2DMatrixto1DArray(int**);

    //data
    const char *_fileName;// = NULL; 
    char *_gridName;// = NULL; 
    char *_gridType;// = NULL;
    char *_topoType;// = NULL;

    float *_x, *_y, *_z;
    int *_cellConMatrix;
    int **_actualCellConMatrix;
    int _varSize;
    char **_varName;// = NULL;
    char **_varType;// = NULL;
    int *_varLength;
    float **_varMatrix;
    float **_temp_varMatrix;
    int _cellNum;
    int _nodePerCell;
    int _nodeNum;
    c_VTK *VTK;
//  Parallel related
    MPI_Info _info;
    MPI_Comm _comm;

}; 

#endif

