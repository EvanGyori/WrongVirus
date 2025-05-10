cmake_minimum_required(VERSION 3.20)
project(WrongVirus2)

add_subdirectory(Utility)
add_subdirectory(GLFWwrappers)
add_subdirectory(VulkanWrappers)
add_subdirectory(Rendering)

add_executable(wrongVirus main.cpp)
target_link_libraries(wrongVirus PRIVATE Rendering)

add_custom_command(TARGET wrongVirus POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/Shaders/vert.spv"
    "$<TARGET_FILE_DIR:wrongVirus>/vert.spv"
)

add_custom_command(TARGET wrongVirus POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/Shaders/frag.spv"
    "$<TARGET_FILE_DIR:wrongVirus>/frag.spv"
)
