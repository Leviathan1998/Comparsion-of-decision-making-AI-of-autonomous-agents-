# Autonomous Agent Decision-Making Testbed

> **Bachelor's Thesis Project | Unreal Engine 5 | C++ | Artificial Intelligence**

An experimental Unreal Engine 5 testbed for implementing and comparing different decision-making architectures for autonomous game agents.

The project is being developed as part of my Bachelor's thesis at **Tomas Bata University in Zlín**. Its primary goal is to implement multiple AI decision-making approaches within a common environment and evaluate their behavior using measurable performance metrics.

The project currently focuses on three approaches:

- **Finite State Machine (FSM)**
- **Behavior Tree (BT)**
- **Goal-Oriented Action Planning (GOAP)**

> **Project Status:** Work in Progress  
> The project is under active development. Systems, environments, assets, and implementation details may change as development progresses.

---

## Project Overview

Autonomous agents in games can use different approaches to select actions and react to changes in their environment.

This project provides a common Unreal Engine 5 environment in which multiple decision-making architectures can be implemented, tested, and compared under similar conditions.

The main objectives are:

- implement autonomous agents using FSM, Behavior Trees, and GOAP;
- provide agents with comparable tasks and environmental conditions;
- collect quantitative data about agent behavior;
- evaluate differences between the decision-making approaches;
- provide tools for observing and testing agent behavior.

The project is intended primarily as a technical and experimental environment rather than a complete game.

---

## Decision-Making Systems

### Finite State Machine

The FSM agent uses explicitly defined states and transitions to determine its current behavior.

This approach provides a relatively simple and predictable architecture and serves as one of the baseline decision-making models in the comparison.

**Focus:**

- state-based behavior;
- explicit transitions;
- predictable decision logic;
- relatively low architectural complexity.

---

### Behavior Tree

The Behavior Tree agent uses Unreal Engine's AI framework to organize decision-making into a hierarchical structure.

The implementation makes use of Unreal Engine AI systems such as:

- Behavior Trees;
- Blackboards;
- AI Controllers;
- navigation and movement tasks;
- conditions and task execution.

This architecture allows more complex behavior to be represented through reusable and hierarchical decision logic.

---

### Goal-Oriented Action Planning

The GOAP agent is designed around goals, actions, world states, and planning.

Instead of following a predefined sequence of states, the agent evaluates available actions and constructs a plan capable of transforming the current world state into a state satisfying the selected goal.

The system is intended to include concepts such as:

- world state representation;
- goals;
- actions;
- action preconditions;
- action effects;
- action costs;
- dynamic plan generation.

GOAP is being developed as the most planning-oriented architecture included in the comparison.

---

## Experimental Environment

The agents operate inside a shared Unreal Engine test environment designed to provide comparable scenarios for all decision-making architectures.

The environment includes or is planned to include:

- autonomous AI agents;
- navigation using Unreal Engine's navigation system;
- interactable world objects;
- agent objectives and tasks;
- procedural environment elements;
- repeatable testing scenarios;
- runtime visualization of agent behavior.

The environment itself is still under development and currently contains placeholder and experimental assets.

Visual presentation is therefore **not representative of the final version of the project**.

---

## Metrics and Data Collection

One of the primary goals of the project is to compare the implemented architectures using quantitative measurements rather than visual observation alone.

The testbed is designed to collect metrics including:

| Metric | Description |
|---|---|
| **Completion Time** | Time required by an agent to complete a task |
| **Path Length** | Total distance travelled during task execution |
| **Collisions** | Number of detected collisions during a test |
| **Success Rate** | Percentage of successfully completed scenarios |

Experimental results can be exported using **CSV logging** for further processing and comparison.

Additional metrics may be introduced as the experimental methodology develops.

---

## Technical Features

The project currently includes or is being developed around the following systems:

- Unreal Engine AI framework;
- C++ gameplay and AI programming;
- AI Controllers;
- Behavior Trees;
- Blackboard data;
- navigation and pathfinding;
- autonomous agent behavior;
- interactable world objects;
- procedural environment generation;
- runtime agent information;
- performance metric collection;
- CSV data logging.

---

## Technologies

### Core

- **Unreal Engine 5**
- **C++**
- Unreal Engine AI Framework
- Unreal Engine Navigation System

### AI

- Finite State Machines
- Behavior Trees
- Blackboards
- Goal-Oriented Action Planning

### Development

- Visual Studio
- Git / GitHub
- Blender

---

## Repository Structure

The repository primarily contains the source code and configuration required to demonstrate the technical implementation of the project.

```text
.
├── Config/                 # Unreal Engine project configuration
├── Content/                # Selected project assets and UE resources
├── Source/                 # C++ source code
│   └── MyProject4/
│       ├── ...
│       └── ...
├── MyProject4.uproject     # Unreal Engine project descriptor
├── .gitignore
└── README.md
```

Generated Unreal Engine directories such as `Binaries`, `DerivedDataCache`, `Intermediate`, and `Saved` are intentionally excluded from version control.

Some third-party visual assets may also be excluded from the public repository.

---

## Current Development Status

The project is actively being developed as a Bachelor's thesis.

Current development focuses on implementing and integrating the decision-making systems, establishing common testing scenarios, and collecting comparable experimental data.

Some systems are functional while others remain under development.

The repository should therefore be considered an **experimental work-in-progress project**, not a finished production game.

---

## Planned Development

Development is expected to include further work on:

- FSM implementation and refinement;
- Behavior Tree scenarios;
- GOAP planning and action selection;
- common testing scenarios for all three architectures;
- automated metric collection;
- experimental data logging;
- agent debugging and visualization tools;
- test environment improvements;
- simple user interface for controlling experiments;
- test console for configuring and running scenarios;
- analysis of experimental results.

---

## Academic Context

This project is being developed as part of a Bachelor's thesis focused on the comparison of decision-making models for autonomous agents.

**Thesis topic:**  
*Comparison of Decision-Making Models for Autonomous Agents*

**University:**  
Tomas Bata University in Zlín

**Field:**  
Intelligent Systems with Robots

The project investigates both theoretical properties and practical behavior of different AI architectures by implementing them within the same Unreal Engine environment.

---

## Screenshots and Demonstration

Screenshots and video demonstrations will be added as the project environment and visual assets reach a more representative stage of development.

Current environment models and visual assets are primarily placeholders and are subject to change.

---

## Author

**Ján Lušňák**

Software Development / Intelligent Systems Student  
C++ • Unreal Engine 5 • Artificial Intelligence • Game Development

GitHub:

- [Leviathan1998](https://github.com/Leviathan1998)
- [janlu12](https://github.com/janlu12)

---

## Disclaimer

This repository represents an academic project currently under active development.

The repository may not contain all visual assets used during development, particularly third-party or licensed assets that cannot be redistributed.

Implementation details, project structure, experimental methodology, and features may change throughout development.
