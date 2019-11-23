cmake_minimum_required(VERSION 3.12)
project(ACM_club)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB SOURCE_FILES "src/*.cpp")
add_executable(ACM_club ${SOURCE_FILES})
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Add SFML library
set(SFML_ROOT "SFML")
set(SFML_INCLUDE_DIR "SFML/include")
find_package(SFML 2 COMPONENTS audio graphics window system network)

# If found, include and link; otherwise output error message
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(ACM_club ${SFML_LIBRARIES})
else()
    set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
    message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
    message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

# Add LUA and LuaBridge libraries
set(LUA_INCLUDE_DIR "Lua/src")
set(LUABRIDGE_INCLUDE_DIR "LuaBridge/Source")
file(GLOB LUA_LIBRARIES "Lua/src/*.o") # need to delete lua.o and luac.o
find_package(Lua 52)

if(LUA_FOUND)
    include_directories(${LUA_INCLUDE_DIR})
    include_directories(${LUABRIDGE_INCLUDE_DIR}) # C++ bindings
    target_link_libraries(ACM_club ${LUA_LIBRARIES})
else()
    message("\n-> Lua directory not found. Set LUA_INCLUDE_DIR to \"src\" subfolder of Lua top-level path.")
endif()
