# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Asser_autogen"
  "CMakeFiles/Asser_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Asser_autogen.dir/ParseCache.txt"
  )
endif()
