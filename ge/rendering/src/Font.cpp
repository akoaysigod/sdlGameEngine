#include "../include/ge/Font.h"

using namespace ge;

Font::Font(const std::shared_ptr<TTF_Font> font): font(font) {}

std::shared_ptr<Font> Font::init(const std::string &fileName, const int &size) {
  return std::make_shared<Font>(std::shared_ptr<TTF_Font>
                                (TTF_OpenFont(fileName.c_str(), size),
                                 TTF_CloseFont));
}

TTF_Font* Font::getCPtr() const {
  return font.get();
}
