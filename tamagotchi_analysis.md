# Tamagotchi Game Boy Decompilation Project

## ROM Information
- **Title:** GB TAMAGOTCHI
- **Region:** USA, Europe
- **Size:** 512 KB (0x80000 bytes)
- **Cartridge Type:** MBC1+RAM+BATTERY (0x03)
- **ROM Banks:** 32 (16KB each)
- **RAM:** 8 KB with battery backup
- **SGB Enhanced:** Yes

## Tools You'll Need

### 1. Disassemblers
- **mgbdis** - Game Boy specific disassembler (recommended)
- **Ghidra** - Free, powerful reverse engineering tool
- **IDA Free** - Also works for GB ROMs

### 2. Debuggers/Emulators
- **BGB** - Best GB debugger (Windows, works in Wine)
- **Emulicious** - Cross-platform with great debugging
- **mGBA** - Good general emulator with debug features

### 3. Development Tools
- **RGBDS** - Game Boy assembler/linker for rebuilding
- **Python** - For analysis scripts
- **Git** - Version control (essential!)

## Decompilation Strategy

### Phase 1: Initial Analysis
1. Map out ROM structure and banks
2. Identify entry point (0x0100)
3. Find major functions (graphics, input, save system)
4. Document memory map

### Phase 2: Disassembly
1. Use mgbdis or Ghidra to generate initial disassembly
2. Identify and label known functions
3. Map out data structures
4. Document sprite/tile data

### Phase 3: Conversion to C
1. Start with simple functions
2. Understand the game's state machine
3. Reverse engineer save data format
4. Recreate graphics routines

## Memory Map Notes
- 0x0000-0x3FFF: ROM Bank 0 (fixed)
- 0x4000-0x7FFF: ROM Bank 1-31 (switchable)
- 0x8000-0x9FFF: VRAM (tile data, maps)
- 0xA000-0xBFFF: External RAM (save data)
- 0xC000-0xDFFF: Work RAM
- 0xFF00-0xFF7F: I/O Registers

## Resources
- [Pan Docs](https://gbdev.io/pandocs/) - Game Boy hardware reference
- [gbdev.io](https://gbdev.io) - GB development wiki
- [awesome-gbdev](https://github.com/gbdev/awesome-gbdev) - Curated resources
- [RGBDS documentation](https://rgbds.gbdev.io/docs/)

## Project Goals
- [ ] Full disassembly of all ROM banks
- [ ] Identify all game functions
- [ ] Document save data format
- [ ] Create matching C/C++ code
- [ ] Achieve byte-perfect rebuild
- [ ] Port to modern platforms
