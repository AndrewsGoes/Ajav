#include <raylib.h>
#include <raymath.h>
#include <emscripten/emscripten.h>

static Rectangle Scene1 = {0, 130, 1280, 225};
static Rectangle Scene2 = {1280, 130, 1280, 225};
static Rectangle Obstacule = {0, 0, 300, 140};
static float loopReference = 1280.0f;
static Vector2 player = {375, 100};
static Camera2D camera = {0};

static Texture2D playerSprite;

static bool pause = false;
static bool maxJumpReach = false;
static bool hitObstacule = false;
static bool gameOver = false;

static const int screenWidth = 1280;
static const int screenHeight = 720;

static void UpdateDrawFrame(void);

EM_JS(bool, exitWindow, (), {
	return document.hidden || document.visiblityState === 'hidden';
})

int main(){
	InitWindow(screenWidth, screenHeight, "weakpompaelo");
	
	playerSprite = LoadTexture("resources/player.png");

	Obstacule.x = loopReference;
	Obstacule.y = 200;
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
		if(exitWindow() == true && !gameOver){
			pause = true;
		}

		if(IsKeyPressed(KEY_P) && pause){
			pause = false;
		}

		if(IsKeyPressed(KEY_SPACE) && gameOver){
			player.x = 375;
			player.y = 100;
			Scene1.x = 0;
			Scene2.x = loopReference;
			Obstacule.x = loopReference;
			gameOver = false;
		}
		if(!gameOver){
			if(!pause){
				player.x -= 100 * deltaTime;
			
				if(player.x <= 100){
					gameOver = true;
				}

				if(Scene1.x > -loopReference){
					Scene1.x -= 500.0f * deltaTime;
				}else{
					Scene1.x += loopReference*2;
				}

				if(Scene2.x > -loopReference){
					Scene2.x -= 500.0f * deltaTime;
				}else{
					Scene2.x += loopReference*2;
				}

				if(Obstacule.x > -Obstacule.width){
					Obstacule.x -= 350.0f * deltaTime;
				}else{
					Obstacule.x += loopReference + Obstacule.width;
				}
	
				if(IsKeyDown(KEY_SPACE) && !maxJumpReach){
					if(player.y >= -150){
						player.y -= 600 * deltaTime;
					}else{
						maxJumpReach = true;
					}
				}

				if(player.y <= 100){
					player.y += 200 * deltaTime;
				}else{
					maxJumpReach = false;
				}

				if(Obstacule.x <= player.x &&
			   	   Obstacule.x + Obstacule.width >= player.x &&
			   	   Obstacule.y - 220 <= player.y){
					hitObstacule = true;
					player.x -= 320 * deltaTime;
				}else{
					hitObstacule = false;
				}

				if(IsKeyDown(KEY_LEFT)){
					player.x -= 50 * deltaTime;
				}
				if(IsKeyDown(KEY_RIGHT)){
					player.x += 150 * deltaTime;
				}
			}
		}
		ClearBackground(DARKGRAY);
		BeginDrawing();
			BeginMode2D(camera);
				DrawRectangleV((Vector2){Scene1.x, Scene1.y},(Vector2){Scene1.width, Scene1.height}, WHITE);
				DrawRectangleV((Vector2){Scene2.x, Scene2.y},(Vector2){Scene2.width, Scene2.height}, BLUE);
				DrawRectangleV((Vector2){Obstacule.x, Obstacule.y - 120.5f},(Vector2){Obstacule.width, Obstacule.height}, RED);
				DrawRectangle(0, 0, 113, 400, DARKBROWN);
				DrawTextureV(playerSprite, player, WHITE);
			EndMode2D();
			if(hitObstacule){
				DrawText("HIT", Obstacule.x, 450, 25, YELLOW);
			}
			if(gameOver){
				DrawText("GAMEOVER", screenWidth/2 - 150, screenHeight/2 - 50, 50, PURPLE);
				DrawText("Press Space to continue", screenWidth/2 - 300, screenHeight/2 + 50, 50, PURPLE);
			}
			if(!pause){
				DrawText("rodando...", 0, 0, 50, WHITE);
			}else{
				DrawText("pausado! aperte P para continuar", 0, 0, 35, RED);
			}
			DrawText("BOI, CORRE!", 0, 400, 15, SKYBLUE);
		EndDrawing();
}
