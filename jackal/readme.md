# Jackal Pup Game Engine

## Realm System

### Important facts

Realm System must keep objects grouped together based on MeshIds.

## Render System

Uses a Ring or Circular style Shader Storage Buffer Object(SSBO).

## Main Game Loop

`PollEvents()`: Check for user input

`Update()`: The game state within Realm system is updated. This handles any actions triggered by player or the game app.

`CraftFrame()`: The FrameData_t is passed into the Realm system where object data is converted to model data ready to be rendered

`Render()`: Handles submitting model data to gpu for rendering

`SwapBuffers()`:
