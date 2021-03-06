/*==============================================================================

	main.h

	joyosc: a device event to osc bridge
  
	Copyright (C) 2007, 2010 Dan Wilcox <danomatika@gmail.com>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/

#include "App.h"

int main(int argc, char **argv) {

	// init config settings
	if(!Config::instance().parseCommandLine(argc, argv)) {
		return EXIT_FAILURE;
	}

	// init SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		LOG_ERROR << "could not init SDL: " << SDL_GetError() << endl;
		return EXIT_FAILURE;
	}
	
	// init subsystem
	if(Config::instance().joysticksOnly) {
		if(SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0) {
			LOG_ERROR << "could not init SDL joystick support: " << SDL_GetError() << endl;
			return EXIT_FAILURE;
		}
	}
	else {
		if(SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) {
			LOG_ERROR << "could not init SDL game controller support: " << SDL_GetError() << endl;
			return EXIT_FAILURE;
		}
	}
	if(SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1") == SDL_FALSE) {
		LOG_WARN << "could not set joystick background events" << endl;
	}

	// run the application
	App app;
	app.run();
	
	// cleanup SDL
	SDL_Quit();

	return EXIT_SUCCESS;
}
