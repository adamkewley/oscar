add_executable(oscar-demo-viewer
    oscar_demo_viewer.cpp
)
target_link_libraries(oscar-demo-viewer PUBLIC oscar_demos)

# Ensure an `osc.toml` file is available when running the demo from the build directory
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/osc.toml.in"
    "${CMAKE_CURRENT_BINARY_DIR}/osc.toml"
    @ONLY
)