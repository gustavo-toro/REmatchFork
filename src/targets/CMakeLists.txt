include_directories(main)

set(sources
  main/interface.cpp
  main/interface.hpp
  main/options.hpp
)

set(BUILD_TARGETS
  rematch
)


message("REmatch libs: ${REMATCH_LIBS}")

foreach(target ${BUILD_TARGETS})
  add_executable(${target} ${CMAKE_CURRENT_SOURCE_DIR}/main/${target}.cpp ${sources})
  target_link_libraries(${target} ${REMATCH_LIBS})
endforeach(target ${BUILD_TARGETS})