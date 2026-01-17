#include <raylib.h>
#include <emscripten/emscripten.h>

static Rectangle player = {400, 400, 40, 40};
static Camera2D camera = {0};

static const int screenWidth = 1280;
static const int screenHeight = 720;

static void UpdateDrawFrame(void);

int main(){
	InitWindow(screenWidth, screenHeight, "weakpompaelo");

	camera.target = (Vector2){player.x, player.y};
	camera.offset = (Vector2){50, screenHeight/2};

	emscripten_set_main_loop(UpdateDrawFrame, 60, 1);

	CloseWindow();
	return 0;
}

static void UpdateDrawFrame(void){
		ClearBackground(DARKGRAY);
		if(IsKeyDown(KEY_DOWN)){
			player.y += 2;
		}
		if(IsKeyDown(KEY_UP)){
			player.y -= 2;
		}
		if(IsKeyDown(KEY_RIGHT)){
			player.x += 2;
		}
		if(IsKeyDown(KEY_LEFT)){
			player.x -= 2;
		}

		camera.target = (Vector2){player.x, player.y};
		camera.zoom = 1.0f;
		BeginDrawing();
			BeginMode2D(camera);
				DrawRectangle(400, 400, 50, 50, WHITE);
				DrawRectangleRec(player, RED);
				DrawText("player", player.x + 6, player.y + 12, 10, BLUE);
			EndMode2D();
			DrawText("player", player.x - 20.0f, player.y - 20.0f, 10, DARKGRAY);
			DrawText("jogo teste, nao esta completo ainda!", 0, 0, 10, WHITE);
		EndDrawing();
}
