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

add_executable(CAENBoardInfo src/CAENBoardInfo.cc)
target_link_libraries(CAENBoardInfo PUBLIC ${CAENComm} ${CAENVME} ${CAENDigitizer}) 

add_executable(CAENStatus src/CAENStatus.cc)
target_link_libraries(CAENStatus PUBLIC ${CAENComm} ${CAENVME} ${CAENDigitizer}) 

add_executable(CAENReset src/CAENReset.cc)
target_link_libraries(CAENReset PUBLIC ${CAENComm} ${CAENVME} ${CAENDigitizer})

add_executable(CAENBridgeReset src/CAENBridgeReset.cc)
target_link_libraries(CAENBridgeReset PUBLIC ${CAENComm} ${CAENVME} ${CAENDigitizer})

add_executable(CAENClockOut src/CAENClockOut.cc)
target_link_libraries(CAENClockOut PUBLIC ${CAENComm} ${CAENVME} ${CAENDigitizer})

add_executable(CAENClockPhaseOut src/CAENClockPhaseOut.cc)
target_link_libraries(CAENClockPhaseOut PUBLIC ${CAENComm} ${CAENVME} ${CAENDigitizer})

add_executable(CAENReadRegister src/CAENReadRegister.cc)
target_link_libraries(CAENReadRegister PUBLIC ${CAENComm} ${CAENVME} ${CAENDigitizer})
