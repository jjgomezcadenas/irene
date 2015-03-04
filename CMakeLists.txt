# -*- cmake -*-
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
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
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules) 

MESSAGE("CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")

SET(CMAKE_INSTALL_PREFIX $ENV{INSTALL})


MESSAGE("CMAKE_INSTALL_PREFIX set to: ${CMAKE_INSTALL_PREFIX}")


# Look for the needed libraries

find_package(ROOT REQUIRED)

if(CMAKE_SYSTEM_NAME MATCHES Darwin)
  # To avoid to set ld_Library_path to locate the test libraries
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,@loader_path/.")
endif()


MESSAGE("ROOT include directories: ${ROOT_INCLUDE_DIR}")
MESSAGE("ROOT libraries: ${ROOT_LIBRARIES}")

MESSAGE("ROOT Found: ${ROOT_FOUND}")
MESSAGE("ROOT CINT: ${ROOTCINT_EXECUTABLE}")

include(RootNewMacros)
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


set(IRENE_DICTIONARY ${CMAKE_BINARY_DIR}/ireneDict)  # set dictionary path
set(LINKDEF_FILE ${IRENE_SRC}/LinkDef.h)  # set dictionary path



MESSAGE("Generate Irene dictionary")

 SET(IRENE_HEADERS ${IRENE_SRC}/Track.h ${IRENE_SRC}/Particle.h ${IRENE_SRC}/SensorHit.h 
   ${IRENE_SRC}/ParameterInfo.h ${IRENE_SRC}/Event.h)

 FILE(GLOB irene_headers ${IRENE_SRC}/Track.h ${IRENE_SRC}/Particle.h ${IRENE_SRC}/SensorHit.h 
   ${IRENE_SRC}/ParameterInfo.h ${IRENE_SRC}/Event.h)

# ROOT_GENERATE_DICTIONARY(
#            "${IRENE_DICTIONARY}"            # path to dictionary to generate
#            "${IRENE_SRC}"  # list of includes
#            "${IRENE_HEADERS}" 
#            "${IRENE_SRC}/LinkDef.h"   # ROOT linkDef file
#          )


#function(root_generate_dictionary DICT_FILE INCLUDE_DIRS HEADER_FILES LINKDEF_FILE)

#ROOT_GENERATE_DICTIONARY ("${irene_headers}" "${LINKDEF_FILE}" "${IRENE_DICTIONARY}" "${IRENE_SRC}")

ROOT_GENERATE_DICTIONARY(${IRENE_DICTIONARY} ${irene_headers} MODULE irene LINKDEF ${LINKDEF_FILE})

#---------------------------------------------------------------------------------------------------
#---ROOT_GENERATE_DICTIONARY( dictionary headerfiles MODULE module DEPENDENCIES dep1 dep2
#                                                    STAGE1 LINKDEF linkdef OPTIONS opt1 opt2 ...)
#---------------------------------------------------------------------------------------------------


FILE(GLOB irene_src ${IRENE_SRC}/*.cc)


# # # # Finally, create it!

MESSAGE("Creating Irene library")

ROOT_LINKER_LIBRARY(irene ${irene_src} ${IRENE_DICTIONARY} LIBRARIES ${ROOT_LIBRARIES})

# ADD_LIBRARY(irene SHARED ${irene_src} ${IRENE_DICTIONARY})
# SET_TARGET_PROPERTIES(irene PROPERTIES VERSION 1.1.0 SOVERSION 1)
# TARGET_LINK_LIBRARIES(irene ${ROOT_LIBRARIES})



# # Installation destinations (just for the lib, not the python module)
INSTALL(TARGETS irene DESTINATION lib)
INSTALL(FILES ${i_headers} DESTINATION include/irene)
INSTALL(FILES ${CMAKE_BINARY_DIR}/libirene.rootmap DESTINATION lib)
INSTALL(FILES ${CMAKE_BINARY_DIR}/libirene_rdict.pcm DESTINATION lib)



#ADD_SUBDIRECTORY(src)


