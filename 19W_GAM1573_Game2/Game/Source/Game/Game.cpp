#include "GamePCH.h"

#include "Events/GameEventTypes.h"
#include "Events/RemoveFromSceneEvent.h"
#include "Game/Game.h"
#include "Game/ImguiManager.h"
#include "Game/ResourceManager.h"
#include "Game/Scene.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "BulletManager/BulletManager.h"
#include "BulletManager/GameObjectMotionState.h"
#include "Mesh/Mesh.h"
#include "Mesh/Texture.h"
#include "SceneManager/SceneManager.h"
#include "Scenes/EndScene.h"
#include "Scenes/GameScene.h"
#include "Scenes/PauseScene.h"
#include "Scenes/VictoryScene.h"
#include "Scenes/TitleScene.h"
#include "Scenes/PostEffectScene.h"
#include "Scenes/Options.h"
#include "Scenes/HUD.h"
#include "Mesh/FBODefinition.h"
#include "Mesh/VertexFormat.h"


Game::Game(Framework* pFramework)
: GameCore( pFramework, new EventManager() )
{
    m_pImGuiManager = nullptr;

    m_pResources = nullptr;

    for( int i=0; i<4; i++ )
    {
        m_pControllers[i] = nullptr;
    }

    m_pSceneManager = nullptr;
    HasStartedGame = false;
    IsGameOver = false;
    IsPaused = false;
    InOptionsTab = false;

    m_pFBO = nullptr;
    m_pPostEffectScene = nullptr;

    m_pPlayer = nullptr;
}

Game::~Game()
{
    delete m_pSceneManager;

    for( int i=0; i<4; i++ )
    {
        delete m_pControllers[i];
    }

    delete m_pResources;

    delete m_pPostEffectScene;

    delete m_pImGuiManager;

    delete m_pFBO;

    if (m_pHUD)
    {
        m_pHUD = NULL;
        delete m_pHUD;
    }
}

void Game::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    // Set OpenGL to draw to the entire window.
    glViewport( 0, 0, width, height );
}

