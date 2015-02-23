CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

MESSAGE("+++Entering src directory ++++")

#set everything needed for the root dictonary and create the dictionary


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


FILE(GLOB irene_src *.cc)


# # # # Finally, create it!

MESSAGE("Creating Irene library")

ROOT_LINKER_LIBRARY(irene ${irene_src} ${IRENE_DICTIONARY} LIBRARIES ${ROOT_LIBRARIES})

# ADD_LIBRARY(irene SHARED ${irene_src} ${IRENE_DICTIONARY})
# SET_TARGET_PROPERTIES(irene PROPERTIES VERSION 1.1.0 SOVERSION 1)
# TARGET_LINK_LIBRARIES(irene ${ROOT_LIBRARIES})



# # Installation destinations (just for the lib, not the python module)
INSTALL(TARGETS irene DESTINATION lib)
INSTALL(FILES ${i_headers} DESTINATION include/irene)
INSTALL(FILES ${CMAKE_BINARY_DIR}/src/libirene.rootmap DESTINATION lib)
INSTALL(FILES ${CMAKE_BINARY_DIR}/src/libirene_rdict.pcm DESTINATION lib)


