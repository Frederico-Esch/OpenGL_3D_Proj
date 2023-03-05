cmake_minimum_required(VERSION 3.20)
project(opengl_3d_project)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(/EHsc /W4 /WX)

add_executable(opengl_3d_project
    "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Window.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Buffers.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Shader.cpp"
)

target_include_directories(opengl_3d_project PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(opengl_3d_project PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glfw3dll.lib" PRIVATE opengl32.lib PRIVATE User32.lib PRIVATE Gdi32.lib PRIVATE Shell32.lib)

#DLL
add_custom_command(
    TARGET opengl_3d_project POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/glfw3.dll"
    $<TARGET_FILE_DIR:opengl_3d_project>
)

#SHADERS
add_custom_command(
    TARGET opengl_3d_project POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
    "$<TARGET_FILE_DIR:opengl_3d_project>/shaders" #"${CMAKE_BINARY_DIR}/shaders"
)

#TEXTURES
add_custom_command(
    TARGET opengl_3d_project POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    "${CMAKE_CURRENT_SOURCE_DIR}/textures"
    "$<TARGET_FILE_DIR:opengl_3d_project>/textures" #"${CMAKE_BINARY_DIR}/textures"
)
