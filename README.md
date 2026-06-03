# Design-Pattern-C-Kelompok-3

Omar Ginza/5224600063<br>
Muhammad Firdaus El Ghaby/5224600068

---

# Project: Balatro-Inspired Poker Game (C++)

A C++17 poker-based deck-building roguelike inspired by Balatro, featuring unique Joker effects and a dynamic blind system.

## Project Overview

*   **Language:** C++17
*   **Architecture:** Heavily driven by Design Patterns for modularity and extensibility.
*   **Key Mechanics:**
    *   **Scoring:** Uses a "Chips x Mult" formula. Hand ranks have base stats that are combined with individual card values.
    *   **Blind System:** Players progress through Small, Big, and Boss Blinds across multiple Antes.
    *   **Jokers:** Unique cards providing passive bonuses. Managed by a Shop system.
    *   **Shop:** Appears after clearing blinds, offering Jokers for purchase.
    *   **Skip Blind:** Players can skip blinds to receive "Skip Tags" (delayed rewards) instead of playing them.

## Design Patterns

*   **State Pattern (`BlindState`):** Manages transitions between `SmallBlindState`, `BigBlindState`, and `BossBlindState`. Each state dictates target score, reward, and transition logic.
*   **Chain of Responsibility (`PokerHandChecker`):** A sequence of checkers (`FlushHouseChecker`, `FiveOfAKindChecker`, ..., down to `HighCardChecker`) detects the highest possible poker hand rank in a set of played cards.
*   **Simple Factory Pattern (`ShopSystem::makeJoker`):** Instantiates Joker objects based on an ID without exposing the object creation logic to the rest of the game loop.
*   **Command Pattern (`RewardCommand`):** Encapsulates rewards (like Skip Tags) as objects that can be queued in `SessionState` and executed at specific timings (`RewardTiming::Start`, `RewardTiming::NextBlind`).

## 1. Class Diagram (Balatro C++ Architecture)

Semua komponen saling terhubung melalui `GameManager` dan `SessionState` sebagai orchestrator utama. Relasi antar pattern (State, Command, Factory, CoR) digambarkan di bawah ini:

```text
+---------------------------------------------------------------------------------------------------+
|                                          GameManager                                              |
|            (Central Hub: Orchestrates the game loop, deals hands, and handles phases)             |
+-------+---------------+---------------+---------------+---------------+---------------+-----------+
        |               |               |               |               |               |
+-------v-------+ +-----v-----+ +-------v-------+ +-----v-----+ +-------v-------+ +-----v-------+
| HandGenerator | | HandPlayer| |  BlindState   | |ShopSystem | |  ScoringRule  | | SessionState|
+-------+-------+ +-----+-----+ +-------+-------+ +-----+-----+ +-------+-------+ +-------------+
|               |       |       |               | |           | | - checkers    | |- money      |
+---------------+       |       +---------------+ +-----------+ +-------+-------+ |- pending_cmds
        |               |               |               |               |         |- current_ante
        | deals         | selects       | manages       | uses          | owns    +-------------+
        |               |               |               |               |
+-------v---------------v---------------v---------------v---------------v---------------------------+
|                                             Hand                                                  |
|                        (Core Data: Struct containing vector of Cards)                             |
+---------------------------------------+-----------------------------------------------------------+
                                        |
        +-------------------------------+---------------------------------------+
        |                                                                       |
+-------v-------+                                            +------------------v-----------------+
|  BlindState   |                                            |           ScoringRule            |
+---------------+                                            +------------------+-----------------+
| (Small, Big,  |                                            | - jokerManager   | - checkers (CoR)|
| Boss States)  |                                            +--------+---------+--------+--------+
+-------+-------+                                                     |                  |
        |                                                             | owns             | uses
        | creates                                                     |                  |
        |                                                    +--------v-------+  +-------v--------+
+-------v-------+                                            |  JokerManager  |  |PokerHandChecker|
| RewardCommand |                                            +--------+-------+  +----------------+
+---------------+                                            | - jokers       |  | (Pair, Flush)  |
| (Skip Tags)   |                                            +--------+-------+  +----------------+
+-------+-------+                                                     |
        |                                                             | holds polymorphic objects
        | queued in                                                   |
        |                                                    +--------v-------+   +-------------------+
+-------v-------+                                            |      Joker     |<--|    ShopSystem     |
| SessionState  |                                            +--------+-------+   +-------------------+
+---------------+                                            | AbstractJoker, |   | (makeJoker factory|
| - money       |                                            | PairJoker, etc |   +-------------------+
| - pending_cmds|                                            +----------------+
+---------------+
```