void Game::LoadContent()
{
#if WIN32
    // Turn on V-Sync.
    wglSwapInterval( 1 );
#endif

    // Turn on depth buffer testing.
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );

    // Turn on alpha blending.
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    // Enable back-face culling.
    //glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );
    glFrontFace( GL_CW );

    //Create FBO
    m_pFBO = new FBODefinition(1280, 720, GL_LINEAR, GL_LINEAR, true);

    // Create our resource manager.
    m_pResources = new ResourceManager();

    // Create our meshes.
    {
        m_pResources->AddMesh( "Box", new Mesh() )->CreateBox( vec2(1,1), vec2(0,0) );
        m_pResources->AddMesh("Emerald", new Mesh())->CreateBox(vec2(1.0f, 0.75f), vec2(0, 0));
        m_pResources->AddMesh("DoubleBox", new Mesh())->CreateBox(vec2(2, 2), vec2(0, 0));
        m_pResources->AddMesh("Screen", new Mesh())->CreateBox(vec2(23, 12.5), vec2(0, 0));
        m_pResources->AddMesh("PostScreen", new Mesh())->CreateBox(vec2(26, 13.5), vec2(0, 0));
        m_pResources->AddMesh("Plane", new Mesh())->CreatePlane(vec2(10.0f, 10.0f), ivec2(5, 5), vec2(0.0f, 0.0f), vec2(0.0f, 0.0f));
        m_pResources->AddMesh("Cube", new Mesh())->CreateCube(vec3(1,1,1));
        m_pResources->AddMesh("Sphere", new Mesh())->CreateOBJ("Data/OBJs/sphere.obj", vec3(1, 1, 1));
        m_pResources->AddMesh("BoxOBJ", new Mesh())->CreateOBJ("Data/OBJs/Box.obj", vec3(1, 1, 1));
        m_pResources->AddMesh("RingOBJ", new Mesh())->CreateOBJ("Data/OBJs/RingV4.obj", vec3(1, 1, 1));
        m_pResources->AddMesh("TerrainOBJ", new Mesh())->CreateOBJ("Data/OBJs/TerrainV2.obj", vec3(1, 1, 1));
        m_pResources->AddMesh("Bonic", new Mesh())->CreateOBJ("Data/OBJs/Bonic.obj", vec3(1, 1, 1));
        m_pResources->AddMesh("SuperBonic", new Mesh())->CreateOBJ("Data/OBJs/SuperBonicV1.obj", vec3(1, 1, 1));
        m_pResources->AddMesh("Bnuckles", new Mesh())->CreateOBJ("Data/OBJs/BnucklesV2.obj", vec3(1, 1, 1));
        m_pResources->AddMesh("SkyBox", new Mesh())->CreateOBJ("Data/OBJs/SkyBoxV1.obj", vec3(1, 1, 1));
        m_pResources->AddMesh("CheckPointMesh", new Mesh())->CreateOBJ("Data/OBJs/CheckPointCollision.obj", vec3(1, 1, 1));
        m_pResources->AddMesh("WreakingBall", new Mesh())->CreateOBJ("Data/OBJs/WreakingBall.obj", vec3(1, 1, 1));
    }

    // Create our shaders.
    {
        m_pResources->AddShader( "Texture", new ShaderProgram( "Data/Shaders/Texture.vert", "Data/Shaders/Texture.frag" ) );
        m_pResources->AddShader("Color", new ShaderProgram("Data/Shaders/Color.vert", "Data/Shaders/Color.frag"));
        m_pResources->AddShader("Light", new ShaderProgram("Data/Shaders/Light.vert", "Data/Shaders/Light.frag"));
        m_pResources->AddShader("Cubemap", new ShaderProgram("Data/Shaders/Cubemap.vert", "Data/Shaders/Cubemap.frag"));
        m_pResources->AddShader("BlackandWhite", new ShaderProgram("Data/Shaders/BlackandWhite.vert", "Data/Shaders/BlackandWhite.frag"));

        m_pResources->AddShader("HorizontalBlur", new ShaderProgram("Data/Shaders/HorizontalBlur.vert", "Data/Shaders/HorizontalBlur.frag"));
        m_pResources->AddShader("VerticalBlur", new ShaderProgram("Data/Shaders/VerticalBlur.vert", "Data/Shaders/VerticalBlur.frag"));
    }
    // Load some textures.
    {
        m_pResources->AddTexture("HealthMaterial", new Texture("Data/Textures/SonicBall.png"));
        m_pResources->AddTexture("Zero", new Texture("Data/Textures/Zero.png"));
        m_pResources->AddTexture("One", new Texture("Data/Textures/One.png"));
        m_pResources->AddTexture("Two", new Texture("Data/Textures/Two.png"));
        m_pResources->AddTexture("Three", new Texture("Data/Textures/Three.png"));
        m_pResources->AddTexture("Four", new Texture("Data/Textures/Four.png"));
        m_pResources->AddTexture("Five", new Texture("Data/Textures/Five.png"));
        m_pResources->AddTexture("Six", new Texture("Data/Textures/Six.png"));
        m_pResources->AddTexture("Seven", new Texture("Data/Textures/Seven.png"));
        m_pResources->AddTexture("Eight", new Texture("Data/Textures/Eight.png"));
        m_pResources->AddTexture("Nine", new Texture("Data/Textures/Nine.png"));
        m_pResources->AddTexture("Slash", new Texture("Data/Textures/Slash.png"));

        m_pResources->AddTexture("TimeZero", new Texture("Data/Textures/Time/TimeZero.png"));
        m_pResources->AddTexture("TimeOne", new Texture("Data/Textures/Time/TimeOne.png"));
        m_pResources->AddTexture("TimeTwo", new Texture("Data/Textures/Time/TimeTwo.png"));
        m_pResources->AddTexture("TimeThree", new Texture("Data/Textures/Time/TimeThree.png"));
        m_pResources->AddTexture("TimeFour", new Texture("Data/Textures/Time/TimeFour.png"));
        m_pResources->AddTexture("TimeFive", new Texture("Data/Textures/Time/TimeFive.png"));
        m_pResources->AddTexture("TimeSix", new Texture("Data/Textures/Time/TimeSix.png"));
        m_pResources->AddTexture("TimeSeven", new Texture("Data/Textures/Time/TimeSeven.png"));
        m_pResources->AddTexture("TimeEight", new Texture("Data/Textures/Time/TimeEight.png"));
        m_pResources->AddTexture("TimeNine", new Texture("Data/Textures/Time/TimeNine.png"));
        m_pResources->AddTexture("TimePeriod", new Texture("Data/Textures/Time/TimePeriod.png"));
        m_pResources->AddTexture("TimeColon", new Texture("Data/Textures/Time/TimeColon.png"));

        m_pResources->AddTexture("Ground", new Texture("Data/Textures/Ground.png"));
        m_pResources->AddTexture( "Megaman", new Texture( "Data/Textures/Megaman.png" ) );
        m_pResources->AddTexture("Pause", new Texture("Data/Textures/Pause.png"));
        m_pResources->AddTexture("Start", new Texture("Data/Textures/Start.png"));
        m_pResources->AddTexture("GameOver", new Texture("Data/Textures/GameOver.png"));
        m_pResources->AddTexture("OptionsSuper", new Texture("Data/Textures/OptionsSuper.png"));
        m_pResources->AddTexture("OptionsSonic", new Texture("Data/Textures/OptionsSonic.png"));
        m_pResources->AddTexture("OptionsKnuckles", new Texture("Data/Textures/OptionsKnuckles.png"));
        m_pResources->AddTexture("Coin", new Texture("Data/Textures/Gold_Texture.png"));
        m_pResources->AddTexture("Checkered", new Texture("Data/Textures/Checkered_Board.png"));

        m_pResources->AddTexture("Render", new Texture(m_pFBO->GetColorTextureHandle()));

        m_pResources->AddTexture("RedEmerald", new Texture("Data/Textures/RedEmerald.png"));
        m_pResources->AddTexture("TealEmerald", new Texture("Data/Textures/TealEmerald.png"));
        m_pResources->AddTexture("PurpleEmerald", new Texture("Data/Textures/PurpleEmerald.png"));
        m_pResources->AddTexture("WhiteEmerald", new Texture("Data/Textures/WhiteEmerald.png"));
        m_pResources->AddTexture("YellowEmerald", new Texture("Data/Textures/YellowEmerald.png"));
        m_pResources->AddTexture("BlueEmerald", new Texture("Data/Textures/BlueEmerald.png"));
        m_pResources->AddTexture("GreenEmerald", new Texture("Data/Textures/GreenEmerald.png"));

        m_pResources->AddTexture("DashPad", new Texture("Data/Textures/DashPad.png"));

        m_pResources->AddTexture("Dead", new Texture("Data/Textures/Dead.png"));

        m_pResources->AddTexture("Red", new Texture("Data/Textures/BnucklesTexture.png"));
        m_pResources->AddTexture("Blue", new Texture("Data/Textures/BonicTexture.png"));
        m_pResources->AddTexture("Yellow", new Texture("Data/Textures/SuperBonicTexture.png"));

        m_pResources->AddTexture("Sky", new Texture("Data/Textures/Sky.png"));

        m_pResources->AddTexture("Black", new Texture("Data/Textures/Black.png"));

        m_pResources->AddTexture("SRank", new Texture("Data/Textures/SRank.png"));
        m_pResources->AddTexture("ARank", new Texture("Data/Textures/ARank.png"));
        m_pResources->AddTexture("BRank", new Texture("Data/Textures/BRank.png"));
        m_pResources->AddTexture("CRank", new Texture("Data/Textures/CRank.png"));
        m_pResources->AddTexture("DRank", new Texture("Data/Textures/DRank.png"));
    }

    // Create some materials.
    {
        m_pResources->AddMaterial( "Megaman", new Material( m_pResources->GetShader( "Light" ), m_pResources->GetTexture( "Megaman" ), 100.0f) );
        m_pResources->AddMaterial("FloorColor", new Material(m_pResources->GetShader("Light"), m_pResources->GetTexture("Ground"), 100.0f));
        m_pResources->AddMaterial("CoinMaterial", new Material(m_pResources->GetShader("Light"), m_pResources->GetTexture("Coin"), 10.0f));
        m_pResources->AddMaterial("CheckeredMaterial", new Material(m_pResources->GetShader("Light"), m_pResources->GetTexture("Checkered"), 10.0f));
        m_pResources->AddMaterial("Start", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Start"), 100.0f));
        m_pResources->AddMaterial("GameOver", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("GameOver"), 100.0f));
        m_pResources->AddMaterial("OptionsSonic", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("OptionsSonic"), 100.0f));
        m_pResources->AddMaterial("OptionsSuper", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("OptionsSuper"), 100.0f));
        m_pResources->AddMaterial("OptionsKnuckles", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("OptionsKnuckles"), 100.0f));
        m_pResources->AddMaterial("Pause", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Pause"), 100.0f));
    
        m_pResources->AddMaterial("TimePeriodMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("TimePeriod"), 10.0f));
        m_pResources->AddMaterial("TimeColonMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("TimeColon"), 10.0f));
        m_pResources->AddMaterial("TimeZeroMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("TimeZero"), 10.0f));
        m_pResources->AddMaterial("TimeOneMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("TimeOne"), 10.0f));
        m_pResources->AddMaterial("TimeTwoMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("TimeTwo"), 10.0f));
        m_pResources->AddMaterial("TimeThreeMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("TimeThree"), 10.0f));
        m_pResources->AddMaterial("TimeFourMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("TimeFour"), 10.0f));
        m_pResources->AddMaterial("TimeFiveMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("TimeFive"), 10.0f));
        m_pResources->AddMaterial("TimeSixMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("TimeSix"), 10.0f));
        m_pResources->AddMaterial("TimeSevenMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("TimeSeven"), 10.0f));
        m_pResources->AddMaterial("TimeEightMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("TimeEight"), 10.0f));
        m_pResources->AddMaterial("TimeNineMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("TimeNine"), 10.0f));
        
        m_pResources->AddMaterial("HealthMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("HealthMaterial"), 10.0f));

        m_pResources->AddMaterial("SlashMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Slash"), 10.0f));
        m_pResources->AddMaterial("ZeroMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Zero"), 10.0f));
        m_pResources->AddMaterial("OneMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("One"), 10.0f));
        m_pResources->AddMaterial("TwoMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Two"), 10.0f));
        m_pResources->AddMaterial("ThreeMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Three"), 10.0f));
        m_pResources->AddMaterial("FourMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Four"), 10.0f));
        m_pResources->AddMaterial("FiveMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Five"), 10.0f));
        m_pResources->AddMaterial("SixMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Six"), 10.0f));
        m_pResources->AddMaterial("SevenMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Seven"), 10.0f));
        m_pResources->AddMaterial("EightMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Eight"), 10.0f));
        m_pResources->AddMaterial("NineMaterial", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Nine"), 10.0f));

        m_pResources->AddMaterial("Render", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Render"), 10.0f));

        m_pResources->AddMaterial("VerticalBlur", new Material(m_pResources->GetShader("VerticalBlur"), m_pResources->GetTexture("Render"), 10.0f));
        m_pResources->AddMaterial("HorizontalBlur", new Material(m_pResources->GetShader("HorizontalBlur"), m_pResources->GetTexture("Render"), 10.0f));
        m_pResources->AddMaterial("BlackandWhite", new Material(m_pResources->GetShader("BlackandWhite"), m_pResources->GetTexture("Render"), 10.0f));

        m_pResources->AddMaterial("RedEmerald", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("RedEmerald"), 10.0f));
        m_pResources->AddMaterial("TealEmerald", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("TealEmerald"), 10.0f));
        m_pResources->AddMaterial("PurpleEmerald", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("PurpleEmerald"), 10.0f));
        m_pResources->AddMaterial("YellowEmerald", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("YellowEmerald"), 10.0f));
        m_pResources->AddMaterial("WhiteEmerald", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("WhiteEmerald"), 10.0f));
        m_pResources->AddMaterial("BlueEmerald", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("BlueEmerald"), 10.0f));
        m_pResources->AddMaterial("GreenEmerald", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("GreenEmerald"), 10.0f));

        m_pResources->AddMaterial("NoTex", new Material(m_pResources->GetShader("Texture"), nullptr, 100.0f));
        m_pResources->AddMaterial("Dead", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Dead"), 10.0f));

        m_pResources->AddMaterial("DashPad", new Material(m_pResources->GetShader("Light"), m_pResources->GetTexture("DashPad"), 10.0f));

        m_pResources->AddMaterial("Knuckles", new Material(m_pResources->GetShader("Light"), m_pResources->GetTexture("Red"), 10.0f));
        m_pResources->AddMaterial("Sonic", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Blue"), 10.0f));
        m_pResources->AddMaterial("Super", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Yellow"), 10.0f));

        m_pResources->AddMaterial("Sky", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Sky"), 10.0f));
        m_pResources->AddMaterial("Black", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("Black"), 10.0f));

        m_pResources->AddMaterial("SRank", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("SRank"), 10.0f));
        m_pResources->AddMaterial("ARank", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("ARank"), 10.0f));
        m_pResources->AddMaterial("BRank", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("BRank"), 10.0f));
        m_pResources->AddMaterial("CRank", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("CRank"), 10.0f));
        m_pResources->AddMaterial("DRank", new Material(m_pResources->GetShader("Texture"), m_pResources->GetTexture("DRank"), 10.0f));
    }

    //Create Collision Shapes
    {
#undef new
        m_pResources->AddCollisionShape("GroundShape", new btBoxShape(btVector3(btScalar(5.0f), btScalar(0.1f), btScalar(5.0f))));
        m_pResources->AddCollisionShape("Player", new btSphereShape(btScalar(1.0f)));
        m_pResources->AddCollisionShape("WreakingBall", new btSphereShape(btScalar(5.0f)));
        m_pResources->AddCollisionShape("Cube", new btBoxShape(btVector3(btScalar(0.5f), btScalar(0.5f), btScalar(0.5f))));
        m_pResources->AddCollisionShape("Dash", new btBoxShape(btVector3(btScalar(5.0f), btScalar(5.0f), btScalar(5.0f))));

        btBvhTriangleMeshShape* TerrainShape = new btBvhTriangleMeshShape(LoadTriangleMesh("TerrainOBJ"),true,true);
        m_pResources->AddCollisionShape("Ground", TerrainShape);

        btBvhTriangleMeshShape* CheckPointShape = new btBvhTriangleMeshShape(LoadTriangleMesh("CheckPointMesh"), true, true);
        m_pResources->AddCollisionShape("CheckPointCollision", CheckPointShape);

        //btBvhTriangleMeshShape* WreakingBallShape = new btBvhTriangleMeshShape(LoadTriangleMesh("WreakingBall"), true, true);
        //m_pResources->AddCollisionShape("WreakingBall", WreakingBallShape);
    }

    const char* cubemapfilenames[6] = {
        "Data/Cubemap/TestCubemap/posx.png",
        "Data/Cubemap/TestCubemap/negx.png",
        "Data/Cubemap/TestCubemap/posy.png",
        "Data/Cubemap/TestCubemap/negy.png",
        "Data/Cubemap/TestCubemap/posz.png",
        "Data/Cubemap/TestCubemap/negz.png",
    };
    m_pResources->AddTexture("Cubemap", new Texture(cubemapfilenames));
    m_pResources->AddMaterial("Cubemap", new Material(m_pResources->GetShader("Cubemap"), nullptr , 10.0f, m_pResources->GetTexture("Cubemap")));
    // Create our controllers.
    for( int i=0; i<4; i++ )
    {
        m_pControllers[i] = new PlayerController();
    }
    {
        // Create our scenes.
        TitleScene* pTitleScene = new TitleScene(this, m_pResources, "Title");
        pTitleScene->LoadContent();
        m_pResources->AddScene("Title", pTitleScene);

        PauseScene* pPauseScene = new PauseScene(this, m_pResources, "Pause");
        pPauseScene->LoadContent();
        m_pResources->AddScene("Pause", pPauseScene);

        GameScene* pGameScene = new GameScene(this, m_pResources, "Game");
        pGameScene->LoadContent();
        m_pResources->AddScene("Game", pGameScene);

        OptionsScene* pOptionsScene = new OptionsScene(this, m_pResources, "Options", (Player*)pGameScene->GetGameObjectByName("Player"));
        pOptionsScene->LoadContent();
        m_pResources->AddScene("Options", pOptionsScene);

        m_pHUD = new HUD(this, m_pResources, "HUD", (Player*)pGameScene->GetGameObjectByName("Player"));
        m_pHUD->LoadContent();
        m_pResources->AddScene("HUD", m_pHUD);

        EndScene* pEndScene = new EndScene(this, m_pResources, "End");
        pEndScene->LoadContent();
        m_pResources->AddScene("End", pEndScene);

        VictoryScene* pVictoryScreen = new VictoryScene(this, m_pResources, "Victory", (Player*)pGameScene->GetGameObjectByName("Player"));
        pVictoryScreen->LoadContent();
        m_pResources->AddScene("Victory", pVictoryScreen);

        m_pSceneManager = new SceneManager(m_pResources);
        m_pSceneManager->PushScene("Title");

        m_pPostEffectScene = new PostEffectScene(this, m_pResources, "PostEffect", (Player*)pGameScene->GetGameObjectByName("Player"));
        m_pPostEffectScene->LoadContent();

        m_pPlayer = (Player*)pGameScene->GetGameObjectByName("Player");
    }
  

    // Create an ImGui object.
    m_pImGuiManager = new ImGuiManager();
    m_pImGuiManager->Init();

    CheckForGLErrors();
}

