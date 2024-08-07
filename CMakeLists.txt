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
		src/2DProjection/easy_image.cc
	engine.cc
		src/Configuration/ini_configuration.cc
		src/Configuration/ini_configuration.h
        src/LSystems/l_parser.cc
        src/LSystems/l_parser.h
		src/Figure/Point2D.cpp src/Figure/Point2D.h src/Figure/Color.cpp src/Figure/Color.h src/Figure/Line2D.cpp src/Figure/Line2D.h src/2DProjection/tools2D.cpp src/2DProjection/tools2D.h src/LSystems/L_system.cpp src/LSystems/L_system.h
		src/Figure/vector3d.cc src/Figure/vector3d.h src/Figure/Face.cpp src/Figure/Face.h src/Figure/Figure.cpp src/Figure/Figure.h src/ObjectCreation/Bodies3D.cpp src/ObjectCreation/Bodies3D.h src/LSystems/L_system3D.cpp src/LSystems/L_system3D.h src/2DProjection/Z_buffer.cpp src/2DProjection/Z_buffer.h src/Clipping/Clipping.cpp src/Clipping/Clipping.h src/Lighting/Light.cpp src/Lighting/Light.h src/Lighting/LightTools.cpp src/Lighting/LightTools.h src/2DProjection/BufferStorage.cpp src/2DProjection/BufferStorage.h src/Lighting/ShadowMask.cpp src/Lighting/ShadowMask.h src/Textures/TextureMap.cpp src/Textures/TextureMap.h src/Configuration/obj_parser.cc src/Configuration/obj_parser.h src/CubeMapping/CubeMap.cpp src/CubeMapping/CubeMap.h src/CubeMapping/CubeMapVertex.cpp src/CubeMapping/CubeMapVertex.h src/CubeMapping/CubeMapFace.cpp src/CubeMapping/CubeMapFace.h src/Textures/TextureCoord.cpp src/Textures/TextureCoord.h
		src/ObjectType/FigureType.cpp
		src/ObjectType/FigureType.h
		src/ObjectType/FigureFactory.cpp
		src/ObjectType/FigureFactory.h
		src/Configuration/SectionReader.cpp
		src/Configuration/SectionReader.h
		src/Perspective/EyePerspective.cpp
		src/Perspective/EyePerspective.h
		src/Configuration/ConfigurationChecks.cpp
		src/Configuration/ConfigurationChecks.h
)

############################################################
# Create an executable
############################################################
set(exe_name "engine")
add_executable( ${exe_name} ${engine_sources} )
install( TARGETS ${exe_name} DESTINATION ${PROJECT_SOURCE_DIR}/ )
