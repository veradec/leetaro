#include <stdlib.h>
#include <raylib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "helpers.h"
#include "ante.h"

ScreenType screentype = GameStartScreen;
int width = 1920;
int height = 1080;
int font_size = 12;
int master_level = 9;
int music_level = 9;
int sfx_level = 9;
Vector2 mouse_position = {0.0, 0.0};
Vector2 foo;
	    
Font title_font;
Font text_font;
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

// ante_count
int ante_count = 0;


char file_path[1024];
#define BTN_PADDING 25

void MainMenu() {
  WriteDrawTextFont(title_font, "Leetaro", width / 2, height / 5, font_size * 10, 0, BLACK);

  // Play Button
  

  Rectangle play_btn = MakeBtn(width/2, height/2, "Play", font_size *5, BTN_PADDING);

  if (IsMouseInside(play_btn)) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      WriteText("Play", width / 2, height / 2, font_size * 5, RED);
      screentype = GameStartScreen;
    } else {
      WriteText("Play", width/2, height/2, font_size*5.2, BLACK);
      ClearBackground(RAYWHITE);
    }
  } else {
    WriteText("Play", width / 2, height / 2, font_size * 5, BLACK);
  }
  
  // Settings Button
    Rectangle rec = MakeBtn(width/2, height/2 + (height/10), "Settings", font_size * 5, BTN_PADDING);
    if (IsMouseInside(rec)) {
      if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        WriteText("Settings", width / 2, height / 2 + (height / 10),
                  (font_size * 5 + 3), RED);

	screentype = SettingsScreen;
      } else {
	WriteText( "Settings", width / 2, height / 2 + (height / 10),
			  font_size * 5.1, BLACK);
	ClearBackground(RAYWHITE);
      }
    } else {
      WriteText( "Settings", width / 2, height / 2 + (height / 10),
			font_size * 5,  BLACK);
    }

    /* rec = {width / 2 - MeasureText("Exit", font_size * 5), height /2  + (height / 5), MeasureText("Exit", font_size * 5), 80}; */

    Rectangle exit_btn = MakeBtn(width/2, height/2 + (height/5), "Exit",font_size*5, 10);

    if (CheckCollisionPointRec(mouse_position, exit_btn)) {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
	WriteText("Exit", width / 2, height / 2 + (height / 5),
		      (font_size * 5 + 3), RED);
	EndDrawing();
	CloseWindow();
	exit(0);
      } else {
	WriteText("Exit", width / 2, height / 2 + (height / 5), font_size * 5.2,
		      BLACK);
      }
    } else {
    WriteText("Exit", width / 2, height / 2 + (height / 5), font_size * 5,
		  BLACK);

    }

}

