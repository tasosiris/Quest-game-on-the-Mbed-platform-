## Project Overview

This repository contains the code for a top-down RPG game built on the Mbed platform. The game allows the player to navigate a map, interact with NPCs, fight enemies, and complete a quest using a Nav Switch and action buttons.

### Key Features

- **Player Movement**: Controls the player using the Nav Switch.
- **Map Navigation**: Displays a map larger than the screen, where only part of the map is shown at any time.
- **Hash Table**: Stores map objects and looks up their locations to display them correctly.
- **Quests and Interactions**: The player interacts with NPCs, fights enemies, and defeats a boss to complete a quest.
- **Game Logic**: Implements basic game mechanics such as movement, attacks, and item collection.

### Files

- `main.cpp`: Contains the main game loop and core logic.
- `hash_table.cpp` and `hash_table.h`: Implements the hash table used for storing and retrieving map items.
- `graphics.cpp`: Handles drawing the game elements to the screen.
- `map.cpp` and `map.h`: Manages map data and interactions.

## Installation

1. Import the project into the Mbed environment.
2. Compile and flash the code to your Mbed device.

## Game Flow

1. **Player Control**: Move the player character using the Nav Switch.
2. **Interactions**: Approach NPCs, enemies, or objects and press the action button to interact.
3. **Quest Progression**: Complete a quest by defeating enemies, collecting items, and defeating a boss.

## Advanced Features (Optional)

- Add a start page with options to view controls and start the game.
- Include sound effects or background music.
- Create animated interactions (e.g., moving NPCs or enemies).
- Implement an in-game menu for inventory or save-game features.

## Submission Requirements

- Export your project files (.c and .h) and compress them into a zip folder named `P2-2.zip`.
- Upload the zip file and the checklist to Canvas.
- Include your compiled `.bin` file.
- Provide a video demonstration via a YouTube link.

---

Any code not fully created and debugged by the student will be considered academic misconduct. Code must not be made publicly available.

