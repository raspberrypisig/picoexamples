add_library(eeram_47L16 INTERFACE)

target_sources(eeram_47L16 INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/eeram.cpp
)

target_include_directories(eeram_47L16 INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Pull in pico libraries that we need
target_link_libraries(eeram_47L16 INTERFACE pico_stdlib hardware_i2c)
