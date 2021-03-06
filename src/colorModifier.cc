/* colorModifier.cc
   allow to modify the color of a cell

   Copyright (C) 2000  Mathias Broxvall
                       Yannick Perret

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

#include "colorModifier.h"
#include "game.h"
#include "map.h"

ColorModifier::ColorModifier(int col, int x, int y, Real min, Real max, Real freq,
                             Real phase) {
  this->x = x;
  this->y = y;
  this->min = min;
  this->max = max;
  this->freq = freq;
  this->phase = phase;
  if ((col < 0) || (col > 3)) {
    warning("erroneous color ID (%d) of ColorModifier (%d,%d). Using '0' instead.", col, x, y);
    col = 0;
  }
  this->colors = col;
  // not used
  position[0] = 0.;
  position[1] = 0.;
  position[2] = 0.;
  primaryColor[0] = 1.;
  primaryColor[1] = 1.;
  primaryColor[2] = 1.;
  secondaryColor[0] = 1.;
  secondaryColor[1] = 1.;
  secondaryColor[2] = 1.;
  is_on = 1;
}

int ColorModifier::generateBuffers(GLuint*& /*idxbufs*/, GLuint*& /*databufs*/) { return 0; }
void ColorModifier::drawBuffers1(GLuint* /*idxbufs*/, GLuint* /*databufs*/) {}
void ColorModifier::drawBuffers2(GLuint* /*idxbufs*/, GLuint* /*databufs*/) {}

void ColorModifier::tick(Real /*t*/) {
  double tt = Game::current->gameTime;
  Cell& c = Game::current->map->cell(x, y);
  if (!is_on) return;
  float v = min + (max - min) * (1. + cos(phase + (tt * freq) * 2. * 3.14159)) / 2.;
  switch (colors) {
  case 0:
    for (int i = 0; i < 5; i++) {
      c.colors[i][0] = v;
      c.colors[i][1] = v;
      c.colors[i][2] = v;
    }
    break;
  case 1:
    for (int i = 0; i < 5; i++) c.colors[i][0] = v;
    break;
  case 2:
    for (int i = 0; i < 5; i++) c.colors[i][1] = v;
    break;
  case 3:
    for (int i = 0; i < 5; i++) c.colors[i][2] = v;
    break;
  }
  Game::current->map->markCellUpdated(x, y);
}
