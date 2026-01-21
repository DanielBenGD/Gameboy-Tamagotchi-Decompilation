# Tamagotchi Game Boy - Complete Decompilation Project

## Project Goal
100% accurate decompilation of Tamagotchi (USA, Europe) (SGB Enhanced) with:
- All code converted to readable C/C++
- All assets extracted and documented
- Byte-perfect matching build
- Full understanding of game mechanics

## ROM Information
- Size: 512 KB (32 ROM banks × 16KB)
- RAM: 8 KB (battery-backed save)
- Cartridge: MBC1+RAM+BATTERY
- SGB Enhanced: Yes

---

## PHASE 1: FUNCTION IDENTIFICATION ✓ (In Progress)

### Entry Point Analysis (0x0100-0x01FF)
- [x] Located entry point at 0x0150
- [x] Identified memset_zero function (0x034d)
- [ ] Rename all functions in entry()
- [ ] Map out initialization sequence

### Critical Functions to Find:
1. **Memory Functions** (High Priority)
   - [x] 0x034d - memset_zero(address, size)
   - [ ] 0x031b - init_hardware()
   - [ ] memcpy equivalent
   - [ ] DMA transfer functions

2. **Graphics Functions** (High Priority)
   - [ ] VBlank handler
   - [ ] Sprite rendering
   - [ ] Tile loading
   - [ ] Background update
   - [ ] SGB border/palette setup

3. **Input Functions** (High Priority)
   - [ ] Joypad reading (0xFF00)
   - [ ] Button state tracking
   - [ ] Input debouncing

4. **Game Logic Functions** (Core Gameplay)
   - [ ] Main game loop
   - [ ] State machine handler
   - [ ] Tamagotchi status update (hunger, happiness, age)
   - [ ] Time/clock system
   - [ ] Evolution logic
   - [ ] Death conditions
   - [ ] Mini-games

5. **Save System** (Critical)
   - [ ] Save data format
   - [ ] Save to RAM function
   - [ ] Load from RAM function
   - [ ] Checksum validation

6. **Sound Functions**
   - [ ] 0x0266 - Sound initialization
   - [ ] Music playback
   - [ ] SFX playback

7. **Bank Switching**
   - [ ] 0x4000 - Bank 6 loader (graphics?)
   - [ ] Bank management functions
   - [ ] Asset loading by bank

---

## PHASE 2: ASSET EXTRACTION

### Graphics Assets
**Location: Check ROM banks 1-31**

1. **Tile Data** (8x8 pixel tiles)
   - [ ] Extract all tile sets
   - [ ] Convert to PNG format
   - [ ] Document tile IDs

2. **Sprite Data**
   - [ ] Tamagotchi creatures (egg, baby, child, teen, adult forms)
   - [ ] UI elements
   - [ ] Menu graphics
   - [ ] Mini-game sprites
   - [ ] Icons (food, toilet, medicine, etc.)

3. **Background Maps**
   - [ ] Main screen layout
   - [ ] Menu screens
   - [ ] Mini-game backgrounds

4. **SGB Data**
   - [ ] Super Game Boy border
   - [ ] SGB color palettes
   - [ ] SGB commands

### Audio Assets
1. **Music Tracks**
   - [ ] Menu music
   - [ ] Gameplay music
   - [ ] Mini-game music

2. **Sound Effects**
   - [ ] Button press
   - [ ] Tamagotchi calls
   - [ ] Evolution sound
   - [ ] Death sound
   - [ ] Eating sounds
   - [ ] Game over

### Text/String Data
- [ ] Extract all text strings
- [ ] Menu text
- - [ ] Dialog text
- [ ] Character names

---

## PHASE 3: CODE STRUCTURE MAPPING

### Memory Map Documentation
```
0x0000-0x00FF: Interrupt vectors & RST handlers
0x0100-0x014F: ROM header
0x0150-0x3FFF: ROM Bank 0 (fixed) - Core engine code
0x4000-0x7FFF: ROM Bank 1-31 (switchable) - Assets & game logic
0x8000-0x9FFF: VRAM - Tile data & maps
0xA000-0xBFFF: External RAM - Save data
0xC000-0xDFFF: Work RAM - Game variables
0xFE00-0xFE9F: OAM - Sprite attributes
0xFF00-0xFF7F: I/O Registers
0xFF80-0xFFFE: High RAM (HRAM) - Stack & fast variables
```

