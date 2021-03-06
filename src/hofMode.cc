/** \file hofMode.cc
   Displayes the "Hall of Fame"
*/
/*
   Copyright (C) 2000  Mathias Broxvall

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "hofMode.h"

#include "font.h"
#include "highScore.h"
#include "menuMode.h"
#include "menusystem.h"
#include "settings.h"

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_surface.h>

HallOfFameMode *HallOfFameMode::hallOfFameMode;
SDL_Surface *HallOfFameMode::background;

#define CODE_LEVELSET 1

void HallOfFameMode::init() {
  if (low_memory)
    background = NULL;
  else {
    background = loadImage("displayHighscoreBackground.jpg");
  }
  hallOfFameMode = new HallOfFameMode();
}
HallOfFameMode::HallOfFameMode() {
  levelSet = 0;
  timeLeft = 0.;
  isExiting = 0;
}
void HallOfFameMode::activated() {
  if (!background) { background = loadImage("displayHighscoreBackground.jpg"); }

  /* Loads the background images. */
  texture = LoadTexture(background, texCoord);
  isExiting = 0;
  timeLeft = 1.0;
}
void HallOfFameMode::deactivated() {
  glDeleteTextures(1, &texture);
  if (low_memory && background) {
    SDL_FreeSurface(background);
    background = NULL;
  }
}
void HallOfFameMode::display() {
  char str[256];

  // Draw the background using the preloaded texture
  Enter2DMode();
  draw2DRectangle(0, 0, screenWidth, screenHeight, texCoord[0], texCoord[1], texCoord[2],
                  texCoord[3], timeLeft, timeLeft, timeLeft, 1., texture);

  int y, dy, size, x;
  if (screenWidth <= 640)
    x = 300;
  else if (screenWidth <= 800)
    x = 350;
  else if (screenWidth <= 1024)
    x = 400;
  else
    x = 450;
  if (screenHeight <= 480) {
    y = 160;
    dy = 32;
    size = 16;
  } else if (screenHeight <= 600) {
    y = 200;
    dy = 40;
    size = 20;
  } else if (screenHeight <= 768) {
    y = 280;
    dy = 52;
    size = 24;
  } else {
    y = 300;
    dy = 58;
    size = 24;
  }

  int fontSize = size * 2;
  int col0 = screenWidth / 2 - x;  // screenWidth/2 - 400;
  int col1 = screenWidth / 2 + x + fontSize / 2;
  Settings *settings = Settings::settings;
  clearSelectionAreas();
  addText_Left(0, fontSize / 2, y - dy * 2, _("Level Set"), col0);
  addText_Right(CODE_LEVELSET, fontSize / 2, y - dy * 2, settings->levelSets[levelSet].name,
                col1);

  HighScore *highscore = HighScore::highScore;

  for (int i = 0; i < 10; i++) {
    Font::drawSimpleText(&highscore->names[levelSet][i][0], screenWidth / 2 - x,
                         y + dy * i - size, size, menuColor[0], menuColor[1], menuColor[2],
                         menuColor[3]);
    snprintf(str, sizeof(str), _("%d points"), highscore->points[levelSet][i]);
    Font::drawRightSimpleText(str, screenWidth / 2 + x + size / 2, y + dy * i - size, size,
                              menuColor[0], menuColor[1], menuColor[2], menuColor[3]);
  }

  drawMousePointer();
  displayFrameRate();

  Leave2DMode();
}
void HallOfFameMode::key(int key) {
  if (key == SDLK_SPACE) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    mouseDown(1, x, y);
  }
  if (key == SDLK_RETURN) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    mouseDown(3, x, y);
  }
}
void HallOfFameMode::idle(Real td) {
  if (isExiting)
    timeLeft = fmax(0.0, timeLeft - td);
  else
    timeLeft = fmin(1.0, timeLeft + td);
  if (timeLeft <= 0.0) MenuMode::activate(MenuMode::menuMode);
  tickMouse(td);
}
void HallOfFameMode::mouseDown(int state, int /*mouseX*/, int /*mouseY*/) {
  int selection = getSelectedArea();
  if (selection == CODE_LEVELSET) {
    levelSet = mymod((levelSet + (state == 1 ? 1 : -1)), Settings::settings->nLevelSets);
  } else {
    isExiting = 1;
    timeLeft = 1.0;
  }
}
