#ifndef NP_SEMESTERPROJEKT_MAIN_HPP
#define NP_SEMESTERPROJEKT_MAIN_HPP

#include "Warehouse.h"

void endlessThread(Warehouse&);

[[noreturn]] void endlessThreadHandlerIPoint( Warehouse &warehouse );

[[noreturn]] void endlessThreadHandlerKPoint( Warehouse &warehouse );



#endif //NP_SEMESTERPROJEKT_MAIN_HPP
