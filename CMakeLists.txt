cmake_minimum_required(VERSION 3.26)
project(PROJECT_II)

set(CMAKE_CXX_STANDARD 14)


include_directories(src)
add_subdirectory(Tests)

set(SOURCE_FILES
        src/Airline.cpp
        src/Airline.h
        src/Airport.h
        src/Flight.h
        src/Airport.cpp
        src/Flight.cpp
        src/Script.cpp
        main.cpp
        src/Graph.h
        src/Menu.cpp
        src/Menu.h
        src/AirportManager.cpp
        src/AirportManager.h

)

add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCE_FILES})
add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCE_FILES})

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)



