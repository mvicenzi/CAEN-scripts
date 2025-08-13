cmake_minimum_required (VERSION 3.18.2)

project(CAEN-toolkit)

## ask for minimum required version (update?)
find_library(CAENVME NAMES CAENVME PATHS /usr/lib /usr/local/lib)
find_library(CAENDigitizer NAMES CAENDigitizer PATHS /usr/lib /usr/local/lib)
find_library(CAENComm NAMES CAENComm PATHS /usr/lib /usr/local/lib)

# Ensure both the library and headers are found
if (CAENVME)
    message(STATUS "Found CAENVME library: ${CAENVME}")
else()
    message(FATAL_ERROR "Could not find CAENVME library")
endif()
if (CAENComm)
    message(STATUS "Found CAENComm library: ${CAENComm}")
else()
    message(FATAL_ERROR "Could not find CAENComm library")
endif()
if (CAENDigitizer)
    message(STATUS "Found CAENDigitizer library: ${CAENDigitizer}")
else()
    message(FATAL_ERROR "Could not find CAENDigitizer library")
endif()

add_definitions(-DLINUX)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(CAENV1730_BoardInfo src/CAENV1730_BoardInfo.cc)
target_link_libraries(CAENV1730_BoardInfo PUBLIC ${CAENComm} ${CAENVME} ${CAENDigitizer}) 

add_executable(CAENV1730_Status src/CAENV1730_Status.cc)
target_link_libraries(CAENV1730_Status PUBLIC ${CAENComm} ${CAENVME} ${CAENDigitizer}) 

add_executable(CAENV1730_Reset src/CAENV1730_Reset.cc)
target_link_libraries(CAENV1730_Reset PUBLIC ${CAENComm} ${CAENVME} ${CAENDigitizer})

add_executable(CAENVME_BridgeReset src/CAENVME_BridgeReset.cc)
target_link_libraries(CAENVME_BridgeReset PUBLIC ${CAENComm} ${CAENVME} ${CAENDigitizer})

add_executable(CAENV1730_ClockOut src/CAENV1730_ClockOut.cc)
target_link_libraries(CAENV1730_ClockOut PUBLIC ${CAENComm} ${CAENVME} ${CAENDigitizer})

add_executable(CAENV1730_ClockPhaseOut src/CAENV1730_ClockPhaseOut.cc)
target_link_libraries(CAENV1730_ClockPhaseOut PUBLIC ${CAENComm} ${CAENVME} ${CAENDigitizer})

add_executable(CAENV1730_ReadRegister src/CAENV1730_ReadRegister.cc)
target_link_libraries(CAENV1730_ReadRegister PUBLIC ${CAENComm} ${CAENVME} ${CAENDigitizer})

# -------------------------------------

add_executable(CAENA2795_BoardInfo src/CAENA2795_BoardInfo.cc)
target_link_libraries(CAENA2795_BoardInfo PUBLIC ${CAENComm} ${CAENVME} ${CAENDigitizer}) 

add_executable(CAENA2795_Status src/CAENA2795_Status.cc)
target_link_libraries(CAENA2795_Status PUBLIC ${CAENComm} ${CAENVME} ${CAENDigitizer}) 

