typedef unsigned char   undefined;

typedef unsigned char    byte;
typedef unsigned char    undefined1;
typedef unsigned int    undefined2;
typedef unsigned int    word;
typedef enum cart_type {
    ROM_ONLY=0,
    MBC1=1,
    MBC1_RAM=2,
    MBC1_RAM_BATT=3,
    MBC2=5,
    MBC2_BATT=6,
    RAM=8,
    RAM_BATT=9,
    MMM01=11,
    MMM01_RAM=12,
    MMM01_RAM_BATT=13,
    MBC3_RTC_BATT=15,
    MBC3_RAM_RTC_BATT=16,
    MBC3=17,
    MBC3_RAM=18,
    MBC3_RAM_BATT=19,
    MBC5=25,
    MBC5_RAM=26,
    MBC5_RAM_BATT=27,
    MBC5_RUMBLE=28,
    MBC5_RAM_RUMBLE=29,
    MBC5_RAM_BATT_RUMBLE=30,
    MBC6=32,
    MBC7=34,
    POCKET_CAMERA=252,
    TAMA5=253,
    HUC3=254,
    HUC1=255
} cart_type;

typedef union title_block title_block, *Ptitle_block;

typedef struct title_block_old title_block_old, *Ptitle_block_old;

typedef struct title_block_new title_block_new, *Ptitle_block_new;

typedef enum cgb_flag {
    NONE=0,
    SUPPORT=128,
    ONLY=192
} cgb_flag;

struct title_block_new {
    char title[11];
    char manufacturer_code[4];
    enum cgb_flag cgb_flag;
};

struct title_block_old {
    char title[15];
    enum cgb_flag cgb_flag;
};

union title_block {
    char title_only[16];
    struct title_block_old old_format;
    struct title_block_new new_format;
};

typedef enum ram_size {
    NONE=0,
    2KB=1,
    8KB=2,
    32KB=3,
    128KB=4,
    64KB=5
} ram_size;

typedef enum sgb_flag {
    NONE=0,
    SUPPORT=3
} sgb_flag;

typedef byte logo[48];

typedef struct header header, *Pheader;

typedef enum rom_size {
    32K=0,
    64K=1,
    128K=2,
    256K=3,
    512K=4,
    1MB=5,
    2MB=6,
    4MB=7,
    8MB=8
} rom_size;

typedef enum region {
    JAPAN=0,
    WORLD=1
} region;

struct header {
    union title_block title_block;
    char new_licensee_code[2];
    enum sgb_flag sgb_flag;
    enum cart_type cartridge_type;
    enum rom_size rom_size;
    enum ram_size ram_size;
    enum region region;
    byte old_licensee_code;
    byte mask_rom_version;
    byte header_checksum;
    word global_checksum;
};



undefined1 DAT_5fff;
undefined1 current_rom_bank;
undefined1 game_var_1;
undefined UNK_0256;
undefined1 game_var_2;
undefined1 frame_counter;
undefined1 UNK_fffe;
undefined save_data_start;
undefined1 save_data_1;
undefined1 save_data_2;
byte STAT;
byte BGP;
byte OBP0;
byte OBP1;
undefined2 debug_marker;
undefined ram_bank_select;
undefined rom_bank;
undefined1 saved_rom_bank;
undefined1 vblank_flag;
undefined1 lcd_update_flag;
undefined graphics_bank_id;
undefined1 display_mode;
undefined1 display_flag_1;
undefined1 display_counter;
undefined1 display_flag_2;
undefined1 display_ptr_low;
undefined1 display_ptr_high;
undefined1 DAT_0329;
byte LY;
byte LCDC;
byte IE;
byte IF;
undefined1 dma_busy_flag;
byte SCX;
undefined1 window_enable;
undefined1 scroll_x;
undefined1 scroll_y;
byte SCY;
undefined1 lcd_disable_flag;
undefined1 joypad_state;
undefined1 joypad_pressed;
byte P1;
undefined UNK_1167;
byte TIMA;
byte TMA;
byte TAC;
undefined1 save_magic;
undefined1 save_version;
undefined save_status_flag;
undefined save_flags;
undefined save_initialized_flag;
undefined UNK_0500;
undefined game_mode;
undefined1 creature_type;
undefined game_flag_1;
undefined game_flag_2;
undefined animation_state;
undefined DAT_ffe8;
undefined1 DAT_d505;
undefined1 DAT_8700;
undefined2 DAT_c500;
undefined UNK_202b;
char DAT_d495;
undefined1 current_creature_id;

undefined1 jump_table_lookup(byte index,undefined2 table_addr)

