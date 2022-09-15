cmake_minimum_required(VERSION 3.1)

set(project_name oatpp-rest-ybs)

project(${project_name})

set(CMAKE_CXX_STANDARD 17)

add_library(${project_name}-lib
        src/AppComponent.hpp
        src/controller/APIController.cpp
        src/controller/APIController.hpp
        src/dto/RequestDTOs.hpp
        src/dto/StatusDto.hpp
        src/dto/ConfigDto.hpp
        src/db/SystemItemDb.hpp
        src/DatabaseComponent.hpp
        src/Serializers.hpp
        src/ErrorHandler.hpp
        src/ErrorHandler.cpp
        src/service/SystemItemService.cpp
        src/service/SystemItemService.hpp
        src/Serializers.hpp)

## link libs

find_package(oatpp 1.3.0 REQUIRED)
find_package(oatpp-postgresql 1.3.0 REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-postgresql
)

target_include_directories(${project_name}-lib PUBLIC src)

add_definitions(
        # Path to config file #
        -DCONFIG_PATH="${CMAKE_CURRENT_LIST_DIR}/resources/config.json"

        ## Path to database migration scripts
        -DDATABASE_MIGRATIONS="${CMAKE_CURRENT_SOURCE_DIR}/sql"
)

## add executables

add_executable(${project_name}-exe
        src/App.cpp)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

set_target_properties(${project_name}-lib ${project_name}-exe PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)