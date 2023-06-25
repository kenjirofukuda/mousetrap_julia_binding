cmake_minimum_required(VERSION 3.18)

### PROJECT ###

project(mousetrap_julia_binding
    VERSION 0.1.0
    LANGUAGES CXX
)

set(LIBRARY_NAME mousetrap_julia_binding)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

### DEPENDENCIES ###

find_package(JlCxx REQUIRED)
find_package(mousetrap REQUIRED)

### LIBRARY ###

add_library(${LIBRARY_NAME} SHARED

    mousetrap_julia_binding.hpp

    src/action.cpp
    src/adjustment.cpp
    src/alignment.cpp
    src/application.cpp
    src/aspect_frame.cpp
    src/blend_mode.cpp
    src/box.cpp
    src/button.cpp
    src/center_box.cpp
    src/check_button.cpp
    src/click_event_controller.cpp
    src/clipboard.cpp
    src/color.cpp
    src/column_view.cpp
    src/cursor_type.cpp
    src/define_julia_module.cpp
    src/drag_event_controller.cpp
    src/drop_down.cpp
    src/entry.cpp
    src/event_controller.cpp
    src/expander.cpp
    src/file_chooser.cpp
    src/file_descriptor.cpp
    src/file_monitor.cpp
    src/file_system.cpp
    src/fixed.cpp
    src/focus_event_controller.cpp
    src/frame.cpp
    src/frame_clock.cpp
    src/gl_transform.cpp
    src/grid.cpp
    src/grid_view.cpp
    src/header_bar.cpp
    src/icon.cpp
    src/image.cpp
    src/image_display.cpp
    src/implement_orientation.cpp
    src/justify_mode.cpp
    src/key_codes.cpp
    src/key_event_controller.cpp
    src/key_file.cpp
    src/label.cpp
    src/level_bar.cpp
    src/list_view.cpp
    src/log.cpp
    src/long_press_event_controller.cpp
    src/menu_bar.cpp
    src/menu_model.cpp
    src/motion_event_controller.cpp
    src/music.cpp
    src/notebook.cpp
    src/overlay.cpp
    src/pan_event_controller.cpp
    src/paned.cpp
    src/pinch_zoom_event_controller.cpp
    src/popover.cpp
    src/popover_button.cpp
    src/popover_menu.cpp
    src/progress_bar.cpp
    src/relative_position.cpp
    src/render_area.cpp
    src/render_task.cpp
    src/revealer.cpp
    src/rotate_event_controller.cpp
    src/scale.cpp
    src/scroll_event_controller.cpp
    src/scrollbar.cpp
    src/selection_model.cpp
    src/separator.cpp
    src/shader.cpp
    src/shape.cpp
    src/shortcut_event_controller.cpp
    src/sound.cpp
    src/sound_buffer.cpp
    src/spin_button.cpp
    src/spinner.cpp
    src/stack.cpp
    src/stylus_event_controller.cpp
    src/swipe_event_controller.cpp
    src/switch.cpp
    src/text_view.cpp
    src/texture.cpp
    src/time.cpp
    src/toggle_button.cpp
    src/viewport.cpp
    src/widget.cpp
    src/window.cpp
    src/box_unbox.cpp
    src/gc_sentinel.cpp
)

target_link_libraries(${LIBRARY_NAME} PUBLIC
    OpenGL
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

install(TARGETS ${LIBRARY_NAME} DESTINATION "${CMAKE_INSTALL_LIBDIR}")