{
  return *(undefined1 *)
          CONCAT11((char)((uint)table_addr >> 8) + CARRY1(index,(byte)table_addr),
                   index + (byte)table_addr);
}



undefined1 jump_table_lookup_2(byte index,undefined2 table_addr)

{
  return *(undefined1 *)
          CONCAT11((char)((uint)table_addr >> 8) + CARRY1(index,(byte)table_addr),
                   index + (byte)table_addr);
}



void memcpy_rst(undefined1 *source,int size,undefined1 *dest)

{
  do {
    *dest = *source;
    dest = dest + 1;
    size = size + -1;
    source = source + 1;
  } while (size != 0);
  return;
}



// WARNING: This function may have set the stack pointer

void entry(void)

{
  undefined1 extraout_A;
  int jump_table_addr;
  code *main_loop_ptr;
  
  uRamfffe = 0;
  BGP = 0xff;
  OBP0 = 0xff;
  OBP1 = 0xff;
  IME(0);
  debug_marker = 0x168;
  memset_zero(0xff80,0x7e);
  debug_marker = 0x171;
  memset_zero(0xc000,0x1e00);
  debug_marker = 0x174;
  init_hram();
  ram_bank_select = 10;
  rom_bank_select_low = 0;
  save_data_start = 0xfe;
  save_data_1 = 0;
  save_data_2 = 0xff;
  current_rom_bank = 6;
  rom_bank = 6;
  debug_marker = 0x195;
  func_0x4000();
  current_rom_bank = 1;
  rom_bank = 1;
  debug_marker = 0x19f;
  init_graphics();
  debug_marker = 0x1a2;
  init_timer();
  uRamfffe = 1;
  STAT = 0;
  debug_marker = 0x1af;
  enable_interrupts(5);
  game_var_2 = 0xe;
  game_var_1 = 7;
  frame_counter = frame_counter + '\x01';
  debug_marker = 0x1c3;
  jump_table_addr = jump_table_lookup(0xe,&UNK_0256);
  main_loop_ptr = (code *)CONCAT11(*(undefined1 *)(jump_table_addr + 1),extraout_A);
                    // WARNING: Could not recover jumptable at 0x01c6. Too many branches
                    // WARNING: Treating indirect jump as call
  (*main_loop_ptr)(main_loop_ptr);
  return;
}



void init_graphics(void)

{
  current_rom_bank = saved_rom_bank;
  rom_bank = saved_rom_bank;
  vblank_flag = 1;
  lcd_update_flag = 1;
  init_display_params();
  graphics_bank_id = 0xb;
  init_save_system();
  load_initial_graphics();
  call_bank_31_function(0x4042);
  return;
}



void init_display_params(void)

{
  display_mode = 0x31;
  display_counter = 0xb;
  display_flag_1 = 0;
  display_flag_2 = 0;
  display_ptr_low = 0x21;
  display_ptr_high = 0x85;
  return;
}



char calculate_checksum(char *address,int size)

{
  char checksum;
  
  checksum = '\0';
  do {
    checksum = *address + checksum;
    size = size + -1;
    address = address + 1;
  } while (size != 0);
  return checksum;
}



void init_hram(void)

{
  byte hram_addr;
  char count;
  undefined1 *puVar1;
  
  hram_addr = 0x80;
  count = '\n';
  puVar1 = &DAT_0329;
  do {
    *(undefined1 *)(hram_addr | 0xff00) = *puVar1;
    hram_addr = hram_addr + 1;
    count = count + -1;
    puVar1 = puVar1 + 1;
  } while (count != '\0');
  return;
}



void lcd_off(void)

{
  byte lcdc_value;
  
  lcdc_value = LCDC;
  if ((lcdc_value & 0x80) != 0) {
    do {
      lcdc_value = LY;
    } while (lcdc_value != 0x91);
    lcdc_value = LCDC;
    LCDC = lcdc_value & 0x7f;
  }
  return;
}



void memset_zero(undefined1 *address,int size)

{
  do {
    *address = 0;
    size = size + -1;
    address = address + 1;
  } while (size != 0);
  return;
}



void memcpy(undefined1 *source,int size,undefined1 *dest)

{
  do {
    *dest = *source;
    dest = dest + 1;
    size = size + -1;
    source = source + 1;
  } while (size != 0);
  return;
}



void disable_interrupts(byte interrupt_mask)

{
  byte current_ie;
  
  current_ie = IE;
  IE = current_ie & (interrupt_mask ^ 0xff);
  return;
}



void enable_interrupts(byte interrupt_mask)

