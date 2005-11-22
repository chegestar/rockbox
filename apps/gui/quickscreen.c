/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2005 by Kevin Ferrare
 *
 * All files in this archive are subject to the GNU General Public License.
 * See the file COPYING in the source tree root for full license agreement.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ****************************************************************************/

#include "quickscreen.h"
#ifdef HAS_QUICKSCREEN

#include "icons.h"
#include "textarea.h"
#include "font.h"
#include "kernel.h"
#include "misc.h"
#include "statusbar.h"

void gui_quickscreen_init(struct gui_quickscreen * qs,
                          struct option_select *left_option,
                          struct option_select *bottom_option,
                          struct option_select *right_option,
                          char * left_right_title,
                          quickscreen_callback callback)
{
    qs->left_option=left_option;
    qs->bottom_option=bottom_option;
    qs->right_option=right_option;
    qs->left_right_title=left_right_title;
    qs->callback=callback;
}

void gui_quickscreen_draw(struct gui_quickscreen * qs, struct screen * display)
{
    int w,h;
    char buffer[30];
    const char * option;
    const char * title;
#ifdef HAS_BUTTONBAR
    display->has_buttonbar=false;
#endif
    gui_textarea_clear(display);
    display->getstringsize("M",&w,&h);
    /* Displays the icons */
    display->mono_bitmap(bitmap_icons_7x8[Icon_FastBackward],
                         display->width/2 - 16,
                         display->height/2 - 4, 7, 8);
    display->mono_bitmap(bitmap_icons_7x8[Icon_DownArrow],
                         display->width/2 - 3,
                         display->height - h*3, 7, 8);
    display->mono_bitmap(bitmap_icons_7x8[Icon_FastForward],
                         display->width/2 + 8,
                         display->height/2 - 4, 7, 8);
    display->setfont(FONT_SYSFIXED);

    /* Displays the left's text */
    title=option_select_get_title(qs->left_option);
    option=option_select_get_text(qs->left_option, buffer, sizeof buffer);
    display->putsxy(0, display->height/2 - h*2, title);
    display->putsxy(0, display->height/2 - h, qs->left_right_title);
    display->putsxy(0, display->height/2, option);

    /* Displays the bottom's text */
    title=option_select_get_title(qs->bottom_option);
    option=option_select_get_text(qs->bottom_option, buffer, sizeof buffer);
    display->getstringsize(title, &w, &h);
    display->putsxy((display->width-w)/2, display->height - h*2, title);
    display->getstringsize(option, &w, &h);
    display->putsxy((display->width-w)/2, display->height - h, option);

    /* Displays the right's text */
    title=option_select_get_title(qs->right_option);
    option=option_select_get_text(qs->right_option, buffer, sizeof buffer);
    display->getstringsize(title,&w,&h);
    display->putsxy(display->width - w, display->height/2 - h*2, title);
    display->getstringsize(qs->left_right_title,&w,&h);
    display->putsxy(display->width - w, display->height/2 - h, qs->left_right_title);
    display->getstringsize(option,&w,&h);
    display->putsxy(display->width - w, display->height/2, option);

    gui_textarea_update(display);
    lcd_setfont(FONT_UI);
}

void gui_syncquickscreen_draw(struct gui_quickscreen * qs)
{
    int i;
    FOR_NB_SCREENS(i)
        gui_quickscreen_draw(qs, &screens[i]);
}

bool gui_quickscreen_do_button(struct gui_quickscreen * qs, int button)
{
    switch(button)
    {
        case QUICKSCREEN_LEFT :
        case QUICKSCREEN_LEFT | BUTTON_REPEAT :
#ifdef QUICKSCREEN_RC_LEFT
        case QUICKSCREEN_RC_LEFT :
        case QUICKSCREEN_RC_LEFT | BUTTON_REPEAT :
#endif
            option_select_next(qs->left_option);
            return(true);

        case QUICKSCREEN_BOTTOM :
        case QUICKSCREEN_BOTTOM | BUTTON_REPEAT :
#ifdef QUICKSCREEN_RC_BOTTOM
        case QUICKSCREEN_RC_BOTTOM :
        case QUICKSCREEN_RC_BOTTOM | BUTTON_REPEAT :
#endif
            option_select_next(qs->bottom_option);
            return(true);

        case QUICKSCREEN_RIGHT :
        case QUICKSCREEN_RIGHT | BUTTON_REPEAT :
#ifdef QUICKSCREEN_RC_RIGHT
        case QUICKSCREEN_RC_RIGHT :
        case QUICKSCREEN_RC_RIGHT | BUTTON_REPEAT :
#endif
            option_select_next(qs->right_option);
            return(true);

        case QUICKSCREEN_BOTTOM_INV :
        case QUICKSCREEN_BOTTOM_INV | BUTTON_REPEAT :
#ifdef QUICKSCREEN_RC_BOTTOM_INV
        case QUICKSCREEN_RC_BOTTOM_INV :
        case QUICKSCREEN_RC_BOTTOM_INV | BUTTON_REPEAT :
#endif
            option_select_prev(qs->bottom_option);
            return(true);
    }
    return(false);
}

bool gui_syncquickscreen_run(struct gui_quickscreen * qs)
{
    int key;
    gui_syncquickscreen_draw(qs);
    while (true) {
        key = button_get(true);
        if(default_event_handler(key) == SYS_USB_CONNECTED)
            return(true);
        if(gui_quickscreen_do_button(qs, key))
        {
            if(qs->callback)
                qs->callback(qs);
            gui_syncquickscreen_draw(qs);
        }
        else if(key==QUICKSCREEN_QUIT
#ifdef QUICKSCREEN_QUIT
                || key==QUICKSCREEN_QUIT
#endif
#ifdef QUICKSCREEN_QUIT2
                || key==QUICKSCREEN_QUIT2
#endif
#if QUICKSCREEN_RC_QUIT
                || key==QUICKSCREEN_RC_QUIT
#endif
        )
        {
            return(false);
        }
        gui_syncstatusbar_draw(&statusbars, false);
    }
}

#endif /* HAS_QUICKSCREEN */

