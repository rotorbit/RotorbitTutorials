to compile and run

mkdir build
cd build
cmake ..
make
mpirun -np 4 ./rtbt_vtk.x
