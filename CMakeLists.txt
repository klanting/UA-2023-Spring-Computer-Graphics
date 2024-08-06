cmake_minimum_required(VERSION 3.5)

project(engine)

############################################################
# Set compiler flags
############################################################
# If supported by your compiler, you can add the -Wall, -Wextra, –fstack-protector-all and -g3 flags here.
set(OWN_GXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS}")

############################################################
# List all sources
############################################################
set(engine_sources
	easy_image.cc
	engine.cc
	ini_configuration.cc
	ini_configuration.h
	l_parser.cc
	l_parser.h
		Point2D.cpp Point2D.h Color.cpp Color.h Line2D.cpp Line2D.h tools2D.cpp tools2D.h L_system.cpp L_system.h
		vector3d.cc vector3d.h Face.cpp Face.h Figure.cpp Figure.h Bodies3D.cpp Bodies3D.h L_system3D.cpp L_system3D.h Z_buffer.cpp Z_buffer.h Clipping.cpp Clipping.h Light.cpp Light.h LightTools.cpp LightTools.h BufferStorage.cpp BufferStorage.h ShadowMask.cpp ShadowMask.h TextureMap.cpp TextureMap.h obj_parser.cc obj_parser.h CubeMap.cpp CubeMap.h CubeMapVertex.cpp CubeMapVertex.h CubeMapFace.cpp CubeMapFace.h TextureCoord.cpp TextureCoord.h
		src/ObjectType/FigureType.cpp
		src/ObjectType/FigureType.h
		src/ObjectType/FigureFactory.cpp
		src/ObjectType/FigureFactory.h
		src/Configuration/SectionReader.cpp
		src/Configuration/SectionReader.h
)

############################################################
# Create an executable
############################################################
set(exe_name "engine")
add_executable( ${exe_name} ${engine_sources} )
install( TARGETS ${exe_name} DESTINATION ${PROJECT_SOURCE_DIR}/ )
