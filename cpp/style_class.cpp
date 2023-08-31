//
// Created by clem on 8/27/23.
//

#include "../mousetrap_julia_binding.hpp"

namespace mousetrap
{
    void implement_style_class(jlcxx::Module& module)
    {
        auto style = module.add_type(StyleClass)
            .add_constructor(const std::string&)
            .add_type_method(StyleClass, get_name)
            .add_type_method(StyleClass, serialize)
            .method("set_property!", [](StyleClass& self, const std::string& target, const std::string& property, const std::string& value){
                self.set_property(target, property, value);
            })
            .method("get_property", [](const StyleClass& self, const std::string& property) -> std::string {
                return self.get_property(property);
            })
        ;

        module.method("style_manager_add_style_class!", [](const StyleClass& style){
            StyleManager::add_style_class(style);
        });
        module.method("remove_style_class!", [](const StyleClass& style){
            StyleManager::remove_style_class(style);
        });
        module.method("style_manager_get_style_class!", [](const std::string& name) -> StyleClass{
            return StyleManager::get_style_class(name);
        });
        module.method("style_manager_add_css!", [](const std::string& css){
            StyleManager::add_css(css);
        });
        module.method("style_manager_color_to_css_rgba", [](float r, float g, float b, float a){
            return StyleManager::color_to_css(RGBA(r, g, b, a));
        });
        module.method("style_manager_color_to_css_hsva", [](float h, float s, float v, float a){
           return StyleManager::color_to_css(HSVA(h, s, v, a));
        });
        module.method("style_manager_define_color_rgba!", [](const std::string& name, float r, float g, float b, float a){
            StyleManager::define_color(name, RGBA(r, g, b, a));
        });
        module.method("style_manager_define_color_hsva!", [](const std::string& name, float h, float s, float v, float a){
            StyleManager::define_color(name, RGBA(h, s, v, a));
        });
        
        #define EXPORT_CSS_PROPERTY(NAME) module.set_const(jl_box_string(std::string("STYLE_PROPERTY_") + #NAME, STYLE_PROPERTY_##NAME));
        EXPORT_CSS_PROPERTY(FOREGROUND_COLOR)
        EXPORT_CSS_PROPERTY(COLOR)
        EXPORT_CSS_PROPERTY(BACKGROUND_COLOR)
        EXPORT_CSS_PROPERTY(OPACITY)
        EXPORT_CSS_PROPERTY(FILTER)
        EXPORT_CSS_PROPERTY(FONT)
        EXPORT_CSS_PROPERTY(FONT_FAMILY)
        EXPORT_CSS_PROPERTY(FONT_SIZE)
        EXPORT_CSS_PROPERTY(FONT_STYLE)
        EXPORT_CSS_PROPERTY(FONT_WEIGHT)
        EXPORT_CSS_PROPERTY(FONT_TRANSFORM)
        EXPORT_CSS_PROPERTY(CARET_COLOR)
        EXPORT_CSS_PROPERTY(TEXT_DECORATION)
        EXPORT_CSS_PROPERTY(TEXT_DECORATION_COLOR)
        EXPORT_CSS_PROPERTY(TEXT_SHADOW)
        EXPORT_CSS_PROPERTY(ICON_SIZE)
        EXPORT_CSS_PROPERTY(TRANSFORM)
        EXPORT_CSS_PROPERTY(BORDER)
        EXPORT_CSS_PROPERTY(BORDER_STYLE)
        EXPORT_CSS_PROPERTY(BORDER_COLOR)
        EXPORT_CSS_PROPERTY(BORDER_WIDTH)
        EXPORT_CSS_PROPERTY(BORDER_RADIUS)
        EXPORT_CSS_PROPERTY(OUTLINE)
        EXPORT_CSS_PROPERTY(OUTLINE_STYLE)
        EXPORT_CSS_PROPERTY(OUTLINE_COLOR)
        EXPORT_CSS_PROPERTY(OUTLINE_WIDTH)
        EXPORT_CSS_PROPERTY(BOX_SHADOW)
        EXPORT_CSS_PROPERTY(BACKGROUND_CLIP)
        EXPORT_CSS_PROPERTY(TRANSITION)
        EXPORT_CSS_PROPERTY(ANIMATION)
        EXPORT_CSS_PROPERTY(ANIMATION_NAME)
        EXPORT_CSS_PROPERTY(ANIMATION_DURATION)
        EXPORT_CSS_PROPERTY(ANIMATION_TIMING_FUNCTION)
        EXPORT_CSS_PROPERTY(ANIMATION_ITERATION_COUNT)
        EXPORT_CSS_PROPERTY(ANIMATION_DIRECTION)
        EXPORT_CSS_PROPERTY(ANIMATION_PLAY_STATE)
        EXPORT_CSS_PROPERTY(ANIMATION_DELAY)
        EXPORT_CSS_PROPERTY(ANIMATION_FILL_MODE)

        #define EXPORT_PRE_MADE_STYLE_CLASS_NAME(NAME) module.set_const(jl_box_string(std::string("STYLE_CLASS_") + #NAME, STYLE_CLASS_##NAME.get_name()));
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(SUGGESTED_ACTION);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(DESTRUCTIVE_ACTION);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(BUTTON_FLAT);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(BUTTON_RAISED);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(BUTTON_CIRCULAR);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(BUTTON_PILL);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(BOX_LINKED);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(TOOLBAR);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(DIMMED);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(FONT_HEADING_1);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(FONT_HEADING_2);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(FONT_HEADING_3);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(FONT_HEADING_4);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(FONT_LARGER);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(FONT_REGULAR);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(FONT_CAPTION_HEADING);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(FONT_CAPTION);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(FONT_MONOSPACE);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(FONT_NUMERIC);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(COLOR_ACCENT);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(COLOR_SUCCESS);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(COLOR_WARNING);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(COLOR_ERROR);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(ACTIVATABLE);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(CARD);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(LIST_VIEW_SIDEBAR);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(LIST_VIEW_RICH_LIST);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(LIST_VIEW_DATA_TABLE);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(LIST_VIEW_MENUBAR);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(ICON_DROPSHADOW);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(ICON_SMALL);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(CHECK_BUTTON_ROUND);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(ON_SCREEN_DISPLAY);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(BACKGROUND);
        EXPORT_PRE_MADE_STYLE_CLASS_NAME(VIEW);

        #define EXPORT_STYLE_TARGET(NAME) module.set_const(jl_box_string(std::string("STYLE_TARGET_") + #NAME, STYLE_TARGET_##NAME));
        EXPORT_STYLE_TARGET(SELF)

        // ActionBar

        EXPORT_STYLE_TARGET(ACTION_BAR)
        EXPORT_STYLE_TARGET(ACTION_BAR_BOX_START) // widgets added via `push_front`
        EXPORT_STYLE_TARGET(ACTION_BAR_BOX_END)     // widgets added via `push_back`

        // AspectFrame

        EXPORT_STYLE_TARGET(ASPECT_FRAME);

        // Box

        EXPORT_STYLE_TARGET(BOX);

        // Button

        EXPORT_STYLE_TARGET(BUTTON);
        EXPORT_STYLE_TARGET(BUTTON_PRESSED); // while click animation is playing

        // CenterBox

        EXPORT_STYLE_TARGET(CENTER_BOX);

        // CheckButton

        EXPORT_STYLE_TARGET(CHECK_BUTTON);
        EXPORT_STYLE_TARGET(CHECK_BUTTON_CHECK_MARK_ACTIVE)  // state is `ACTIVE`
        EXPORT_STYLE_TARGET(CHECK_BUTTON_CHECK_MARK_INCONSISTENT) // state is `INCONSISTENT`
        EXPORT_STYLE_TARGET(CHECK_BUTTON_CHECK_MARK_INACTIVE) // state is `INACTIVE`

        // ClampFrame

        EXPORT_STYLE_TARGET(CLAMP_FRAME);

        // ColumnView

        EXPORT_STYLE_TARGET(COLUMN_VIEW);

        // DropDown

        EXPORT_STYLE_TARGET(DROP_DOWN);

        // Entry

        EXPORT_STYLE_TARGET(ENTRY);
        EXPORT_STYLE_TARGET(ENTRY_TEXT);    // letters of entries text
        EXPORT_STYLE_TARGET(ENTRY_TEXT_SELECTION);    // selection indicator when selecting letters using cursor

        // Expander

        EXPORT_STYLE_TARGET(EXPANDER);
        EXPORT_STYLE_TARGET(EXPANDER_TITLE); // label widget
        EXPORT_STYLE_TARGET(EXPANDER_TITLE_ARROW);  // arrow indicator next to label

        // Fixed
        // no css targets

        // FlowBox

        EXPORT_STYLE_TARGET(FLOW_BOX);
        EXPORT_STYLE_TARGET(FLOW_BOX_CHILD);  // any child

        // Frame

        EXPORT_STYLE_TARGET(FRAME);

        // Grid

        EXPORT_STYLE_TARGET(GRID);

        // GridView

        EXPORT_STYLE_TARGET(GRID_VIEW);
        EXPORT_STYLE_TARGET(GRID_VIEW_CHILDREN);    // any child
        EXPORT_STYLE_TARGET(GRID_VIEW_SELECTED);   // child that is currently selected
        EXPORT_STYLE_TARGET(GRID_VIEW_NOT_SELECTED);   // child that is not currently selected

        // HeaderBar

        EXPORT_STYLE_TARGET(HEADER_BAR);

        // ImageDisplay

        EXPORT_STYLE_TARGET(IMAGE_DISPLAY);

        // Label

        EXPORT_STYLE_TARGET(LABEL);
        EXPORT_STYLE_TARGET(LABEL_SELECTION); // selection indicator area when `set_is_selectable` is set to `true`

        // LevelBar

        EXPORT_STYLE_TARGET(LEVEL_BAR);
        EXPORT_STYLE_TARGET(LEVEL_BAR_TROUGH);  // background of level bar, does not change with level bar value
        EXPORT_STYLE_TARGET(LEVEL_BAR_BLOCK_LOW);  // block area with value in [0%, 25%]
        EXPORT_STYLE_TARGET(LEVEL_BAR_BLOCK_HIGH); // block area with value in [25%, 75%]
        EXPORT_STYLE_TARGET(LEVEL_BAR_BLOCK_FULL); // block area with value in [75%, 100%]

        // ListView

        EXPORT_STYLE_TARGET(LIST_VIEW);
        EXPORT_STYLE_TARGET(LIST_VIEW_CHILDREN);  // any child
        EXPORT_STYLE_TARGET(LIST_VIEW_SELECTED); // child that is selected
        EXPORT_STYLE_TARGET(LIST_VIEW_NOT_SELECTED); // child that is not selected

        // MenuBar

        EXPORT_STYLE_TARGET(MENU_BAR);
        EXPORT_STYLE_TARGET(MENU_BAR_ITEM); // item in outermost menu model
        EXPORT_STYLE_TARGET(MENU_BAR_DISABLED_ITEM); // item in outermost menu mode
        EXPORT_STYLE_TARGET(MENU_BAR_SELECTED_ITEM);

        // Notebook

        EXPORT_STYLE_TARGET(NOTEBOOK);
        EXPORT_STYLE_TARGET(NOTEBOOK_TABS)
        EXPORT_STYLE_TARGET(NOTEBOOK_SELECTED_TAB)

        // Overlay

        EXPORT_STYLE_TARGET(OVERLAY);

        // Paned

        EXPORT_STYLE_TARGET(PANED);
        EXPORT_STYLE_TARGET(PANED_HANDLE);
        EXPORT_STYLE_TARGET(PANED_START_CHILD);
        EXPORT_STYLE_TARGET(PANED_END_CHILD);

        // Popover

        EXPORT_STYLE_TARGET(POPOVER);
        EXPORT_STYLE_TARGET(POPOVER_ARROW);

        // PopoverButton

        EXPORT_STYLE_TARGET(POPOVER_BUTTON);
        EXPORT_STYLE_TARGET(POPOVER_BUTTON_INDICATOR);

        // PopoverMenu

        EXPORT_STYLE_TARGET(POPOVER_MENU);
        EXPORT_STYLE_TARGET(POPOVER_MENU_ARROW);

        // ProgressBar

        EXPORT_STYLE_TARGET(PROGRESS_BAR);
        EXPORT_STYLE_TARGET(PROGRESS_BAR_EMPTY);
        EXPORT_STYLE_TARGET(PROGRESS_BAR_FULL);
        EXPORT_STYLE_TARGET(PROGRESS_BAR_TROUGH);
        EXPORT_STYLE_TARGET(PROGRESS_BAR_TEXT);
        EXPORT_STYLE_TARGET(PROGRESS_BAR_DURING_PULSE);

        // RenderArea

        // no css targets

        // Revealer

        EXPORT_STYLE_TARGET(REVEALER);

        // Scale

        EXPORT_STYLE_TARGET(SCALE);
        EXPORT_STYLE_TARGET(SCALE_TROUGH);
        EXPORT_STYLE_TARGET(SCALE_TROUGH_FILL);
        EXPORT_STYLE_TARGET(SCALE_SLIDER);
        EXPORT_STYLE_TARGET(SCALE_VALUE_TEXT);

        // ScrollBar

        EXPORT_STYLE_TARGET(SCROLLBAR);
        EXPORT_STYLE_TARGET(SCROLLBAR_TROUGH);
        EXPORT_STYLE_TARGET(SCOLLBAR_SLIDER);

        // Separator

        EXPORT_STYLE_TARGET(SEPARATOR);

        // SpinButton

        EXPORT_STYLE_TARGET(SPINBUTTON);
        EXPORT_STYLE_TARGET(SPINBUTTON_TEXT);
        EXPORT_STYLE_TARGET(SPINBUTTON_TEXT_SELECTION);
        EXPORT_STYLE_TARGET(SPINBUTTON_BUTTON_INCREASE);
        EXPORT_STYLE_TARGET(SPINBUTTON_BUTTON_DECREASE);

        // Spinner

        EXPORT_STYLE_TARGET(SPINNER); // only applied if set_is_spinning is true

        // Stack

        EXPORT_STYLE_TARGET(STACK);

        // StackSwitcher

        EXPORT_STYLE_TARGET(STACK_SWITCHER);

        // StackSidebar

        EXPORT_STYLE_TARGET(STACK_SIDEBAR);

        // Switch

        EXPORT_STYLE_TARGET(SWITCH);
        EXPORT_STYLE_TARGET(SWITCH_SLIDER);
        EXPORT_STYLE_TARGET(SWITCH_NOT_ACTIVE);
        EXPORT_STYLE_TARGET(SWITCH_ACTIVE);

        // TextView

        EXPORT_STYLE_TARGET(TEXTVIEW);
        EXPORT_STYLE_TARGET(TEXTVIEW_TEXT);
        EXPORT_STYLE_TARGET(TEXTVIEW_TEXT_SELECTION);
        /// \bug textview subnodes don't apply css correctly

        // TransformBin

        EXPORT_STYLE_TARGET(TRANSFORM_BIN);

        // ToggleButton

        EXPORT_STYLE_TARGET(TOGGLE_BUTTON);
        EXPORT_STYLE_TARGET(TOGGLE_BUTTON_ACTIVE);
        EXPORT_STYLE_TARGET(TOGGLE_BUTTON_NOT_ACTIVE);

        // Viewport

        EXPORT_STYLE_TARGET(VIEWPORT);
        EXPORT_STYLE_TARGET(VIEWPORT_HORIZONTAL_SCROLLBAR);
        EXPORT_STYLE_TARGET(VIEWPORT_HORIZONTAL_SCROLLBAR_TROUGH);
        EXPORT_STYLE_TARGET(VIEWPORT_HORIZONTAL_SCOLLBAR_SLIDER);
        EXPORT_STYLE_TARGET(VIEWPORT_VERTICAL_SCROLLBAR);
        EXPORT_STYLE_TARGET(VIEWPORT_VERTICAL_SCROLLBAR_TROUGH);
        EXPORT_STYLE_TARGET(VIEWPORT_VERTICAL_SCOLLBAR_SLIDER);

        // Window

        EXPORT_STYLE_TARGET(WINDOW);

        // Widget

        EXPORT_STYLE_TARGET(WIDGET);
    }
}
