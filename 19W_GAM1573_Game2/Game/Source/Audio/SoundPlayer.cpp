//
// Copyright (c) 2017-2018 Jimmy Lord http://www.flatheadgames.com
//
// This software is provided 'as-is', without any express or implied warranty.  In no event will the authors be held liable for any damages arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

#include "GamePCH.h"

#include "SoundPlayer.h"
#include "SoundChannel.h"
#include "SoundObject.h"
#include "Cue.h"

//====================================================================================================
// SoundPlayer
//====================================================================================================
SoundPlayer::SoundPlayer()
{
    CoInitializeEx( NULL, COINIT_MULTITHREADED );

    HRESULT result = XAudio2Create( &m_pEngine );
    
    if( result == S_OK )
    {
        result = m_pEngine->CreateMasteringVoice( &m_pMasteringVoice );
    }

    if( result != S_OK )
    {
        OutputMessage( "Error initializing XAudio\n" );
        exit( 1 );
    }
    for (int i = 0; i < 4; i++)
    {
        SoundChannel * tempChannel = new SoundChannel(m_pEngine);
        m_pChannels.push_back(tempChannel);
    }
    currentChannel = 0;
}

SoundPlayer::~SoundPlayer()
{
    delete m_pChannel;

    /*while (m_pChannels.size > 0)
    {
        delete m_pChannels.back;
        m_pChannels.pop_back();
    }*/
    for (auto channel : m_pChannels)
    {
        if (channel)
        {
            channel = NULL;
            delete channel;
        }
    }
    m_pChannels.clear();
    m_pEngine->Release();
    CoUninitialize();
}

SoundObject* SoundPlayer::LoadSound(const char* fullpath)
{
    SoundObject* pSound = new SoundObject();

    long len;
    const char* fileBuffer = LoadCompleteFile( fullpath, &len );
    assert( fileBuffer );
    if( fileBuffer )
    {
        MyWaveDescriptor waveDescriptor = WaveLoader::ParseWaveBuffer( fileBuffer, len );

        if( waveDescriptor.valid == false )
        {
            OutputMessage( "WAV file parsing failed (%s)\n", fullpath );
            delete[] fileBuffer;
        }
        else
        {
            pSound->Init( fileBuffer, waveDescriptor );
        }
    }

    return pSound;
}

int SoundPlayer::PlaySound(Cue* pCue)
{
    //if (pSoundObject->IsValid() == false)
        //return -1; // Sound didn't play.
    if (currentChannel >= 4)
    {
        double oldestSound = m_pChannels[0]->GetTimePlaybackStarted();
        int oldestSoundIndex = 0;
        for (int i = 0; i < m_pChannels.size(); i++)
        {
            if (oldestSound < m_pChannels[i]->GetTimePlaybackStarted())
            {
                oldestSoundIndex = i;
                oldestSound = m_pChannels[i]->GetTimePlaybackStarted();
            }
        }
        currentChannel = 0;
        m_pChannels[currentChannel]->StopSound();
        m_pChannels[currentChannel]->PlaySound(pCue->Play());
        currentChannel++;
    }
    else
    {
        m_pChannels[currentChannel]->PlaySound(pCue->Play());
        currentChannel++;        
    }
    return 0;
}

//int SoundPlayer::PlaySound(SoundObject* pSoundObject)
//{
//    if( pSoundObject->IsValid() == false )
//        return -1; // Sound didn't play.
//
//    m_pChannel->PlaySound( pSoundObject );
//
//    return 0;
//}

void SoundPlayer::StopSound(int channelIndex)
{
    m_pChannels[channelIndex]->StopSound();
}
