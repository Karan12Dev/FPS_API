FPS Box Destruction Game – JSON-Driven Dynamic Spawning (UE5 C++)


🎯 Overview

This is a First-Person Shooter (FPS) project built entirely in Unreal Engine C++. The game dynamically spawns damageable colored boxes using JSON data fetched from a remote URL, 
and integrates complete combat, damage, UI, and score systems using clean, modular architecture.

|

✅ Key Features

🔗 A) Online JSON Data Fetching
Fetches box data from:
https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json

Uses only native Unreal C++ (FHttpModule, FJsonModule).

|

📦 B) Dynamic Box Spawning

Boxes are spawned every 3 seconds after fetching JSON data.

Uses a simple UE box mesh and dynamically changes its color.

Properties (health, score, color) are driven by data.

|

🎨 C) Custom Material & Color Logic

Custom material instance uses a parameterized color vector.

Box color is set in C++ at runtime using UMaterialInstanceDynamic.

|

🔫 D) Bullet and Shooting Mechanics

Player shoots bullets via the gun actor.

Bullets are aimed toward the center of the screen using a trace.

Bullet hits:

Reduce the box’s health by 1

Destroy the box if health reaches 0

Award score to the shooter

|

🧱 E) Damageable Boxes

Each box stores and updates:

Health

Color

Score value

Boxes are destroyed when health reaches zero.

Score is transferred to the bullet owner (the player).

|

🖥️ F) Score & Health UI (UMG + C++)

Two UUserWidget-derived C++ widgets:

Score Widget for the player's score

Health Widget shown above each box

Blueprint can be used to arrange layout, but logic is in C++.

|

🎮 AFPS_GameModeBase

Controls JSON data fetching and spawning logic.

Retrieves data using FHttpModule.

Parses JSON using TSharedPtr<FJsonObject>.

Spawns boxes dynamically every 3 seconds.

Passes parsed data to each spawned AFloatingBox.

|

🔫 AGun

Spawns bullets and handles targeting logic.

Fires bullets with input from the player.

Targets center of the screen using GetPlayerController() and viewport size.

Sets bullet owner for score handling.

|

💥 ABullet

Applies damage and awards score.

Detects hits via OnHit or line trace.

Applies 1 damage to boxes.

Destroys itself on impact.

Awards score to the owning character.

|

🧍 AFPS_Character

Handles movement, aiming, and scoring.

Controls player input and movement.

Equips gun on spawn.

Tracks and updates player's score.

Interfaces with UScoreWidget to update UI.

|

🧊 AFloatingBox

The box actor driven by JSON data.

Accepts and stores JSON values (color, health, score).

Applies material color via dynamic material instance.

Updates UI widget for current health.

Destroys itself on zero health.

|

🖼️ UScoreWidget & UBoxHealthWidget

Real-time HUD updates

UScoreWidget: Displays the current score of the player.

UBoxHealth: Floats above boxes showing current health.

Created in C++, designed in Blueprint.
