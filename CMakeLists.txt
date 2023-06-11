cmake_minimum_required(VERSION 3.12)

### PROJECT ###

project(mousetrap_julia_binding
    VERSION 0.1.0
    LANGUAGES CXX
)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

### DEPENDENCIES ###

find_package(JlCxx REQUIRED)
find_package(mousetrap REQUIRED)

### LIBRARY ###

set(LIBRARY_NAME mousetrap_julia_binding)

add_library(${LIBRARY_NAME} SHARED
    mousetrap_julia_binding.hpp
        src/adjustment.cpp src/blend_mode.cpp src/click_event_controller.cpp src/drag_event_controller.cpp src/focus_event_controller.cpp src/long_press_event_controller.cpp src/music.cpp src/notebook.cpp src/implement_orientation.cpp src/implement_orientation.cpp src/paned.cpp src/pinch_zoom_event_controller.cpp src/popover.cpp src/popover_button.cpp src/render_task.cpp src/revealer.cpp src/rotate_event_controller.cpp src/scroll_event_controller.cpp src/scrollbar.cpp src/selection_model.cpp src/separator.cpp src/shader.cpp src/shape.cpp src/shortcut_event_controller.cpp src/sound.cpp src/sound_buffer.cpp src/spin_button.cpp src/spinner.cpp src/stack.cpp src/stylus_event_controller.cpp src/swipe_event_controller.cpp src/switch.cpp src/text_view.cpp src/texture.cpp src/toggle_button.cpp src/viewport.cpp src/widget.cpp src/window.cpp)

target_link_libraries(${LIBRARY_NAME} PUBLIC
    ${MOUSETRAP_LIBRARIES}
    JlCxx::cxxwrap_julia
)

target_include_directories(${LIBRARY_NAME} PUBLIC
    "${MOUSETRAP_INCLUDE_DIRECTORIES}"
    "${Julia_INCLUDE_DIRS}"
)

target_compile_features(${LIBRARY_NAME} PUBLIC
    cxx_std_17
)

set_target_properties(${LIBRARY_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

### INSTALL ###

install(
    TARGETS ${LIBRARY_NAME}
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

