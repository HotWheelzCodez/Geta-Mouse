#include "../include/gui.h"

namespace GUI
{
  bool ButtonText(Rectangle bounds, GUI::ButtonStyle style, const char* text, Vector2 mousePosition, bool& hover)
  {
    #define SEGMENTS 10
    #define SPACING  5

    bool clicked = false;
    Color bgColor = style.baseBgColor;
    Color textColor = style.baseTextColor;

    if (CheckCollisionPointRec(mousePosition, bounds))
    {
      hover = true;
      bgColor = style.hoverBgColor;
      textColor = style.hoverTextColor;

      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        clicked = true;
    }

    DrawRectangleRounded(bounds, style.roundness, SEGMENTS, bgColor);

    switch (style.textAlignment)
    {
      case GUI::TEXT_ALIGNMENT_LEFT:
        DrawTextEx(style.font, text, { bounds.x+SPACING, bounds.y+(bounds.height/2.0f)-(style.fontSize/2.0f) }, style.fontSize, SPACING, textColor);
        break;
      case GUI::TEXT_ALIGNMENT_CENTER:
        DrawTextEx(style.font, text, { bounds.x+(bounds.width/2.0f)-(MeasureTextEx(style.font, text, style.fontSize, SPACING).x/2.0f), bounds.y+(bounds.height/2.0f)-(style.fontSize/2.0f) }, style.fontSize, SPACING, textColor);
        break;
      case GUI::TEXT_ALIGNMENT_RIGHT:
        break;
    }

    return clicked;
  }

  bool ButtonCallback(Rectangle bounds, GUI::ButtonStyle style, void (*drawCallback)(Rectangle), Vector2 mousePosition, bool& hover)
  {
    #define SEGMENTS 10
    #define SPACING  5

    bool clicked = false;
    Color bgColor = style.baseBgColor;
    Color textColor = style.baseTextColor;

    if (CheckCollisionPointRec(mousePosition, bounds))
    {
      hover = true;
      bgColor = style.hoverBgColor;
      textColor = style.hoverTextColor;

      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        clicked = true;
    }

    DrawRectangleRounded(bounds, style.roundness, SEGMENTS, bgColor);
    drawCallback(bounds);

    return clicked;
  }
}
