#include "../include/textAnimation.h"

TextAnimation::TextAnimation(void)
{ }

TextAnimation::TextAnimation(Font font, const char* text, int fontSize, float originalX, float originalY, float targetX, float targetY, Color originalColor, Color targetColor, float duration)
  : m_Font(font), m_Text(text), m_FontSize(fontSize), m_OriginalX(originalX), m_OriginalY(originalY), m_TargetX(targetX), m_TargetY(targetY), m_CurrentX(originalX), m_CurrentY(originalY), m_Duration(duration), m_OriginalColor(originalColor), m_CurrentColor(originalColor), m_TargetColor(targetColor)
{
  m_IsFinished = false;
}

void TextAnimation::Animate(void)
{
  if (m_CurrentColor.a == m_TargetColor.a)
    m_IsFinished = true;

  if (m_OriginalX == m_TargetX)
  {
    m_CurrentX = m_OriginalX;
  }
  else if (m_OriginalX < m_TargetX)
  {
    if (m_CurrentX < m_TargetX)
      m_CurrentX += (m_TargetX-m_OriginalX)/(GetFPS()*m_Duration);

    if (m_CurrentX >= m_TargetX)
    {
      m_CurrentX = m_TargetX;
      m_IsFinished = true;
    }
  }
  else
  {
    if (m_CurrentX > m_TargetX)
      m_CurrentX -= (m_TargetX-m_OriginalX)/(GetFPS()*m_Duration);

    if (m_CurrentX <= m_TargetX)
    {
      m_CurrentX = m_TargetX;
      m_IsFinished = true;
    }
  }

  if (m_OriginalY == m_TargetY)
  {
    m_CurrentY = m_OriginalY;
  }
  else if (m_OriginalY > m_TargetY)
  {
    if (m_CurrentY > m_TargetY)
      m_CurrentY -= (m_OriginalY-m_TargetY)/(GetFPS()*m_Duration);

    if (m_CurrentY <= m_TargetY)
    {
      m_CurrentY = m_TargetY;
      m_IsFinished = true;
    }
    else
    {
      m_CurrentY -= (m_OriginalY-m_TargetY)/(GetFPS()*m_Duration);
    }
  }
  else
  {
    if (m_CurrentY > m_TargetY)
      m_CurrentY += (m_TargetY-m_OriginalY)/(GetFPS()*m_Duration);

    if (m_CurrentY <= m_TargetY)
    {
      m_CurrentY = m_TargetY;
      m_IsFinished = true;
    }
  }

  if (m_OriginalColor.r == m_TargetColor.r)
  {
    m_CurrentColor.r = m_OriginalColor.r;
  }
  else if (m_OriginalColor.r < m_TargetColor.r)
  {
    if (m_CurrentColor.r < m_TargetColor.r)
      m_CurrentColor.r += (m_TargetColor.r-m_OriginalColor.r)/(GetFPS()*m_Duration);

    if (m_CurrentColor.r >= m_TargetColor.r)
    {
      m_CurrentColor.r = m_TargetColor.r;
      m_IsFinished = true;
    }
  }
  else
  {
    if (m_CurrentColor.r > m_TargetColor.r)
      m_CurrentColor.r -= (m_OriginalColor.r-m_TargetColor.r)/(GetFPS()*m_Duration);

    if (m_CurrentColor.r <= m_TargetColor.r)
    {
      m_CurrentColor.r = m_TargetColor.r;
      m_IsFinished = true;
    }
  }

  if (m_OriginalColor.g == m_TargetColor.g)
  {
    m_CurrentColor.g = m_OriginalColor.g;
  }
  else if (m_OriginalColor.g < m_TargetColor.g)
  {
    if (m_CurrentColor.g < m_TargetColor.g)
      m_CurrentColor.g += (m_TargetColor.g-m_OriginalColor.g)/(GetFPS()*m_Duration);

    if (m_CurrentColor.g >= m_TargetColor.g)
    {
      m_CurrentColor.g = m_TargetColor.g;
      m_IsFinished = true;
    }
  }
  else
  {
    if (m_CurrentColor.g > m_TargetColor.g)
      m_CurrentColor.g -= (m_OriginalColor.g-m_TargetColor.g)/(GetFPS()*m_Duration);

    if (m_CurrentColor.g <= m_TargetColor.g)
    {
      m_CurrentColor.g = m_TargetColor.g;
      m_IsFinished = true;
    }
  }

  if (m_OriginalColor.b == m_TargetColor.b)
  {
    m_OriginalColor.b = m_OriginalColor.b;
  }
  else if (m_OriginalColor.b < m_TargetColor.b)
  {
    if (m_CurrentColor.b < m_TargetColor.b)
      m_CurrentColor.b += (m_TargetColor.b-m_OriginalColor.b)/(GetFPS()*m_Duration);

    if (m_CurrentColor.b >= m_TargetColor.b)
    {
      m_CurrentColor.b = m_TargetColor.b;
      m_IsFinished = true;
    }
  }
  else
  {
    if (m_CurrentColor.b > m_TargetColor.b)
      m_CurrentColor.b -= (m_OriginalColor.b-m_TargetColor.b)/(GetFPS()*m_Duration);

    if (m_CurrentColor.b <= m_TargetColor.b)
    {
      m_CurrentColor.b = m_TargetColor.b;
      m_IsFinished = true;
    }
  }

  if (m_OriginalColor.a == m_TargetColor.a)
  {
    m_CurrentColor.a = m_OriginalColor.a;
  }
  else if (m_OriginalColor.a < m_TargetColor.a)
  {
    if (m_CurrentColor.a < m_TargetColor.a)
      m_CurrentColor.a += (m_TargetColor.a-m_OriginalColor.a)/(GetFPS()*m_Duration);

    if (m_CurrentColor.a >= m_TargetColor.a)
    {
      m_CurrentColor.a = m_TargetColor.a;
      m_IsFinished = true;
    }
  }
  else
  {
    if (m_CurrentColor.a > m_TargetColor.a)
      m_CurrentColor.a -= (m_OriginalColor.a-m_TargetColor.a)/(GetFPS()*m_Duration);

    if (m_CurrentColor.a <= m_TargetColor.a)
    {
      m_CurrentColor.a = m_TargetColor.a;
      m_IsFinished = true;
    }
  }

  DrawTextEx(m_Font, m_Text, { m_CurrentX, m_CurrentY }, m_FontSize, 5, m_CurrentColor); 
}

void TextAnimation::Reverse(void)
{
  std::swap(m_OriginalX, m_TargetX);
  std::swap(m_OriginalColor, m_TargetColor);
}

void TextAnimation::Restart(void)
{
  m_CurrentX = m_OriginalX;
  m_CurrentY = m_OriginalY;
  m_CurrentColor = m_OriginalColor;
  m_IsFinished = false;
}

bool TextAnimation::IsFinished(void)
{
  return m_IsFinished;
}
