#include "rtbtOut.h"

using namespace std;
int main(int argc, char **argv){
//int main(){

  int mpi_size, mpi_rank;
  MPI_Comm comm  = MPI_COMM_WORLD;
  MPI_Info info  = MPI_INFO_NULL;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(comm, &mpi_size);
  MPI_Comm_rank(comm, &mpi_rank);

  const char *fileName = "rotorbit" ;
  char *gridName = "Unstructered" ;
  char *gridType = "Uniform" ;
  char *topoType = "Hexahedron" ;
  int cellNum = 2;
  int nodePerCell = 8;//Hexahedron
  int nodeNum = 16;
  int varSize = 2;

  float passed_x[16], passed_y[16],passed_z[16];
  float *cellData= NULL;
  float *cellData2= NULL;
  if(mpi_rank == 0){
    passed_x[0] = 0; 
    passed_x[1] = 0; 
    passed_x[2] = 0; 
    passed_x[3] = 0; 
    passed_x[4] = 1; 
    passed_x[5] = 1; 
    passed_x[6] = 1; 
    passed_x[7] = 1; 
    passed_x[8] = 0; 
    passed_x[9] = 0; 
    passed_x[10] = 0; 
    passed_x[11] = 0; 
    passed_x[12] = 1; 
    passed_x[13] = 1; 
    passed_x[14] = 1; 
    passed_x[15] = 1; 
    passed_y[0] = 0; 
    passed_y[1] = 0; 
    passed_y[2] = 1; 
    passed_y[3] = 1; 
    passed_y[4] = 0; 
    passed_y[5] = 0; 
    passed_y[6] = 1; 
    passed_y[7] = 1; 
    passed_y[8] = 0; 
    passed_y[9] = 0; 
    passed_y[10] = 1; 
    passed_y[11] = 1; 
    passed_y[12] = 0; 
    passed_y[13] = 0; 
    passed_y[14] = 1; 
    passed_y[15] = 1; 
    passed_z[0] = 0; 
    passed_z[1] = 1; 
    passed_z[2] = 0; 
    passed_z[3] = 1; 
    passed_z[4] = 0; 
    passed_z[5] = 1; 
    passed_z[6] = 0; 
    passed_z[7] = 1; 
    passed_z[8] = -1; 
    passed_z[9] = 0; 
    passed_z[10] = -1; 
    passed_z[11] = 0; 
    passed_z[12] = -1; 
    passed_z[13] = 0; 
    passed_z[14] = -1; 
    passed_z[15] = 0; 
    cellData = new float[cellNum];
    cellData2 = new float[cellNum];
    cellData[0] = mpi_rank;
    cellData[1] = mpi_rank;
    cellData2[0] = 0;
    cellData2[1] = 1;
  }
  if(mpi_rank == 1){
    passed_x[0] = 0; 
    passed_x[1] = 0; 
    passed_x[2] = 0; 
    passed_x[3] = 0; 
    passed_x[4] = 1; 
    passed_x[5] = 1; 
    passed_x[6] = 1; 
    passed_x[7] = 1; 
    passed_x[8] = 0; 
    passed_x[9] = 0; 
    passed_x[10] = 0; 
    passed_x[11] = 0; 
    passed_x[12] = 1; 
    passed_x[13] = 1; 
    passed_x[14] = 1; 
    passed_x[15] = 1; 
    passed_y[0] = 0; 
    passed_y[1] = 0; 
    passed_y[2] = 1; 
    passed_y[3] = 1; 
    passed_y[4] = 0; 
    passed_y[5] = 0; 
    passed_y[6] = 1; 
    passed_y[7] = 1; 
    passed_y[8] = 0; 
    passed_y[9] = 0; 
    passed_y[10] = 1; 
    passed_y[11] = 1; 
    passed_y[12] = 0; 
    passed_y[13] = 0; 
    passed_y[14] = 1; 
    passed_y[15] = 1; 
    passed_z[0] = 1; 
    passed_z[1] = 2; 
    passed_z[2] = 1; 
    passed_z[3] = 2; 
    passed_z[4] = 1; 
    passed_z[5] = 2; 
    passed_z[6] = 1; 
    passed_z[7] = 2; 
    passed_z[8] = 2; 
    passed_z[9] = 3; 
    passed_z[10] = 2; 
    passed_z[11] = 3; 
    passed_z[12] = 2; 
    passed_z[13] = 3; 
    passed_z[14] = 2; 
    passed_z[15] = 3; 
    cellData = new float[cellNum];
    cellData2 = new float[cellNum];
    cellData[0] = mpi_rank;
    cellData[1] = mpi_rank;
    cellData2[0] = 2;
    cellData2[1] = 3;
  }
  if(mpi_rank == 2){
    passed_x[0] = 1; 
    passed_x[1] = 1; 
    passed_x[2] = 1; 
    passed_x[3] = 1; 
    passed_x[4] = 2; 
    passed_x[5] = 2; 
    passed_x[6] = 2; 
    passed_x[7] = 2; 
    passed_x[8] = 1; 
    passed_x[9] = 1; 
    passed_x[10] = 1; 
    passed_x[11] = 1; 
    passed_x[12] = 2; 
    passed_x[13] = 2; 
    passed_x[14] = 2; 
    passed_x[15] = 2; 
    passed_y[0] = 0; 
    passed_y[1] = 0; 
    passed_y[2] = 1; 
    passed_y[3] = 1; 
    passed_y[4] = 0; 
    passed_y[5] = 0; 
    passed_y[6] = 1; 
    passed_y[7] = 1; 
    passed_y[8] = 0; 
    passed_y[9] = 0; 
    passed_y[10] = 1; 
    passed_y[11] = 1; 
    passed_y[12] = 0; 
    passed_y[13] = 0; 
    passed_y[14] = 1; 
    passed_y[15] = 1; 
    passed_z[0] = 0; 
    passed_z[1] = 1; 
    passed_z[2] = 0; 
    passed_z[3] = 1; 
    passed_z[4] = 0; 
    passed_z[5] = 1; 
    passed_z[6] = 0; 
    passed_z[7] = 1; 
    passed_z[8] = -1; 
    passed_z[9] = 0; 
    passed_z[10] = -1; 
    passed_z[11] = 0; 
    passed_z[12] = -1; 
    passed_z[13] = 0; 
    passed_z[14] = -1; 
    passed_z[15] = 0; 
    cellData = new float[cellNum];
    cellData2 = new float[cellNum];
    cellData[0] = mpi_rank;
    cellData[1] = mpi_rank;
    cellData2[0] = 4;
    cellData2[1] = 5;
  }
  if(mpi_rank == 3){
    passed_x[0] = 1; 
    passed_x[1] = 1; 
    passed_x[2] = 1; 
    passed_x[3] = 1; 
    passed_x[4] = 2; 
    passed_x[5] = 2; 
    passed_x[6] = 2; 
    passed_x[7] = 2; 
    passed_x[8] = 1; 
    passed_x[9] = 1; 
    passed_x[10] = 1; 
    passed_x[11] = 1; 
    passed_x[12] = 2; 
    passed_x[13] = 2; 
    passed_x[14] = 2; 
    passed_x[15] = 2; 
    passed_y[0] = 0; 
    passed_y[1] = 0; 
    passed_y[2] = 1; 
    passed_y[3] = 1; 
    passed_y[4] = 0; 
    passed_y[5] = 0; 
    passed_y[6] = 1; 
    passed_y[7] = 1; 
    passed_y[8] = 0; 
    passed_y[9] = 0; 
    passed_y[10] = 1; 
    passed_y[11] = 1; 
    passed_y[12] = 0; 
    passed_y[13] = 0; 
    passed_y[14] = 1; 
    passed_y[15] = 1; 
    passed_z[0] = 1; 
    passed_z[1] = 2; 
    passed_z[2] = 1; 
    passed_z[3] = 2; 
    passed_z[4] = 1; 
    passed_z[5] = 2; 
    passed_z[6] = 1; 
    passed_z[7] = 2; 
    passed_z[8] = 2; 
    passed_z[9] = 3; 
    passed_z[10] = 2; 
    passed_z[11] = 3; 
    passed_z[12] = 2; 
    passed_z[13] = 3; 
    passed_z[14] = 2; 
    passed_z[15] = 3; 
    cellData = new float[cellNum];
    cellData2 = new float[cellNum];
    cellData[0] = mpi_rank;
    cellData[1] = mpi_rank;
    cellData2[0] = 6;
    cellData2[1] = 7;
  }

  char* varName[]={"ATemperature", "APressure"};
  char* varType[]={"Cell", "Cell"};

  int **cells=NULL;
  cells = new int *[cellNum];
  for(int i =0; i<cellNum; i++){
    cells[i] = new int [nodePerCell];
  }
  int dummy_cells[2][8]={{0,1,2,3,4,5,6,7     },
                         {8,9,10,11,12,13,14,15    }};

  for(int i=0;i<cellNum;i++){
    for(int j=0;j<nodePerCell;j++){
      cells[i][j]=dummy_cells[i][j];
    }
  };
    
  float **varMatrix=NULL;

  varMatrix = new float *[varSize];
  varMatrix[0]=cellData;
  varMatrix[1]=cellData2;

  /*define cell distribution among processors.*/
  
  rtbtOut(fileName,gridName, gridType,topoType, cellNum, nodePerCell,nodeNum,varSize, varName, varType, varMatrix,passed_x, passed_y, passed_z,cells,
  info, comm);

//delete allocated arrays
  delete [] varMatrix;
  varMatrix=NULL;

  for (int i=0;i<cellNum;i++){
    delete [] cells[i];
    cells[i]=NULL;
  }
  delete [] cells;
  cells=NULL;

  if(mpi_rank==0){
    cout << " communication was successful." << '\n';
  }

  MPI_Finalize();

}
