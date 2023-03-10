cmake_minimum_required (VERSION 3.8)

project ("transportation problem")


add_executable (CMakeTarget "main.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()


