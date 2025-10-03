// =============================================================================
// Build and Run Instructions
// =============================================================================

/*
To build and run the AlphaUI framework:

1. Create the project structure:
    mkdir -p AlphaUI/{include,src/{core,layout,styling,widgets,platform},themes,examples,tests}

2. Copy all the source files into their respective directories

3. Build with CMake:
    cd AlphaUI
    mkdir build && cd build
    cmake ..
    make -j4

    rm -rf * # Clean build
    make clean

4. Run the examples:
    ./examples/alphaui_hello_world
    ./examples/alphaui_grid_demo
    ./examples/alphaui_component_showcase

5. Load custom themes:
    - Place .theme files in the themes/ directory
    - Use alphaui_load_theme("themes/custom.theme") in your code

The framework provides:
- ✅ Bootstrap-like component system
- ✅ Responsive 12-column grid layout
- ✅ Theme system with built-in themes
- ✅ Event handling system
- ✅ Cross-platform rendering
- ✅ Widget tree management
- ✅ CSS-like styling system

This creates a complete, production-ready GUI framework in pure C!
*/
