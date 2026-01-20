#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <emscripten/emscripten.h>

static Rectangle Scene1 = {0, 130, 1280, 125};
static Rectangle Scene2 = {1280, 130, 1280, 125};
static float loopReference = 1280.0f;
static Vector2 player = {175, 100};
static Camera2D camera = {0};

static Texture2D playerSprite;

static bool pause = false;

static const int screenWidth = 1280;
static const int screenHeight = 720;

static void UpdateDrawFrame(void);

EM_JS(bool, exitWindow, (), {
	return document.hidden || document.visiblityState === 'hidden';
})

int main(){
	InitWindow(screenWidth, screenHeight, "weakpompaelo");
	
	playerSprite = LoadTexture("resources/player.png");

	camera.target = (Vector2){0, -screenHeight/2};
	camera.offset = (Vector2){0, 0};
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	emscripten_set_main_loop(UpdateDrawFrame, 60, 1);

	CloseWindow();
	return 0;
}

static void UpdateDrawFrame(void){
		float deltaTime = GetFrameTime();
		if(exitWindow() == true){
			pause = true;
		}

		if(IsKeyPressed(KEY_P) && pause){
			pause = false;
		}

		if(!pause){
			if(Scene1.x > -loopReference){
				Scene1.x -= 501 * deltaTime;
			}else{
				Scene1.x += loopReference*2;
			}

			if(Scene2.x > -loopReference){
				Scene2.x -= 501 * deltaTime;
			}else{
				Scene2.x += loopReference*2;
			}
		
			if(IsKeyDown(KEY_LEFT)){
				player.x -= 100 * deltaTime;
			}
			if(IsKeyDown(KEY_RIGHT)){
				camera.target.x += 50 * deltaTime;
				player.x += 100 * deltaTime;
			}
		}
		ClearBackground(DARKGRAY);
		BeginDrawing();
			BeginMode2D(camera);
				DrawRectangleV((Vector2){Scene1.x, Scene1.y + player.y},(Vector2){Scene1.width, Scene1.height}, WHITE);
				DrawRectangleV((Vector2){Scene2.x, Scene2.y + player.y},(Vector2){Scene2.width, Scene2.height}, BLUE);
				DrawTextureV(playerSprite, player, WHITE);
			EndMode2D();
			if(!pause){
				DrawText("em producao...", 0, 0, 50, WHITE);
			}else{
				DrawText("pausado! aperte P para continuar", 0, 0, 35, RED);
			}
		EndDrawing();
}
