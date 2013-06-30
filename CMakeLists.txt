cmake_minimum_required (VERSION 2.6)
project (Cedar)

set(executable_name Tragopan)

aux_source_directory(Source/ FILES)

add_library(Cedar SHARED ${FILES})

add_definitions("-g")
add_definitions("-Wall")
add_definitions("-std=c++11")

aux_source_directory(Spec/ FILES_SPEC)
aux_source_directory(Spec/Matchers/ MATCHERS_FILES_SPEC)
add_definitions("-g")
add_definitions("-Wall")
add_definitions("-std=c++11")
include_directories("Source/Headers")
include_directories("Source/Headers/Matchers/")
add_executable (Tests ${FILES_SPEC} ${MATCHERS_FILES_SPEC})
target_link_libraries(Tests Cedar)
