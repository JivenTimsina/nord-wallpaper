#include <math.h>
#include <raylib.h>
#define screenWidth 1000
#define screenHeight 600
#define maxRect 100
int main() {
  InitWindow(screenWidth, screenHeight, "test window");

  int boxHeight;
  int boxWidth;
  int boxX, boxY;
  boxX = 0;
  Color buildcolor[maxRect] = {0};
  Rectangle rect[maxRect] = {0};
  Rectangle player = {(float)screenWidth / 2 - 50, (float)screenHeight / 2 - 50,
                      100, 100};

  for (int i = 0; i < maxRect; i++) {
    boxHeight = GetRandomValue(150, 300);
    boxWidth = GetRandomValue(70, 100);
    rect[i].height = boxHeight;
    rect[i].width = boxWidth;
    rect[i].x = boxX;
    rect[i].y = (float)screenHeight -
                ((float)(screenWidth - screenHeight) / 3) - rect[i].height;
    boxX += boxWidth;
    buildcolor[i] = (Color){(unsigned char)GetRandomValue(200, 240),
                            (unsigned char)GetRandomValue(200, 240),
                            (unsigned char)GetRandomValue(200, 250), 255};
  }

  Camera2D camera = {0};
  camera.target = (Vector2){player.x + 50.0f, player.y + 50.0f};
  camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;
  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    // Update
    //----------------------------------------------------------------------------------
    // Player movement
    if (IsKeyDown(KEY_RIGHT))
      player.x += 2;
    else if (IsKeyDown(KEY_LEFT))
      player.x -= 2;

    // Camera target follows player
    camera.target = (Vector2){player.x + 20, player.y + 20};

    // Camera rotation controls
    if (IsKeyDown(KEY_A))
      camera.rotation--;
    else if (IsKeyDown(KEY_S))
      camera.rotation++;

    // Limit camera rotation to 80 degrees (-40 to 40)
    if (camera.rotation > 40)
      camera.rotation = 40;
    else if (camera.rotation < -40)
      camera.rotation = -40;

    // Camera zoom controls
    // Uses log scaling to provide consistent zoom speed
    camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove() * 0.1f));

    if (camera.zoom > 3.0f)
      camera.zoom = 3.0f;
    else if (camera.zoom < 0.1f)
      camera.zoom = 0.1f;

    // Camera reset (zoom and rotation)
    if (IsKeyPressed(KEY_R)) {
      camera.zoom = 1.0f;
      camera.rotation = 0.0f;
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode2D(camera);
    DrawRectangle(-3000, 320, 13000, 8000, DARKGRAY);
    for (int i = 0; i < maxRect; i++) {
      DrawRectangleRec(rect[i], buildcolor[i]);
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