void Game::OnEvent(Event* pEvent)
{
    m_pImGuiManager->OnEvent( pEvent );

    m_pControllers[0]->OnEvent( pEvent );

    m_pSceneManager->OnEvent(pEvent);

    if( pEvent->GetEventType() == GameEventType_RemoveFromScene )
    {
        RemoveFromSceneEvent* pRemoveFromSceneEvent = static_cast<RemoveFromSceneEvent*>( pEvent );

        Scene* pScene = pRemoveFromSceneEvent->GetScene();
        GameObject* pGameObject = pRemoveFromSceneEvent->GetGameObject();
        
        if( pScene->IsGameObjectInScene( pGameObject ) )
        {
            pGameObject->RemoveFromScene();
        }
    }

    //m_pSceneManager->OnEvent( pEvent );

#if WIN32
    // Enable/Disable V-Sync with F1 and F2.
    if( pEvent->GetEventType() == EventType_Input )
    {
        InputEvent* pInput = static_cast<InputEvent*>( pEvent );

        // Enable V-Sync.
        if( pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_F1 )
            wglSwapInterval( 1 );

        // Disable V-Sync.
        if( pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_F2 )
            wglSwapInterval( 0 );

        // Reset active scene.
        if( pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetInputState() == InputState_Pressed && pInput->GetID() == VK_SPACE )
            if (HasStartedGame == false && IsGameOver == false && InOptionsTab == false)
            {
                m_pSceneManager->PopAllScenes();
                m_pSceneManager->PushScene("Game");
                m_pSceneManager->PushScene("HUD");
                HasStartedGame = true;
            }
        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetInputState() == InputState_Pressed && pInput->GetID() == 'O')
            if (HasStartedGame == false && IsGameOver == false)
            {
                if (InOptionsTab == false)
                {
                    m_pSceneManager->PopScene();
                    m_pSceneManager->PushScene("Options");
                    InOptionsTab = true;
                }

                else if (InOptionsTab == true)
                {
                    m_pSceneManager->PopScene();
                    m_pSceneManager->PushScene("Title");
                    InOptionsTab = false;
                }
            }

        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetInputState() == InputState_Pressed && pInput->GetID() == 'P')
        {
            if (HasStartedGame == true && IsGameOver == false)
            {
                if (IsPaused == false)
                {
                    m_pSceneManager->PushScene("Pause");
                    IsPaused = true;
                }
                else if (IsPaused == true)
                {
                    m_pSceneManager->PopScene();
                    IsPaused = false;
                }
            }
        }
        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetInputState() == InputState_Pressed && pInput->GetID() == 'R')
        {
            if (IsGameOver == false && IsPaused == false)
            {
                m_pSceneManager->PopScene();
                m_pSceneManager->PushScene("End");
                IsGameOver = true;
                glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
            }
        }
        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetInputState() == InputState_Pressed && pInput->GetID() == 'V')
        {
            if (IsGameOver == false && IsPaused == false)
            {
                m_pSceneManager->PopScene();
                m_pSceneManager->PushScene("Victory");
                IsGameOver = true;
            }
        }
        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetInputState() == InputState_Pressed && pInput->GetID() == 'E')
        {
            if (IsGameOver == true && IsPaused == false)
            {
                m_pSceneManager->GetSceneByName("Game")->Reset();
                m_pSceneManager->GetSceneByName("HUD")->Reset();
                m_pSceneManager->PopAllScenes();
                m_pSceneManager->PushScene("Title");
                IsGameOver = false;
                HasStartedGame = false;
            }
        }
    }
