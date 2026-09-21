#include <raylib.h>

int main() {
  const int windowWidth = 800;
  const int windowHeight = 450;

  ::InitWindow(windowWidth, windowHeight, "test");

  ::Image bgImage = ::LoadImage("assets/textures/reactor.png");
  
  ::SetWindowIcon(bgImage); 

  float scale = (float)windowWidth / (float)bgImage.width;
  
  int newWidth = windowWidth;
  int newHeight = (int)(bgImage.height * scale);

  ::ImageResize(&bgImage, newWidth, newHeight);

  ::Texture2D texture = ::LoadTextureFromImage(bgImage);
  ::UnloadImage(bgImage);

  int posX = 0;
  int posY = (windowHeight - texture.height) / 2;

  while (!::WindowShouldClose()) {
    ::BeginDrawing();
    ::ClearBackground(BLACK); 
    
    ::DrawTexture(texture, posX, posY, WHITE);
    
    ::EndDrawing();
  }
  
  ::UnloadTexture(texture);
  ::CloseWindow();
}
