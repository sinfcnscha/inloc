ADD_EXECUTABLE ( ../run main.cpp DatCoordPoint.cpp DatCoordPoints.cpp DatCam.cpp DatGUI.cpp DatObjDetect.cpp DatCoordMeth.cpp DatLinearEquation.cpp DatMapping.cpp InLoc_Richtung.cpp)
INCLUDE_DIRECTORIES( ../include/ )
target_link_libraries( ../run ${OpenCV_LIBS} )
