// This file is part of the 3D Scene Viewer.
// by Tiago de Lima <tiago.delima@univ-artois.fr>
//
// Defines behavior interface.

#ifndef _IBEHAVIOR_H
#define _IBEHAVIOR_H

class IBehavior
{
    public:
        virtual void start() const = 0;
        virtual void stop() const = 0;
};

#endif