#endif //WIN32
}

void Game::Update(float deltaTime)
{
    // Once our events are processed, tell ImGui we're starting a new frame.
    m_pImGuiManager->StartFrame( (float)m_pFramework->GetWindowWidth(), (float)m_pFramework->GetWindowHeight(), deltaTime );

    m_pSceneManager->Update( deltaTime );

    m_pPostEffectScene->Update(deltaTime);

    if (m_pPlayer->GetHealth() == 0)
    {
        if (IsGameOver == false && IsPaused == false)
        {
            m_pSceneManager->PopScene();
            m_pSceneManager->PushScene("End");
            IsGameOver = true;
            glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
        }
    }

    if (m_pPlayer->GetVictory() == true)
    {
        if (IsGameOver == false && IsPaused == false)
        {
            m_pSceneManager->PopScene();
            m_pSceneManager->PushScene("Victory");
            IsGameOver = true;
        }
    }
}

void Game::Draw()
{
    // Setup the values we will clear to, then actually clear the color and depth buffers.
    if (m_pPlayer->GetHealth() > 0)
        glClearColor( 0.0f, 0.0f, 0.4f, 0.0f ); // (red, green, blue, alpha) - dark blue.
#if WIN32
    glClearDepth( 1 ); // 1 is maximum depth.
#endif
    m_pFBO->Bind();
    glViewport(0, 0, 1280, 720);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // Draw our scene.
    m_pSceneManager->Draw();
    m_pFBO->Unbind();

    glViewport(0, 0, 1280, 720);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //m_pSceneManager->Draw();
    m_pPostEffectScene->Draw();
    //fix this sturcture
    //put blur scene last
    // Tell imgui we're at the end of our frame, so it will draw all queued objects.
    m_pImGuiManager->EndFrame();

    CheckForGLErrors();
}

btTriangleMesh* Game::LoadTriangleMesh(std::string objMeshName)
{
    btTriangleMesh* tris = new btTriangleMesh();
    int numOfTri = m_pResources->GetMesh(objMeshName)->GetNumberOfTriangle();
    VertexFormat* verts = m_pResources->GetMesh(objMeshName)->m_Vertices;
    for (int i = 0; i < numOfTri; i += 3)
    {
        tris->addTriangle(btVector3(verts[i].m_Pos.x, verts[i].m_Pos.y, verts[i].m_Pos.z), btVector3(verts[i + 1].m_Pos.x, verts[i + 1].m_Pos.y, verts[i + 1].m_Pos.z), btVector3(verts[i + 2].m_Pos.x, verts[i + 2].m_Pos.y, verts[i + 2].m_Pos.z), true);
    }
    return tris;
}
