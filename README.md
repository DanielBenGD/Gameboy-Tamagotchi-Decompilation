# Tamagotchi Game Boy Decompilation

**Status:** Core engine functions identified and cleaned (35/35 ✓)  
**Progress:** ~10% complete (initialization and save system fully understood)

## 📋 Project Info

- **Game:** Tamagotchi (USA, Europe) (SGB Enhanced)
- **Platform:** Nintendo Game Boy
- **ROM Size:** 512 KB (32 ROM banks × 16KB)
- **RAM:** 8 KB battery-backed SRAM
- **Cartridge:** MBC1+RAM+BATTERY
- **Release:** 1997

## 🎯 Current Status

### ✅ Completed
- [x] All 35 core functions identified and renamed
- [x] Save system fully understood and documented
- [x] Memory layout mapped
- [x] Input system identified
- [x] Graphics initialization documented
- [x] Tamagotchi creature initialization traced

### 🚧 In Progress
- [ ] ROM bank contents analysis (banks 6, 7, 31)
- [ ] Main game loop identification
- [ ] Asset extraction (graphics, audio, text)

### 📅 To Do
- [ ] Interrupt handlers (VBlank, Timer)
- [ ] Game logic (hunger, happiness, evolution)
- [ ] Mini-games
- [ ] Sound system
- [ ] Complete asset extraction
- [ ] Matching C build

## 📁 File Structure

```
tamagotchi_hardware.h    - Hardware definitions and function declarations
tamagotchi_decompiled.c  - Decompiled C code (exported from Ghidra)
TAMAGOTCHI_DECOMP_PLAN.md - Comprehensive project roadmap
function_analysis.md      - Function identification notes
tamagotchi_analysis.md    - ROM analysis and documentation
```

## 🗺️ Memory Map

### ROM (0x0000-0x7FFF)
```
0x0000-0x00FF: Interrupt vectors & RST handlers
0x0100-0x014F: ROM header
0x0150-0x3FFF: ROM Bank 0 (fixed) - Core engine
0x4000-0x7FFF: ROM Banks 1-31 (switchable) - Assets & game code
```

### RAM (0x8000-0xFFFF)
```
0x8000-0x9FFF: VRAM - Tile data & maps
0xA000-0xBFFF: External RAM - Save data (battery-backed)
0xC000-0xDFFF: Work RAM - Game variables
0xE000-0xFDFF: Echo RAM
0xFE00-0xFE9F: OAM - Sprite attributes
0xFF00-0xFF7F: I/O Registers
0xFF80-0xFFFE: High RAM (HRAM) - Fast variables
0xFFFF:        Interrupt Enable register
```

### Save Data Layout (0xA000-0xBFFF)
```
0xA000:        Magic byte (0x01)
0xA001:        Save version (0x01)
0xA002:        Save flags
0xA003-0xA7FE: Main game data
0xA7FF:        Checksum for main save

0xA800-0xAFFE: Graphics/tileset data
0xAFFF:        Checksum for graphics

0xB000-0xBFFE: Extended save data
0xBFFF:        Checksum for extended data
```

## 🔧 Functions Identified (35/35)

### Core System (5)
- `entry()` - Main entry point
- `jump_table_lookup()` - Function pointer lookup (RST 0x00)
- `jump_table_lookup_2()` - Data pointer lookup (RST 0x08)
- `memcpy_rst()` - Memory copy (RST 0x18)
- `short_delay()` - 8-cycle delay loop

### Memory Operations (4)
- `memset_zero()` - Clear memory
- `memcpy()` - Copy memory
- `memcpy_32()` - Copy 32 bytes

### Initialization (8)
- `init_hram()` - Initialize high RAM
- `init_graphics()` - Initialize graphics system
- `init_display_params()` - Set display parameters
- `init_timer()` - Set up Game Boy timer
- `init_save_system()` - Validate/initialize save data
- `init_game_state()` - Initialize game variables
- `init_tamagotchi()` - Initialize creature
- `init_graphics_save_data()` - Initialize graphics save

### Graphics (6)
- `lcd_off()` - Safely disable LCD
- `check_and_disable_lcd()` - Conditional LCD disable
- `update_lcd_control()` - Update LCDC register
- `copy_tiles_to_vram()` - Copy tiles to VRAM
- `load_initial_graphics()` - Load default graphics
- `vram_dma_transfer()` - VRAM DMA transfer

### Input (1)
- `read_joypad()` - Read controller input

### Interrupts (2)
- `enable_interrupts()` - Enable specific interrupts
- `disable_interrupts()` - Disable specific interrupts

### Save System (6)
- `calculate_checksum()` - Calculate save checksum
- `create_new_save()` - Create new save file
- `write_main_save_checksum()` - Update save checksum
- `recover_all_save_data()` - Full save recovery
- `recover_save_region_a800()` - Recover graphics save
- `init_extended_save_region()` - Initialize extended save

### Tamagotchi Logic (3)
- `load_creature_data()` - Load creature stats from ROM
- `copy_creature_graphics()` - Load creature sprites
- `increase_stat_capped()` - Increase stat (max 100)

### ROM Banking (1)
- `call_bank_31_function()` - Switch to bank 31 and execute

## 🎮 Key Discoveries

### Save System
- Uses simple byte-sum checksums for validation
- Three independent save regions with separate checksums
- Automatic recovery if corruption detected
- Save format version 1

### Creature System
- Creature IDs start at 0x30 (offset by 48)
- Each creature has 20 bytes of data
- Initial creature type is 9
- Stats capped at 100
- Starting age is 180 (0xB4)

### Graphics
- Uses DMA transfers during VBlank for safety
- VRAM updates wait for STAT mode 0/1
- Tileset stored in save RAM (customizable?)
- SGB Enhanced features

### Input
- Standard Game Boy input reading
- Debounced button detection
- Tracks both current state and newly pressed

## 🔍 Next Steps

1. **Analyze ROM Banks**
   - Bank 6: Graphics/data loader
   - Bank 7: Timer initialization data
   - Bank 31: Main game logic?

2. **Find Main Game Loop**
   - Entry jumps to function at 0x0256 + 0x0E
   - This is the main state machine

3. **Extract Assets**
   - Tile data at 0x0500
   - Creature data at 0x202B
   - More graphics in ROM banks

4. **Reverse Engineer Mechanics**
   - How does hunger/happiness decrease?
   - What triggers evolution?
   - How do mini-games work?

## 🛠️ Tools Used

- **Ghidra 11.4.2** with GhidraBoy plugin
- **BGB Debugger** (recommended for testing)
- **Python** for analysis scripts
- **RGBDS** (for eventual rebuild)

## 📚 Resources

- [Pan Docs](https://gbdev.io/pandocs/) - Game Boy hardware reference
- [gbdev.io](https://gbdev.io) - Game Boy development wiki
- [GhidraBoy](https://github.com/Gekkio/GhidraBoy) - Ghidra GB extension
- [Awesome GB Dev](https://github.com/gbdev/awesome-gbdev) - GB resources

## 🤝 Contributing

This is a personal decompilation project. Key areas needing work:
- ROM bank analysis
- Asset extraction
- Game logic reverse engineering
- Documentation

## ⚖️ Legal

This is a reverse engineering project for educational and preservation purposes. No ROM files or copyrighted assets are included. You must own a legal copy of the game to use this decompilation.

## 📝 License

Decompiled code and documentation: Public Domain / CC0  
Original game: © Bandai

---

**Last Updated:** January 21, 2026
**Completion:** 10%
