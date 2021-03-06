/*
 * This file is part of the BlizzLikeCore Project.
 * See CREDITS and LICENSE files for Copyright information.
 */

#ifndef _VMAPFACTORY_H
#define _VMAPFACTORY_H

#include "IVMapManager.h"

// This is the access point to the VMapManager.

namespace VMAP
{
    class VMapFactory
    {
        public:
            static IVMapManager* createOrGetVMapManager();
            static void clear();

            static void preventSpellsFromBeingTestedForLoS(const char* pSpellIdString);
            static bool checkSpellForLoS(unsigned int pSpellId);
    };

}
#endif

