#include "../mousetrap_julia_binding.hpp"

// ### GRID

void implement_grid(jlcxx::Module& module)
{
    auto grid = module.add_type(Grid)
    .add_constructor()
    .method("insert!", [](Grid& grid, void* widget, uint64_t row_i, uint64_t col_i, uint64_t n_horizontal_cells, uint64_t n_vertical_cells){
        grid.insert(*((Widget*) widget), Vector2i(row_i, col_i), n_horizontal_cells, n_vertical_cells);
    })
    .method("insert_next_to!", [](Grid& grid, void* to_insert, void* already_in_grid, RelativePosition position, uint64_t n_horizontal_cells, uint64_t n_vertical_cells){
        grid.insert_next_to(*((Widget*)to_insert), *((Widget*) already_in_grid), position, n_horizontal_cells, n_vertical_cells);
    })
    .method("remove!", [](Grid& grid, void* widget) {
        grid.remove(*((Widget*) widget));
    })
    .method("get_position", [](Grid& grid, void* widget) -> jl_value_t* {
        static auto* vector2i_ctor = (jl_function_t*) jl_eval_string("return Mousetrap.Vector2i");
        auto position = grid.get_position(*((Widget*) widget));
        return jl_safe_call("Grid::get_position",vector2i_ctor, jl_box_int64(position.x), jl_box_int64(position.y));
    })
    .method("get_size", [](Grid& grid, void* widget) -> jl_value_t* {
        static auto* vector2i_ctor = (jl_function_t*) jl_eval_string("return Mousetrap.Vector2i");
        auto size = grid.get_size(*((Widget*) widget));
        return jl_safe_call("Grid::get_size",vector2i_ctor, jl_box_int64(size.x), jl_box_int64(size.y));
    })
    .add_type_method(Grid, insert_row_at, !)
    .add_type_method(Grid, remove_row_at, !)
    .add_type_method(Grid, insert_column_at, !)
    .add_type_method(Grid, remove_column_at, !)
    .add_type_method(Grid, set_column_spacing, !)
    .add_type_method(Grid, get_column_spacing)
    .add_type_method(Grid, set_row_spacing, !)
    .add_type_method(Grid, get_row_spacing)
    .add_type_method(Grid, set_rows_homogeneous, !)
    .add_type_method(Grid, get_rows_homogeneous)
    .add_type_method(Grid, set_columns_homogeneous, !)
    .add_type_method(Grid, get_columns_homogeneous)
    .add_type_method(Grid, get_orientation)
    .add_type_method(Grid, set_orientation, !)
    ;

    add_widget_signals<Grid>(grid, "Grid");
}