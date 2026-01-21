#ifndef TAMAGOTCHI_HARDWARE_H
#define TAMAGOTCHI_HARDWARE_H

// =============================================================================
// TAMAGOTCHI GAME BOY - HARDWARE DEFINITIONS
// Decompiled from: Tamagotchi (USA, Europe) (SGB Enhanced).gb
// ROM Size: 512KB (32 banks)
// RAM Size: 8KB (battery-backed)
// =============================================================================

typedef unsigned char byte;
typedef unsigned char undefined1;
typedef unsigned int word;
typedef unsigned int undefined2;

// =============================================================================
// GAME BOY HARDWARE REGISTERS
// =============================================================================

// Graphics Registers
extern byte LCDC;       // 0xFF40 - LCD Control
extern byte STAT;       // 0xFF41 - LCD Status
extern byte SCY;        // 0xFF42 - Scroll Y
extern byte SCX;        // 0xFF43 - Scroll X
extern byte LY;         // 0xFF44 - Current scanline
extern byte BGP;        // 0xFF47 - Background Palette
extern byte OBP0;       // 0xFF48 - Object Palette 0
extern byte OBP1;       // 0xFF49 - Object Palette 1

// Input Register
extern byte P1;         // 0xFF00 - Joypad

// Timer Registers
extern byte TIMA;       // 0xFF05 - Timer Counter
extern byte TMA;        // 0xFF06 - Timer Modulo
extern byte TAC;        // 0xFF07 - Timer Control

// Interrupt Registers
extern byte IE;         // 0xFFFF - Interrupt Enable
extern byte IF;         // 0xFF0F - Interrupt Flag

// =============================================================================
// MEMORY BANK CONTROLLER (MBC1)
// =============================================================================

extern undefined1 ram_bank_select;      // 0x1FFF - RAM bank select
extern undefined1 DAT_5fff;             // 0x5FFF - ROM bank select (low)
extern undefined1 rom_bank;             // 0x3FFF - ROM bank select (high)

// =============================================================================
// GAME VARIABLES (HIGH RAM - 0xFF80-0xFFFF)
// =============================================================================

extern undefined1 current_rom_bank;     // Current ROM bank number
extern undefined1 saved_rom_bank;       // Saved ROM bank for restoration

// Display State
extern undefined1 display_mode;         // 0xFFF0 - Display mode/state
extern undefined1 display_flag_1;       // 0xFFF1
extern undefined1 display_counter;      // 0xFFF2
extern undefined1 display_flag_2;       // 0xFFF3
extern undefined1 display_ptr_low;      // 0xFFF4
extern undefined1 display_ptr_high;     // 0xFFF5

// Game State
extern undefined1 game_var_1;           // 0xFFB7 - Game variable 1
extern undefined1 game_var_2;           // 0xFFB8 - Game variable 2
extern undefined1 frame_counter;        // 0xFFB9 - Frame counter

// Input State
extern undefined1 joypad_state;         // 0xFFBB - Current button state
extern undefined1 joypad_pressed;       // 0xFFBC - Newly pressed buttons

// Flags
extern undefined1 vblank_flag;          // 0xFFDB - VBlank flag
extern undefined1 lcd_update_flag;      // 0xFFDC - LCD update flag
extern undefined1 lcd_disable_flag;     // 0xFFEE - LCD disable request
extern undefined1 dma_busy_flag;        // 0xFFBA - DMA busy flag
extern undefined1 window_enable;        // 0xCD90 - Window enable flag

// Scroll Position
extern undefined1 scroll_x;             // 0xFFD0 - Scroll X position
extern undefined1 scroll_y;             // 0xFFD1 - Scroll Y position

// Debug
extern undefined2 debug_marker;         // 0xDFFD - Debug trace marker

// =============================================================================
// SAVE DATA (BATTERY-BACKED RAM - 0xA000-0xBFFF)
// =============================================================================

// Save Header (0xA000-0xA002)
extern undefined1 save_magic;           // 0xA000 - Magic byte (0x01)
extern undefined1 save_version;         // 0xA001 - Save version (0x01)
extern undefined save_flags;            // 0xA002 - Save flags
extern undefined save_initialized_flag; // 0xA003 - Initialization flag

// Save Data Regions
extern undefined save_data_start;       // 0xA000 - Start of main save
extern undefined1 save_data_1;          // Save data region 1
extern undefined1 save_data_2;          // Save data region 2

// Save regions with checksums:
// 0xA000-0xA7FF: Main game save (2KB) + checksum at 0xA7FF
// 0xA800-0xAFFF: Graphics save (2KB) + checksum at 0xAFFF  
// 0xB000-0xBFFF: Extended save (4KB) + checksum at 0xBFFF

