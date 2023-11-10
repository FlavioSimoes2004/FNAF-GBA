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
#include "animatronics.h"
#include "ventilador.h"

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
    //y = 80 = new game
    //y = 97 = continue
    //y = 114 = extras
    uint8_t prevJoypad, currentJoypad;
    while(1)
    {
        currentJoypad = joypad();

        if(currentJoypad & J_DOWN)
        {
            if(prevJoypad != J_DOWN)
            {
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
            }
            prevJoypad = J_DOWN;
        }
        else if(currentJoypad & J_UP)
        {
            if(prevJoypad != J_UP)
            {
                if(setaY == 114)
                {
                    setaY = 97;
                }
                else if(setaY == 97)
                {
                    setaY = 80;
                }
                else
                {
                    setaY = 114;
                }
            }
            prevJoypad = J_UP;
        }
        else if(currentJoypad & J_A)
        {
            if(setaY == 80)
            {
                tutorial();
            }
            else if(setaY == 97)
            {
                night();
            }
            else
            {
                //extras
            }
        }
        else
        {
            prevJoypad = 0;
        }

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
    hide_sprite(0);
    set_bkg_data(0, 41, fonte);
    set_bkg_tiles(0, 0, 20, 18, tutorialmap);

    waitpad(J_START);

    night();
}

void night(void){
    set_bkg_data(0, 41, fonte);
    set_bkg_tiles(0, 0, officeMapWidth, officeMapHeight, officeMap);

    //animatronics
    set_sprite_data(0, 7, animatronics);
    uint8_t currentCharacter = 0;
    uint8_t robotNb = 0;
    set_sprite_tile(0, currentCharacter);

    //freddy
    uint8_t freddySprite = 0;
    uint8_t posFreddy = 0;

    //bonnie
    uint8_t bonnieSprite = 1;
    uint8_t posBonnie = 0;

    //chica
    uint8_t chicaSprite = 2;
    uint8_t posChica = 0;

    //foxy
    uint8_t posFoxy = 5;

    //-------------------------------------------------//
    //ventilador
    set_sprite_data(7, 3, ventilador);
    uint8_t ventiY = 75;
    uint8_t currentVentiIndex = 7;
    uint8_t ventiNb = 1;
    set_sprite_tile(1, 4);

    uint8_t ventiBaseNb = 2;
    set_sprite_tile(2, 9);

    move_sprite(ventiNb, 75, ventiY);
    move_sprite(ventiBaseNb, 75, ventiY + 8);

    uint32_t currentTime = 0;
    uint32_t maxTime = 10000; //1 segundo, nao é o tempo do jogo
    uint8_t hour = 0; //horas do jogo, quando isso aki ficar 6 o jogador passa

    uint8_t camOpen = FALSE;
    uint8_t prevJoypad;
    while(1)
    {
        uint8_t auxCam = camOpen;
        uint8_t currentJoypad = joypad();

        if(currentJoypad & J_LEFT)
        {
            if(prevJoypad != J_LEFT)
            {
                if(camOpen == TRUE)
                {
                    //trocar personagem
                    if(currentCharacter == 0)
                    {
                        currentCharacter = 3;
                    }
                    else
                    {
                        currentCharacter--;
                    }
                }
                else
                {
                    //fechar porta esquerda
                }
            }
            prevJoypad = currentJoypad;
        }
        else if(currentJoypad & J_RIGHT)
        {
            if(prevJoypad != J_RIGHT)
            {
                if(camOpen == TRUE)
                {
                    if(currentCharacter == 3)
                    {
                        currentCharacter = 0;
                    }
                    else
                    {
                        currentCharacter++;
                    }
                }
                else
                {
                    //fechar porta esquerda
                }
            }
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
                //esconde sprite animatronic
                hide_sprite(robotNb);

                //aparece sprite do escritorio
                move_sprite(ventiNb, 75, 75);
                move_sprite(ventiBaseNb, 75, ventiY + 8);

                set_bkg_data(0, 41, fonte);
                set_bkg_tiles(0, 0, officeMapWidth, officeMapHeight, officeMap);
            }
            else //camOpen == TRUE
            {
                //desaparece sprite escritorio
                hide_sprite(ventiNb);
                hide_sprite(ventiBaseNb);

                //aparece sprites da camera
                move_sprite(0, 75, 75);
                set_bkg_data(0, 10, camTiles);
                set_bkg_tiles(0, 0, CamMapWidth, CamMapHeight, CamMap);
            }
        }
        else //camOpen == auxCam
        {
            if(camOpen == FALSE)
            {
                set_sprite_tile(ventiNb, currentVentiIndex);
            }
            else //camOpen == TRUE
            {
                if(currentCharacter == 0) //freddy
                {
                    if(posFreddy == 0)
                    {
                        set_sprite_tile(robotNb, freddySprite);
                        move_sprite(robotNb, 85, 37);
                    }
                }
                else if(currentCharacter == 1) //bonnie
                {
                    if(posBonnie == 0)
                    {
                        set_sprite_tile(robotNb, bonnieSprite);
                        move_sprite(robotNb, 70, 37);
                    }
                }
                else if(currentCharacter == 2) //chica
                {
                    if(posChica == 0)
                    {
                        set_sprite_tile(robotNb, chicaSprite);
                        move_sprite(robotNb, 100, 37);
                    }
                }
                else //foxy
                {
                    if(posFoxy == 0)
                    {
                        set_sprite_tile(robotNb, 3);
                    }
                    else if(posFoxy == 1)
                    {
                        set_sprite_tile(robotNb, 4);
                    }
                    else if(posFoxy == 2)
                    {
                        set_sprite_tile(robotNb, 5);
                    }
                    else
                    {
                        set_sprite_tile(robotNb, 6);
                    }

                    if(posFoxy <= 5)
                    {
                        move_sprite(robotNb, 45, 60);
                    }
                }
            }
        }

        if(currentTime >= maxTime)
        {
            currentTime = 0;
            currentVentiIndex = 7;
        }
        else
        {
            if(currentTime == maxTime / 2)
            {
                currentVentiIndex = 8;
            }
            currentTime++;
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