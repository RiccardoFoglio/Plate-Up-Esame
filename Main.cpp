#include "Entity.h"
#include "Light.h"
#include "Model.h"
#include "object_selection.h"
#include "shader.h"
#include "auxiliary.h"
#include "game_control.h"

void renderMainMenu(Shader& textShader, Entity& textEntity, int selectedIndex);
void renderInstructions(Shader& textShader, Entity& textEntity);
void renderGame(Shader& ourShader, Shader& lightCubeShader, Shader& crosshairShader, Shader& textShader, Shader& wireframeShader, Entity& plane, Entity& walls, Entity& crosshair, Entity& textEntity, Entity& hitbox, std::vector<Light>& lights, unsigned int lightCubeVAO);
void renderGameOver(Shader& textShader, Entity& textEntity);
void renderOverlayText(Shader& textShader, Entity& textEntity, const std::string& text);

int main()
{
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
    Shader postItShader("shader_post-it.vs", "shader_post-it.fs");
    Shader textShader("shader_text.vs", "shader_text.fs");
    Shader wireframeShader("hitbox.vs", "hitbox.fs");

    // Entities
    // -------------------------------------------------------------------------------------------

    Entity plane = createEntity(planeVertices, sizeof(planeVertices), "resources/images/floor2.jpg", glm::vec3(0.0f, -0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    Entity walls = createEntity(wallVertices, sizeof(wallVertices), "resources/images/walls.jpg", glm::vec3(0.0f, -0.5f, 0.0f), glm::vec3(10.0f, 1.0f, 10.0f));
	Entity displayWall = createEntity(displayWallVertices, sizeof(displayWallVertices), "resources/images/cheeseburger_1.jpg", glm::vec3(1.0f, -0.5f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f));


    // lighting setup
    // -------------------------------------------------------------------------------------------

    std::vector<Light> lights;

    unsigned int lightCubeVAO, lightCubeVBO;
    glGenVertexArrays(1, &lightCubeVAO);
    glGenBuffers(1, &lightCubeVBO);

    glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CubeLightVertices), CubeLightVertices, GL_STATIC_DRAW);

    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Aggiungi luci all'array
    lights.push_back({ glm::vec3(3.0f, 2.75f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f }); // Luce esistente
    //lights.push_back({ glm::vec3(-3.0f, 4.0f, -2.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.2f }); // Nuova luce 


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
    setupCrosshair(crosshair, crosshairVertices, sizeof(crosshairVertices));
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
    setupHitbox(hitbox, hitboxVertices, sizeof(hitboxVertices), hitboxIndices, sizeof(hitboxIndices));

    // Inizializza il timer del gioco
    GameTimer timer(EASY);

    // Inizializza il punteggio del gioco
    Points score; 
	score.resetPoints();



    // RENDER LOOP
    // ---------------------------------------------------------------------------------------------------
    // ---------------------------------------------------------------------------------------------------

    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // Check if the game is over
        if (timer.isGameOver()) {
            gameState = GAME_OVER;
        }

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
            break;
        case GAME_OVER:
            renderGameOver(textShader, textEntity);
            break;
        }


        if (renderTheGame)
        {
                
			timer.update(deltaTime);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, plane.textureID);
		

            // set uniforms
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = camera.GetViewMatrix();
            projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

            ourShader.use();
            ourShader.setMat4("view", view);
            ourShader.setMat4("projection", projection);
            ourShader.setVec3("viewPos", camera.Position);
            ourShader.setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f)); // Optional if using texture


            // light properties
            ourShader.setInt("numLights", lights.size());
            for (int i = 0; i < lights.size(); ++i) {
                ourShader.setVec3("lights[" + std::to_string(i) + "].position", lights[i].position);
                ourShader.setVec3("lights[" + std::to_string(i) + "].color", lights[i].color);
                ourShader.setFloat("lights[" + std::to_string(i) + "].intensity", lights[i].intensity);
            }


            // draw floor as normal, but don't write the floor to the stencil buffer, we only care about the containers. We set its mask to 0x00 to not write to the stencil buffer.
            glStencilMask(0x00);


            updateFridgeDoorAnimation(deltaTime);



            // floor
            //glBindVertexArray(planeVAO);
            drawEntity(plane, ourShader, view, projection);

            // Display wall
            drawEntity(displayWall, ourShader, view, projection);

            // Renderizza le pareti e il soffitto
            glBindVertexArray(walls.VAO);
            glBindTexture(GL_TEXTURE_2D, walls.textureID); 
            ourShader.setMat4("model", glm::mat4(1.0f));
            glDrawArrays(GL_TRIANGLES, 0, 30);

            // render the island model
            model = glm::mat4(1.0f);
            model = glm::translate(model, islandPosition);
            model = glm::scale(model, islandSize);
            ourShader.setMat4("model", model);
            island.Draw(ourShader);

            // render the egg model
            model = glm::mat4(1.0f);
            model = glm::translate(model, eggPosition);
            model = glm::scale(model, eggSize);
            ourShader.setMat4("model", model);
            egg.Draw(ourShader);

            // render the cheese model
            model = glm::mat4(1.0f);
            model = glm::translate(model, cheesePosition);
            model = glm::scale(model, cheeseSize);
            ourShader.setMat4("model", model);
            cheese.Draw(ourShader);


            // render the burger model
            model = glm::mat4(1.0f);
            model = glm::translate(model, burgerPosition);
            model = glm::scale(model, burgerSize);
            ourShader.setMat4("model", model);
            burger.Draw(ourShader);

            // render the tagliere model
            model = glm::mat4(1.0f);
            model = glm::translate(model, taglierePosition);
            model = glm::scale(model, tagliereSize);
            ourShader.setMat4("model", model);
            tagliere.Draw(ourShader);

            // render the insalata model
            model = glm::mat4(1.0f);
            model = glm::translate(model, insalataPosition);
            model = glm::scale(model, insalataSize);
            ourShader.setMat4("model", model);
            insalata.Draw(ourShader);

            // render the bread model
            model = glm::mat4(1.0f);
            model = glm::translate(model, breadPosition);
            model = glm::scale(model, breadSize);
            ourShader.setMat4("model", model);
            bread.Draw(ourShader);

            // render the ham model
            model = glm::mat4(1.0f);
            model = glm::translate(model, hamPosition);
            model = glm::scale(model, hamSize);
            ourShader.setMat4("model", model);
            ham.Draw(ourShader);


            

            // render the fridge model
            model = glm::mat4(1.0f);
            model = glm::translate(model, fridgePosition);
            model = glm::scale(model, fridgeSize);
            ourShader.setMat4("model", model);
            fridgeBody.Draw(ourShader);

			// render the fridge door model
            glm::mat4 modelDoor = glm::mat4(1.0f);

            glm::vec3 pivotOffset = glm::vec3(0.25f, 0.0f, 0.0f);

            modelDoor = glm::translate(modelDoor, fridgeDoorPosition);         // Porta in posizione

            //modelDoor = glm::translate(modelDoor, pivotOffset);            // Sposta il pivot
            modelDoor = glm::rotate(modelDoor, glm::radians(currentFridgeDoorAngle), glm::vec3(0.0f, 1.0f, 0.0f)); // Ruota
            //modelDoor = glm::translate(modelDoor, -pivotOffset);           // Riporta indietro il pivot

            modelDoor = glm::scale(modelDoor, fridgeSize);                 // Scala

            ourShader.setMat4("model", modelDoor);
            fridgeDoor.Draw(ourShader);
            
           

            
            // render the counter model
            model = glm::mat4(1.0f);
            model = glm::translate(model, counterPosition);
            model = glm::scale(model, counterSize);
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
            ourShader.setMat4("model", model);
            counter.Draw(ourShader);
            
            

            // render the oven top model
            model = glm::mat4(1.0f);
            model = glm::translate(model, ovenPosition + glm::vec3(0.0f, 0.2f, 0.0f));
            model = glm::scale(model, counterSize);
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
            ourShader.setMat4("model", model);
            ovenTop.Draw(ourShader);

            // render the oven bottom model
            model = glm::mat4(1.0f);
            model = glm::translate(model, ovenPosition);
            model = glm::scale(model, counterSize);
            model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
            ourShader.setMat4("model", model);
            ovenBottom.Draw(ourShader);

            // render the lamp objects
            lightCubeShader.use();
            lightCubeShader.setMat4("projection", projection);
            lightCubeShader.setMat4("view", view);
            for (const auto& light : lights) {
                model = glm::mat4(1.0f);
                model = glm::translate(model, light.position);
                model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
                lightCubeShader.setMat4("model", model);

                glBindVertexArray(lightCubeVAO);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }

            // render the crosshair
            crosshairShader.use();
            glBindVertexArray(crosshair.VAO);
            glDrawArrays(GL_LINES, 0, 4);


            // Draw the inventory
            // -------------------------------------------------------------------------------

            // Render the timer
            textShader.use();
            std::string timerText = "Timer: " + std::to_string(static_cast<int>(timer.getTime()));
            inventoryText.RenderText(textShader, timerText, 10.0f, SCR_HEIGHT - 30.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);


			// Render the points
            textShader.use(); 
            std::string pointText = "Points: " + std::to_string(static_cast<int>(score.getPoints()));
			inventoryText.RenderText(textShader, pointText, 10.0f, SCR_HEIGHT - 60.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);

            if (inventory.GetState())
            {
                // Enable blending for text rendering
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                textShader.use(); // Ensure text shader is active

                inventoryText.RenderText(textShader, "Inventario", 600.0f, 560.0f, 0.75f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
                inventoryText.RenderText(textShader, "Pomodori ", 610.0f, 530.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
                std::string pom = std::to_string(inventory.GetPomodori());
                inventoryText.RenderText(textShader, pom, 740.0f, 530.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
                inventoryText.RenderText(textShader, "Insalata ", 610.0f, 508.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
                std::string ins = std::to_string(inventory.GetInsalata());
                inventoryText.RenderText(textShader, ins, 740.0f, 508.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
                inventoryText.RenderText(textShader, "Pane ", 610.0f, 486.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
                std::string pan = std::to_string(inventory.GetPane());
                inventoryText.RenderText(textShader, pan, 740.0f, 486.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
                inventoryText.RenderText(textShader, "Carne ", 610.0f, 464.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
                std::string carn = std::to_string(inventory.GetCarne());
                inventoryText.RenderText(textShader, carn, 740.0f, 464.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
                inventoryText.RenderText(textShader, "Hamburger ", 610.0f, 442.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);
                std::string ham = std::to_string(inventory.GetHamburger());
                inventoryText.RenderText(textShader, ham, 740.0f, 442.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f), textEntity.VAO, textEntity.VBO);

                // Disable blending after text rendering
                glDisable(GL_BLEND);
            }


            // hitbox FOR DEBUG PURPOSES

            if (DEBUG) {
                // Bind the wireframe shader
                wireframeShader.use();

                glm::vec3 objectPosition = glm::vec3(4.38f, 0.0f, -0.05f);
                glm::vec3 objectSize = glm::vec3(1.0f, 1.1f, 3.85f);

                // Width, height, length

                // Set uniforms for the shader
                model = glm::mat4(1.0f);
                model = glm::translate(model, objectPosition); // Position of the hitbox
                model = glm::scale(model, objectSize);        // Size of the hitbox (matches the bounding box)

                wireframeShader.setMat4("model", model);
                wireframeShader.setMat4("view", view);
                wireframeShader.setMat4("projection", projection);
                wireframeShader.setVec3("color", glm::vec3(1.0f, 0.0f, 0.0f)); // Red color

                // Draw the edges of the bounding box
                glBindVertexArray(hitbox.VAO);
                glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
                glBindVertexArray(0);

            }

            checkHitboxSelections(camera, inventory, engine, timer, score);
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