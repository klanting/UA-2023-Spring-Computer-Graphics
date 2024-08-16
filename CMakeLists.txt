cmake_minimum_required(VERSION 3.5)

project(engine)

############################################################
# Set compiler flags
############################################################
# If supported by your compiler, you can add the -Wall, -Wextra, –fstack-protector-all and -g3 flags here.
set(OWN_GXX_FLAGS "-std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OWN_GXX_FLAGS}")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${OWN_GXX_FLAGS}")

############################################################
# List all sources
############################################################
set(engine_sources
        libraries/easy_image.cc
	engine.cc
		libraries/ini_configuration.cc
		libraries/ini_configuration.h
		libraries/l_parser.cc
		libraries/l_parser.h
		src/Figure/Point2D.cpp src/Figure/Point2D.h src/Figure/Color.cpp src/Figure/Color.h src/Figure/Line2D.cpp src/Figure/Line2D.h src/2DProjection/tools2D.cpp src/2DProjection/tools2D.h src/LSystems/LSystem.cpp src/LSystems/LSystem.h
		libraries/vector3d.cc libraries/vector3d.h src/Figure/Face.cpp src/Figure/Face.h src/Figure/Figure.cpp src/Figure/Figure.h src/ObjectCreation/Bodies3D.cpp src/ObjectCreation/Bodies3D.h src/LSystems/LSystem3D.cpp src/LSystems/LSystem3D.h src/2DProjection/Z_buffer.cpp src/2DProjection/Z_buffer.h src/Clipping/Clipping.cpp src/Clipping/Clipping.h src/Lighting/Light.cpp src/Lighting/Light.h src/Lighting/LightTools.cpp src/Lighting/LightTools.h src/2DProjection/BufferStorage.cpp src/2DProjection/BufferStorage.h src/Lighting/ShadowMask.cpp src/Lighting/ShadowMask.h src/Textures/TextureMap.cpp src/Textures/TextureMap.h src/Configuration/obj_parser.cc src/Configuration/obj_parser.h src/CubeMapping/CubeMap.cpp src/CubeMapping/CubeMap.h src/CubeMapping/CubeMapVertex.cpp src/CubeMapping/CubeMapVertex.h src/CubeMapping/CubeMapFace.cpp src/CubeMapping/CubeMapFace.h src/Textures/TextureCoord.cpp src/Textures/TextureCoord.h
		src/InputType/FigureType.cpp
		src/InputType/FigureType.h
		src/ObjectCreation/FigureFactory.cpp
		src/ObjectCreation/FigureFactory.h
		src/ConfigReaders/FigureReader.cpp
		src/ConfigReaders/FigureReader.h
		src/Perspective/EyePerspective.cpp
		src/Perspective/EyePerspective.h
		src/Configuration/ConfigurationChecks.cpp
		src/Configuration/ConfigurationChecks.h
		src/ConfigReaders/ConfigReader.cpp
		src/ConfigReaders/ConfigReader.h
		src/ConfigReaders/LightReader.cpp
		src/ConfigReaders/LightReader.h
		src/ObjectCreation/LightCreator.cpp
		src/ObjectCreation/LightCreator.h
		src/LSystems/Adapter/LSystemAdapt.cpp
		src/LSystems/Adapter/LSystemAdapt.h
		src/LSystems/Adapter/L2DAdapt.cpp
		src/LSystems/Adapter/L2DAdapt.h
		src/LSystems/Adapter/L3DAdapt.cpp
		src/LSystems/Adapter/L3DAdapt.h
)

############################################################
# Create an executable
############################################################
set(exe_name "engine")
add_executable( ${exe_name} ${engine_sources} )
install( TARGETS ${exe_name} DESTINATION ${PROJECT_SOURCE_DIR}/ )
