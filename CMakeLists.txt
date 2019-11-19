set(CMAKE_LEGACY_CYGWIN_WIN32 0)

cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 14)
add_compile_options(-fpermissive)
#add_compile_options(-O3)
link_libraries(cunit)
project (algorithms_project)

add_executable(cluster
        src/main.cpp
        src/Curve.cpp
        src/Curve.h
        src/curve_hasher.cpp
        src/Dataset.cpp
        src/Dataset.h
        src/dba.cpp
        src/kmeans.h
        src/distance.h
        src/distance.cpp
        src/hasher.h
        src/HashTableStruct.h
        src/HashTableStruct.cpp
        src/Object.h
        src/Point.cpp
        src/Point.h
        src/point_hasher.cpp
        src/utils.cpp
        src/utils.h
        src/ui.cpp
        src/ui.h
        src/LSH.h
        src/parse_files.cpp src/parse_files.h
        src/search.cpp
        src/search.h
        src/spread_out.cpp
        src/GeneralParameters.h
        src/Cluster.cpp src/Cluster.h src/strategy.cpp)

add_executable(test_kmeans
        src/test_kmeans.cpp
        src/strategy.h
        src/Dataset.cpp
        src/Dataset.h
        src/dba.cpp 
        src/kmeans.h 
        src/Curve.h src/Curve.cpp
        src/Point.h src/Point.cpp
        src/distance.h src/distance.cpp
        src/Cluster.cpp src/Cluster.h)

add_executable(test_spread_out
        src/test_spread_out.cpp
        src/spread_out.cpp 
        src/strategy.h
        src/Curve.h src/Curve.cpp
        src/Point.h src/Point.cpp
        src/Dataset.h src/Dataset.cpp
        src/utils.h src/utils.cpp
        src/distance.h src/distance.cpp
        src/Cluster.cpp src/Cluster.h)

add_executable(test_point_hasher
        src/test_point_hasher.cpp
        src/Curve.cpp
        src/Curve.h
        src/curve_hasher.cpp
        src/Dataset.cpp
        src/Dataset.h
        src/distance.h
        src/distance.cpp
        src/hasher.h
        src/HashTableStruct.h
        src/HashTableStruct.cpp
        src/Object.h
        src/Point.cpp
        src/Point.h
        src/point_hasher.cpp
        src/utils.cpp
        src/utils.h
        src/ui.cpp
        src/ui.h
        src/LSH.h
        src/parse_files.cpp src/parse_files.h
        src/search.cpp
        src/search.h
        src/GeneralParameters.h
        src/Cluster.cpp src/Cluster.h)

add_executable(test_curve_hasher
        src/test_curve_hasher.cpp
        src/Curve.cpp
        src/Curve.h
        src/Dataset.cpp
        src/Dataset.h
        src/distance.h
        src/distance.cpp
        src/hasher.h
        src/HashTableStruct.h
        src/HashTableStruct.cpp
        src/Object.h
        src/Point.cpp
        src/Point.h
        src/curve_hasher.cpp
        src/point_hasher.cpp
        src/utils.cpp
        src/utils.h
        src/ui.cpp
        src/ui.h
        src/LSH.h
        src/parse_files.cpp src/parse_files.h
        src/search.cpp
        src/search.h
        src/GeneralParameters.h
        src/Cluster.cpp src/Cluster.h)