{
  byte bVar1;
  
  IF = 0;
  bVar1 = IE;
  IE = bVar1 | interrupt_mask;
  return;
}



void vram_dma_transfer(void)

{
  char byte_count;
  char *vram_dest;
  char *transfer_list;
  char *source_data;
  byte stat_reg;
  
  if (dma_busy_flag != '\0') {
    return;
  }
  transfer_list = &save_data_2;
  while( true ) {
    save_data_2 = *transfer_list;
    if (save_data_2 == -1) break;
    vram_dest = (char *)CONCAT11(save_data_2,transfer_list[1]);
    byte_count = transfer_list[2];
    source_data = transfer_list + 3;
    do {
      do {
        IME(1);
        IME(0);
        stat_reg = STAT;
      } while ((stat_reg & 3) != 0);
      transfer_list = source_data + 1;
      *vram_dest = *source_data;
      IME(1);
      vram_dest = vram_dest + 1;
      if (((uint)vram_dest & 0x1f) == 0) {
        vram_dest = (char *)CONCAT11((char)((uint)vram_dest >> 8) - ((byte)vram_dest < 0x20),
                                     (byte)vram_dest - 0x20);
      }
      byte_count = byte_count + -1;
      source_data = transfer_list;
    } while (byte_count != '\0');
  }
  save_data_1 = 0;
  return;
}



void update_lcd_control(void)

{
  byte lcdc_value;
  
  if (window_enable == '\0') {
    lcdc_value = LCDC;
    lcdc_value = lcdc_value & 0xdf;
  }
  else {
    lcdc_value = LCDC;
    lcdc_value = lcdc_value | 0x20;
  }
  LCDC = lcdc_value;
  SCY = scroll_y;
  SCX = scroll_x;
  lcdc_value = LCDC;
  LCDC = lcdc_value | 2;
  lcdc_value = LCDC;
  LCDC = lcdc_value & 0xef;
  return;
}



void check_and_disable_lcd(void)

{
  if (lcd_disable_flag == '\0') {
    return;
  }
  lcd_off();
  lcd_disable_flag = 0;
  return;
}



void read_joypad(void)

{
  byte dpad;
  byte buttons;
  
  P1 = 0x20;
  dpad = P1;
  dpad = P1;
  P1 = 0x10;
  buttons = P1;
  buttons = P1;
  buttons = P1;
  buttons = P1;
  buttons = P1;
  buttons = P1;
  dpad = ~buttons & 0xf | ~dpad << 4;
  joypad_pressed = (joypad_state ^ dpad) & dpad;
  joypad_state = dpad;
  P1 = 0x30;
  return;
}



undefined2 short_delay(undefined2 value)

{
  char count;
  
  count = '\b';
  do {
    count = count + -1;
  } while (count != '\0');
  return value;
}



void memcpy_32(void)

{
  memcpy_rst(&UNK_1167,0x20);
  return;
}



void init_timer(void)

{
  current_rom_bank = 7;
  rom_bank = 7;
  func_0x4000(0);
  TMA = 0xbc;
  TIMA = 0xbc;
  TAC = 4;
  current_rom_bank = saved_rom_bank;
  rom_bank = saved_rom_bank;
  return;
}



void call_bank_31_function(code *function_ptr)

{
  saved_rom_bank = 0x1f;
  current_rom_bank = 0x1f;
  rom_bank = 0x1f;
                    // WARNING: Could not recover jumptable at 0x14da. Too many branches
                    // WARNING: Treating indirect jump as call
  (*function_ptr)();
  return;
}



void init_save_system(void)

{
  char extraout_A;
  char extraout_A_00;
  char extraout_A_01;
  char *checksum_ptr;
  
  save_status_flag = 0;
  if ((save_magic != '\0') && (save_version == '\x01')) {
    checksum_ptr = (char *)calculate_checksum(&save_magic,0x7ff);
    if (extraout_A != *checksum_ptr) {
      recover_all_save_data();
    }
    checksum_ptr = (char *)calculate_checksum(0xa800,0x7ff);
    if (extraout_A_00 != *checksum_ptr) {
      recover_save_region_a800();
    }
    checksum_ptr = (char *)calculate_checksum(0xb000,0xfff);
    if (extraout_A_01 != *checksum_ptr) {
      init_extended_save_region();
    }
    return;
  }
  create_new_save();
  init_extended_save_region();
  init_game_state();
  init_graphics_save_data();
  save_flags = 1;
  write_main_save_checksum();
  return;
}



void recover_all_save_data(void)

