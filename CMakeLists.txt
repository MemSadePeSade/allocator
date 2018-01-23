cmake_minimum_required(VERSION 3.6.2)

project(allocator VERSION 0)


add_executable(allocator  main.cpp)

set_target_properties(allocator PROPERTIES
     CXX_STANDARD 14
     CXX_STANDARD_REQUIRED ON
)

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT PonomarevVictor@yandex.ru)

include(CPack)
