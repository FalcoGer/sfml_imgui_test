#pragma once

#include <cmath>
#include <stdexcept>

namespace Application
{
  
  class Color
  {
    public:
      Color() : _r{0.0f}, _g{0.0f}, _b{0.0f}
      {
      }
      
      Color(float r, float g, float b)
      : _r{r}, _g{g}, _b{b}
      {
        if (r < 0.0f || r > 1.0f)
        {
          throw std::range_error("_r must be between 0 and 1");
        }
        if (g < 0.0f || g > 1.0f)
        {
          throw std::range_error("_g must be between 0 and 1");
        }
        if (b < 0.0f || b > 1.0f)
        {
          throw std::range_error("_b must be between 0 and 1");
        }
      }
      
      [[ nodiscard ]]
      inline float GetR() const { return _r; }
      [[ nodiscard ]]
      inline float GetG() const { return _g; }
      [[ nodiscard ]]
      inline float GetB() const { return _b; }
      [[ nodiscard ]]
      inline float GetH() const
      {
        float cMax = getMax();
        float cMin = getMin();
        float delta = cMax - cMin;
        
        if (delta == 0.0f)
        {
          // achromatic
          return 0.0f;
        }
        else if (isNear(cMax, _r))
        {
          return 60.0f * ((_g - _b) / delta + (_g > _b ? 0.0f : 6.0f));
        }
        else if (isNear(cMax, _g))
        {
          return 60.0f * (((_b - _r) / delta) + 2.0f);
        }
        else
        {
          return 60.0f * (((_r - _g) / delta) + 4.0f);
        }
      }
      [[ nodiscard ]]
      inline float GetS() const
      {
        float cMax = getMax();
        float cMin = getMin();
        float delta = cMax - cMin;
        
        if (delta == 0.0f)
        {
          // achromatic
          return 0.0f;
        }
        else
        {
          const float l = GetL();
          return delta / (1 - std::abs(2*l - 1));
        }
      }
      [[ nodiscard ]]
      inline float GetL() const
      {
        return (getMax() + getMin()) / 2.0f;
      }
    
      inline void SetR(float r)
      {
        if (r < 0.0f || r > 1.0f)
        {
          throw std::range_error("_r must be between 0 and 1");
        }
        this->_r = r;
      }
      inline void SetG(float g)
      {
        if (g < 0.0f || g > 1.0f)
        {
          throw std::range_error("_g must be between 0 and 1");
        }
        this->_g = g;
      }
      inline void SetB(float b)
      {
        if (b < 0.0f || b > 1.0f)
        {
          throw std::range_error("_b must be between 0 and 1");
        }
        this->_b = b;
      }
      void SetRGB(float r, float g, float b)
      {
        SetR(r);
        SetG(g);
        SetB(b);
      }
      inline void SetH(float h)
      {
        if (h < 0.0f || h > 360.0f)
        {
          throw std::range_error("h must be between 0 and 360");
        }
        Color c = hsl2rgb(h, GetS(), GetL());
        SetRGB(c.GetR(), c.GetG(), c.GetB());
      }
      inline void SetS(float s)
      {
        if (s < 0.0f || s > 1.0f)
        {
          throw std::range_error("s must be between 0 and 1");
        }
        Color c = hsl2rgb(GetH(), s, GetL());
        SetRGB(c.GetR(), c.GetG(), c.GetB());
      }
      inline void SetL(float l)
      {
        if (l < 0.0f || l > 1.0f)
        {
          throw std::range_error("l must be between 0 and 1");
        }
        Color c = hsl2rgb(GetH(), GetS(), l);
        SetRGB(c.GetR(), c.GetG(), c.GetB());
      }
    
      [[ nodiscard ]]
      static Color hsl2rgb(float h, float s, float l)
      {
        float r, g, b;
        if (h < 0.0f || h > 360.0f)
        {
          throw std::range_error("h must be between 0 and 360");
        }
        if (s == 0.0f)
        {
          // achromatic
          r = l;
          g = l;
          b = l;
        }
        else
        {
          h /= 360.0f;
          auto hue2rgb = [](float p, float q, float t)
          {
            if (t < 0.0f) { t += 1.0f; }
            if (t > 1.0f) { t -= 1.0f; }
            if(t < 1.0f/6.0f) return p + (q - p) * 6.0f * t;
            if(t < 1.0f/2.0f) return q;
            if(t < 2.0f/3.0f) return p + (q - p) * (2.0f/3.0f - t) * 6.0f;
            return p;
          };
          float q = l < 0.5f ? l * (1.0f + s) : l + s - l * s;
          float p = 2.0f * l - q;
          r = hue2rgb(p, q, h + 1.0f/3.0f);
          g = hue2rgb(p, q, h);
          b = hue2rgb(p, q, h - 1.0f/3.0f);
        }
        return {r, g, b};
      }
    private:
      float _r;
      float _g;
      float _b;
      
      [[ nodiscard ]]
      inline float getMax() const
      {
        if (_r > _b && _r > _g) { return _r; }
        if (_g > _b && _g > _r) { return _g; }
        return _b;
      }
    
      [[ nodiscard ]]
      inline float getMin() const
      {
        if (_r < _b && _r < _g) { return _r; }
        if (_g < _b && _g < _r) { return _g; }
        return _b;
      }
    
      [[ nodiscard ]]
      inline static bool isNear(float lhs, float rhs, unsigned char precision = 10)
      {
        return ((lhs - (1.0f / static_cast<float>(pow10(precision)))) <= rhs) && ((lhs + (1.0f / static_cast<float>(pow10(
          precision
        )))) >= rhs);
      }
      
      constexpr inline static long long int pow10(int exp)
      {
        long long int arr[] = {
          1, 10, 100, 1000, 10000,
          100000, 1000000, 10000000, 100000000, 1000000000,
          10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000,
          10000000000000000, 100000000000000000, 1000000000000000000
        };
        return arr[exp];
      }
  };
  
} // Application
