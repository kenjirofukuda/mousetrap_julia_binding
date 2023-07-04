#include "../mousetrap_julia_binding.hpp"

// ### CURSOR_TYPE

void implement_cursor_type(jlcxx::Module& module)
{
    define_enum_in(module, CursorType);
    module.add_enum_value(CursorType, CURSOR_TYPE, NONE);
    module.add_enum_value(CursorType, CURSOR_TYPE, DEFAULT);
    module.add_enum_value(CursorType, CURSOR_TYPE, HELP);
    module.add_enum_value(CursorType, CURSOR_TYPE, POINTER);
    module.add_enum_value(CursorType, CURSOR_TYPE, CONTEXT_MENU);
    module.add_enum_value(CursorType, CURSOR_TYPE, PROGRESS);
    module.add_enum_value(CursorType, CURSOR_TYPE, WAIT);
    module.add_enum_value(CursorType, CURSOR_TYPE, CELL);
    module.add_enum_value(CursorType, CURSOR_TYPE, CROSSHAIR);
    module.add_enum_value(CursorType, CURSOR_TYPE, TEXT);
    module.add_enum_value(CursorType, CURSOR_TYPE, MOVE);
    module.add_enum_value(CursorType, CURSOR_TYPE, NOT_ALLOWED);
    module.add_enum_value(CursorType, CURSOR_TYPE, GRAB);
    module.add_enum_value(CursorType, CURSOR_TYPE, GRABBING);
    module.add_enum_value(CursorType, CURSOR_TYPE, ALL_SCROLL);
    module.add_enum_value(CursorType, CURSOR_TYPE, ZOOM_IN);
    module.add_enum_value(CursorType, CURSOR_TYPE, ZOOM_OUT);
    module.add_enum_value(CursorType, CURSOR_TYPE, COLUMN_RESIZE);
    module.add_enum_value(CursorType, CURSOR_TYPE, ROW_RESIZE);
    module.add_enum_value(CursorType, CURSOR_TYPE, NORTH_RESIZE);
    module.add_enum_value(CursorType, CURSOR_TYPE, NORTH_EAST_RESIZE);
    module.add_enum_value(CursorType, CURSOR_TYPE, EAST_RESIZE);
    module.add_enum_value(CursorType, CURSOR_TYPE, SOUTH_EAST_RESIZE);
    module.add_enum_value(CursorType, CURSOR_TYPE, SOUTH_RESIZE);
    module.add_enum_value(CursorType, CURSOR_TYPE, SOUTH_WEST_RESIZE);
    module.add_enum_value(CursorType, CURSOR_TYPE, WEST_RESIZE);
    module.add_enum_value(CursorType, CURSOR_TYPE, NORTH_WEST_RESIZE);
    module.add_enum_value(CursorType, CURSOR_TYPE, HORIZONTAL_RESIZE);
    module.add_enum_value(CursorType, CURSOR_TYPE, VERTICAL_RESIZE);
}