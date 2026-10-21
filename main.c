#include <stdlib.h>
#include <raylib.h>
#include "main.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

ScreenType screentype = MainScreen;
int width = 1920;
int height = 1080;
int font_size = 12;
int master_level = 9;
int music_level = 9;
int sfx_level = 9;
Vector2 mouse_position = {0.0, 0.0};

Font title_font;

// FPS Counters
bool show_fps = true;
int max_fps = 60;
int fps[] = {60,144,165,240,280,0};
int fps_counter = 0;

// Resolution
int widths[] = {1920, 1366, 2560 };
int heights[] = {1080, 768, 1440 };
int resolution_counter = 0;

// Vsync
bool vsync_check = false;


void MainMenu() {
  WriteDrawTextFont(title_font, "Leetaro", width / 2, height / 5, font_size * 10, 0, BLACK);

  /* DrawTextEx(font, text, position, fontSize, spacing, color); */

    WriteDrawText("Play", width / 2, height / 2, font_size * 5, BLACK);

    Rectangle rec = MakeBtn(width/2, height/2 + (height/10), "Settings", font_size * 5, 25);
    if (IsMouseInside(rec)) {
      if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
	WriteDrawText("Settings", width / 2, height / 2 + (height / 10),
		      (font_size * 5 + 3), RED);
	screentype = SettingsScreen;
      } else {
	WriteDrawText("Settings", width / 2, height / 2 + (height / 10),
		      font_size * 5, BLACK);
	ClearBackground(RAYWHITE);
      }
    } else {
      WriteDrawText("Settings", width / 2, height / 2 + (height / 10),
		      font_size * 5, BLACK);
    }

    /* rec = {width / 2 - MeasureText("Exit", font_size * 5), height /2  + (height / 5), MeasureText("Exit", font_size * 5), 80}; */

    Rectangle exit_btn = MakeBtn(width/2, height/2 + (height/5), "Exit",font_size*5, 10);

    if (CheckCollisionPointRec(mouse_position, exit_btn)) {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
	WriteDrawText("Exit", width / 2, height / 2 + (height / 5),
		      (font_size * 5 + 3), RED);
	EndDrawing();
	CloseWindow();
	exit(0);
      } else {
	WriteDrawText("Exit", width / 2, height / 2 + (height / 5), font_size * 5,
		      BLACK);
      }
    } else {
    WriteDrawText("Exit", width / 2, height / 2 + (height / 5), font_size * 5,
		  BLACK);

    }

}

