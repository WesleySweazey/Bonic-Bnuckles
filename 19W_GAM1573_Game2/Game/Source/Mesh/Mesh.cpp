#include "GamePCH.h"

#include "Material.h"
#include "Mesh.h"
#include "Texture.h"
#include "VertexFormat.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/LightObject.h"

Mesh::Mesh()
{
    m_VBO = 0;
    m_IBO = 0;

    m_NumVerts = 0;
    m_NumIndices = 0;
    m_NumberOfTriangles = 0;

    m_PrimitiveType = -1;
}

Mesh::~Mesh()
{
    glDeleteBuffers( 1, &m_VBO );
    glDeleteBuffers( 1, &m_IBO );
    //delete[] m_Vertices;
}

void Mesh::Init(VertexFormat* verts, int numVerts, unsigned int* indices, int numIndices, GLenum primitiveType, GLenum usage)
{
    assert( numVerts != 0 );

    m_NumVerts = numVerts;
    m_NumIndices = numIndices;
    m_PrimitiveType = primitiveType;

    // Generate and fill buffer with our vertex attributes.
    if( m_VBO == 0 )
        glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(VertexFormat)*numVerts, verts, usage );

    // Generate and fill buffer with our indices.
    if( m_IBO == 0 )
        glGenBuffers( 1, &m_IBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*numIndices, indices, usage );

    CheckForGLErrors();
}

void Mesh::Init(const void* verts, int numVerts, GLenum primitiveType, GLenum usage)
{
    m_NumVerts = numVerts;
    m_NumIndices = 0;
    m_PrimitiveType = primitiveType;

    // Generate and fill buffer with our vertex attributes.
    if( m_VBO == 0 )
        glGenBuffers( 1, &m_VBO );
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(VertexFormat) * numVerts, verts, usage );

    CheckForGLErrors();
}

void SetUniform1f(GLuint shader, const char* uniformName, float value)
{
    GLint loc = glGetUniformLocation( shader, uniformName );
    if( loc != -1 )
    {
        glUniform1f( loc, value );
    }
}

void SetUniform2f(GLuint shader, const char* uniformName, vec2 value)
{
    GLint loc = glGetUniformLocation( shader, uniformName );
    if( loc != -1 )
    {
        glUniform2f( loc, value.x, value.y );
    }
}

void SetUniform3f(GLuint shader, const char* uniformName, vec3 value)
{
    GLint loc = glGetUniformLocation( shader, uniformName );
    if( loc != -1 )
    {
        glUniform3f( loc, value.x, value.y, value.z );
    }
}

void Mesh::SetupAttributes(Material* pMaterial)
{
    assert( m_VBO != 0 );
    assert( pMaterial != nullptr );
    assert( pMaterial->GetShader() != nullptr );
    assert( pMaterial->GetShader()->GetProgram() != 0 );
    CheckForGLErrors();

    GLuint shader = pMaterial->GetShader()->GetProgram();

    // Bind buffer and set up attributes.
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );

    GLint loc = glGetAttribLocation( shader, "a_Position" );
    if( loc != -1 )
    {
        glVertexAttribPointer( loc, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), reinterpret_cast<void*>( offsetof(VertexFormat, m_Pos) ) );
        glEnableVertexAttribArray( loc );
    }

    loc = glGetAttribLocation( shader, "a_Color" );
    if( loc != -1 )
    {
        glVertexAttribPointer( loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), reinterpret_cast<void*>( offsetof(VertexFormat, m_Color) ) );
        glEnableVertexAttribArray( loc );
    }

    loc = glGetAttribLocation( shader, "a_UV" );
    if( loc != -1 )
    {
        glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), reinterpret_cast<void*>( offsetof(VertexFormat, m_UV) ) );
        glEnableVertexAttribArray( loc );
    }
    loc = glGetAttribLocation(shader, "a_Normal");
    if (loc != -1)
    {
        glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), reinterpret_cast<void*>(offsetof(VertexFormat, m_Normal)));
        glEnableVertexAttribArray(loc);
    }
}

