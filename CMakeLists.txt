cmake_minimum_required(VERSION 3.6)
project(V5render)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -Wall -Wextra -Wshadow -Wnull-dereference -Wunused-parameter -Wno-psabi -pthread -g -O0 -fprofile-arcs -ftest-coverage -D THREADS_STD")


include_directories(include/FastPix3D)
include_directories(pcbuild)
include_directories(include)


#add_library(SDL2 STATIC pcbuild/SDL2.lib pcbuild/SDL2_image.lib pcbuild/SDL2main.lib)
#SET_TARGET_PROPERTIES(SDL2 PROPERTIES LINKER_LANGUAGE CXX)
link_directories("pcbuild")


add_executable(V5render
	pcbuild/api.cpp
	
	include/FastPix3D/FastPix3D.h  
	include/FastPix3D/Color.h    
	include/FastPix3D/CullMode.h  
	include/FastPix3D/Directory.h  
	include/FastPix3D/Font.h        
	include/FastPix3D/FreelookManager.h  
	include/FastPix3D/Input.h  
	include/FastPix3D/LightType.h  
	include/FastPix3D/MathUtility.h  
	include/FastPix3D/Mesh.h         
	include/FastPix3D/Path.h   
	include/FastPix3D/ProcessedVertex.h  
	include/FastPix3D/SeekOrigin.h      
	include/FastPix3D/ShadowVolume.h  
	include/FastPix3D/Texture.h   
	include/FastPix3D/Vector2f.h  
	include/FastPix3D/Vertex.h
	include/FastPix3D/Convert.h  
	include/FastPix3D/Device.h    
	include/FastPix3D/Drawer.h     
	include/FastPix3D/File.h       
	include/FastPix3D/FPSCounter.h  
	include/FastPix3D/Graphics.h         
	include/FastPix3D/Light.h  
	include/FastPix3D/lodepng.h    
	include/FastPix3D/Matrix.h       
	include/FastPix3D/MouseButton.h  
	include/FastPix3D/Point.h  
	include/FastPix3D/RenderStates.h     
	include/FastPix3D/ShadowTriangle.h  
	include/FastPix3D/Subset.h        
	include/FastPix3D/Triangle.h  
	include/FastPix3D/Vector3f.h
	
	src/FastPix3D/Color.cpp  
	src/FastPix3D/Directory.cpp  
	src/FastPix3D/Font.cpp        
	src/FastPix3D/FreelookManager.cpp  
	src/FastPix3D/Input.cpp  
	src/FastPix3D/MathUtility.cpp  
	src/FastPix3D/Mesh.cpp         
	src/FastPix3D/Path.cpp   
	src/FastPix3D/ProcessedVertex.cpp   
	src/FastPix3D/ShadowVolume.cpp  
	src/FastPix3D/Texture.cpp   
	src/FastPix3D/Vector2f.cpp  
	src/FastPix3D/Vertex.cpp
	src/FastPix3D/Convert.cpp  
	src/FastPix3D/Device.cpp    
	src/FastPix3D/Drawer.cpp     
	src/FastPix3D/File.cpp       
	src/FastPix3D/FPSCounter.cpp  
	src/FastPix3D/Graphics.cpp         
	src/FastPix3D/Light.cpp  
	src/FastPix3D/lodepng.cpp    
	src/FastPix3D/Matrix.cpp       
	src/FastPix3D/Point.cpp  
	src/FastPix3D/RenderStates.cpp     
	src/FastPix3D/ShadowTriangle.cpp  
	src/FastPix3D/Subset.cpp        
	src/FastPix3D/Triangle.cpp  
	src/FastPix3D/Vector3f.cpp
	src/main.cpp
	)
target_link_libraries(V5render SDL2main SDL2 SDL2_image )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/pcbuild/SDL2.dll
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/pcbuild/SDL2_image.dll
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	 
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Media DESTINATION ${CMAKE_CURRENT_BINARY_DIR})