void SettingsMenu() {
  WriteDrawText("Settings", width / 2, height / 2 - (height / 3),
		(font_size * 3), BLACK);


  WriteDrawText("Resolution", width / 2 - (width / 6),
		height / 2 - (height / 4), (font_size * 2), BLACK);

  Rectangle resolution_left_arrow = MakeBtn(((width / 2 + width / 5) - MeasureText("1920x108", font_size*2)), height / 2 - height / 4,
				 ">", font_size * 2, 10);
  Rectangle resolution_right_arrow = MakeBtn(((width / 2 + width / 5) + MeasureText("1920x108", font_size*2)), height / 2 - height / 4,
				 ">", font_size * 2, 10);
  WriteDrawText(TextFormat("<   %ix%i   >", widths[resolution_counter], heights[resolution_counter]),
		width / 2 + (width / 5), height / 2 - (height / 4),
		(font_size * 2), BLACK);

  if (IsMouseInside(resolution_left_arrow)) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      if (resolution_counter == 0)
	resolution_counter = 2;
      else
	resolution_counter--;
    }
  }

  if (IsMouseInside(resolution_right_arrow)) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      resolution_counter = (resolution_counter + 1)% 3;
    }
  }

  ///////////////



  // VSync
  WriteDrawText("Vsync", width / 2 - (width / 6), height / 3.1, (font_size * 2),
		BLACK);
  Rectangle vsync_left_arrow = MakeBtn(((width / 2 + width / 5) - MeasureText("True", font_size*2)), height / 3.1 ,
				 ">", font_size * 2, 10);
  Rectangle vsync_right_arrow = MakeBtn(((width / 2 + width / 5) + MeasureText("True", font_size*2)), height / 3.1,
				 ">", font_size * 2, 10);
  if (vsync_check) {

    WriteDrawText("<   True   >", width / 2 + (width / 5), height / 3.1, (font_size * 2), BLACK);
  } else {
    WriteDrawText("<   False   >", width / 2 + (width / 5), height / 3.1, (font_size * 2), BLACK);
  }
  if (IsMouseInside(vsync_left_arrow) || IsMouseInside(vsync_right_arrow)) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      vsync_check = !vsync_check;
    }
  }

  ///////////////


  // FPS
  WriteDrawText("FPS", width / 2 - (width / 6), height / 2.5, (font_size * 2),
		BLACK);
  Rectangle fps_left_arrow = MakeBtn(((width / 2 + width / 5) - MeasureText("144 ", font_size*2)), height / 2.5 ,
				 ">", font_size * 2, 10);
  Rectangle fps_right_arrow = MakeBtn(((width / 2 + width / 5) + MeasureText("144 ", font_size*2)), height / 2.5,
				 ">", font_size * 2, 10);

  WriteDrawText(TextFormat("<   %i   >", fps[fps_counter]),
		width / 2 + (width / 5), height / 2.5, (font_size * 2), BLACK);

  if (IsMouseInside(fps_left_arrow)) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      if (fps_counter == 0) {
        fps_counter = 5;
      } else {
        fps_counter--;
      }
      SetTargetFPS(fps[fps_counter]);
    }
  }

  if (IsMouseInside(fps_right_arrow)) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      fps_counter = (fps_counter + 1) % 6;
    }
    SetTargetFPS(fps[fps_counter]);
  }

  ///////////////





  WriteDrawText("Audio Level", width /2, height/2, (font_size * 3), BLACK);

  // Master Level
  WriteDrawText("Master Level", width / 2 - (width / 6),
		height / 2 + (height / 10), (font_size * 2), BLACK);

  /* Rectangle master_rec = {width / 2 + (width / 5), height / 2 + (height / 10), */
  /*                         MeasureText("[]", font_size * 3) * master_level, */
  /*                         font_size * 2, BLACK}; */

  Rectangle master_rec = MakeRect(width/2+(width/5), height/2 + (height/10), MeasureText("[]", font_size * 3) * master_level, font_size*2);
  Rectangle master_bg = MakeRect(width/2+(width/5), height/2 + (height/10), MeasureText("[]", font_size * 3) * 9, font_size*2);
  DrawRectangleRec(master_bg, RAYWHITE);
  DrawRectangleRec(master_rec, BLACK);

  if (IsMouseInside(master_bg)) {
    float delta_mouse_scroll = GetMouseWheelMove();
    if (delta_mouse_scroll < 0) {
      if (master_level > 0) {
	master_level--;
      }
    }
    if (delta_mouse_scroll > 0) {
      if (master_level < 9) {
	master_level++;
      }
    }
    WriteConfiguration("master_level", master_level);
  }
  
  //////////////

  // Music Level
  WriteDrawText("Music Level", width / 2 - (width / 6),
		height / 2 + (height / 10) * 2, (font_size * 2), BLACK);


  Rectangle music_rec = MakeRect(width/2+(width/5), height/2 + (height/10)*2, MeasureText("[]", font_size * 3) * music_level, font_size*2);
  Rectangle music_bg = MakeRect(width/2+(width/5), height/2 + (height/10)*2, MeasureText("[]", font_size * 3) * 9, font_size*2);

  DrawRectangleRec(music_bg, RAYWHITE);
  DrawRectangleRec(music_rec, BLACK);

  
  if (IsMouseInside(music_bg)) {
    float delta_mouse_scroll = GetMouseWheelMove();
    if (delta_mouse_scroll < 0) {
      if (music_level > 0) {
	music_level--;
      }
    }
    if (delta_mouse_scroll > 0) {
      if (music_level < 9) {
	music_level++;
      }
    }
    WriteConfiguration("music_level", music_level);
  }

 //////////////

  // SFX Level
  WriteDrawText("SFX Level", width / 2 - (width / 6),
		height / 2 + (height / 10) * 3, (font_size * 2), BLACK);

  Rectangle sfx_rec = MakeRect(width/2+(width/5), height/2 + (height/10)*3, MeasureText("[]", font_size * 3) * sfx_level, font_size*2);
  Rectangle sfx_bg = MakeRect(width/2+(width/5), height/2 + (height/10)*3, MeasureText("[]", font_size * 3) * 9, font_size*2);
		   
  DrawRectangleRec(sfx_bg, RAYWHITE);
  DrawRectangleRec(sfx_rec, BLACK);

    if (IsMouseInside(sfx_bg)) {
    float delta_mouse_scroll = GetMouseWheelMove();
    if (delta_mouse_scroll < 0) {
      if (sfx_level > 0) {
	sfx_level--;
      }
    }
    if (delta_mouse_scroll > 0) {
      if (sfx_level < 9) {
	sfx_level++;
      }
    }
  }

  //////////////

  // Back

    Rectangle back_rec = MakeRect(width/2, height/2 + (height/10)*4, MeasureText("BACK", font_size) * sfx_level, font_size*2);

		   
  DrawRectangleRec(back_rec, RAYWHITE);
    WriteDrawText("Back", width / 2,
		height / 2 + (height / 10) * 4, (font_size * 2), BLACK);

    if (IsMouseInside(back_rec)) {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
	screentype = MainScreen;
      }
    }


  ///
}

