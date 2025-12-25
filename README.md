# Blackjack (C)

This is a simple **Blackjack (21) game** written in **C**, developed as a
personal project

The program implements the core mechanics of Blackjack with an
interactive terminal interface, allowing the player to play against
the dealer following standard rules.

---

## Features

- Single-player Blackjack against the dealer
- Random card generation
- Automatic handling of:
  - Dealer rules (hits until 16)
  - Blackjack detection
  - Bust conditions
- Correct Ace handling (1 or 11)
- Clear turn-based game flow
- Simple text-based interface

---

## Missing / Planned Features

The following features are **not implemented yet** and were intentionally
left out for simplicity:

- Betting system
- Split
- Double down
- Multiple decks
- Persistent balance / save system

---

## How It Works

- Cards are generated randomly
- Each card has:
  - A value (1–10)
  - A suit (clubs, spades, diamonds, hearts)
- The player can:
  - Hit (draw a card)
  - Stand
- The dealer draws cards automatically following Blackjack rules
- The winner is decided based on standard Blackjack scoring

---

## Build and Run

### Linux / macOS

```bash
gcc blackjack.c -o blackjack
./blackjack
```

### Windows
```bash
gcc blackjack.c -o blackjack.exe
blackjack.exe
```

## Author

ShiroiShi  
Computer Science student 
