#include "Entity.h"
#include "model.h"
#include "object_selection.h"
#include "shader.h"
#include "auxiliary.h"
#include "game_control.h"
#include "RenderScene.h"
#include "Light.h"
#include "globals.h"
void renderMainMenu(Shader& textShader, Entity& textEntity, int selectedIndex);
void renderInstructions(Shader& textShader, Entity& textEntity);
void renderGameOver(Shader& textShader, Entity& textEntity);
void renderOverlayText(Shader& textShader, Entity& textEntity, const std::string& text);

int main()
{

    srand(static_cast<unsigned int>(time(nullptr)));

    // glfw: initialize and configure
    // -------------------------------------------------------------------------------------------

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // -------------------------------------------------------------------------------------------

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "PlateUp-POV", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // -------------------------------------------------------------------------------------------

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -------------------------------------------------------------------------------------------

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // build and compile our shader zprogram
    // -------------------------------------------------------------------------------------------

    Shader ourShader("shader.vs", "shader.fs");
    Shader lightCubeShader("shader_light.vs", "shader_light.fs");
    Shader crosshairShader("crosshair.vs", "crosshair.fs");
    Shader textShader("shader_text.vs", "shader_text.fs");
    Shader wireframeShader("hitbox.vs", "hitbox.fs");

    // Entities
    // -------------------------------------------------------------------------------------------

    Entity plane = createEntity(planeVertices, sizeof(displayWallVerticesCount), "resources/images/floor2.jpg", glm::vec3(0.0f, -0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    Entity walls = createEntity(wallVertices, sizeof(wallVerticesCount), "resources/images/walls.jpg", glm::vec3(0.0f, -0.5f, 0.0f), glm::vec3(10.0f, 1.0f, 10.0f));
	Entity displayWall = createEntity(displayWallVertices, sizeof(displayWallVerticesCount), "resources/images/cheeseburger_1.jpg", glm::vec3(1.0f, -0.5f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f));

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    ourShader.use();
    ourShader.setInt("texture_diffuse1", 0);    //island
    ourShader.setInt("texture_diffuse2", 1);    //fridge body
    ourShader.setInt("texture_diffuse3", 2);    //fridge door
    ourShader.setInt("texture_diffuse4", 3);    //counter
    ourShader.setInt("texture_diffuse5", 4);    //oven top
    ourShader.setInt("texture_diffuse6", 5);    //oven down
    ourShader.setInt("texture_diffuse7", 6);    //burger
    ourShader.setInt("texture_diffuse8", 7);    //cheese
    ourShader.setInt("texture_diffuse9", 8);    //egg texture
    ourShader.setInt("texture_diffuse10", 9);   //tagliere texture
    ourShader.setInt("texture_diffuse11", 10);  //insalata
    ourShader.setInt("texture_diffuse12", 11);  //bread texture
    ourShader.setInt("texture_diffuse13", 12);  //ham texture
    ourShader.setInt("texture_diffuse14", 13);  //trash bin body texture
    ourShader.setInt("texture_diffuse15", 14);  //trash bin top texture
    ourShader.setInt("texture_diffuse16", 15);  //trash bin top texture

    // Models
    // -------------------------------------------------------------------------------------------

    Model island("resources/isola/isola_OpenGL.obj");
    Model fridgeBody("resources/fridge_body/frigo.obj");
    Model fridgeDoor("resources/fridge_door_rotate/Anta.obj");
    Model counter("resources/Kitchen_02/Kitchen_02.obj");
    Model ovenTop("resources/Oven_Up/oven_Up_OpenGL.obj");
    Model ovenBottom("resources/Oven_Down/oven_Down_OpenGL.obj");
    Model burger("resources/burger/burger.obj");
    Model cheese("resources/cheese/cheese.obj");
    Model egg("resources/egg/egg.obj");
    Model tagliere("resources/tagliere/tagliere.obj");
    Model insalata("resources/insalata/insalata.obj");
    Model bread("resources/bread/bread.obj");
    Model ham("resources/ham/ham.obj");
    Model trashBinBody("resources/Trash_Bin_Body/trash_bin.obj");
    Model trashBinTop("resources/Trash_Bin_Top/trash_bin_top.obj");
    Model tomato("resources/tomato/tomato.obj");


    // lighting setup
    // -------------------------------------------------------------------------------------------

    unsigned int lightCubeVAO, lightCubeVBO;
    glGenVertexArrays(1, &lightCubeVAO);
    glGenBuffers(1, &lightCubeVBO);

    glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubeLightVerticesCount), CubeLightVertices, GL_STATIC_DRAW);

    glBindVertexArray(lightCubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    std::vector<Light> lights;
    lights.push_back({ glm::vec3(3.0f, 2.75f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f });


    
    // turn on Sound engine
    // -------------------------------------------------------------------------------------------

    engine = irrklang::createIrrKlangDevice();
    if (!engine)
        return 0; // error starting up the engine


    //text shader
    // -------------------------------------------------------------------------------------------

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
    textShader.use();
    glUniformMatrix4fv(glGetUniformLocation(textShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    FT_Library ft = inventoryText.SetFreeType();
    std::string font_name = "resources/fonts/the-bomb-sound/The Bomb Sound.ttf";
    std::string font = inventoryText.FindFont(font_name);
    inventoryText.LoadFontAsFace(ft, font);


    // Crosshair Setup
    // -------------------------------------------------------------------------------------------

    Entity crosshair;
    setupCrosshair(crosshair, crosshairVertices, sizeof(crosshairVerticesCount));
    crosshairShader.use();

    //Inventory Setup
    // -------------------------------------------------------------------------------------------

    glm::vec3 inventoryPosition = glm::vec3(650.0f, 450.0f, -0.5f);

    Entity textEntity;
    setupText(textEntity);
    textShader.use();


    // hitbox setup
    // -------------------------------------------------------------------------------------------

    Entity hitbox;
    setupHitbox(hitbox, hitboxVertices, sizeof(hitboxVerticesCount), hitboxIndices, sizeof(hitboxIndicesCount));


    //Instanza di RenderScene 
    RenderScene scene(
        ourShader,
        lightCubeShader,
        crosshairShader,
        textShader,
        wireframeShader,
        plane,
        walls,
        crosshair,
        textEntity,
        hitbox,
        lights,
        lightCubeVAO,
        displayWall,
        island,
        fridgeBody,
        fridgeDoor,
        counter,
        ovenTop,
        ovenBottom,
        burger,
        cheese,
        egg,
        tagliere,
        insalata,
        bread,
        ham,
        trashBinBody,
        trashBinTop,
        tomato
    );


    // Inizializza il timer del gioco
    GameTimer timer(LEVEL_0);

    // Inizializza il punteggio del gioco
    Points score; 
	score.resetPoints();

    // RENDER LOOP
    // ---------------------------------------------------------------------------------------------------
    // ---------------------------------------------------------------------------------------------------

    while (!glfwWindowShouldClose(window))
    {
        // ==== TIME LOGIC ==== 

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // ==== INPUT ==== 

        processInput(window);
       
        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


        switch (gameState) {
        case MAIN_MENU:
            renderMainMenu(textShader, textEntity, selectedIndex);
            break;

        case INSTRUCTIONS:
            renderInstructions(textShader, textEntity);
            break;

        case PLAYING:
            if (isPaused) {
                renderOverlayText(textShader, textEntity, "Game Paused");
                renderTheGame = false;
            }
            else {
                renderTheGame = true;
            }
            
            if (gameManager.isTransitioning) {
                std::string countdownText = "Next Round in: " + std::to_string(static_cast<int>(ceil(gameManager.transitionCountdown)));
                renderOverlayText(textShader, textEntity, countdownText);

                gameManager.transitionCountdown -= deltaTime;
                if (gameManager.transitionCountdown <= 0.0f) {
                    gameManager.isTransitioning = false;
                    timer.reset();
                    gameManager.currentRecipe = Recipe::getRandomRecipe(gameManager.level);
                    engine->play2D("resources/media/start.wav");
                }

                renderTheGame = false;
                break;
            }

            // === LOGICA DI GIOCO ===
            timer.update(deltaTime);

            if (timer.isGameOver()) {
                if (gameManager.checkRoundPassed(score)) {
                    gameManager.round++;

                    if (gameManager.checkVictory()) {
                        gameState = GAME_WIN;
                    }
                    else {
                        if (gameManager.round > gameManager.maxRounds) {
                            gameManager.level = static_cast<GameLevel>(static_cast<int>(gameManager.level) + 1);
                            gameManager.round = 1;
                        }
                        gameManager.resetTransition();
                        score.resetPoints();
                    }
                }
                else {
                    gameState = GAME_OVER;
                }

                renderTheGame = false;
                break;
            }

            // === RENDERING ===
            if (renderTheGame) {
                scene.draw(gameManager.currentRecipe);
                scene.drawUI(score, timer, inventory);  
            }

            // === INTERAZIONE CON HITBOX E CONSEGNA ===
            checkHitboxSelections(camera, inventory, engine, timer, score, gameManager.currentRecipe);

            break;

        case GAME_OVER:
            renderGameOver(textShader, textEntity);
            break;
        
        case GAME_WIN:
            renderOverlayText(textShader, textEntity, "You Win!");
            break;
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &plane.VAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &plane.VBO);
	glDeleteVertexArrays(1, &displayWall.VAO);
	glDeleteBuffers(1, &displayWall.VBO);
    // Add cleanup for crosshair VAO/VBO before terminating GLFW
    glDeleteVertexArrays(1, &crosshair.VAO);
    glDeleteBuffers(1, &crosshair.VBO);

    // Add cleanup for text VAO/VBO before terminating GLFW
    glDeleteVertexArrays(1, &textEntity.VAO);
    glDeleteBuffers(1, &textEntity.VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}



void renderMainMenu(Shader& textShader, Entity& textEntity, int selectedIndex) {


    // in renderMainMenu()
    static float lastRotationTime = 0.0f;
    static float modelAngle = 0.0f;

    float currentTime = glfwGetTime();
    if (currentTime - lastRotationTime > 0.05f) {  // update every ~50ms
        modelAngle += 1.0f; // or any increment
        lastRotationTime = currentTime;
    }


    float angle = glfwGetTime() * 0.5f;
    float radius = 5.0f;
    glm::vec3 camPos = glm::vec3(sin(angle) * radius, 1.0f, cos(angle) * radius);
    glm::mat4 view = glm::lookAt(camPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));


    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),          // FOV
        (float)SCR_WIDTH / SCR_HEIGHT, // aspect ratio
        0.1f, 100.0f                  // near e far plane
    );


    // 1. Disegna il modello 3D di sfondo
    Shader menuObjectShader("menuObjectshader.vs", "menuObjectshader.fs");
    Model kitchenModel("resources/isola/isola_OpenGL.obj");

    menuObjectShader.use();

    // model matrix → rotazione
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
    model = glm::rotate(model, glm::radians(modelAngle), glm::vec3(0, 1, 0));
    model = glm::scale(model, glm::vec3(0.5f));

    menuObjectShader.setMat4("model", model);
    menuObjectShader.setMat4("view", view);         // usa la camera menu
    menuObjectShader.setMat4("projection", projection);

    kitchenModel.Draw(menuObjectShader);



    textShader.use();

    std::string title = "Main Menu";
    float titleScale = 1.0f;
    float time = glfwGetTime();  // per animazioni

    float titleWidth = inventoryText.GetTextWidth(title, titleScale);
    float titleX = SCR_WIDTH / 2 - titleWidth / 2;
    float titleY = SCR_HEIGHT - 100;

    inventoryText.RenderText(textShader, title, titleX, titleY, titleScale, glm::vec3(1.0, 0.8, 0.3), textEntity.VAO, textEntity.VBO);

    std::vector<std::string> menuItems = {
        "1. Play",
        "2. Instructions",
        "3. Quit"
    };

    float scale = 0.75f;
    float spacing = 50.0f;



    for (size_t i = 0; i < menuItems.size(); ++i) {
        std::string item = menuItems[i];
        float textWidth = inventoryText.GetTextWidth(item, scale);
        float x = SCR_WIDTH / 2 - textWidth / 2;

        // Animazione verticale a onda (leggera fluttuazione)
        //float floatY = 3.0f * sin(time * 2.0f + i);
		float floatY = 0.0f; // Disabilitato per ora
        float y = titleY - (i + 1) * spacing + floatY;

        // Colore: evidenzia l'elemento selezionato
        glm::vec3 color = (i == selectedIndex)
            ? glm::vec3(1.0, 0.85, 0.2)  // giallo
            : glm::vec3(0.3, 0.7f, 0.9f); // blu chiaro

        // Animazione alpha (pulsazione leggera)
        //float alpha = 0.9f + 0.1f * sin(time * 4.0f + i);
        //color *= alpha;

        inventoryText.RenderText(textShader, item, x, y, scale, color, textEntity.VAO, textEntity.VBO);
    }
}

void renderInstructions(Shader& textShader, Entity& textEntity) {
    textShader.use();
    inventoryText.RenderText(textShader, "Instructions", SCR_WIDTH / 2 - 50, SCR_HEIGHT - 100, 1.0f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
    inventoryText.RenderText(textShader, "Use WASD to move", SCR_WIDTH / 2 - 50, SCR_HEIGHT - 150, 0.75f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
    inventoryText.RenderText(textShader, "Press P to pause", SCR_WIDTH / 2 - 50, SCR_HEIGHT - 200, 0.75f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
    inventoryText.RenderText(textShader, "Press ESC to quit", SCR_WIDTH / 2 - 50, SCR_HEIGHT - 250, 0.75f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
    inventoryText.RenderText(textShader, "Press B to go back", SCR_WIDTH / 2 - 50, SCR_HEIGHT - 300, 0.75f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
}

void renderGameOver(Shader& textShader, Entity& textEntity) {
    // render the game over screen
    renderOverlayText(textShader, textEntity, "Game Over");
}

void renderOverlayText(Shader& textShader, Entity& textEntity, const std::string& text) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    textShader.use();
    inventoryText.RenderText(textShader, text, SCR_WIDTH / 2 - 50, SCR_HEIGHT / 2, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f), textEntity.VAO, textEntity.VBO);
}