void SetVariables(char *line) {
  char *token = strtok(line, " = ");
  while (token != NULL) {	
    char* next_token = strtok(NULL, " = ");

    if (strcmp(token, "resolution") == 0) {
      printf("INFO: RESOLUTION - %s", next_token);
      width = atoi(strtok(next_token, "x"));
      height = atoi(strtok(NULL, "x"));
    }
    if (strcmp(token, "vsync") == 0) {
      if (strcmp(next_token, "false\n") == 0) {
        printf("INFO: VSYNC - FALSE");
	vsync_check = false;
      } else {
	vsync_check = true;
      }
    }
    
    if (strcmp(token, "fps") == 0) {
      printf("INFO: FPS - %s", next_token);
      max_fps = atoi(next_token);
    }
    if (strcmp(token, "master_level") == 0) {
      printf("INFO: MASTER LEVEL - %s", next_token);
      master_level = atoi(next_token);
    }
    if (strcmp(token, "music_level") == 0) {
      printf("INFO: MUSIC LEVEL - %s", next_token);
      music_level = atoi(next_token);
    }
    if (strcmp(token, "sfx_level") == 0) {
      printf("INFO: SFX LEVEL - %s", next_token);
      sfx_level = atoi(next_token);
    }

    token = next_token;
  }
}

void LoadConfiguration() {
  // Make a config directory
  chdir(getenv("HOME"));
  int check = mkdir(".config/raycar", 0777);

  chdir(".config/raycar");

  /* Make a file */
  FILE *fptr = fopen("settings.conf", "rw");
  if (!fptr) {
    fptr = fopen("settings.conf", "w");
    printf("INFO: Couldn't read the file, so made one\n");
    printf("INFO: Writing Configuration");
    // Write configuration to it
    fprintf(fptr, "resolution  = 1920x1080\nvsync = false\nfps = "
                  "60\nmaster_level = 9\nmusic_level = 9\nsfx_level = 9\n");
    return;
  }

  printf("INFO: reading config\n");
  char buf[1024] = "";
  
  while (fgets(buf, 1024, fptr)) {
    SetVariables(buf);
  }

  /*
    Check For 1. Resolution
              2. VSYNC
	      3. FPS
              4. Master Level
              5. Music Level
              6. SFX Level
  */
  fclose(fptr);
}

void WriteConfiguration(char *key, int value) {
  
}

int main() {
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(width, height, "Leetaro");
  title_font = LoadFontEx("/home/san/code/raylib_car/assets/Pixelout.ttf", 32, NULL,0);
  SetTargetFPS(max_fps);
  LoadConfiguration();
  while (!WindowShouldClose()) {
    mouse_position = GetMousePosition();
    if (show_fps) {
      DrawFPS(5,5);
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);
    switch (screentype) {
    case MainScreen:
      MainMenu();
      break;
    case SettingsScreen:
      ClearBackground(RAYWHITE);
      SettingsMenu();
      break;
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
