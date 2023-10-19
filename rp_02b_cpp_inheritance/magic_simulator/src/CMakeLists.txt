add_library(simple_sim_library SHARED
  geometry_2d.cpp)

add_executable(test_geometry_2d
  test_geometry_2d.cpp)

target_link_libraries(test_geometry_2d
  simple_sim_library)
