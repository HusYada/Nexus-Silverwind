#ifndef GAME_H
#define GAME_H
// Butano
#include "bn_bg_palettes.h"
#include "bn_color.h"
#include "bn_core.h"
#include "bn_display.h"
#include "bn_fixed.h"
#include "bn_keypad.h"
#include "bn_log.h"
#include "bn_math.h"
#include "bn_music_actions.h"
#include "bn_random.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sound_items.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_tiles_ptr.h"
// Include
#include "collision.h"
// Sprites
#include "bn_sprite_items_bhp.h"
#include "bn_sprite_items_blade.h"
#include "bn_sprite_items_boss.h"
#include "bn_sprite_items_bullet.h"
#include "bn_sprite_items_dot.h"
#include "bn_sprite_items_explode.h"
#include "bn_sprite_items_foe.h"
#include "bn_sprite_items_fruit.h"
#include "bn_sprite_items_player.h"
// Backgrounds
#include "bn_regular_bg_items_background.h"
#include "bn_regular_bg_items_back2.h"
#include "bn_regular_bg_items_sun.h"
#include "bn_regular_bg_items_title.h"
//-------------------------------

// Player Variables
//-------------------------------
// Player, Blade, Endpoint
int px = 0; int py = 0;
int bx = 0; int by = 0;
int ex = 0; int ey = -32;
// Fruit Positions
int fx[4]  = {   80,  -40,   40,  -80};
int fy[4]  = { -180, -300, -270, -240};
float frx[4]  = { 0 };
float fry[4]  = { 0 };
bool fly[4] = { false };
// Other Variables
bool slashing = false;
int run = 2;
// Back Scroll
int bgx = 0;
int sky = 10;
int suny = -20;
int bgy = 0;
// Time and Position
int bossencounter = 0; bool bossstart = false; int laughcount = 0; //bool fight = false; 
int bossx = 0; int bossy = -140; int bhpbar = 0; int bdamaged = 0; bool bdcount = false;
// Anim
int fanim1 = 0; bool fup1 = true; int facnt1 = 0;
int fanim2 = 0; bool fup2 = true; int facnt2 = 0;
int fanim3 = 0; bool fup3 = true; int facnt3 = 0;
int fanim4 = 0; bool fup4 = true; int facnt4 = 0;
// Explosion Stuff
int exanim = 0; bool exup = true;
namespace {
	collision ocol;
}
#endif