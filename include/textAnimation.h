#pragma once

#include <algorithm>

#include "raylib/raylib.h"

class TextAnimation
{
public:
  TextAnimation(void);
  TextAnimation(Font font, const char* text, int fontSize, float originalX, float originalY, float targetX, float targetY, Color originalColor, Color targetColor, float duration);

  void Animate(void);
  void Reverse(void);
  void Restart(void);
  bool IsFinished(void);

private:
  Font m_Font;
  const char* m_Text;
  int m_FontSize;
  float m_OriginalX, m_OriginalY;
  float m_TargetX, m_TargetY;
  float m_CurrentX, m_CurrentY;
  float m_Duration;
  Color m_OriginalColor, m_CurrentColor, m_TargetColor;
  bool m_IsFinished;
};


