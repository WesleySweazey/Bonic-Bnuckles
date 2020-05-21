//
// Copyright (c) 2017-2018 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "GamePCH.h"

#include "Cue.h"
#include "Audio/SoundCueObject.h"

Cue::Cue(SoundPlayer * pSoundPlayer)
{
    m_SoundPlayer = pSoundPlayer;
    currentIndex = 0;
    m_PreviousSoundCueObject = nullptr;
}

Cue::~Cue()
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
    //m_Cue.empty();
    //delete[] m_pFileBuffer;
}

void Cue::AddSound(SoundCueObject* pSoundCueObject)
{
    m_Cue.push_back(pSoundCueObject);
}

SoundObject* Cue::Play()
{
    currentIndex++;
    if (currentIndex >= m_Cue.size())
    {
        currentIndex = 0;
    }
    
    return m_Cue[currentIndex]->m_SoundObject;
}