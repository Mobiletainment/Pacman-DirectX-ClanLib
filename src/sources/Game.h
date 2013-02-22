/*
 * Pacman
 * Copyright (C) 2012 David Pertiller <http://pertiller.me>
 * Basic set up by Patrick Schwarz
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once
#include "precomp.h"
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/application.h>
#include "Level.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GameMode.h"


class Game
{
private:
	static void on_key_down(const CL_InputEvent& event, const CL_InputState& state);
	CL_Slot  slot_key_down;
	static CL_Timer *switchGameModeTimer;
	static GameMode _gameMode;
	static AutoSwitchMode _autoSwitch;
	static string gameInfoString;
	static void UpdateGameInfoString();
	void Update();
	static void ToggleGameMode();
public:
	Game(void);
	static KI::Level *Level;
	static KI::Pacman *Pacman;
	static KI::Ghost *Blinky;
	static KI::Ghost *Pinky;
	static KI::Ghost *Inky;
	static KI::Ghost *Clyde;
	void Start();
	~Game(void);
};