## 2. Runtime Walkthrough (1 Ante Example)

**Ante 1 Start**
- `SessionState` initializes `current_ante` = 1 and sets the state to `SmallBlindState`.

**Small Blind Phase**
```text
=== Ante 1 - Small Blind ===
Target Score: 300
Skip Reward: [Generated by SmallBlindState]
Do you want to PLAY or SKIP?
Choice: SKIP
Skipping Small Blind...
Generated Skip Reward Command. (Stored in SessionState)
```

**Big Blind Phase**
```text
=== Ante 1 - Big Blind ===
[Commands Executed] Pending commands from Small Blind are triggered (e.g. Free Playing Card).
Target Score: 450 | Remaining Plays: 4
... Player plays hand ...
Calculating hand score...
Success! Target reached.
... Shop opens ...
```

**Boss Blind Phase**
```text
=== Ante 1 - Boss Blind ===
Target Score: 600 | Remaining Plays: 4
... Player wins ...
Success! Target reached.
... Shop opens ...
... Increment Ante to 2 (handled by BossBlindState transitioning to SmallBlindState of next ante) ...
```

## 3. Data Lifecycle Analysis

| Variable | Scope | Lifecycle | Reset/Update Logic |
| :--- | :--- | :--- | :--- |
| `money` | `SessionState` | Persistent (Run) | Increased by clearing blinds (`calculateAndAddReward`). Decreased in `ShopSystem`. |
| `current_ante` | `SessionState` | Persistent (Run) | Incremented naturally when transitioning from Boss Blind to Small Blind. |
| `base_plays` | `SessionState` | Persistent (Run) | Default value (4) used as base for `remaining_plays`. |
| `remaining_plays` | `SessionState` | Local (Blind) | Resets to `base_plays` at the start of every Played Blind. |
| `pending_commands`| `SessionState` | Transitory | Commands added during SKIP. Executed and cleared at `RewardTiming::NextBlind` or `RewardTiming::Start`. |
| `jokers` | `JokerManager` | Persistent (Run) | Added via `ShopSystem`. Persistent until game over (max 5 slots). |
| `current_blind_state` | `SessionState` | Dynamic | Changes from `SmallBlindState` -> `BigBlindState` -> `BossBlindState` -> `SmallBlindState` (next Ante). |

## 4. Key Mechanics Summary

*   **Scoring:** Formula: `(Base Chips + Card Chips) * Base Mult`.
*   **Jokers:** Unique instances, added to `JokerManager` and modify the `ScoreContext` during hand evaluation. They are generated via `ShopSystem::makeJoker`.
*   **Skip Tags:** Reward commands generated by the current `BlindState`. Queued in `SessionState` and executed at specific timing hooks.
*   **Chain of Responsibility:** Used by `ScoringRule` to evaluate hand combinations sequentially from highest (Flush House) to lowest (High Card).
*   **Shop:** Offers 3 random Jokers out of the available pool for $4 each.

## 5. Building and Running

### Build Command
To compile the game, navigate to the `Chapter1_CoreLoop` directory 

cd "C:\Users\firo1\OneDrive\Documents\GitHub\New folder\Design-Pattern-C-Kelompok-3\Chapter1_CoreLoop"

and run the following command using `g++` (requires GCC/MinGW):

```bash
g++ -std=c++17 -I. -I./checker_card *.cpp checker_card/*.cpp -o run.exe
```

### Execution
```batch
.\run.exe
```

## Core Components

*   **`GameManager`**: The central orchestrator that runs the game loop, handles player input for PLAY/SKIP, and triggers transitions.
*   **`SessionState`**: Holds the runtime data such as money, current ante, the current blind state, and pending reward commands.
*   **`ScoringRule`**: Evaluates poker hands using the Chain of Responsibility checkers, tracks base chips/mults, and applies Joker effects via `JokerManager`.
*   **`ShopSystem`**: Manages the shop interface, offering randomized Jokers and allowing players to spend `money`.
*   **`BlindState` (and children)**: Defines the rules for each blind (target score, reward money, skip tags) and determines the next state.

