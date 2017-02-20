cmake_minimum_required(VERSION 2.0) # setting this is required
project(RTBT_VTK)            # this sets the project name

file(GLOB_RECURSE sources rtbtVTK.cpp rtbtOut.cpp main.cpp)

###############################################################################
## target definitions #########################################################
###############################################################################

# The data is just added to the executable, because in some IDEs (QtCreator) 
# files are invisible when they are not explicitly part of the project.
add_executable(rtbt_vtk.x ${sources})

target_compile_options(rtbt_vtk.x PUBLIC -std=gnu++0x -Wno-deprecated -Wno-write-strings)

###############################################################################
## dependencies ###############################################################
###############################################################################

#### MPI
find_package(MPI REQUIRED)
if (MPI_FOUND)
    include_directories(SYSTEM ${MPI_INCLUDE_PATH})
else (MPI_FOUND)
    message(SEND_ERROR "This application cannot compile without MPI")
endif (MPI_FOUND)

#### VTK

find_package(VTK COMPONENTS vtkCommonCore vtkIOXML vtkIOParallelXML NO_MODULE)
if (VTK_FOUND)
    include(${VTK_USE_FILE})
else (VTK_FOUND)
    message(SEND_ERROR "This application cannot compile without VTK")
endif (VTK_FOUND)

target_link_libraries(rtbt_vtk.x ${MPI_LIBRARIES} ${VTK_LIBRARIES})
