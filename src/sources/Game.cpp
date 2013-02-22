/*
 * Pacman
 * Copyright (C) 2012 David Pertiller <http://pertiller.me>
 * Basic set up by Patrick Schwarz
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "precomp.h"
#include "Game.h"
#include "Direction.h"
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"
#include <ClanLib\Display\2D\color.h>
#include "FrameRateCounter.h"

#define SWITCHTIME 10000

KI::Pacman *Game::Pacman;
KI::Ghost *Game::Blinky;
KI::Ghost *Game::Pinky;
KI::Ghost *Game::Inky;
KI::Ghost *Game::Clyde;

KI::Level *Game::Level;
GameMode Game::_gameMode;
AutoSwitchMode Game::_autoSwitch;
CL_Timer *Game::switchGameModeTimer;
string Game::gameInfoString;

Game::Game(void)
{
	Pacman=NULL;
	_gameMode = GameMode::Patrol;
}

void Game::UpdateGameInfoString()
{
	string gameModeInfo;
	string gameModeInfoInactive;
	
	switch (_gameMode)
	{
	case Patrol:
		gameModeInfo = "Patrol";
		gameModeInfoInactive = "Pursuit";
		break;
	case Pursuit:
		gameModeInfo = "Pursuit";
		gameModeInfoInactive = "Frightened";
		break;
	case Frightened:
		gameModeInfo = "Frightened";
		gameModeInfoInactive = "Patrol";
		break;
	}

	string autoSwitchInfo = (_autoSwitch == Enabled) ? "(automatically switching Modes every 10 seconds - " : "";
	string autoSwitchButton = (_autoSwitch == Enabled) ? "Press [2] to disable)" : "(Press [Space] to activate " + gameModeInfoInactive + " Mode or [1] to enable autoswitching)";

	gameInfoString = "Movement = [W,S,A,D] or Arrow Keys\n";
	gameInfoString += "GameMode = " + gameModeInfo + " " + autoSwitchInfo + autoSwitchButton;
}

void Game::on_key_down(const CL_InputEvent& event, const CL_InputState& state)
{
	if (event.type == event.pressed)
	{
		//check Movement (WSAD or Arrows)
 		if (event.id == CL_KEY_A || event.id ==  37) //Left = A or Arrow Left
			Pacman->Move(Left);
		else if (event.id == CL_KEY_D || event.id == 39) //Right = D or Arrow right
			Pacman->Move(Right);
		else if (event.id == CL_KEY_W || event.id == 38) //Up = W or Arrow Up
			Pacman->Move(Top);
		else if (event.id == CL_KEY_S || event.id == 40) //Down = S or Arrow Down
			Pacman->Move(Bottom);

		else if (event.id == CL_KEY_SPACE) //Toogle GameMode
		{
				_autoSwitch = Disabled;
				switchGameModeTimer->stop();
				ToggleGameMode();
				UpdateGameInfoString();
		}
		else if (event.id == CL_KEY_1) //Enable Autoswtiching GameMode
		{
			_autoSwitch = Enabled;
			switchGameModeTimer->start(SWITCHTIME, true);
			UpdateGameInfoString();
		}
		else if (event.id == CL_KEY_2) //Disable Autoswitching GameMode
		{
			_autoSwitch = Disabled;
			switchGameModeTimer->stop();
			UpdateGameInfoString();
		}
	}
}

void Game::Start()
{
		CL_SetupCore setup_core;
		CL_SetupDisplay setup_display;
		CL_SetupGL setup_gl;

		CL_DisplayWindow window("Pacman", 708, 862);

		CL_GraphicContext& gc = window.get_gc();
		CL_InputDevice keyboard = window.get_ic().get_keyboard();
		CL_Font font(gc, "Tahoma", 20);

		slot_key_down = keyboard.sig_key_down().connect(&Game::on_key_down);
		
		_autoSwitch = Disabled;
		UpdateGameInfoString();
		Level =new KI::Level(gc);
		Pacman = new KI::Pacman(gc, Level->GetTileForPacman());
		Blinky = new KI::Blinky(gc, Level->GetTileAtGridPosition(15, 11));
		Pinky = new KI::Pinky(gc, Level->GetTileAtGridPosition(12, 11));	
		Inky = new KI::Inky(gc, Level->GetTileAtGridPosition(14, 11));	
		Clyde = new KI::Clyde(gc, Level->GetTileAtGridPosition(13, 11));	

		CL_Timer* updateTimer=new CL_Timer();
		updateTimer->func_expired().set(this, &Game::Update);
		updateTimer->start((unsigned int)(1000.0f/60.0f), true); //Game Loop with 60FPS

		switchGameModeTimer = new CL_Timer(); //if timer is running, it will toggle the GameMode every 10s
		switchGameModeTimer->func_expired().set(&Game::ToggleGameMode);

		FramerateCounter frameratecounter; //calculates the FPS

		while (!keyboard.get_keycode(CL_KEY_ESCAPE))
		{
			gc.clear(CL_Colorf::black);
	
			Level->Render();
			Pacman->Render();
			Blinky->Render();
			Pinky->Render();
			Inky->Render();
			Clyde->Render();

			font.draw_text(gc, 20.0f, 795.0f, gameInfoString, CL_Colorf::white);
			CL_String fps = cl_format("%1 fps", frameratecounter.get_framerate());
			font.draw_text(gc, 20, 30, fps);

			// Make the stuff visible:
			window.flip();
			frameratecounter.frame_shown();

			// Read messages from the windowing system message queue, if any are available:
			CL_KeepAlive::process();
 
			// Avoid using 100% CPU in the loop:
			CL_System::sleep(1);
		}
}

void Game::Update()
{
	//Calculate the new positions
	Pacman->Update();
	Blinky->Update();
	Pinky->Update();
	Inky->Update();
	Clyde->Update();
}

void Game::ToggleGameMode() //Switch from Patrol to Pursuit and Vice Versa
{
	switch (_gameMode)
	{
	case Patrol:
		_gameMode = Pursuit;
		break;
	case Pursuit:
		_gameMode = Frightened;
		break;
	case Frightened:
		_gameMode = Patrol;
		break;
	}

	UpdateGameInfoString();

	Blinky->NotifyGameModeChanged(_gameMode); //Notify ghosts about new GameMode
	Pinky->NotifyGameModeChanged(_gameMode); //Notify ghosts about new GameMode
	Inky->NotifyGameModeChanged(_gameMode);
	Clyde->NotifyGameModeChanged(_gameMode);
}

Game::~Game(void)
{
}