{
  create_new_save();
  init_extended_save_region();
  init_game_state();
  init_graphics_save_data();
  save_flags = 1;
  write_main_save_checksum();
  return;
}



void recover_save_region_a800(void)

{
  init_game_state();
  init_graphics_save_data();
  save_flags = 1;
  write_main_save_checksum();
  return;
}



void init_extended_save_region(void)

{
  memset_zero(0xb000,0x1000);
  save_initialized_flag = 0;
  write_main_save_checksum();
  return;
}



void load_initial_graphics(void)

{
  memcpy(0xa800,&UNK_0500,0xd000);
  return;
}



void init_graphics_save_data(void)

{
  undefined1 extraout_A;
  undefined1 *checksum_ptr;
  
  memcpy(0xd000,&UNK_0500,0xa800);
  checksum_ptr = (undefined1 *)calculate_checksum(0xa800,0x7ff);
  *checksum_ptr = extraout_A;
  return;
}



void write_main_save_checksum(void)

{
  undefined1 extraout_A;
  undefined1 *checksum_ptr;
  
  checksum_ptr = (undefined1 *)calculate_checksum(&save_magic,0x7ff);
  *checksum_ptr = extraout_A;
  return;
}



void create_new_save(void)

{
  memset_zero(&save_magic,0x800);
  save_magic = 1;
  save_version = 1;
  write_main_save_checksum();
  return;
}



void init_game_state(void)

{
  memset_zero(0xd000,&UNK_0500);
  game_mode = 1;
  creature_type = 9;
  game_flag_1 = 1;
  game_flag_2 = 1;
  init_tamagotchi(0);
  animation_state = 0;
  memcpy(0xd000,0x200,0xd100);
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void copy_tiles_to_vram(void)

{
  char tile_count;
  undefined2 tile_data;
  undefined1 *vram_dest;
  undefined2 *ram_source;
  byte stat_reg;
  
  vram_dest = &DAT_8700;
  tile_count = -0x80;
  IME(0);
  ram_source = &DAT_c500;
  _DAT_ffe8 = (undefined1 *)register0x0a;
  do {
    tile_data = *ram_source;
    ram_source = ram_source + 1;
    do {
      stat_reg = STAT;
    } while ((stat_reg & 3) != 0);
    *vram_dest = (char)tile_data;
    vram_dest[1] = (char)((uint)tile_data >> 8);
    vram_dest = vram_dest + 2;
    tile_count = tile_count + -1;
  } while (tile_count != '\0');
  DAT_d505 = 0;
  IME(1);
  return;
}



void init_tamagotchi(void)

{
  undefined2 in_AF;
  char creature_id;
  
  creature_id = (char)((uint)in_AF >> 8);
  memcpy(&UNK_202b,0x14,(uint)(byte)(creature_id - 0x30) << 8);
  load_creature_data(creature_id);
  copy_creature_graphics(creature_id);
  return;
}



void copy_creature_graphics(char creature_id)

{
  memcpy_32(CONCAT11(creature_id + -0x30,0x80));
  return;
}



void increase_stat_capped(char amount)

{
  byte new_value;
  byte *stat_ptr;
  
  stat_ptr = (byte *)CONCAT11(DAT_d495 + -0x30,200);
  new_value = *stat_ptr + amount;
  if (99 < new_value) {
    new_value = 100;
  }
  *stat_ptr = new_value;
  return;
}



void load_creature_data(char creature_id)

{
  char *creature_ram;
  int data_addr;
  char creature_index;
  
  creature_ram = (char *)((uint)(byte)(creature_id - 0x30) << 8);
  current_creature_id = creature_id;
  data_addr = short_delay(CONCAT11(*creature_ram + -1,0x10));
  jump_table_lookup_2(0x28,data_addr + 0x413c,creature_ram);
  memcpy(0x10);
  creature_index = current_creature_id + -0x30;
  *(undefined1 *)CONCAT11(creature_index,0x3b) = *(undefined1 *)CONCAT11(creature_index,0x28);
  *(undefined1 *)CONCAT11(creature_index,0x38) = *(undefined1 *)CONCAT11(creature_index,0x2a);
  *(undefined1 *)CONCAT11(creature_index,0x39) = *(undefined1 *)CONCAT11(creature_index,0x2b);
  *(undefined1 *)CONCAT11(creature_index,0x3c) = *(undefined1 *)CONCAT11(creature_index,0x2c);
  *(undefined1 *)CONCAT11(creature_index,0x46) = *(undefined1 *)CONCAT11(creature_index,0x2d);
  *(undefined1 *)CONCAT11(creature_index,0x3a) = 0xb4;
  return;
}


