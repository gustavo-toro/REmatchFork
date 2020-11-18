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

if(SWIG) # Only set shared library target
  set(project_LIB "${PROJECT_NAME}")
  set_property(SOURCE interfaces/rematch.i PROPERTY CPLUSPLUS ON)
  swig_add_library(${project_LIB} TYPE MODULE LANGUAGE python SOURCES interfaces/rematch.i ${sources})
  set_property(TARGET ${project_LIB} PROPERTY LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SWIG_OUTDIR})
  set_property(TARGET ${project_LIB} PROPERTY SWIG_COMPILE_OPTIONS -O)
  target_link_libraries(${project_LIB} PRIVATE Python3::Module)
else()
  add_library(rematchlib ${sources})
  set_property (TARGET rematchlib PROPERTY CXX_STANDARD 17)
  target_link_libraries (rematchlib ${project_LIBS})
  list(APPEND project_LIBS rematchlib)

  if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    foreach(target ${BUILD_TARGETS})
      add_executable(${target} ${CMAKE_CURRENT_SOURCE_DIR}/main/${target}.cpp)
      target_link_libraries(${target} ${project_LIBS})
      set_property(TARGET ${target} PROPERTY CXX_STANDARD 17)
    endforeach(target ${BUILD_TARGETS})
  endif()

endif()


