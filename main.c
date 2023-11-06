#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>
#include <gb/gb.h>
#include <gb/cgb.h>

#include "gbdk-rocks.h"
#include "fnaf.h"
#include "charmander.h"
#include "seta.h"
#include "fonte.h"
#include "menu_fnaf.h"
#include "tutorial_fnaf.h"

uint8_t currentNight;

void menu(void){
    //carregar o background, sprites, etc
    set_bkg_data(0, 32, fonte);
    set_bkg_tiles(0, 0, 20, 18, menu_fnaf_map);

    uint8_t setaNb = 0;
    uint8_t setaY = 80;
    set_sprite_data(0, 0, seta);
    set_sprite_tile(setaNb, 0);
    move_sprite(setaNb, 87, setaY);

    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    uint8_t pressed = FALSE;
    uint8_t setaHidden = FALSE;
    uint32_t currentTick = 0;
    uint32_t maxTick = 3500;
    while(1)
    {
        if(pressed == TRUE)
        {
            waitpadup();
            pressed = FALSE;
        }

        switch(joypad())
        {
            case J_UP:
                if(setaY == 80)
                {
                    setaY = 114;
                }
                else if(setaY == 97)
                {
                    setaY = 80;
                }
                else
                {
                    setaY = 97;
                }
                pressed = TRUE;
            break;

            case J_DOWN:
                if(setaY == 80)
                {
                    setaY = 97;
                }
                else if(setaY == 97)
                {
                    setaY = 114;
                }
                else
                {
                    setaY = 80;
                }
                pressed = TRUE;
            break;

            case J_A:
                if(setaY == 80)
                {
                    //ir para tutorial
                    currentNight = 0;
                    tutorial();
                }
                else if(setaY == 97)
                {
                    //continuar
                    night();
                }
                else
                {
                    //extras
                    extras();
                }
            break;
        }

        //move_sprite(setaNb, 87, setaY);

        if(currentTick >= maxTick)
        {
            currentTick = 0;
            if(setaHidden == FALSE)
            {
                hide_sprite(setaNb);
                setaHidden = TRUE;
            }
            else
            {
                move_sprite(setaNb, 87, setaY);
                setaHidden = FALSE;
            }
        }
        else
        {
            currentTick++;
        }
    }
}

void tutorial(void){
    set_bkg_data(0, 0, fonte);
    set_bkg_tiles(0, 0, 20, 18, tutorialmap);

    waitpad(J_START);

    menu();
}

void night(void){
    //carregar as coisas

    while(1)
    {
        
    }
}

void extras(void){

}

void main(void){
    currentNight = 0;
    menu();
}