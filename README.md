# FPS Game Engine - C++

[🎮 **PLAY THE GAME NOW** →](https://github.com/karma-zeus/C-/)

---

A core FPS (First-Person Shooter) game engine implementation in C++ using OpenGL.

## Features

### Core Systems
- **Graphics Engine**: OpenGL-based rendering with shader support
- **Physics System**: Basic rigid body physics with gravity simulation
- **Input System**: Keyboard and mouse input handling with camera control
- **Entity System**: Player, Enemy, and Projectile entities
- **World System**: Level generation and object management
- **Audio Framework**: Ready for sound integration

### Gameplay Mechanics
- **First-Person Camera**: Mouse look and WASD movement
- **Combat System**: Projectile firing and enemy AI
- **Damage System**: Health tracking for player and enemies
- **Enemy AI**: Chase and attack behavior
- **HUD System**: Health, ammo, and kill counter display

## Requirements

- C++ 17 or later
- CMake 3.10 or later
- GLFW3
- OpenGL 3.3+
- GLM (header-only)

## Dependencies Installation

### Ubuntu/Debian
```bash
sudo apt-get install libglfw3-dev libglm-dev libgl1-mesa-dev
```

### macOS
```bash
brew install glfw glm
```

### Windows (with vcpkg)
```bash
vcpkg install glfw3 glm
```

## Building

```bash
mkdir build
cd build
cmake ..
make
./fps_game
```

## Controls

- **WASD**: Movement
- **Mouse**: Look around
- **Left Click**: Shoot
- **ESC**: Exit

## Project Structure

```
src/
├── main.cpp                 # Entry point
├── engine/
│   ├── game.h/cpp          # Main game loop
│   ├── window.h/cpp        # Window management
│   ├── input.h/cpp         # Input handling
│   └── camera.h/cpp        # Camera system
├── graphics/
│   ├── shader.h/cpp        # Shader compilation
│   ├── mesh.h/cpp          # Mesh rendering
│   └── renderer.h/cpp      # Rendering system
├── physics/
│   └── physics.h/cpp       # Physics simulation
├── entity/
│   ├── player.h/cpp        # Player entity
│   ├── enemy.h/cpp         # Enemy entity
│   └── projectile.h/cpp    # Projectile entity
└── world/
    └── world.h/cpp         # Level and world management
```

## Game Architecture

### Entity-Component Pattern
The game uses a component-based approach for flexibility and scalability.

### Game Loop
```
while (running) {
    handleInput()   // Process player input
    update()        // Update game state
    render()        // Render frame
}
```

## Next Steps to Enhance

1. **Advanced Graphics**
   - Texture mapping
   - Normal mapping
   - Shadow mapping
   - Particle effects

2. **Audio**
   - Background music
   - Sound effects
   - 3D spatial audio

3. **AI Improvements**
   - Pathfinding (A*)
   - State machines for behavior
   - Tactical awareness

4. **Networking**
   - Multiplayer support
   - Client-server architecture

5. **UI/UX**
   - Main menu
   - Settings panel
   - Level selection
   - Scoreboard

6. **Advanced Physics**
   - Collision detection
   - Ragdoll physics
   - Vehicle physics

## Performance Tips

- Use frustum culling to skip off-screen objects
- Implement level-of-detail (LOD) systems
- Use object pooling for projectiles and enemies
- Profile with tools like RenderDoc or NVIDIA Nsight

## License

MIT License - Feel free to use this for learning and projects!

## Contributing

Contributions are welcome! Please submit pull requests or open issues for bugs and features.

## References

- [OpenGL Tutorials](https://learnopengl.com/)
- [GLM Documentation](https://glm.g-truc.net/)
- [GLFW Documentation](https://www.glfw.org/docs/latest/)
