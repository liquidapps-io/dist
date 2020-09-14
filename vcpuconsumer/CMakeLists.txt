get_filename_component(PROJ_NAME "${CMAKE_CURRENT_SOURCE_DIR}" NAME )
cmake_minimum_required(VERSION 3.5)
set(EOSIO_WASM_OLD_BEHAVIOR "Off")
project(${PROJ_NAME} VERSION 1.0.0)
if(EOSIO_CDT_ROOT STREQUAL "" OR NOT EOSIO_CDT_ROOT)
   find_package(eosio.cdt)
endif()
add_contract( ${PROJ_NAME} ${PROJ_NAME} ${PROJ_NAME}.cpp )
include_directories( ${PROJ_NAME} PUBLIC ./ )


include(ExternalProject)
ExternalProject_Add(
               ${PROJ_NAME}-vcpu
               SOURCE_DIR vcpu
               BINARY_DIR vcpu
               CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${EOSIO_CDT_ROOT}/lib/cmake/eosio.cdt/EosioWasmToolchain.cmake
               UPDATE_COMMAND ""
               PATCH_COMMAND ""
               TEST_COMMAND ""
               INSTALL_COMMAND ""
               BUILD_ALWAYS 1
            )
