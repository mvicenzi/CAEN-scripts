cmake_minimum_required (VERSION 3.18.2)

find_package(cetmodules)
set(CET_CETBUILDTOOLS_COMPAT TRUE)
include(Compatibility)
set(CET_WARN_DEPRECATED)

project(CAEN-toolkit)

set(CMAKE_MODULE_PATH
  $ENV{ARTDAQ_UTILITIES_DIR}/Modules
  ${CMAKE_MODULE_PATH})
include(CetCMakeEnv)

cet_cmake_env()

## ask for minimum required version (update?)
find_ups_product( caenvme v2_50 )
find_ups_product( caencomm v1_2a )
find_ups_product( caendigitizer v2_7_2 )

## get the right libraries
add_definitions(-DLINUX)
link_directories($ENV{CAENCOMM_LIB})
link_directories($ENV{CAENVME_LIB})
link_directories($ENV{CAENDIGITIZER_LIB})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(CAENBoardInfo src/CAENBoardInfo.cc)
target_link_libraries(CAENBoardInfo PUBLIC CAENComm CAENVME CAENDigitizer) 

add_executable(CAENStatus src/CAENStatus.cc)
target_link_libraries(CAENStatus PUBLIC CAENComm CAENVME CAENDigitizer) 

#add_executable(checkBridge stolenBridgeUpgrade.cc)
#target_link_libraries(checkBridge PUBLIC CAENComm CAENVME CAENDigitizer) 

#add_executable(CAENStatus CAENStatus.cc)
#target_link_libraries(CAENStatus PUBLIC CAENComm CAENVME CAENDigitizer)

#add_executable(checkCAENStatus checkCAENStatus.cc)
#target_link_libraries(checkCAENStatus PUBLIC CAENComm CAENVME CAENDigitizer)
