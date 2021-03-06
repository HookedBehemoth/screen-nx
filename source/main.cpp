/*
 * Copyright (c) 2019-2020 ShareNX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <switch.h>

#include "ui/MainApplication.hpp"
#include "util/set.hpp"

using namespace pu::ui::render;

int main(int argc, char *argv[]) {
	socketInitializeDefault();
#ifdef __DEBUG__
	nxlinkStdio();
#endif
	capsaInitialize();
	printf("starting...\n");
	try {
		auto renderer = Renderer::New(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER,
									  RendererInitOptions::RendererNoSound, RendererHardwareFlags);
		auto main = ui::MainApplication::New(renderer);
		main->Prepare();
		main->Show();
	} catch (std::exception &e) {
		printf("An error occurred:\n%s\n", e.what());
	} catch (...) {
		printf("Unknown exception\n");
	}
	printf("exiting\n");
	romfsExit();
	capsaExit();
	socketExit();
	return 0;
}
