#include "Entity.h"
#include "model.h"
#include "object_selection.h"
#include "shader.h"
#include "auxiliary.h"
#include "game_control.h"
#include "RenderScene.h"
#include "records.h"
#include "Light.h"
#include "globals.h"

void renderMainMenu(Shader& textShader, Entity& textEntity);
void renderInstructions(Shader& textShader, Entity& textEntity);
void renderRecords(Shader& textShader, Entity& textEntity);
void renderWin(Shader& textShader, Entity& textEntity);
void renderGameOver(Shader& textShader, Entity& textEntity);
void renderOverlayText(Shader& textShader, Entity& textEntity, const std::string& text, float scale, glm::vec3 color);

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
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CCW);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);


    // build and compile our shader zprogram
    // -------------------------------------------------------------------------------------------

    Shader ourShader("shader.vs", "shader.fs");
    Shader lightCubeShader("shader_light.vs", "shader_light.fs");
    Shader crosshairShader("crosshair.vs", "crosshair.fs");
    Shader textShader("shader_text.vs", "shader_text.fs");
    Shader wireframeShader("hitbox.vs", "hitbox.fs");
    Shader rectangleShader("shader_rect.vs", "shader_rect.fs");

    // Entities
    // -------------------------------------------------------------------------------------------

    Entity plane = createEntity(
        planeVertices,
        planeVerticesCount,
        "resources/images/floor.jpg",
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    );

    Entity walls = createEntity(
        wallVertices,
        wallVerticesCount,
        "resources/images/wall.jpg",
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    );

    Entity ceiling = createEntity(
        ceilingVertices,
        ceilingVerticesCount,
        "resources/images/soffitto.jpg",
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    );


    Entity displayWall = createEntity(
        displayWallVertices,
        displayWallVerticesCount,
        "",
        glm::vec3(0.01f, -0.5f, 0.1f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    );

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
    ourShader.setInt("texture_diffuse16", 15);  //tomato texture
	ourShader.setInt("texture_diffuse17", 16);  //padella texture
    ourShader.setInt("texture_diffuse18", 17);  //texture cubo

    // Models
    // -------------------------------------------------------------------------------------------

    Model island("resources/isola/isola_OpenGL.obj");
    Model fridgeBody("resources/fridge_body/frigo.obj");
    Model fridgeDoor("resources/fridge_door_rotate/Anta.obj");
    Model counter("resources/counter/counter.obj");
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
    Model trashBinTop("resources/Trash_Bin_Top_Rotate/trash_bin_top.obj");
	Model padella("resources/padella_metallo/padella.obj");
	Model tomato("resources/tomato/tomato.obj");
    Model bonusMalusCube("resources/cube_bonus_malus/cube_bonus_malus.obj");


    // lighting setup
    // -------------------------------------------------------------------------------------------

    std::vector<Light> lights;

    unsigned int lightCubeVAO, lightCubeVBO;
    glGenVertexArrays(1, &lightCubeVAO);
    glGenBuffers(1, &lightCubeVBO);

    glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
    glBufferData(GL_ARRAY_BUFFER, CubeLightVerticesCount * 6 * sizeof(float), CubeLightVertices, GL_STATIC_DRAW);


    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Aggiungi luci all'array
    lights.push_back({ glm::vec3(3.0f, 2.75f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f }); // Luce esistente
    //lights.push_back({ glm::vec3(-3.0f, 4.0f, -2.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.2f }); // Nuova luce 

    
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
    setupCrosshair(
        crosshair, 
        crosshairVertices, 
        crosshairVerticesCount *3 * sizeof(float)
    );

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
    
    setupHitbox(hitbox, hitboxVertices, hitboxVerticesCount * 3 * sizeof(float), hitboxIndices, hitboxIndicesCount * sizeof(unsigned int));


    //Instanza di RenderScene 
    RenderScene scene(ourShader, lightCubeShader, projection, crosshairShader, textShader, wireframeShader, plane, walls, ceiling, crosshair, textEntity, hitbox,
        lights, lightCubeVAO, displayWall, island, fridgeBody, fridgeDoor, counter, ovenTop, ovenBottom, burger, cheese, egg, tagliere, insalata, bread,
        ham, trashBinBody, trashBinTop, tomato, padella, bonusMalusCube );


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
            renderMainMenu(textShader, textEntity);
            break;

        case INSTRUCTIONS:
            renderInstructions(textShader, textEntity);
            break;

		case RECORDS:
            renderRecords(textShader, textEntity);
            break;

        case PAUSE:
            renderOverlayText(textShader, textEntity, "Pause", 0.9f, glm::vec3(0.3f, 0.7f, 0.9f));
            break;

        case PLAYING:
            renderTheGame = true;
            if (gameManager.isTransitioning) {
                std::string countdownText = "Next Round in: " + std::to_string(static_cast<int>(ceil(gameManager.transitionCountdown)));
                
                textShader.use();
                float scale = 0.9f;
                float textWidth = inventoryText.GetTextWidth(countdownText, scale);
                float x = SCR_WIDTH / 2 - textWidth / 2;
                float y = SCR_HEIGHT / 2;
                inventoryText.RenderText(textShader, countdownText, x, y, scale, glm::vec3(0.3f, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);

                //renderOverlayText(textShader, textEntity, countdownText);

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
            // 2 è il bonus che aumenta il tempo
            // just activated per attivare il bonus solo una volta
            if (bonusMalus.bonusMalusJustActivated && bonusMalus.getNumBonusMalusActive() == 2) {
                float d = 10.0f;
                timer.addTime(d);
            }
            
            timer.update(deltaTime);

            if (timer.isGameOver()) {
                if (gameManager.checkRoundPassed(score)) {
                    if (gameManager.checkVictory()) {
                        gameState = GAME_WIN;
                    }
                    else {
                        gameManager.nextRound(score);
						timer.setLevel(gameManager.level);
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
                scene.drawUI(score, timer, inventory, gameManager.currentRecipe);  
            }

            // === INTERAZIONE CON HITBOX E CONSEGNA ===
            checkHitboxSelections(camera, inventory, engine, timer, score, gameManager.currentRecipe);

            // === GESTIONE BONUS / MALUS ===
            gestioneBonusMalus(camera, timer.getLevel(), timer, bonusMalus);

            break;

        case GAME_OVER:
            if (!gameManager.scoreSaved) {
			    gameManager.saveScoreRecord();
				gameManager.scoreSaved = true;
            }
            renderGameOver(textShader, textEntity);

            if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
                resetGame(score);
                gameState = MAIN_MENU;
            }

            break;
        
        case GAME_WIN:
            if (!gameManager.scoreSaved) {
                gameManager.saveScoreRecord();
                gameManager.scoreSaved = true;
            }
            renderWin(textShader, textEntity);

            if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
                resetGame(score);
                gameState = MAIN_MENU;
            }
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
    engine->drop();
    return 0;
}

void renderMainMenu(Shader& textShader, Entity& textEntity) {
    // === BACKGROUND (MODELLO 3D ECC) ===
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    textShader.use();

    std::string title = "Main Menu";
    float titleScale = 1.0f;
    float titleWidth = inventoryText.GetTextWidth(title, titleScale);
    float titleX = SCR_WIDTH / 2 - titleWidth / 2;
    float titleY = SCR_HEIGHT - 100;

    inventoryText.RenderText(textShader, title, titleX, titleY, titleScale, glm::vec3(1.0, 0.8, 0.3), textEntity.VAO, textEntity.VBO);


    std::vector<std::string> menuItems = {"1. Play", "2. Instructions", "3. Records", "4. Quit" };

    float scale = 0.75f;
    float spacing = 50.0f;
    float baseY = SCR_HEIGHT - 150.0f;

    for (size_t i = 0; i < menuItems.size(); ++i) {
        std::string item = menuItems[i];
        float textWidth = inventoryText.GetTextWidth(item, scale);
        float x = SCR_WIDTH / 2 - textWidth / 2;
		float y = baseY - i * spacing;

        inventoryText.RenderText(textShader, item, x, y, scale, glm::vec3(0.3f, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
    }
}

void renderInstructions(Shader& textShader, Entity& textEntity) {
    textShader.use();

    float titleScale = 0.9f;
    float textScale = 0.6f;
    float spacing = 40.0f;

    float yStart = SCR_HEIGHT - 100.0f;

    // === Titolo centrato ===
    std::string title = "INSTRUCTIONS";
    float titleWidth = inventoryText.GetTextWidth(title, titleScale);
    float titleX = SCR_WIDTH / 2 - titleWidth / 2;
    inventoryText.RenderText(textShader, title, titleX, yStart, titleScale, glm::vec3(1.0f, 0.8f, 0.3f), textEntity.VAO, textEntity.VBO);

    // === Comandi principali ===
    std::vector<std::pair<std::string, std::string>> commands = {
        {"W", "Move forward"},
        {"A", "Move left"},
        {"S", "Move backward"},
        {"D", "Move right"},
        {"Mouse", "Look around"},
        {"Click", "Interact with objects"},
        {"P", "Pause / Resume"}
    };

    std::pair<std::string, std::string> backCommand = { "B", "Back to main menu" };

    // Calcolo larghezza massima per la colonna 1
    float maxKeyWidth = 0.0f;
    for (const auto& pair : commands) {
        float keyWidth = inventoryText.GetTextWidth(pair.first, textScale);
        if (keyWidth > maxKeyWidth) maxKeyWidth = keyWidth;
    }

    // Punto centrale della colonna 1
    float col1CenterX = SCR_WIDTH / 2 - 100.0f;
    float col2StartX = col1CenterX + maxKeyWidth / 2 + 20.0f;

    // Disegna i comandi
    for (size_t i = 0; i < commands.size(); ++i) {
        float y = yStart - ((i + 1) * spacing);

        const std::string& key = commands[i].first;
        const std::string& desc = commands[i].second;

        float keyWidth = inventoryText.GetTextWidth(key, textScale);
        float keyX = col1CenterX - keyWidth / 2.0f;

        inventoryText.RenderText(textShader, key, keyX, y, textScale, glm::vec3(0.9f, 0.2f, 0.2f), textEntity.VAO, textEntity.VBO);
        inventoryText.RenderText(textShader, desc, col2StartX, y, textScale, glm::vec3(0.3f, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
    }

    // === Separatore ===
    float yLast = yStart - (commands.size() * spacing);
    float yB = yLast - 100.0f;  // B è almeno 100px sotto
    float yLine = (yLast + yB) / 2.0f;

    std::string line = "------------------------------";
    float lineWidth = inventoryText.GetTextWidth(line, textScale);
    float lineX = SCR_WIDTH / 2 - lineWidth / 2;
    inventoryText.RenderText(textShader, line, lineX, yLine, textScale, glm::vec3(0.5f), textEntity.VAO, textEntity.VBO);

    // === Comando B ===
    float keyWidthB = inventoryText.GetTextWidth(backCommand.first, textScale);
    float keyXB = col1CenterX - keyWidthB / 2.0f;
    inventoryText.RenderText(textShader, backCommand.first, keyXB, yB, textScale, glm::vec3(0.9f, 0.2f, 0.2f), textEntity.VAO, textEntity.VBO);

    inventoryText.RenderText(textShader, backCommand.second, col2StartX, yB, textScale, glm::vec3(0.3f, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
}

void renderWin(Shader& textShader, Entity& textEntity) {
    // render the game over screen
    renderOverlayText(textShader, textEntity, "You Won!", 0.9f, glm::vec3(0.3f, 0.7f, 0.9f));
    engine->play2D("resources/media/win.wav");
}

void renderGameOver(Shader& textShader, Entity& textEntity) {
    
    static bool soundPlayed = false;

    if (!soundPlayed) {
        engine->play2D("resources/media/gameover.wav");
        soundPlayed = true;
    }
        
    // render the game over screen
    renderOverlayText(textShader, textEntity, "Game Over", 0.9f, glm::vec3(0.3f, 0.7f, 0.9f));
}

void renderOverlayText(Shader& textShader, Entity& textEntity, const std::string& text, float scale = 1.0f, glm::vec3 color = glm::vec3(1.0f)) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    textShader.use();
    float textWidth = inventoryText.GetTextWidth(text, scale);
    float x = SCR_WIDTH / 2 - textWidth / 2;
    float y = SCR_HEIGHT / 2;
    inventoryText.RenderText(textShader, text, x, y, scale, color, textEntity.VAO, textEntity.VBO);
}

void renderRecords(Shader& textShader, Entity& textEntity){

    textShader.use();

    float titleScale = 0.9f;
    float textScale = 0.6f;
    float spacing = 40.0f;

    float yStart = SCR_HEIGHT - 100.0f;

    // === Titolo centrato ===
    std::string title = "TOP 10 RECORDS";
    float titleWidth = inventoryText.GetTextWidth(title, titleScale);
    float titleX = SCR_WIDTH / 2 - titleWidth / 2;
    inventoryText.RenderText(textShader, title, titleX, yStart, titleScale, glm::vec3(1.0f, 0.8f, 0.3f), textEntity.VAO, textEntity.VBO);

    // === Carica record dal file ===
    auto records = getTopRecords();

    float col1X = SCR_WIDTH / 2 - 200.0f;
    float col2X = SCR_WIDTH / 2 + 50.0f;

    for (size_t i = 0; i < records.size(); ++i) {
        float y = yStart - ((i + 1) * spacing);

        std::string time = records[i].timestamp;
        std::string scoreStr = std::to_string(records[i].score);

        inventoryText.RenderText(textShader, time, col1X, y, textScale, glm::vec3(0.7f), textEntity.VAO, textEntity.VBO);
        inventoryText.RenderText(textShader, scoreStr, col2X+50.0f, y, textScale, glm::vec3(0.3f, 0.9f, 0.3f), textEntity.VAO, textEntity.VBO);
    }

    // === Separatore ===
    float yLast = yStart - (records.size() * spacing);
    float yB = yLast - 100.0f;
    float yLine = (yLast + yB) / 2.0f;

    std::string line = "------------------------------";
    float lineWidth = inventoryText.GetTextWidth(line, textScale);
    float lineX = SCR_WIDTH / 2 - lineWidth / 2;
    inventoryText.RenderText(textShader, line, lineX, yLine, textScale, glm::vec3(0.5f), textEntity.VAO, textEntity.VBO);

    std::string keyText = "B";
    std::string descText = "   Back to main menu";

    float keyWidth = inventoryText.GetTextWidth(keyText, textScale);
    float descWidth = inventoryText.GetTextWidth(descText, textScale);
    float totalWidth = keyWidth + descWidth;

    // Punto di partenza centrato
    float startX = SCR_WIDTH / 2 - totalWidth / 2;

    // Render "B" in rosso
    inventoryText.RenderText(textShader, keyText, startX, yB, textScale, glm::vec3(0.9f, 0.2f, 0.2f), textEntity.VAO, textEntity.VBO);

    // Render "Back to main menu" in azzurro
    inventoryText.RenderText(textShader, descText, startX + keyWidth, yB, textScale, glm::vec3(0.3f, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
}