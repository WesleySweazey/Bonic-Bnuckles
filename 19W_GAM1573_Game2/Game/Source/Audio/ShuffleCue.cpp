#include "GamePCH.h"
#include "ShuffleCue.h"
#include "Cue.h"
#include "SoundObject.h"
#include "SoundPlayer.h"

ShuffleCue::ShuffleCue(SoundPlayer * m_SoundPlayer) : Cue (m_SoundPlayer)
{
    Reshuffle = true;
    currentIndex = 0;
}

ShuffleCue::~ShuffleCue()
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
    }*/
    //m_Cue.clear();
    for (auto object : m_Cue)
    {
        if (object)
        {
            object = NULL;
            delete object;
        }
    }
}

SoundObject* ShuffleCue::Play()
{
    assert(m_Cue.size() != 0);

    bool bRetryRand = false;
    int random;

    currentIndex++;

    if (currentIndex >= m_Cue.size())
    {
        Reshuffle = true;
        currentIndex = 0;
    }
    if (Reshuffle == true)
    {
        m_orderList.clear();
        for (unsigned int i = 0; i < m_Cue.size(); i++)
        {
            bool failed = false;
            while (bRetryRand == false)
            {
                failed = false;
                random = rand() % m_Cue.size();
                for (unsigned int j = 0; j < m_orderList.size(); j++)
                {
                    if (m_orderList[j] == random)
                    {
                        failed = true;
                        bRetryRand = false;
                    }
                }
                if (failed == false)
                {
                    bRetryRand = true;
                }
                else if(failed == true)
                {
                    bRetryRand = false;
                }
            }
            m_orderList.push_back(random);
            bRetryRand = false;
        }
        Reshuffle = false;
    }
    return m_Cue[m_orderList[currentIndex]]->m_SoundObject;
}