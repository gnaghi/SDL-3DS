/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2014 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "../../SDL_internal.h"

#if SDL_VIDEO_DRIVER_3DS

/* Being a null driver, there's no event stream. We just define stubs for
   most of the API. */

#include "SDL.h"
#include "../../events/SDL_sysevents.h"
#include "../../events/SDL_events_c.h"

#include <3ds.h>
#include "SDL_3dsvideo.h"
#include "SDL_3dsevents_c.h"

static struct {
    int id;
    SDL_Keycode sym;
} keymap[] = {
    { KEY_A, SDLK_a },
    { KEY_B, SDLK_b },
    { KEY_R, SDLK_r },
    { KEY_L, SDLK_l },
    { KEY_X, SDLK_x },
    { KEY_Y, SDLK_y },
    { KEY_SELECT, SDLK_SELECT },
    { KEY_START, SDLK_MENU },
    { KEY_DRIGHT, SDLK_RIGHT },
    { KEY_DLEFT, SDLK_LEFT },
    { KEY_DUP, SDLK_UP },
    { KEY_DDOWN, SDLK_DOWN }
};

void N3DS_PumpEvents(_THIS)
{
    u32 keys;
    int max = sizeof(keymap) / sizeof(keymap[0]);

    //Scan all the inputs. This should be done once for each frame
    hidScanInput();

    //hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
    keys = hidKeysDown();
    for (int i = 0; i < max; ++i)
    {
        if (keys & keymap[i].id)
        {
            SDL_SendKeyboardKey(SDL_PRESSED, SDL_GetScancodeFromKey(keymap[i].sym));
        }
    }

    keys = hidKeysUp();
    for (int i = 0; i < max; ++i)
    {
        if (keys & keymap[i].id)
        {
            SDL_SendKeyboardKey(SDL_RELEASED, SDL_GetScancodeFromKey(keymap[i].sym));
        }
    }
    return;
}

void N3DS_EventInit(_THIS)
{
    hidInit();
}

void N3DS_EventQuit(_THIS)
{
    hidExit();
}

/* end of SDL_3dsevents.c ... */

#endif /* SDL_VIDEO_DRIVER_3DS */

/* vi: set ts=4 sw=4 expandtab: */