void Mesh::SetupUniforms(Material* pMaterial, mat4* worldMat, mat4* rotationMat, CameraObject* pCamera, vec2 uvScale, vec2 uvOffset, LightObject* pLights[])
{
    assert( pMaterial != nullptr );
    assert( pMaterial->GetShader() != nullptr );
    assert( pMaterial->GetShader()->GetProgram() != 0 );
    CheckForGLErrors();

    GLuint shader = pMaterial->GetShader()->GetProgram();

    // Set up shader.
    glUseProgram( shader );

    // Set up uniforms.
    GLint loc;
    loc = glGetUniformLocation( shader, "u_WorldMatrix" );
    glUniformMatrix4fv( loc, 1, false, &worldMat->m11 );

    loc = glGetUniformLocation( shader, "u_ViewMatrix" );
    glUniformMatrix4fv( loc, 1, false, &pCamera->GetViewMatrix()->m11 );

    loc = glGetUniformLocation( shader, "u_ProjectionMatrix" );
    glUniformMatrix4fv( loc, 1, false, &pCamera->GetProjMatrix()->m11 );

    loc = glGetUniformLocation(shader, "u_RotationMatrix");
    glUniformMatrix4fv(loc, 1, false, &rotationMat->m11);

    SetUniform2f( shader, "u_UVScale", uvScale );
    SetUniform2f( shader, "u_UVOffset", uvOffset );

    SetUniform1f(shader, "u_Time", (float)GetSystemTimeSinceGameStart());

    SetUniform1f( shader, "u_MaterialShine", pMaterial->GetShine() );

    SetUniform1f(shader, "u_targetHeight", 300.0f);
    SetUniform1f(shader, "u_targetWidth", 300.0f);
    
    for (int i = 0; i < 5; i++)
    {
        std::string pos = "u_Lights[" + std::to_string(i) + "].LightPos";
        std::string color = "u_Lights[" + std::to_string(i) + "].LightColor";
        std::string range = "u_Lights[" + std::to_string(i) + "].LightRange";
        std::string intensity = "u_Lights[" + std::to_string(i) + "].LightIntensity";

        GLuint uLightPos = glGetUniformLocation(shader, pos.c_str());
        GLuint uLightRange = glGetUniformLocation(shader, range.c_str());
        GLuint uLightIntensity = glGetUniformLocation(shader, intensity.c_str());
        GLuint uLightColor = glGetUniformLocation(shader, color.c_str());

        vec3 tempPosition = pLights[i]->GetPosition();
        vec3 tempColor = pLights[i]->GetColor();
        float tempRange = pLights[i]->GetRange();
        float tempIntensity = pLights[i]->GetIntensity();

        glUniform3f(uLightPos, tempPosition.x, tempPosition.y, tempPosition.z);
        glUniform4f(uLightColor, tempColor.x, tempColor.y, tempColor.z, 1.0f);
        glUniform1f(uLightRange, tempRange);
        glUniform1f(uLightIntensity, tempIntensity);
    }

    SetUniform3f(shader, "u_CameraPos", pCamera->GetPosition());

    // Setup our texture.
    Texture* pTexture = pMaterial->GetTexture();
    if( pTexture != nullptr )
    {
        int textureUnitIndex = 0;
        glActiveTexture( GL_TEXTURE0 + textureUnitIndex );
        glBindTexture( GL_TEXTURE_2D, pTexture->GetTextureID() );
        GLint loc = glGetUniformLocation( shader, "u_TextureSampler" );
        if( loc != -1 )
        {
            glUniform1i( loc, textureUnitIndex );
        }
    }

    Texture* pCubeTexture = pMaterial->GetCubemap();
    if (pCubeTexture != nullptr)
    {
        int textureUnitIndex = 1;
        glActiveTexture(GL_TEXTURE0 + textureUnitIndex);
        glBindTexture(GL_TEXTURE_CUBE_MAP, pCubeTexture->GetTextureID());
        GLint loc = glGetUniformLocation(shader, "u_TextureCubemap");
        if (loc != -1)
        {
            glUniform1i(loc, textureUnitIndex);
        }
    }

    CheckForGLErrors();
}

