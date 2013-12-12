ADD_EXECUTABLE ( ../run main.cpp DatCoordPoint.cpp DatCoordPoints.cpp DatCam.cpp DatGUI.cpp)
INCLUDE_DIRECTORIES( ../include/ )
target_link_libraries( ../run ${OpenCV_LIBS} )
