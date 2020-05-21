#ifndef __SoundCueObject_H__
#define __SoundCueObject_H__

class SoundObject;

class SoundCueObject
{
public:
    int m_Weight;
    int m_VolumeStrength;
    SoundObject* m_SoundObject;

    SoundCueObject(int Weight, int VolumeStrength, SoundObject* pSoundObject)
    {
        m_Weight = Weight;
        m_VolumeStrength = VolumeStrength;
        m_SoundObject = pSoundObject;
    }
    ~SoundCueObject()
    {
       /* if (m_SoundObject)
        {
            m_SoundObject = NULL;
            delete m_SoundObject;
        }*/
    }
};

#endif //__VertexFormat_H__