void Mesh::SetupUniforms(Material * pMaterial, mat4 * worldMat, mat4 * rotationMat, CameraObject * pCamera, vec2 uvScale, vec2 uvOffset)
{
    assert(pMaterial != nullptr);
    assert(pMaterial->GetShader() != nullptr);
    assert(pMaterial->GetShader()->GetProgram() != 0);
    CheckForGLErrors();

    GLuint shader = pMaterial->GetShader()->GetProgram();

    // Set up shader.
    glUseProgram(shader);

    // Set up uniforms.
    GLint loc;
    loc = glGetUniformLocation(shader, "u_WorldMatrix");
    glUniformMatrix4fv(loc, 1, false, &worldMat->m11);

    loc = glGetUniformLocation(shader, "u_ViewMatrix");
    glUniformMatrix4fv(loc, 1, false, &pCamera->GetViewMatrix()->m11);

    loc = glGetUniformLocation(shader, "u_ProjectionMatrix");
    glUniformMatrix4fv(loc, 1, false, &pCamera->GetProjMatrix()->m11);

    loc = glGetUniformLocation(shader, "u_RotationMatrix");
    glUniformMatrix4fv(loc, 1, false, &rotationMat->m11);

    SetUniform2f(shader, "u_UVScale", uvScale);
    SetUniform2f(shader, "u_UVOffset", uvOffset);

    SetUniform1f(shader, "u_Time", (float)GetSystemTimeSinceGameStart());

    SetUniform1f(shader, "u_targetHeight", 1024.0f);
    SetUniform1f(shader, "u_targetWidth", 1024.0f);


    // Setup our texture.
    Texture* pTexture = pMaterial->GetTexture();
    if (pTexture != nullptr)
    {
        int textureUnitIndex = 0;
        glActiveTexture(GL_TEXTURE0 + textureUnitIndex);
        glBindTexture(GL_TEXTURE_2D, pTexture->GetTextureID());
        GLint loc = glGetUniformLocation(shader, "u_TextureSampler");
        if (loc != -1)
        {
            glUniform1i(loc, textureUnitIndex);
        }
    }

    Texture* pCubeTexture = pMaterial->GetCubemap();
    if (pCubeTexture != nullptr)
    {
        int textureUnitIndex = 1;
        glActiveTexture(GL_TEXTURE0 + textureUnitIndex);
        glBindTexture(GL_TEXTURE_CUBE_MAP, pCubeTexture->GetTextureID());
        GLint loc = glGetUniformLocation(shader, "u_TextureCubemap");
        if (loc != -1)
        {
            glUniform1i(loc, textureUnitIndex);
        }
    }

    CheckForGLErrors();
}

void Mesh::Draw(Material* pMaterial)
{
    assert( m_PrimitiveType != -1 );
    assert( m_NumVerts != 0 );
    assert( pMaterial != nullptr );
    assert( pMaterial->GetShader() != nullptr );
    assert( pMaterial->GetShader()->GetProgram() != 0 );
    CheckForGLErrors();

    // Draw.
    if( m_NumIndices > 0 )
    {
        glDrawElements( m_PrimitiveType, m_NumIndices, GL_UNSIGNED_INT, 0 );
    }
    else
    {
        glDrawArrays( m_PrimitiveType, 0, m_NumVerts );
    }

    // Disable the attribute arrays used.
    {
        GLuint shader = pMaterial->GetShader()->GetProgram();

        GLint aPos = glGetAttribLocation( shader, "a_Position" );
        GLint aColor = glGetAttribLocation( shader, "a_Color" );
        GLint aUV = glGetAttribLocation( shader, "a_UV" );

        glDisableVertexAttribArray( aPos );

        if( aColor != -1 )
            glDisableVertexAttribArray( aColor );

        if( aUV != -1 )
            glDisableVertexAttribArray( aUV );
    }

    CheckForGLErrors();
}
