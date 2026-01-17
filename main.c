/*******************************************************************************************
*
*   Ajav - Alternative Friv
*
*   Website developed by AndrewsGoes
*
*   This website has been created using raylib v5.5 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#include <stdio.h>
#include "raylib.h"
#include <emscripten/emscripten.h>

#define MAX_GAMES 34

// Main menu colors
Color menuBackground = {0xE0, 0x71, 0x35, 0xff};
Color guiRect = {0xff, 0xff, 0xff, 0xff};

// Main menu images
Texture2D menuLogo;
Texture2D games[1];

// Main menu variables
Vector2 menuLogoPosition;
Vector2 gamesPosition[1];
Rectangle recGames[MAX_GAMES] = { 0 };
Rectangle recGamesCoord = {45.0f, 160.0f, 100.0f, 100.0f};
Vector2 mousePos;

static const int screenWidth = 1280;
static const int screenHeight = 720;

static void UpdateDrawFrame(void);

EM_JS(void, redirect_page, (), {
	window.location.href = "games/weakpompaelo/index.html";		
})

int main(void){
    InitWindow(screenWidth, screenHeight, "Ajav - Raylib Friv");

    menuLogo = LoadTexture("resources/main_menu/ajav_logo_NOBG.png");
    games[0] = LoadTexture("resources/games/weakpompaelo.png");
    menuLogoPosition.x = screenWidth/2 - menuLogo.width/2;
    menuLogoPosition.y = screenHeight/2 - menuLogo.height/2 - 300;
    gamesPosition[0].x = recGamesCoord.x;
    gamesPosition[0].y = recGamesCoord.y;

    for(int i = 1; i < MAX_GAMES; i++){
	recGames[i].x = recGamesCoord.x;
	recGames[i].y = recGamesCoord.y;
	recGames[i].width = recGamesCoord.width;
	recGames[i].height = recGamesCoord.height;
	recGamesCoord.x += 108.0f;
	if(i % 11 == 0){
		recGamesCoord.x = 45.0f;
		recGamesCoord.y += 115.0f;
	}
    }

    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);

    CloseWindow();
    return 0;
}

static void UpdateDrawFrame(void){
	ClearBackground(menuBackground);
	mousePos = GetMousePosition();
	BeginDrawing();
		if(CheckCollisionPointRec(mousePos, recGames[1]) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
			redirect_page();
		}
		DrawTextureV(menuLogo, menuLogoPosition, WHITE);
		DrawTextureV(games[0], gamesPosition[0], WHITE);
		DrawLine(0, 120, 1280, 120, DARKGRAY);
		DrawRectangleLines(25, 140, screenWidth - 50, screenHeight - 165, guiRect);
		for(int i = 0; i < MAX_GAMES; i++){
			DrawRectangleLinesEx(recGames[i], 2, guiRect);
		}
	EndDrawing();
}
