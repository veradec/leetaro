#include <string.h>
#include <math.h>

#define TEXT_FONT text_font


// TEXT Helpers
#define WriteDrawText(text, posX, posY, fontSize, color)                       \
  DrawText(text, posX - (MeasureText(text, fontSize) / 2), posY, fontSize,     \
           color);

#define WriteDrawTextFont(font, text, posX, posY, fontSize, spacing, color)    \
DrawTextEx(font, text, (Vector2){(posX - MeasureTextEx(font, text, fontSize, spacing).x/2), posY}, fontSize, spacing, color);

#define WriteText(text, posX, posY, fontSize, color)			\
  DrawTextEx(TEXT_FONT, text, (Vector2){(posX - MeasureTextEx(TEXT_FONT, text, fontSize, 0).x/2), posY}, fontSize, 0, color);
///////////////


// Rectangle Helpers
#define MakeRect(posX, posY, width, height) {posX - width/2, posY, width, height};
#define MakeBtn(posX, posY, txt, fontSize, padding)                            \
  {                                                                            \
    posX - MeasureText(txt, fontSize) / 2 - padding,			       \
    posY - padding, MeasureText(txt, fontSize) + padding * 2, fontSize + padding * 2}

#define DrawRect(posX, posY, width, height, color)		\
  DrawRectangle(posX - width/2, posY, width, height, color);

#define DrawRectangleDropShadow(posX,posY,width,height,color)
#define DrawRectangleRecDropShadow(rec, color, angle, shadow_distance)	\
  DrawRectangle(rec.x - rec.width/2 + shadow_distance, rec.y + (sin(angle)*shadow_distance), rec.width, rec.height, (Color){0,0,0,225}); \
  DrawRectangleRec(rec, color);

#define IsMouseInside(rec) CheckCollisionPointRec(mouse_position, rec)


#define DrawSlider(rec, color) DrawTextureRec(slider_texture, rec, (Vector2){rec.x,rec.y}, color);
////////////////////


typedef enum ScreenType {
  TitleScreen, SettingsScreen, GameStartScreen
} ScreenType;


typedef enum Position {
  LEFT_TOP,
  MIDDLE_TOP,
  RIGHT_TOP,
  LEFT_CENTER,
  MIDDLE_CENTER,
  RIGHT_CENTER,
  LEFT_BOTTOM,
  MIDDLE_BOTTOM,
  RIGHT_BOTTOM,
  FILL,
} Position;

// Function Defenitions
void MainMenu();
void SettingsMenu();
void LoadConfiguration();
void WriteConfiguration();
void SetVariables(char* line);
void GameStart();
void WriteTextInsideRectangle(struct Rectangle rec, Position pos, char* text, int font_size, int padding, struct Color color);
