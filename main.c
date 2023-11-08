#include <gb/gb.h>
#include <stdint.h>
#include <stdio.h>
#include <gb/gb.h>
#include <gb/cgb.h>

//SPRITES
#include "fnaf.h"
#include "charmander.h"
#include "seta.h"
#include "fonte.h"
#include "camTiles.h"

//BACKGROUNDS
#include "menu_fnaf.h"
#include "tutorial_fnaf.h"
#include "CamMap.h"
#include "officeMap.h"

uint8_t currentNight;

void menu(void){
    //carregar o background, sprites, etc
    set_bkg_data(0, 41, fonte); //41 = total de tiles + 1
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
                    currentNight = 1;
                    hide_sprite(setaNb);
                    tutorial();
                }
                else if(setaY == 97)
                {
                    //continuar
                    hide_sprite(setaNb);
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
    set_bkg_data(0, 41, fonte);
    set_bkg_tiles(0, 0, 20, 18, tutorialmap);

    waitpad(J_START);

    night();
}

void night(void){
    set_bkg_data(0, 41, fonte);
    set_bkg_tiles(0, 0, officeMapWidth, officeMapHeight, officeMap);

    uint8_t camOpen = FALSE;
    uint8_t prevJoypad;
    while(1)
    {
        uint8_t auxCam = camOpen;
        uint8_t currentJoypad = joypad();

        if(currentJoypad & J_LEFT)
        {
            prevJoypad = currentJoypad;
        }
        else if(currentJoypad & J_RIGHT)
        {
            prevJoypad = currentJoypad;
        }
        else if(currentJoypad & J_DOWN)
        {
            if(prevJoypad != J_DOWN)
            {
                if(camOpen == FALSE)
                {
                    camOpen = TRUE;
                }
                else
                {
                    camOpen = FALSE;
                }
            }
            prevJoypad = currentJoypad;
        }
        else
        {
            prevJoypad = 0;
        }

        if(camOpen != auxCam)
        {
            if(camOpen == FALSE)
            {
                set_bkg_data(0, 41, fonte);
                set_bkg_tiles(0, 0, officeMapWidth, officeMapHeight, officeMap);
            }
            else
            {
                set_bkg_data(0, 6, camTiles);
                set_bkg_tiles(0, 0, CamMapWidth, CamMapHeight, CamMap);
            }
        }
    }
}

void extras(void){

}

void minigame(void){

}

void main(void){
    //ver se tem a variavel salva
    currentNight = 1;
    menu();
}