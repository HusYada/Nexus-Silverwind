// Nexus Silverwind by HusYada
#include "game.h"

void title(){
	bn::regular_bg_ptr title = bn::regular_bg_items::title.create_bg(0,0);
	bhpbar = 0;
	while(!bn::keypad::start_pressed() && !bn::keypad::select_pressed()) {
		// ----------------------------------------------------
		// Brightness Update
		// ----------------------------------------------------
		bn::fixed brightness = bn::bg_palettes::brightness();
		if(bn::keypad::l_held()) { bn::bg_palettes::set_brightness(bn::max(brightness - 0.01, bn::fixed(0))); }
  		else if(bn::keypad::r_held()) { bn::bg_palettes::set_brightness(bn::min(brightness + 0.01, bn::fixed(1))); }
		bn::core::update();
	}
}

void nexus_silverwind(){
	bn::sprite_ptr fruit0 = bn::sprite_items::foe.create_sprite(fx[0], fy[0]);
	bn::sprite_ptr fruit1 = bn::sprite_items::foe.create_sprite(fx[1], fy[1]);
	bn::sprite_ptr fruit2 = bn::sprite_items::foe.create_sprite(fx[2], fy[2]);
	bn::sprite_ptr fruit3 = bn::sprite_items::foe.create_sprite(fx[3], fy[3]);
	bn::sprite_ptr boss = bn::sprite_items::boss.create_sprite(500, -500);
	bn::sprite_ptr blade = bn::sprite_items::blade.create_sprite(px, py);
	bn::sprite_ptr player = bn::sprite_items::player.create_sprite(px, py);
	bn::sprite_ptr dot = bn::sprite_items::dot.create_sprite(px, py);
	bn::sprite_ptr swordtip = bn::sprite_items::dot.create_sprite(px, py);
	bn::sprite_ptr explode1 = bn::sprite_items::explode.create_sprite(-550, -550);
	bn::sprite_ptr explode2 = bn::sprite_items::explode.create_sprite(-550, -550);
	bn::sprite_ptr explode3 = bn::sprite_items::explode.create_sprite(-550, -550);
	bn::sprite_ptr explode4 = bn::sprite_items::explode.create_sprite(-550, -550);
	bn::sprite_ptr bhp = bn::sprite_items::bhp.create_sprite(-120+16, -80+8);
	blade.set_rotation_angle(90);
	blade.set_visible(false);
	dot.set_visible(false);
	swordtip.set_visible(false);
	bhp.set_visible(false);
	bn::regular_bg_ptr background = bn::regular_bg_items::background.create_bg(0,bgy);
	bn::regular_bg_ptr back2 = bn::regular_bg_items::back2.create_bg(bgx,sky);
	bn::regular_bg_ptr sun = bn::regular_bg_items::sun.create_bg(0,suny);
	//rng.get_fixed(0.5, 2.5).round_integer()
	//fo.fruitinit();
	while(!bn::keypad::start_pressed() || !bn::keypad::select_pressed()) {
		if(fy[0] < -10) { fy[0]++; }
		if(fy[1] < -10) { fy[1]++; }
		if(fy[2] < 40) { fy[2]++; }
		if(fy[3] < -40) { fy[3]++; }
		bgx++;
		bgy++;
		if(bossencounter<999) { bossencounter++; }
		if(bossencounter>=999 && !bossstart) { 
			fruit1.set_visible(true); 
			fruit2.set_visible(true); 
			fruit3.set_visible(true);
			fruit0.set_visible(true);
			explode1.set_position(550,550);
			explode2.set_position(550,550);
			explode3.set_position(550,550);
			explode4.set_position(550,550);
			for(int i = 0; i < 4; i++) {
				fx[i] = 500; fy[i] = 500; fly[i] = false;
			}
			if(bossy< -40) { bossy++; }
			if(bossy>=-40) { bossstart = true; }
			if(suny < 40) { suny++; sky++; }
		}
		//fo.fruit();
		// ----------------------------------------------------
		// Boss fight
		// ----------------------------------------------------
		if(bossstart) {
			if(laughcount == 0) {
				bn::sound_items::laugh.play(0.5);
				fx[0] = 90; fx[1] = 45; fx[2] = 45; fx[3] = -90;
				fy[0] =-100;fy[1] =-120;fy[2] =-110;fy[3] = -130;
				bhp.set_visible(true);
				laughcount++;
			}
			if(fy[0] < 50) { fy[0]++; }
			if(fy[1] < 60) { fy[1]++; }
			if(fy[2] < 50) { fy[2]++; }
			if(fy[3] < 60) { fy[3]++; }
			if(fx[0] < -150 || fx[0] > 150 || fy[0] < -150 || fy[0] > 150) { fx[0] = 90; fy[0] =-100;  }
			if(fx[1] < -150 || fx[1] > 150 || fy[1] < -150 || fy[1] > 150) { fx[1] = 45; fy[1] =-120; }
			if(fx[2] < -150 || fx[2] > 150 || fy[2] < -150 || fy[2] > 150) { fx[2] =-45; fy[2] =-110; }
			if(fx[3] < -150 || fx[3] > 150 || fy[3] < -150 || fy[3] > 150) { fx[3] =-90; fy[3] =-130; }
		   if((ocol.overlap(bossx-8,-40-16,16,32,fx[0]-8, fy[0]-8, 16, 16) 
		   	|| ocol.overlap(bossx-8,-40-16,16,32,fx[2]-8, fy[2]-8, 16, 16) 
		   	|| ocol.overlap(bossx-8,-40-16,16,32,fx[3]-8, fy[3]-8, 16, 16) 
		   	|| ocol.overlap(bossx-8,-40-16,16,32,fx[1]-8, fy[1]-8, 16, 16)) && bdcount == false ) {
				if(bhpbar < 3) { 
					bhpbar++;
					bdcount = true; 
				}
			}
			if(bdcount) {
				bdamaged++;
				if(bdamaged < 50) { bdamaged = 0; bdcount = false; }
			}
			bhp.set_tiles(bn::sprite_items::bhp.tiles_item().create_tiles(bhpbar));
		}
		// ----------------------------------------------------
		// Player Input
		// ----------------------------------------------------
		if(bn::keypad::left_held()) { 
			px-= run;
			player.set_tiles(bn::sprite_items::player.tiles_item().create_tiles(1));
			player.set_horizontal_flip(false);
		}
		if(bn::keypad::right_held()) { 
			px+= run;
			player.set_tiles(bn::sprite_items::player.tiles_item().create_tiles(1));
			player.set_horizontal_flip(true);
		}
		if(!bn::keypad::left_held() && !bn::keypad::right_held()) {
			 player.set_tiles(bn::sprite_items::player.tiles_item().create_tiles(0));
		}
		if(bn::keypad::up_held()) { py-= run; }
		if(bn::keypad::down_held()) { py+= run; }
		if(bn::keypad::a_held()) { run = 4; } 
		if(bn::keypad::a_released()) { run = 2; }
		// ----------------------------------------------------
		// Rotate Blade (cool)
		// ----------------------------------------------------
		bn::fixed f_cumr = blade.rotation_angle();
		if(bn::keypad::r_held()) {
			blade.set_rotation_angle(bn::max(f_cumr - 15, bn::fixed(0))); 
			slashing = true; blade.set_visible(true);
			if(blade.rotation_angle() == 0) { 
				blade.set_rotation_angle(360);
			}
		} else if(bn::keypad::l_held()) { 
        	blade.set_rotation_angle(bn::min(f_cumr + 15, bn::fixed(360))); 
        	slashing = true; blade.set_visible(true);
        	if(blade.rotation_angle() == 360) { 
				blade.set_rotation_angle(0);
			}
        }
        if(bn::keypad::l_released() || bn::keypad::r_released()) {
        	blade.set_rotation_angle(90);
        	slashing = false;
        	blade.set_visible(false);
        }
        float anglex = bn::degrees_cos(blade.rotation_angle().to_float()).to_float();
        float angley = bn::degrees_sin(blade.rotation_angle().to_float()).to_float();
        bx = 16 * anglex; by = 16 * -angley;
        ex = 32 * anglex; ey = 32 * -angley;
        // ----------------------------------------------------
		// Sword Collision / Bash
		// ----------------------------------------------------
		if(ocol.lineRect(px,py,ex+px,ey+py, fx[0]-8, fy[0]-8, 16, 16) && slashing) {
			frx[0] = anglex; fry[0] = angley; fly[0]=true; bn::sound_items::octo.play(0.5);
		}
		if(ocol.lineRect(px,py,ex+px,ey+py, fx[1]-8, fy[1]-8, 16, 16) && slashing) {
			frx[1] = anglex; fry[1] = angley; fly[1]=true; bn::sound_items::octo.play(0.5);
		}
		if(ocol.lineRect(px,py,ex+px,ey+py, fx[2]-8, fy[2]-8, 16, 16) && slashing) {
			frx[2] = anglex; fry[2] = angley; fly[2]=true; bn::sound_items::octo.play(0.5);
		}
		if(ocol.lineRect(px,py,ex+px,ey+py, fx[3]-8, fy[3]-8, 16, 16) && slashing) {
			frx[3] = anglex; fry[3] = angley; fly[3]=true; bn::sound_items::octo.play(0.5);
		}
		// When hit they fly
		if(fly[0]) { fx[0] += frx[0]*2; fy[0] -= fry[0]*2; }
		if(fly[1]) { fx[1] += frx[1]*2; fy[1] -= fry[1]*2; }
		if(fly[2]) { fx[2] += frx[2]*2; fy[2] -= fry[2]*2; }
		if(fly[3]) { fx[3] += frx[3]*2; fy[3] -= fry[3]*2; }
		// ----------------------------------------------------
		// Foe Idle Animation (if soup)
		// ----------------------------------------------------
		facnt1++;facnt2++;facnt3++;facnt4++;
		if(fanim1 == 0) { fup1 = true; }
		if(fanim1 == 2) { fup1 = false; }
		if(fup1 && facnt1 > 10) { fanim1++; facnt1=0;}
		if(!fup1 && facnt1 > 10) { fanim1--; facnt1=0;}
		if(fanim2 == 0) { fup2 = true; }
		if(fanim2 == 2) { fup2 = false; }
		if(fup2 && facnt2 > 10) { fanim2++; facnt2=0;}
		if(!fup2 && facnt2 > 10) { fanim2--; facnt2=0;}
		if(fanim3 == 0) { fup3 = true; }
		if(fanim3 == 2) { fup3 = false; }
		if(fup3 && facnt3 > 10) { fanim3++; facnt3=0;}
		if(!fup3 && facnt3 > 10) { fanim3--; facnt3=0;}
		if(fanim4 == 0) { fup4 = true; }
		if(fanim4 == 2) { fup4 = false; }
		if(fup4 && facnt4 > 10) { fanim4++; facnt4=0;}
		if(!fup4 && facnt4 > 10) { fanim4--; facnt4=0;}
		fruit0.set_tiles(bn::sprite_items::foe.tiles_item().create_tiles(fanim1));
		fruit1.set_tiles(bn::sprite_items::foe.tiles_item().create_tiles(fanim2));
		fruit2.set_tiles(bn::sprite_items::foe.tiles_item().create_tiles(fanim3));
		fruit3.set_tiles(bn::sprite_items::foe.tiles_item().create_tiles(fanim4));
		// ----------------------------------------------------
		// Enemy Collision / Bash (the mess begins here)
		// ----------------------------------------------------
		if(exanim == 0) { exup = true; }
		if(exanim == 3) { exup = false; }
		if(exup) { exanim++; }
		if(!exup) { exanim--; }
		explode1.set_tiles(bn::sprite_items::explode.tiles_item().create_tiles(exanim));
		explode2.set_tiles(bn::sprite_items::explode.tiles_item().create_tiles(exanim));
		explode3.set_tiles(bn::sprite_items::explode.tiles_item().create_tiles(exanim));
		explode4.set_tiles(bn::sprite_items::explode.tiles_item().create_tiles(exanim));
		if(ocol.overlap(fx[0]-8, fy[0]-8, 16, 16,fx[1]-8, fy[1]-8, 16, 16) && bossencounter<999) {
			explode1.set_position(fx[0],fy[0]);
			explode2.set_position(fx[1],fy[1]);
			fly[0] = false; fly[1] = false;
			fruit0.set_visible(false); fruit1.set_visible(false);
		}
		if(ocol.overlap(fx[0]-8, fy[0]-8, 16, 16,fx[2]-8, fy[2]-8, 16, 16) && bossencounter<999) {
			explode1.set_position(fx[0],fy[0]);
			explode3.set_position(fx[2],fy[2]);
			fly[0] = false; fly[2] = false;
			fruit0.set_visible(false); fruit2.set_visible(false);
		}
		if(ocol.overlap(fx[0]-8, fy[0]-8, 16, 16,fx[3]-8, fy[3]-8, 16, 16) && bossencounter<999) {
			explode1.set_position(fx[0],fy[0]);
			explode4.set_position(fx[3],fy[3]);
			fly[0] = false; fly[3] = false;
			fruit0.set_visible(false); fruit3.set_visible(false);
		}
		if(ocol.overlap(fx[1]-8, fy[1]-8, 16, 16,fx[2]-8, fy[2]-8, 16, 16) && bossencounter<999) {
			explode2.set_position(fx[1],fy[1]);
			explode3.set_position(fx[2],fy[2]);
			fly[1] = false; fly[2] = false;
			fruit1.set_visible(false); fruit1.set_visible(false);
		}
		if(ocol.overlap(fx[1]-8, fy[1]-8, 16, 16,fx[3]-8, fy[3]-8, 16, 16) && bossencounter<999) {
			explode2.set_position(fx[1],fy[1]);
			explode4.set_position(fx[3],fy[3]);
			fly[1] = false; fly[3] = false;
			fruit1.set_visible(false); fruit3.set_visible(false);
		}
		if(ocol.overlap(fx[2]-8, fy[2]-8, 16, 16,fx[3]-8, fy[3]-8, 16, 16) && bossencounter<999) {
			explode3.set_position(fx[2],fy[2]);
			explode4.set_position(fx[3],fy[3]);
			fly[2] = false; fly[3] = false;
			fruit2.set_visible(false); fruit3.set_visible(false);
		}
		// ----------------------------------------------------
		// Position Update
		// ----------------------------------------------------
		boss.set_position(bossx,bossy);
		blade.set_position(bx+px,by+py);
		dot.set_position(px,py);
		player.set_position(px,py);
		fruit0.set_position(fx[0],fy[0]);
		fruit1.set_position(fx[1],fy[1]);
		fruit2.set_position(fx[2],fy[2]);
		fruit3.set_position(fx[3],fy[3]);
		swordtip.set_position(ex+px,ey+py);
		background.set_position(0, bgy);
		back2.set_position(bgx, sky);
		sun.set_position(0, suny);
		// ----------------------------------------------------
		// Logging
		// ----------------------------------------------------
        if(bn::keypad::select_pressed()) { 
        	BN_LOG("===============");
        	// BN_LOG("Player Width: ",  fp.plyrw);
        	// BN_LOG("Player X - Width: ",  fp.plyrx+fp.leftoffsetx-fp.plyrw+fp.leftoffsetw);
        	// BN_LOG("Player X: ",  fp.plyrx);
        	// BN_LOG("Player X + Width: ",  fp.plyrx+fp.plyrw+1);
        	// BN_LOG("OBJ1 X: ",  fp.lvlt1x[0]);
        	// BN_LOG("OBJ1 X + W: ",  fp.lvlt1x[0]+fp.lvlt1w[0]);
        	// BN_LOG("OBJ2 X: ",  fp.lvlt1x[1]);
        	// BN_LOG("OBJ2 X + W: ",  fp.lvlt1x[1]+fp.lvlt1w[1]);
        	BN_LOG("Angle:    ",  f_cumr);
        	// BN_LOG("Dist:     ",  f_dist);
        	// BN_LOG("Aiming X: ",  f_startx);
        	// BN_LOG("Aiming Y: ",  f_starty);
        	// ----------------------------------------------------
    	}
        bn::core::update();
    }
}

int main() {
    bn::core::init();
    bn::bg_palettes::set_transparent_color(bn::color(0));
    bn::sound_items::laugh.play(0.5);
    title(); bn::core::update();
    nexus_silverwind(); bn::core::update();
}
