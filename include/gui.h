#pragma once /* GUI_H */

#include "raylib/raylib.h"

namespace GUI
{
  enum TextAlignments
  {
    TEXT_ALIGNMENT_LEFT   = 0,
    TEXT_ALIGNMENT_CENTER = 1,
    TEXT_ALIGNMENT_RIGHT  = 2
  };

  typedef struct 
  {
    Color baseBgColor;
    Color baseTextColor;
    Color hoverBgColor;
    Color hoverTextColor;
    Font  font;
    int   fontSize;
    int   textAlignment;
    float roundness;
  } ButtonStyle;

  bool ButtonText(Rectangle bounds, GUI::ButtonStyle style, const char* text, Vector2 mousePosition, bool& hover);
  bool ButtonCallback(Rectangle bounds, GUI::ButtonStyle style, void (*drawCallback)(Rectangle bounds), Vector2 mousePosition, bool& hover);
}