### Variable Mapping
**Save Data (0xA000-0xBFFF):**
- [ ] Tamagotchi type/species
- [ ] Age counter
- [ ] Hunger level
- [ ] Happiness level
- [ ] Discipline level
- [ ] Weight
- [ ] Health status
- [ ] Care mistakes counter
- [ ] Evolution history
- [ ] Time/date data
- [ ] Checksum

**Work RAM Variables (0xC000-0xDFFF):**
- [ ] Current game state
- [ ] Active menu
- [ ] Animation frame counters
- [ ] Temporary calculations
- [ ] RNG state
- [ ] Input state

---

## PHASE 4: REVERSE ENGINEERING GAME MECHANICS

### Core Systems to Understand:
1. **Time System**
   - How does the game track time?
   - Real-time clock vs frame counting
   - Sleep/wake cycles

2. **Evolution System**
   - Evolution conditions
   - Care quality tracking
   - Evolution tree/branches

3. **Status Updates**
   - Hunger decrease rate
   - Happiness decrease rate
   - Poop generation
   - Sickness conditions

4. **Mini-Games**
   - Game mechanics
   - Scoring system
   - Rewards

---

## PHASE 5: C/C++ REWRITE

### Build System Setup
- [ ] Set up RGBDS (assembler/linker)
- [ ] Create Makefile
- [ ] Create project structure:
  ```
  src/
    main.c
    graphics.c
    input.c
    audio.c
    save.c
    game_logic.c
    tamagotchi.c
  include/
    hardware.h
    game.h
    tamagotchi.h
  assets/
    graphics/
    audio/
    maps/
  ```

### Code Conversion Priority:
1. [ ] Hardware abstraction layer (GB registers)
2. [ ] Memory management
3. [ ] Graphics engine
4. [ ] Input handling
5. [ ] Main game loop
6. [ ] Tamagotchi logic
7. [ ] Save system
8. [ ] Audio system
9. [ ] Mini-games

### Matching Build
- [ ] Compile and compare with original ROM
- [ ] Fix any differences (byte-perfect match)
- [ ] Automated build verification

---

## PHASE 6: MODERN PORT (Bonus)

### Cross-Platform Version
- [ ] SDL2 port for PC/Mac/Linux
- [ ] Mobile port (iOS/Android)
- [ ] Web version (WebAssembly)
- [ ] Add modern QOL features (optional):
  - Save states
  - Fast forward
  - HD graphics mode
  - Custom pets

---

## TOOLS & RESOURCES

### Required Tools:
- [x] Ghidra with GhidraBoy plugin
- [ ] BGB debugger
- [ ] RGBDS (assembler/linker)
- [ ] Tile editors (GBTD, GBMB, or modern alternatives)
- [ ] Hex editor
- [ ] Python (for scripting/automation)

### Helpful Resources:
- Pan Docs (GB hardware reference)
- gbdev.io community
- Existing GB decompilations (Pokemon, Zelda)
- MBC1 documentation

---

## PROGRESS TRACKER

### Overall Completion: ~2%

**Functions Identified:** 2/~200 (estimated)
**Functions Renamed:** 1/~200
**Assets Extracted:** 0%
**Code Converted:** 0%
**Build Matching:** No

---

## NEXT IMMEDIATE STEPS:

1. [ ] Analyze func_0x4000 (bank 6 loader)
2. [ ] Find and document main game loop
3. [ ] Identify VBlank interrupt handler
4. [ ] Map out all 32 ROM banks (what's in each)
5. [ ] Extract first tile set
6. [ ] Document save data format

---

## ESTIMATED TIMELINE

**If working solo, part-time:**
- Phase 1-2: 2-4 weeks
- Phase 3-4: 4-8 weeks  
- Phase 5: 8-12 weeks
- **Total: 3-6 months**

**If working full-time or with team:**
- Could be done in 1-2 months

---

## TIPS FOR SUCCESS

1. **Document everything** - Comments are your friend
2. **Work systematically** - Don't jump around randomly
3. **Test frequently** - Run the ROM in debugger alongside your code
4. **Use version control** - Git from day 1
5. **Join GB dev community** - Ask for help when stuck
6. **Compare with similar games** - Other GB games use similar patterns
7. **Take breaks** - Decompilation is mentally taxing

---

## WHEN YOU'RE STUCK

- Search for similar code patterns in other GB decomps
- Ask in gbdev Discord
- Use BGB's debugger to watch what code does in real-time
- Look for Game Boy programming tutorials
- Check if there's a published game manual/guide

---

Good luck! This is totally doable.