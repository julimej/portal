#ifndef __EMITTERSPRITE_H__
#define __EMITTERSPRITE_H__
#include <string>
#include "../Sprite.h"
#include "../Rect.h"

class EmitterSprite : public Sprite
{
public:
  EmitterSprite(const Window &window, const int &code);
  ~EmitterSprite();
  virtual int render(const Rect &dest);
  virtual void setSrc(Rect &src) override;

  /*
  * Metodo encargado de setaer el estado del sprite recibido por parametro con un id
  */
  void setState(const int& state);

private:
  Rect src;
  int state;
};

#endif
