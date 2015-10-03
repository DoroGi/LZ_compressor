cmake_minimum_required(VERSION 2.8)

project(LZ_compressor)

include_directories (include)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set (CMAKE_CXX_FLAGS "-std=c++0x")

################################################################################

add_library (bit_IO src/bit_IO.cc
                    include/bit_IO.h)

add_library (LZ78 src/LZ_78.cc
                  include/compressor.h
			            include/LZ_78.h
                  include/bit_IO.h
                  src/bit_IO.cc)

add_library (LZW src/LZ_W.cc
                 include/compressor.h
                 include/LZ_W.h
                 include/bit_IO.h
                 src/bit_IO.cc)

################################################################################	  

add_executable (LZ_main src/LZ_main.cc)

target_link_libraries (LZ_main bit_IO
                               LZ78
                               LZW)