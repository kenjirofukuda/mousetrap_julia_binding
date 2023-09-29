project('mousetrap_julia_binding', 'c', 'cpp', version: '0.3.0')
add_project_arguments([
    '-Wno-unused-variable',
    '-Wno-unused-function',
    '-Wno-unused-but-set-variable'
], language: 'cpp')

### DEPENDENCIES ###

ADWAITA = dependency('libadwaita-1',
    required: true,
    version: '>=1.2'
)

MOUSETRAP = dependency('mousetrap',
    required : false
)
if not MOUSETRAP.found()
    MOUSETRAP = meson.get_compiler('cpp').find_library('mousetrap')
    if not MOUSETRAP.found()
        error('Unable to locate mousetrap shared library')
    endif
endif

CXXWRAP = dependency('JlCxx',
    required: true,
    modules: ['JlCxx::cxxwrap_julia'],
    version: '>=0.11'
)

if CXXWRAP.get_variable('Julia_FOUND', default_value: 'FALSE') == 'TRUE'
    # if possible, use auto detected variables from jlcxx
    JULIA_LIBRARY = CXXWRAP.get_variable('Julia_LIBRARY')
    JULIA_INCLUDE_DIRS = CXXWRAP.get_variable('Julia_INCLUDE_DIRS')
else
    # otherwise, use manual overrides from options
    warning('Unable to detect Julia_LIBRARY and Julia_INCLUDE_DIRS through JlCxx. Using manual overrides...')
    JULIA_LIBRARY = get_option('Julia_LIBRARY')
    if JULIA_LIBRARY == ''
        warning('Unable to detect Julia_LIBRARY, and fallback option was not specified. Rerun meson with -DJulia_LIBRARY_PATH=/path/to/libjulia.so')
        # sic, non-fatal
    endif
    JULIA_INCLUDE_DIRS = get_option('Julia_INCLUDE_DIRS')
    if JULIA_INCLUDE_DIRS == ''
        error('Unable to detect Julia_INCLUDE_DIRS, and fallback option was not specified. Rerun meson with -DJulia_INCLUDE_DIRS=/path/to/include/julia')
    endif
endif

JULIA_INCLUDE_DIRS = JULIA_INCLUDE_DIRS.split(';')
foreach path : JULIA_INCLUDE_DIRS
    if not (path == '')
        include_directories(path)
    endif
endforeach

### MOUSETRAP JULIA BINDING ###

MOUSETRAP_JULIA_BINDING_SOURCES = [
    'mousetrap_julia_binding.hpp',
    'cpp/action.cpp',
    'cpp/action_bar.cpp',
    'cpp/adjustment.cpp',
    'cpp/alert_dialog.cpp',
    'cpp/alignment.cpp',
    'cpp/animation.cpp',
    'cpp/application.cpp',
    'cpp/aspect_frame.cpp',
    'cpp/blend_mode.cpp',
    'cpp/box.cpp',
    'cpp/box_unbox.cpp',
    'cpp/button.cpp',
    'cpp/center_box.cpp',
    'cpp/check_button.cpp',
    'cpp/clamp_frame.cpp',
    'cpp/click_event_controller.cpp',
    'cpp/clipboard.cpp',
    'cpp/color.cpp',
    'cpp/color_chooser.cpp',
    'cpp/column_view.cpp',
    'cpp/cursor_type.cpp',
    'cpp/define_julia_module.cpp',
    'cpp/drag_event_controller.cpp',
    'cpp/drop_down.cpp',
    'cpp/entry.cpp',
    'cpp/event_controller.cpp',
    'cpp/expander.cpp',
    'cpp/file_chooser.cpp',
    'cpp/file_descriptor.cpp',
    'cpp/file_monitor.cpp',
    'cpp/file_system.cpp',
    'cpp/fixed.cpp',
    'cpp/flow_box.cpp',
    'cpp/focus_event_controller.cpp',
    'cpp/frame.cpp',
    'cpp/frame_clock.cpp',
    'cpp/gc_sentinel.cpp',
    'cpp/gl_canvas.cpp',
    'cpp/gl_transform.cpp',
    'cpp/grid.cpp',
    'cpp/grid_view.cpp',
    'cpp/header_bar.cpp',
    'cpp/icon.cpp',
    'cpp/image.cpp',
    'cpp/image_display.cpp',
    'cpp/orientation.cpp',
    'cpp/justify_mode.cpp',
    'cpp/key_codes.cpp',
    'cpp/key_event_controller.cpp',
    'cpp/key_file.cpp',
    'cpp/label.cpp',
    'cpp/level_bar.cpp',
    'cpp/list_view.cpp',
    'cpp/log.cpp',
    'cpp/long_press_event_controller.cpp',
    'cpp/menu_bar.cpp',
    'cpp/menu_model.cpp',
    'cpp/motion_event_controller.cpp',
    'cpp/notebook.cpp',
    'cpp/overlay.cpp',
    'cpp/pan_event_controller.cpp',
    'cpp/paned.cpp',
    'cpp/pinch_zoom_event_controller.cpp',
    'cpp/popover.cpp',
    'cpp/popover_button.cpp',
    'cpp/popover_menu.cpp',
    'cpp/popup_message.cpp',
    'cpp/progress_bar.cpp',
    'cpp/relative_position.cpp',
    'cpp/render_area.cpp',
    'cpp/render_task.cpp',
    'cpp/revealer.cpp',
    'cpp/rotate_event_controller.cpp',
    'cpp/scale.cpp',
    'cpp/scroll_event_controller.cpp',
    'cpp/scrollbar.cpp',
    'cpp/selection_model.cpp',
    'cpp/separator.cpp',
    'cpp/shader.cpp',
    'cpp/shape.cpp',
    'cpp/shortcut_event_controller.cpp',
    'cpp/spin_button.cpp',
    'cpp/spinner.cpp',
    'cpp/stack.cpp',
    'cpp/style_class.cpp',
    'cpp/stylus_event_controller.cpp',
    'cpp/swipe_event_controller.cpp',
    'cpp/switch.cpp',
    'cpp/text_view.cpp',
    'cpp/texture.cpp',
    'cpp/theme.cpp',
    'cpp/time.cpp',
    'cpp/toggle_button.cpp',
    'cpp/transform_bin.cpp',
    'cpp/viewport.cpp',
    'cpp/widget.cpp',
    'cpp/window.cpp'
]

### PRODUCTS ###

MOUSETRAP_JULIA_BINDING_LIBRARY = library('mousetrap_julia_binding',
    sources: MOUSETRAP_JULIA_BINDING_SOURCES,
    dependencies: [MOUSETRAP, CXXWRAP, ADWAITA],
    version: '0.3.0',
    include_directories: ['cpp', JULIA_INCLUDE_DIRS],
    install: true
)
