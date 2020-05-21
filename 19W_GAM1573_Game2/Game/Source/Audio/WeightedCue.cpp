//
// Copyright (c) 2017-2018 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "GamePCH.h"
#include "WeightedCue.h"
#include "Cue.h"
#include "SoundObject.h"

WeightedCue::WeightedCue(SoundPlayer * m_SoundPlayer) : Cue(m_SoundPlayer)
{

}

WeightedCue::~WeightedCue()
{
    /*if (m_SoundPlayer)
    {
        m_SoundPlayer = NULL;
        delete m_SoundPlayer;
    }
    if (m_PreviousSoundCueObject)
    {
        m_PreviousSoundCueObject = NULL;
        delete m_PreviousSoundCueObject;
    }
    for (auto object : m_Cue)
    {
        if (object)
        {
            object = NULL;
            delete object;
        }
    }*/
}

SoundObject* WeightedCue::Play()
{
    int random = 0;
    int totalWeight = 0;
    int finalWeight = 0;
    bool bPrev = false;

    while (bPrev == false)
    {
    for (unsigned int i = 0; i < m_Cue.size(); i++)
    {
        totalWeight += m_Cue[i]->m_Weight;
    }

    random = rand() % (int)totalWeight;

    for (int i = 0; i < m_Cue.size(); i++)
    {
        finalWeight += m_Cue[i]->m_Weight;
        if (random <= finalWeight)
        {
            if (m_PreviousSoundCueObject == nullptr)
            {
                m_PreviousSoundCueObject = m_Cue[i];
                bPrev = true;
                return m_Cue[i]->m_SoundObject;
            }
            else if (m_PreviousSoundCueObject != m_Cue[i])
            {
                bPrev = true;
                return m_Cue[i]->m_SoundObject;
            }
            
        }
    }
    }
    return 0;
}
