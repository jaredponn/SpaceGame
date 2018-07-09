#include "Src/Engine/Components/Appearance.h"

// -----------------------------------------
//    Procedures
// -----------------------------------------

// renders an appearance. Essentially a wrapper for SDL_RenderCopyEx, but
// assumes that we do not wish to flip to change the center of the object, nor
// flip it.
void SYS_renderCopyAppearance(SDL_Renderer*, const Appearance*);

// renders everythang formating in the Appearance Component
void SYS_renderCopy(SDL_Renderer*, const struct Appearance_Manager*);
