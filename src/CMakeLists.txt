file(GLOB sources
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/automata/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/det/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/factories/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/parser/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/parser/visitors/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/parser_automata/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/regex/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/structs/*.cpp
)

set(BUILD_TARGETS
  rematch
  # generate
  test-regex
  test-anchors
)

add_library(rematchlib ${sources})
set_property (TARGET rematchlib PROPERTY CXX_STANDARD 14)
target_link_libraries(rematchlib ${project_LIBS})
list(APPEND project_LIBS rematchlib)

if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten" AND NOT SWIG)
  foreach(target ${BUILD_TARGETS})
    add_executable(${target} ${CMAKE_CURRENT_SOURCE_DIR}/main/${target}.cpp)
    target_link_libraries(${target} ${project_LIBS})
    set_property(TARGET ${target} PROPERTY CXX_STANDARD 14)
  endforeach(target ${BUILD_TARGETS})
endif()




