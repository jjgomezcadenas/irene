# -*- cmake -*-
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(IRENE)

MESSAGE("CMAKE_SYSTEM_NAME: ${CMAKE_SYSTEM_NAME}")
#Set compilier flags
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
   # Mac OS X specific code
   SET(CMAKE_CXX_FLAGS "-Wall -g -O2 -std=c++11" )
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Linux specific code
    SET(CMAKE_CXX_FLAGS "-Wall -g -O2 -std=c++0x" )
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")


SET(CMAKE_VERBOSE_MAKEFILE ON)
#SET(CMAKE_BUILD_TYPE ${CMAKE_CXX_FLAGS})

MESSAGE("CMAKE source dir: ${CMAKE_SOURCE_DIR}")
MESSAGE("CMAKE binary dir: ${CMAKE_BINARY_DIR}")

MESSAGE("CMAKE compiler: ${CMAKE_CXX_COMPILER}")
MESSAGE("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
MESSAGE("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# Set where to look for external packages 
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/") 

MESSAGE("CMAKE_MODULE_PATH source dir: ${CMAKE_MODULE_PATH}")


# Look for the needed libraries

find_package(ROOT REQUIRED)


MESSAGE("ROOT include directories: ${ROOT_INCLUDE_DIR}")
MESSAGE("ROOT libraries: ${ROOT_LIBRARIES}")

#Make symbolic links in irene/ to all header files

EXECUTE_PROCESS(
  COMMAND mkdir -p irene)


FILE(GLOB i_headers . src/*.h )

FOREACH(file ${i_headers})
  EXECUTE_PROCESS(
    COMMAND ln -s -f ${file} irene)
ENDFOREACH(file)

set (IRENE_SRC ${CMAKE_SOURCE_DIR}/src)

# Directories that will be searched for headers during compilation
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR} ${IRENE_SRC} 
					${ROOT_INCLUDE_DIR})

#set everything needed for the root dictonary and create the dictionary


set(IRENE_DICTIONARY ${CMAKE_BINARY_DIR}/ireneDict.cxx)  # set dictionary path

MESSAGE("Generate Irene dictionary")

SET(IRENE_HEADERS ${IRENE_SRC}/Track.h ${IRENE_SRC}/Particle.h ${IRENE_SRC}/SensorHit.h 
  ${IRENE_SRC}/ParameterInfo.h ${IRENE_SRC}/Event.h)


ROOT_GENERATE_DICTIONARY(
           "${IRENE_DICTIONARY}"            # path to dictionary to generate
           "${IRENE_SRC}"  # list of includes
           "${IRENE_HEADERS}" 
           "${IRENE_SRC}/LinkDef.h"   # ROOT linkDef file
         )

 FILE(GLOB irene_src . src/*.cc)


# # # # Finally, create it!

MESSAGE("Creating Irene library")

ADD_LIBRARY(irene SHARED ${irene_src} ${IRENE_DICTIONARY})

#ADD_LIBRARY(alex SHARED ${alex_src})

SET_TARGET_PROPERTIES(irene PROPERTIES VERSION 1.1.0 SOVERSION 1)
TARGET_LINK_LIBRARIES(irene ${ROOT_LIBRARIES})



# # Installation destinations (just for the lib, not the python module)
# INSTALL(TARGETS alex LIBRARY DESTINATION lib)
# INSTALL(FILES ${alex_headers} DESTINATION include/alex)

# # Get ready for creating a package
# INCLUDE(CPack)