// =============================================================================
// GAME RAM (WORK RAM - 0xC000-0xDFFF)
// =============================================================================

// Game State
extern undefined game_mode;             // 0xD480 - Current game mode
extern undefined1 creature_type;        // 0xD490 - Creature type (9 = default)
extern undefined game_flag_1;           // 0xD491
extern undefined game_flag_2;           // 0xD497
extern undefined animation_state;       // 0xD080 - Animation state
extern undefined save_status_flag;      // 0xD500 - Save system status
extern undefined graphics_bank_id;      // 0xD580 - Graphics ROM bank ID

// Tamagotchi Data
extern char DAT_d495;                   // 0xD495 - Current creature ID
extern undefined1 current_creature_id;  // 0xD4A1 - Active creature ID

// Graphics Buffers
extern undefined1 DAT_8700;             // 0x8700 - VRAM tile destination
extern undefined2 DAT_c500;             // 0xC500 - Tile data source (RAM)
extern undefined1 DAT_d505;             // 0xD505 - Tile copy flag
extern undefined DAT_ffe8;              // 0xFFE8 - DMA register backup

// =============================================================================
// ROM DATA REFERENCES
// =============================================================================

extern undefined UNK_0256;              // 0x0256 - Jump table
extern undefined1 DAT_0329;             // 0x0329 - HRAM init data
extern undefined UNK_0500;              // 0x0500 - Graphics data
extern undefined UNK_1167;              // 0x1167 - Data for memcpy_32
extern undefined UNK_202b;              // 0x202B - Creature data table

// =============================================================================
// FUNCTION DECLARATIONS
// =============================================================================

// Core System
void entry(void);                                   // Main entry point
undefined1 jump_table_lookup(byte index, undefined2 table_addr);
undefined1 jump_table_lookup_2(byte index, undefined2 table_addr);

// Memory Operations
void memset_zero(undefined1 *address, int size);
void memcpy(undefined1 *source, int size, undefined1 *dest);
void memcpy_rst(undefined1 *source, int size, undefined1 *dest);
void memcpy_32(void);

// Initialization
void init_hram(void);
void init_graphics(void);
void init_display_params(void);
void init_timer(void);
void init_save_system(void);
void init_game_state(void);
void init_tamagotchi(void);

// Graphics
void lcd_off(void);
void check_and_disable_lcd(void);
void update_lcd_control(void);
void copy_tiles_to_vram(void);
void load_initial_graphics(void);
void init_graphics_save_data(void);
void vram_dma_transfer(void);

// Input
void read_joypad(void);

// Interrupts
void enable_interrupts(byte interrupt_mask);
void disable_interrupts(byte interrupt_mask);

// Save System
char calculate_checksum(char *address, int size);
void create_new_save(void);
void write_main_save_checksum(void);
void recover_all_save_data(void);
void recover_save_region_a800(void);
void init_extended_save_region(void);

// Tamagotchi Logic
void load_creature_data(char creature_id);
void copy_creature_graphics(char creature_id);
void increase_stat_capped(char amount);

// ROM Banking
void call_bank_31_function(void *function_ptr);

// Utility
undefined2 short_delay(undefined2 value);

// =============================================================================
// CONSTANTS
// =============================================================================

// Interrupt Masks
#define INT_VBLANK  0x01
#define INT_LCD     0x02
#define INT_TIMER   0x04
#define INT_SERIAL  0x08
#define INT_JOYPAD  0x10

// LCDC Flags
#define LCDC_ON           0x80  // LCD enabled
#define LCDC_WIN_MAP      0x40  // Window tile map select
#define LCDC_WIN_ON       0x20  // Window enabled
#define LCDC_BG_TILE      0x10  // BG & Window tile data select
#define LCDC_BG_MAP       0x08  // BG tile map select
#define LCDC_OBJ_SIZE     0x04  // Sprite size (0=8x8, 1=8x16)
#define LCDC_OBJ_ON       0x02  // Sprites enabled
#define LCDC_BG_ON        0x01  // BG enabled

// Joypad Buttons
#define BTN_A         0x01
#define BTN_B         0x02
#define BTN_SELECT    0x04
#define BTN_START     0x08
#define BTN_RIGHT     0x10
#define BTN_LEFT      0x20
#define BTN_UP        0x40
#define BTN_DOWN      0x80

// Save Data
#define SAVE_MAGIC_VALUE    0x01
#define SAVE_VERSION        0x01

// Creature Constants
#define CREATURE_ID_OFFSET  0x30  // Subtract this to get creature index
#define INITIAL_CREATURE    9     // Default creature type
#define INITIAL_AGE         180   // Starting age (0xB4)

#endif // TAMAGOTCHI_HARDWARE_H
