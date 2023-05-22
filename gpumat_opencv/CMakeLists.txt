cmake_minimum_required(VERSION 3.17)

project(Xaiva_GpuMat_Test
    LANGUAGES C CXX CUDA
    VERSION 0.0.00)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++14 -fPIC -D_GLIBCXX_USE_CXX11_ABI=0")

add_executable(${PROJECT_NAME} ./gpumat_test.cpp)

find_package(PkgConfig REQUIRED)
find_package(CUDA)

pkg_check_modules(LIBCUDA REQUIRED IMPORTED_TARGET
    cuda-${CUDA_VERSION}
    cudart-${CUDA_VERSION}
    nvrtc-${CUDA_VERSION}
)
pkg_check_modules(LIBNPP REQUIRED IMPORTED_TARGET
    nppicc-${CUDA_VERSION}
    nppisu-${CUDA_VERSION}
    npps-${CUDA_VERSION}
    nppist-${CUDA_VERSION}
    nppc-${CUDA_VERSION}
    # nppi-${CUDA_VERSION}
    nppig-${CUDA_VERSION}
    nppif-${CUDA_VERSION}
    # nppidei-${CUDA_VERSION}
    # nppicom-${CUDA_VERSION}
    nppitc-${CUDA_VERSION}
    nppial-${CUDA_VERSION}
    nppim-${CUDA_VERSION}
)

set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lwebp -ltbb -ldl -lpthread -lpng -ljpeg -lopenjp2 -lz")
PKG_CHECK_MODULES(LIBOPENCV REQUIRED IMPORTED_TARGET opencv4)
target_link_libraries(${PROJECT_NAME} 
    PkgConfig::LIBOPENCV 
    -ldl -lpthread -lpng -lwebp -ljpeg -lopenjp2) 

target_link_libraries(${PROJECT_NAME} 
    PkgConfig::LIBCUDA
    PkgConfig::LIBNPP
    -llzma)


# execute_process(COMMAND bash -c "pkg-config --cflags opencv4 | sed 's/-I//g'"
#     OUTPUT_VARIABLE MY_PACKAGE_CFLAGS
#     OUTPUT_STRIP_TRAILING_WHITESPACE)
# message(STATUS "CFLAGS : ${MY_PACKAGE_CFLAGS}")
# include_directories("${MY_PACKAGE_CFLAGS}")

# execute_process(COMMAND bash -c "pkg-config --static --libs opencv4 | sed 's/-L//g'"
#     OUTPUT_VARIABLE MY_PACKAGE_STATIC_LDFLAGS
#     OUTPUT_STRIP_TRAILING_WHITESPACE)

# message(STATUS "Parameters : ${MY_PACKAGE_STATIC_LDFLAGS}")

# set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} ${MY_PACKAGE_STATIC_LDFLAGS}")
# target_link_libraries(${PROJECT_NAME} PkgConfig::LIBOPENCV)
