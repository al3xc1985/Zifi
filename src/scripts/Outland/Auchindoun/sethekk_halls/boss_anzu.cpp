/*
 * This file is part of the BlizzLikeCore Project.
 * See CREDITS and LICENSE files for Copyright information.
 */

/* ScriptData
Name: Boss_Anzu
Complete(%): 95
Comment:Summon event is missing. 
Category: Auchindoun, Sethekk Halls
EndScriptData */

#include "ScriptPCH.h"
#include "sethekk_halls.h"

#define SAY_INTRO1          -1900169
#define SAY_INTRO2          -1900170
#define SAY_HELP            -1900171

#define SPELL_CYCLONE       40321
#define SPELL_RIP           40199
#define SPELL_PARALYZING    40184
#define SPELL_BOMB          40303
#define SPELL_BANISH        42354

#define GO_CLAW             185554

#define NPC_BROOD           23132

struct boss_anzuAI : public ScriptedAI
{
    boss_anzuAI(Creature* c) : ScriptedAI(c)
    {
        pInstance = c->GetInstanceData();
        HeroicMode = me->GetMap()->IsHeroic();
        DoScriptText(SAY_INTRO1, me);
        DoScriptText(SAY_INTRO2, me);
    }

    ScriptedInstance* pInstance;

    bool HeroicMode;

    uint32 Cyclone_Timer;
    uint32 Rip_Timer;
    uint32 Paralyzing_Timer;
    uint32 Bomb_Timer;
    uint32 SummonedCount;

    bool Summon1;
    bool Summon2;
    bool Paralyzing;

    void Reset()
    {
        if (GameObject* pClaw = me->FindNearestGameObject(GO_CLAW , 20))
            pClaw->RemoveFromWorld();

        if (pInstance)
            pInstance->SetData(DATA_ANZUEVENT, NOT_STARTED);

        Cyclone_Timer = 10000;
        Rip_Timer = 8000;
        Paralyzing_Timer = 1000;
        Bomb_Timer = 22000;
        Summon1 = false;
        Summon2 = false;
        Paralyzing = false;
        SummonedCount = 5;
    }

    void EnterCombat(Unit*)
    {
        if (pInstance)
            pInstance->SetData(DATA_ANZUEVENT, IN_PROGRESS);        
    }

    void JustDied(Unit*)
    {
        if (pInstance)
            pInstance->SetData(DATA_ANZUEVENT, DONE);
    }
	
    void JustSummoned(Creature* summoned)
    {
        if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
            summoned->AI()->AttackStart(pTarget);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (((me->GetHealth()*100) / me->GetMaxHealth() < 66) && !Summon1)
        {
            DoCast(me, SPELL_BANISH);
            DoScriptText(SAY_HELP, me);
            Paralyzing = true;
            for (uint32 i = 0; i < SummonedCount; i++)
            {
                me->SummonCreature(NPC_BROOD,me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,25000);
            }
            Summon1 = true;
        }

        if (((me->GetHealth()*100) / me->GetMaxHealth() < 33) && !Summon2)
        {
            DoCast(me, SPELL_BANISH);
            DoScriptText(SAY_HELP, me);
            Paralyzing = true;
            for (uint32 i = 0; i < SummonedCount; i++)
            {
                me->SummonCreature(NPC_BROOD,me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,25000);
            }
            Summon2 = true;
        }

        if (Paralyzing)
        {
            if (Paralyzing_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_PARALYZING);
                Paralyzing_Timer = 1000;
                Paralyzing = false;
            } else Paralyzing_Timer -= diff;
        }

        if (!me->HasAura(SPELL_BANISH, 0))
        {
            if (Cyclone_Timer <= diff)
            {
                if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                {
                    DoCast(pTarget, SPELL_CYCLONE);
                    Cyclone_Timer = 20000+rand()%1000;
                }
            } else Cyclone_Timer -= diff;

            if (Bomb_Timer <= diff)
            {
                if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                {
                    DoCast(pTarget, SPELL_BOMB);
                    Bomb_Timer = 30000+rand()%1000;
                }
            } else Bomb_Timer -= diff;

            if (Rip_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_RIP);
                Rip_Timer = 25000+rand()%2000;
            } else Rip_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    }
};

CreatureAI* GetAI_boss_anzu(Creature* pCreature)
{
    return new boss_anzuAI (pCreature);
}

void AddSC_boss_anzu()
{
    Script* newscript;
    newscript = new Script;
    newscript->Name = "boss_anzu";
    newscript->GetAI = &GetAI_boss_anzu;
    newscript->RegisterSelf();
}
