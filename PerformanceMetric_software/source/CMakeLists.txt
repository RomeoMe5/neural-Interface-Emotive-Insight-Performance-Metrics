cmake_minimum_required(VERSION 3.0.0)
project (performance_metrics)

set(PROJECT_LINK_LIBS edk.lib)
set(SDK_DLLS ${PROJECT_SOURCE_DIR}/bin/win64/edk.dll)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib/win64)

set(PERFORMANCE_METRICS_EXE PerformanceMetrics)

add_executable(${PERFORMANCE_METRICS_EXE} PerformanceMetricsDemo.cpp)
target_link_libraries(${PERFORMANCE_METRICS_EXE} ${PROJECT_LINK_LIBS})

add_custom_command(TARGET ${PERFORMANCE_METRICS_EXE} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SDK_DLLS} $<TARGET_FILE_DIR:${PERFORMANCE_METRICS_EXE}>)
