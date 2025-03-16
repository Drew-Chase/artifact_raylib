# Artifact Project C++ Style Guide

## Table of Contents
1. [File Organization](#file-organization)
2. [Naming Conventions](#naming-conventions)
3. [Formatting](#formatting)
4. [Classes and Structs](#classes-and-structs)
5. [Functions](#functions)
6. [Variables](#variables)
7. [Constants](#constants)
8. [Comments](#comments)
9. [Error Handling](#error-handling)
10. [Memory Management](#memory-management)
11. [Namespace Usage](#namespace-usage)

## File Organization

- Header files use `.h` extension
- Implementation files use `.cpp` extension
- Each class should be declared in its own header file with the same name as the class (lowercase with underscores)
- Include guards should use `#pragma once`
- Organize related files in meaningful directories (e.g., `entities/`, `stages/`, `ui/`)
- Headers should include only what they need for declarations
- Implementation files should include their corresponding header first

## Naming Conventions

### General
- Use lowercase with underscores (`snake_case`) for all identifiers except constants
- Be descriptive and avoid abbreviations unless widely understood

### Files
```
player_entity.h
player_entity.cpp
```

### Classes and Structs
- Use `PascalCase` (capitalize first letter of each word)
```c++
class PlayerEntity
class SpriteSheet
```

### Functions and Methods
- Use `snake_case` (all lowercase with underscores between words)
```c++
void startup()
void apply_horizontal_movement(float deltaTime)
void get_formatted_frame_path(const int frame_number)
```

### Variables
- Use descriptive `snake_case` names
```c++
float walk_speed = 300.0f;
bool is_playing;
std::vector<Texture2D> frames;
```

### Member Variables
- Use `snake_case` without prefixes or suffixes
```c++
float walk_speed;
bool is_grounded;
```

### Parameters
- Use `snake_case` just like variables
```c++
void draw(const Vector2 position, const float scale = 1.0f, const Color tint = WHITE) const;
```

### Constants and Enums
- Use `snake_case` for constants as well
```c++
constexpr int framerate = 8;
constexpr float MAX_DELTA_TIME = 0.05f;
```

## Formatting

### Indentation
- Use 4 spaces for indentation, not tabs

### Braces
- Opening braces go on the next line for namespaces, classes, and functions
- Opening braces go on the same line for control statements (if, for, while, etc.)
- Always use braces for control statements, even single-line bodies

```c++
namespace artifact
{
    class SpriteSheet
    {
    public:
        void update(const float delta_time)
        {
            if (!is_playing || frames.empty()) {
                return;
            }
        }
    };
}
```

### Line Length
- Aim for a maximum line length of 120 characters
- Break lines after operators in long expressions

### Spacing
- Use spaces after keywords (`if`, `for`, `while`, etc.)
- Place spaces around binary operators
- No space between function name and opening parenthesis
- No spaces inside parentheses
- Add a space after commas in parameter lists

```c++
if (condition) {
    x = y + z;
    function_call(arg1, arg2);
}
```

## Classes and Structs

### Member Access
- Use `public`, `protected`, and `private` access modifiers explicitly
- Group members by access level, starting with private
- Within each access level group, organize variables first, then methods

### Constructors and Destructors
- Place constructors and destructors together near the beginning of the class definition
- Initialize member variables using the initializer list syntax when appropriate

```c++
SpriteSheet::SpriteSheet(const std::string& root_path, const int frame_count, const float fps)
    : root_path(root_path)
    , frame_count(frame_count)
    , fps(fps)
    , frame_time(1.0f / fps)
    , current_time(0.0f)
    , current_frame(0)
    , is_playing(true)
{
    frames.resize(frame_count);
    load_frames();
}
```

### Inheritance
- Specify inheritance access modifier explicitly
- Use `final` keyword when appropriate for classes not meant to be inherited from

```c++
class PlayerEntity final : public Entity
```

## Functions

### Parameters
- Pass by const reference for non-primitive types that should not be modified
- Pass by value for primitive types and small objects
- Pass by non-const reference only when the function needs to modify the parameter
- Use const for methods that don't modify object state

```c++
void draw(const Vector2 position, const float scale = 1.0f, const Color tint = WHITE) const;
void set_frame(const int frame_index);
```

### Return Values
- Prefer return by value for small objects
- Use return by reference only when necessary (e.g., chaining operations)

### Function Overloading
- Use function overloading for functions that perform similar operations but with different parameters

```c++
void draw(const Vector2 position, const float scale, const Color tint) const;
void draw(const float x, const float y, const float scale, const Color tint) const;
```

## Variables

### Declaration
- Declare variables as close as possible to their first use
- Initialize variables at declaration whenever possible
- One variable per declaration line

### Scope
- Keep variable scope as narrow as possible

## Constants

### Constant Expressions
- Use `constexpr` for values that can be determined at compile time

```c++
constexpr int framerate = 8;
constexpr int button_height = 70;
```

### Magic Numbers
- Avoid using magic numbers directly in code; use named constants instead

## Comments

### General Style
- Use `//` for single-line comments
- Use `/* */` for multi-line comments when needed
- Place comments on their own line before the code they describe
- Keep comments up to date when code changes

### Documentation Comments
- Document public interfaces including classes, methods, and functions
- Include purpose, parameters, return values, and any exceptions that may be thrown

## Error Handling

### Error Checking
- Check function return values and handle errors appropriately
- Use assertions for conditions that should never occur
- Prefer exceptions for exceptional conditions that cannot be handled locally

```c++
if (instance != nullptr)
    throw std::runtime_error("Game::run(): Game instance already exists");
```

## Memory Management

### Resource Management
- Use RAII (Resource Acquisition Is Initialization) principles
- Prefer smart pointers over raw pointers when ownership is involved
- Always clean up resources in destructors

```c++
std::unique_ptr<ButtonComponent> start_button;
```

### Manual Resource Management
- When manual resource management is necessary (e.g., raylib resources), ensure proper cleanup in destructors

```c++
SpriteSheet::~SpriteSheet()
{
    unload_frames();
}
```

## Namespace Usage

- Place all project code in the `artifact` namespace
- Don't use `using namespace` directives in header files
- Use namespace blocks rather than individual namespace prefixes

```c++
namespace artifact
{
    // Code
}
```
