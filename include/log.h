// This file is part of the 3D Scene Viewer.
// by Tiago de Lima <tiago.delima@univ-artois.fr>
//
// Log messages macro.

#ifndef _LOG_H_
#define _LOG_H_

#include <iostream>

#ifdef _LOG_
#define LOG_MSG( msg ) std::cerr << msg
#else
#define LOG_MSG( msg )
#endif

#endif // _LOG_H_
