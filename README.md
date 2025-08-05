# Battleship AI 

A retro-style C++ Battleship game built with **SFML**, featuring a ruthless AI that doesn't just guess...it *hunts you down*. Experience tactical warfare in a 90s pixel-themed grid where every move matters.

---

##  Features

- Turn-based battleship gameplay with **SFML-powered 2D graphics**
- Smart AI that **tracks, locks, and destroys** your fleet once it detects a hit
- Beautifully styled **90s pixel interface** (green-on-black matrix feel)
- Manual ship placement with rotation support
- Clear mission-style narrative and objectives for immersion

---

##  AI Logic

This isn’t random firing. The AI behaves like a cold-blooded naval assassin.

1. Once it gets a **hit**, it checks **all 4 directions** (up, down, left, right).
2. When a second ship tile is hit, it **locks direction** and attacks in a straight line.
3. After sinking the ship, it returns to scanning.

> **Smart. Ruthless. Efficient.**

---

##  Controls

- `R` – Rotate the selected ship
- **Mouse Click** – Select tile
- `Enter` – Confirm placement

---


##  How to Run

### Requirements

- C++17 or later  
- SFML 2.5+  
- Visual Studio, Code::Blocks, or any IDE with SFML set up

### Build (Command Line)

```bash
g++ -std=c++17 -o battleship main.cpp Game.cpp Player.cpp AI.cpp -lsfml-graphics -lsfml-window -lsfml-system
./battleship
```

> Make sure SFML is properly linked if you're using an IDE like Visual Studio.

---

##  Mission Directive

> Agent, a rogue admiral has vanished with a fleet of deadly warships.  
> Your mission: track them down, outwit his forces, and stop him.  
> The world is counting on you. Deploy smart, strike hard, and win.  
> Show them who truly rules the seas.  
>  
> Good luck, Agent.

---

##  Coming Soon

- Sound effects and 90s retro audio  
- Difficulty levels for AI  
- Multiplayer mode  
- Ship hit animations  

---

## License

MIT – Fork, modify, conquer.

---



> Designed and developed by Alvira Rizwan.


