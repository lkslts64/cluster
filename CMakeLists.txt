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

add_executable(lsh
        src/mainPointsLSH.cpp
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

add_executable(curve_grid_lsh
        src/curve_grid_lsh.cpp
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

add_executable(test_dba
        src/test_dba.cpp
        src/strategy.h
        src/dba.h src/dba.cpp 
        src/Curve.h src/Curve.cpp
        src/Point.h src/Point.cpp
        src/distance.h src/distance.cpp
        src/Cluster.cpp src/Cluster.h)

add_executable(test_curve_grid_lsh
        src/test_curve_grid_lsh.cpp
        src/curve_grid_lsh.h
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

add_executable(test_lsh_points
        src/test_lsh_points.cpp
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