void SettingsMenu() {
  WriteText("Settings", width / 2, height / 2 - (height / 3),
		(font_size * 3), BLACK);


  WriteText("Resolution", width / 2 - (width / 6),
		height / 2 - (height / 4), (font_size * 2), BLACK);

  Rectangle resolution_left_arrow = MakeBtn(((width / 2 + width / 5) - MeasureText("1920x108", font_size*2)), height / 2 - height / 4,
				 ">", font_size * 2, 10);
  Rectangle resolution_right_arrow = MakeBtn(((width / 2 + width / 5) + MeasureText("1920x108", font_size*2)), height / 2 - height / 4,
				 ">", font_size * 2, 10);
  WriteText(TextFormat("<   %ix%i   >", widths[resolution_counter], heights[resolution_counter]),
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
  WriteText("Vsync", width / 2 - (width / 6), height / 3.1, (font_size * 2),
		BLACK);
  Rectangle vsync_left_arrow = MakeBtn(((width / 2 + width / 5) - MeasureText("True", font_size*2)), height / 3.1 ,
				 ">", font_size * 2, 10);
  Rectangle vsync_right_arrow = MakeBtn(((width / 2 + width / 5) + MeasureText("True", font_size*2)), height / 3.1,
				 ">", font_size * 2, 10);
  if (vsync_check) {

    WriteText("<   True   >", width / 2 + (width / 5), height / 3.1, (font_size * 2), BLACK);
  } else {
    WriteText("<   False   >", width / 2 + (width / 5), height / 3.1, (font_size * 2), BLACK);
  }
  if (IsMouseInside(vsync_left_arrow) || IsMouseInside(vsync_right_arrow)) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      vsync_check = !vsync_check;
    }
  }

  ///////////////


  // FPS
  Color fps_color = BLACK;
  if (vsync_check) {
    fps_color = (Color){100,100,100,100};
  }
  WriteText("FPS", width / 2 - (width / 6), height / 2.5, (font_size * 2),
		BLACK);
  Rectangle fps_left_arrow = MakeBtn(((width / 2 + width / 5) - MeasureText("144 ", font_size*2)), height / 2.5 ,
				 ">", font_size * 2, 10);
  Rectangle fps_right_arrow = MakeBtn(((width / 2 + width / 5) + MeasureText("144 ", font_size*2)), height / 2.5,
				 ">", font_size * 2, 10);

  WriteText(TextFormat("<   %i   >", fps[fps_counter]),
		width / 2 + (width / 5), height / 2.5, (font_size * 2), fps_color);

  if (IsMouseInside(fps_left_arrow)) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !(vsync_check)) {
      if (fps_counter == 0) {
        fps_counter = 5;
      } else {
        fps_counter--;
      }
      SetTargetFPS(fps[fps_counter]);
    }
  }

  if (IsMouseInside(fps_right_arrow)) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !(vsync_check)) {
      fps_counter = (fps_counter + 1) % 6;
    }
    SetTargetFPS(fps[fps_counter]);
  }

  ///////////////





  WriteText("Audio Level", width /2, height/2, (font_size * 3), BLACK);

  // Master Level
  WriteText("Master Level", width / 2 - (width / 6),
		height / 2 + (height / 10), (font_size * 2), BLACK);

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
  }
  
  //////////////

  // Music Level
  WriteText("Music Level", width / 2 - (width / 6),
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
  }

 //////////////

  // SFX Level
  WriteText("SFX Level", width / 2 - (width / 6),
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
    WriteText("Back", width / 2,
		height / 2 + (height / 10) * 4, (font_size * 2), BLACK);

    if (IsMouseInside(back_rec)) {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        WriteConfiguration();
	screentype = TitleScreen;
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
      for (int i = 0; i < 3; i++) {
        if (widths[i] == width) {
          resolution_counter = i;
          break;
        }
      }
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
      for (int i = 0; i < 6; i++) {
        if (fps[i] == max_fps) {
          fps_counter = i;
          break;
        }
      }
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

  /* Make a file */
  FILE *fptr = fopen(file_path, "rw");
  if (!fptr) {
    fptr = fopen("settings.conf", "w");
    WriteConfiguration();
    printf("INFO: Couldn't read the file, So Write Configuration\n");
    return;
  }

  printf("INFO: reading config\n");
  char buf[1024] = "";
  
  /*
    Check For 1. Resolution
              2. VSYNC
	      3. FPS
              4. Master Level
              5. Music Level
              6. SFX Level
  */
  while (fgets(buf, 1024, fptr)) {
    SetVariables(buf);
  }

  fclose(fptr);
}

void WriteConfiguration() {

  FILE *fptr = fopen(file_path, "w");
  char buf[1024] = "";
  char *vsync_string = "false";
  if (vsync_check) {
    vsync_string = "true";
  }
  sprintf(buf,
          "resolution = %dx%d\nvsync = %s\nfps = %d\nmaster_level = "
          "%d\nmusic_level = %d\nsfx_level = %d\n",
          widths[resolution_counter], heights[resolution_counter], vsync_string,
          fps[fps_counter], master_level, music_level, sfx_level);
  fprintf(fptr, buf);
  printf("INFO: Wrote Configuration\n");
}

void GameStart() {
  ClearBackground(RAYWHITE);
  Rectangle left_rect = MakeRect(width / 2 - width / (3), height / 10,
                                 width / 3.5, height - height / 5);

  Rectangle middle_rect =
    MakeRect(width / 2, height / 10, width / 3.5,
	     height - height / 5);
  
  Rectangle right_rect =
    MakeRect(width / 2 + width / (3), height / 10, width / 3.5,
	     height - height / 5);

  DrawRectangleRec(left_rect, (Color){50,50,50, 255});
  DrawRectangleRec(middle_rect, (Color){50,50,50, 255});
  DrawRectangleRec(right_rect, (Color){50,50,50, 255});

  /* WriteTextInsideRectangle(left_rect, MIDDLE_TOP, "<~    KiloByte    ~>", font_size*2, 20, WHITE); */
  /* WriteTextInsideRectangle(middle_rect, FILL, "<~    KiloByte    ~>", font_size*2, 20, WHITE); */
  /* if (ante_count < 12) { */
  /*   ante_count +=3; */
  /* } */
}

void WriteTextInsideRectangle(Rectangle rec, Position pos, char *text,
                              int font_size, int padding, Color color) {
  int x = rec.x;
  int y = rec.y;
  int w = rec.width;
  int h = rec.height;
  switch (pos) {
  case LEFT_TOP:	    
    WriteText(text, x + MeasureText(text, font_size),y+padding,font_size, color);
    break;		    				   
  case MIDDLE_TOP:						   
    WriteText(text, x + w/2,y+padding,font_size, color);
    break;					       
  case RIGHT_TOP:
    WriteText(text, x + w - MeasureText(text, font_size),y+padding,font_size, color);
    break;
  case LEFT_CENTER:
    WriteText(text, x + MeasureText(text, font_size),y+h/2,font_size, color);
    break;
  case MIDDLE_CENTER:
    WriteText(text, x + w/2,y+h/2,font_size, color);
    break;

  case RIGHT_CENTER:
    WriteText(text, x + w - MeasureText(text, font_size),y+h/2,font_size, color);
    break;
  case LEFT_BOTTOM:
    WriteText(text, x + MeasureText(text, font_size),y+h-padding-font_size,font_size, color);
    break;
  case MIDDLE_BOTTOM:
    WriteText(text, x + w/2,y+h-padding-font_size,font_size, color);
    break;
  case RIGHT_BOTTOM:
    WriteText(text, x + w - MeasureText(text, font_size), y + h - padding - font_size,
              font_size, color);
    break;
  case FILL:
    WriteText(text, x+MeasureTextEx(TEXT_FONT, text, font_size, 0).x/2,y,font_size,color);
    break;
  }
}

int main() {
  char *home = (getenv("HOME"));

  char dir_path[1024];
  sprintf(dir_path, "%s/.config/leetaro/", home);
  mkdir(dir_path, 0777);
  sprintf(file_path, "%s/.config/leetaro/settings.conf", home);

  LoadConfiguration();
  if(vsync_check){   SetConfigFlags(FLAG_VSYNC_HINT); }
  InitWindow(width, height, "Leetaro");

  title_font = LoadFontEx("./assets/Pixelout.ttf", 32, NULL,0);
  text_font = LoadFontEx("./assets/alagard.ttf", 48, NULL,0);
  SetTargetFPS(max_fps);
  while (!WindowShouldClose()) {
    mouse_position = GetMousePosition();
    if (show_fps) {
      DrawFPS(5,5);
    }
    BeginDrawing();
    ClearBackground(RAYWHITE);
    switch (screentype) {
    case TitleScreen:
      MainMenu();
      break;
    case SettingsScreen:
      ClearBackground(RAYWHITE);
      SettingsMenu();
      break;
    case GameStartScreen:
      ClearBackground(BLACK);
      GameStart();
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
