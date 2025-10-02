# snake-in-C

A simple terminal Snake game written in **C** using **ncurses**. Cross‑platform on UNIX‑like systems (Linux/macOS). Tested with `gcc`.  
Repo includes `Main.c` and `headerf.h`.

## Requirements

- C compiler (e.g., `gcc`/`clang`)
- **ncurses** development headers
  - Ubuntu/Debian: `sudo apt-get install libncurses5-dev` (or `libncurses-dev`)
  - macOS (Homebrew): `brew install ncurses` and use `-I`/`-L` if needed
- (Windows) Use MSYS2/WSL or link against **PDCurses**

## Build & Run

From the repo root:

```bash
# Linux/macOS
gcc Main.c -o snake -lncurses
./snake
```

> The original quick tip in the repo: `gcc Main.c -o Main -lncurses && ./Main` (same idea).

If Homebrew ncurses is not found on macOS:

```bash
gcc Main.c -o snake -I/opt/homebrew/include -L/opt/homebrew/lib -lncurses
./snake
```

## Controls

- **Arrow keys** to steer the snake
- **Any key** to start a new run (as noted in the repo’s Readme)

## Gameplay

- Eat food to grow and increase score
- Game over on self‑collision or hitting a wall
- Terminal redraw handled via `ncurses` for smooth movement

## Project files

- `Main.c` — game loop, rendering, input handling
- `headerf.h` — shared declarations/macros
- `.gitignore`, `Readme.txt` — housekeeping / basic usage

## Notes / Tips

- Terminal size matters; use a standard 80×24 or larger
- If input feels sluggish, ensure the code uses non‑blocking getch (`nodelay`) and your terminal app doesn’t intercept arrows

