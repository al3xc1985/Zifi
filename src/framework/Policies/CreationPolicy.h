/*
 * This file is part of the BlizzLikeCore Project.
 * See CREDITS and LICENSE files for Copyright information.
 */

#ifndef BLIZZLIKE_CREATIONPOLICY_H
#define BLIZZLIKE_CREATIONPOLICY_H

#include <stdlib.h>
#include "Platform/Define.h"

namespace BlizzLike
{
    // OperatorNew policy creates an object on the heap using new.
    template <class T>
        class OperatorNew
    {
        public:
            static T* Create(void) { return (new T); }
            static void Destroy(T *obj) { delete obj; }
    };

    /*
     * LocalStaticCreation policy creates an object on the stack
     * the first time call Create.
     */
    template <class T>
        class LocalStaticCreation
    {
        union MaxAlign
        {
            char t_[sizeof(T)];
            short int shortInt_;
            int int_;
            long int longInt_;
            float float_;
            double double_;
            long double longDouble_;
            struct Test;
            int Test::* pMember_;
            int (Test::*pMemberFn_)(int);
        };
        public:
            static T* Create(void)
            {
                static MaxAlign si_localStatic;
                return new(&si_localStatic) T;
            }

            static void Destroy(T *obj) { obj->~T(); }
    };

    /*
     * CreateUsingMalloc by pass the memory manger.
     */
    template<class T>
        class CreateUsingMalloc
    {
        public:
            static T* Create()
            {
                void* p = ::malloc(sizeof(T));
                if (!p) return 0;
                return new(p) T;
            }

            static void Destroy(T* p)
            {
                p->~T();
                ::free(p);
            }
    };

    /*
     * CreateOnCallBack creates the object base on the call back.
     */
    template<class T, class CALL_BACK>
        class CreateOnCallBack
    {
        public:
            static T* Create()
            {
                return CALL_BACK::createCallBack();
            }

            static void Destroy(T *p)
            {
                CALL_BACK::destroyCallBack(p);
            }
    };
}
#endif

