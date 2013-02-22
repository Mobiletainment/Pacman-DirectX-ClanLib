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
#include "program.h"
#include "Game.h"

int Program::main(const std::vector<CL_String> &args)
{
	try
	{
		// Start the Game
		Game* game=new Game();
		game->Start();
		return 0;
	}
	catch(CL_Exception &exception)
	{
		// Create a console window for text-output if not available
		CL_ConsoleWindow console("Console", 80, 160);
		CL_Console::write_line("Exception caught: " + exception.get_message_and_stack_trace());
		console.display_close_message();

		return -1;
	}
}

// Instantiate CL_ClanApplication, informing it where the Program is located
CL_ClanApplication app(&Program::main);
