#include <string.h>

#define WriteDrawText(text, posX, posY, fontSize, color) DrawText(text, posX - (MeasureText(text, fontSize)/2), posY, fontSize, color);

#define DrawRect(posX,posY,width,height,color) DrawRectangle(posX - width/2, posY, width, height, color);

#define MakeRect(posX, posY, width, height) {posX - width/2, posY, width, height};

#define MakeBtn(posX, posY, txt, fontSize, padding) {posX - MeasureText(txt, fontSize) / 2 - padding, posY - padding, MeasureText(txt, fontSize) + padding * 2, fontSize + padding * 2}


#define IsMouseInside(rec) CheckCollisionPointRec(mouse_position, rec)
/* #define HIGHLIGHT_COLOR */
/* #define CLICK_COLOR */

typedef enum ScreenType {
  MainScreen, SettingsScreen 
} ScreenType;

void MainMenu();
void SettingsMenu();
void LoadConfiguration();
