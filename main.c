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

// Main menu variables
Vector2 menuLogoPosition;
Rectangle recGames[MAX_GAMES] = { 0 };
Rectangle recGamesCoord = {45.0f, 160.0f, 100.0f, 100.0f};
Vector2 mousePos;

static const int screenWidth = 1280;
static const int screenHeight = 720;

static void UpdateDrawFrame(void);

EM_JS(void, redirect_page, (), {
	window.location.href = "https://www.google.com";		
})

int main(void){
    InitWindow(screenWidth, screenHeight, "Ajav - Raylib Friv");

    menuLogo = LoadTexture("resources/main_menu/ajav_logo_NOBG.png");
    menuLogoPosition.x = screenWidth/2 - menuLogo.width/2;
    menuLogoPosition.y = screenHeight/2 - menuLogo.height/2 - 300;

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
	if(IsKeyDown(KEY_SPACE)){
		redirect_page();
	}
	BeginDrawing();
		DrawTextureV(menuLogo, menuLogoPosition, WHITE);
		DrawLine(0, 120, 1280, 120, DARKGRAY);
		DrawRectangleLines(25, 140, screenWidth - 50, screenHeight - 165, guiRect);
		for(int i = 0; i < MAX_GAMES; i++){
			DrawRectangleLinesEx(recGames[i], 2, guiRect);
		}
	EndDrawing();
}
