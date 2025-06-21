FPS Box Destruction Game – JSON-Driven Dynamic Spawning (UE5 C++)


🎯 Overview
This is a First-Person Shooter (FPS) project built entirely in Unreal Engine C++ (no plugins or external libraries). The game dynamically spawns damageable colored boxes using JSON data fetched from a remote URL, 
and integrates complete combat, damage, UI, and score systems using clean, modular architecture.
.
✅ Key Features
🔗 A) Online JSON Data Fetching (Native HTTP & JSON API)

Fetches structured box data from:
https://raw.githubusercontent.com/CyrusCHAU/Varadise-Technical-Test/refs/heads/main/data.json
.
.
📦 B) Dynamic Box Spawning

Boxes are spawned every 3 seconds based on JSON data.
Box behavior and properties (color, health, score value) are controlled entirely from fetched data.
.
.
🎨 C) Custom Material Support

A single material instance with a color parameter is used.
Each box sets its material color at runtime via C++ to match its JSON-defined color value.
.
.
🔫 D) Bullet and Shooting System

FPS_Character handles:

Movement

Gun equip

Shooting input

Gun class: Spawns bullets aimed at the center of the screen.

Bullet class: Detects hits via line trace or projectile logic

Deals 1 point of damage per hit

Destroys boxes when health reaches zero

Triggers score update for the player
.
.
🧱 E) Damageable Boxes

FloatingBox class:

Receives all data from the JSON structure

Handles color material assignment

Tracks its health and calls destruction logic

Health and destruction fully driven from code-side logic
.
.
🖥️ F) UI & Score Tracking (UMG + C++)

Two C++-based widgets:

Score Widget (attached to player) updates in real time

Box Health Widget (attached to each box) displays current health

UMG used only for layout — logic is entirely in C++
