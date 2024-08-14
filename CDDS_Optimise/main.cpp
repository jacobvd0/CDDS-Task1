/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include <random>
#include <time.h>
#include "Critter.h"
#include "HashTable.h"
#include "DynamicArray.h"

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "CDDS - Task 1");

    //SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    srand(time(NULL));


    DynamicArray critters; 

    // create some critters
    const int CRITTER_COUNT = 50;
    const int MAX_VELOCITY = 80;

    // Load the critter and destoyer textures
    Texture2D crit = LoadTexture("res/10.png");
    Texture2D dest = LoadTexture("res/9.png");


    // Add the textures to the hash table
    HashTable textureTable;
    textureTable["critter"] = &crit;
    textureTable["destroyer"] = &dest;



    for (int i = 0; i < CRITTER_COUNT; i++)
    {
        // create a random direction vector for the velocity
        Vector2 velocity = { -100+(rand()%200), -100+(rand()%200) };
        // normalize and scale by a random speed
        velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);

        // create a critter in a random location
        critters.Init(12, "critter", &textureTable);
    }


    Critter destroyer;
    Vector2 velocity = { -100 + (rand() % 200), -100 + (rand() % 200) };
    velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);
    destroyer.Init(Vector2{ (float)(screenWidth >> 1), (float)(screenHeight >> 1) }, velocity, 20, "destroyer", &textureTable);

    float timer = 1;
    Vector2 nextSpawnPos = destroyer.GetPosition();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        float delta = GetFrameTime();

        // update the destroyer
        destroyer.Update(delta);
        // check each critter against screen bounds
        if (destroyer.GetX() < 0) {
            destroyer.SetX(0);
            destroyer.SetVelocity(Vector2{ -destroyer.GetVelocity().x, destroyer.GetVelocity().y });
        }
        if (destroyer.GetX() > screenWidth) {
            destroyer.SetX(screenWidth);
            destroyer.SetVelocity(Vector2{ -destroyer.GetVelocity().x, destroyer.GetVelocity().y });
        }
        if (destroyer.GetY() < 0) {
            destroyer.SetY(0);
            destroyer.SetVelocity(Vector2{ destroyer.GetVelocity().x, -destroyer.GetVelocity().y });
        }
        if (destroyer.GetY() > screenHeight) {
            destroyer.SetY(screenHeight);
            destroyer.SetVelocity(Vector2{ destroyer.GetVelocity().x, -destroyer.GetVelocity().y });
        }

        // update the critters
        // (dirty flags will be cleared during update)
        for (int i = 0; i < critters.GetCritCount(); i++)
        {
            critters[i]->Update(delta);

            // check each critter against screen bounds
            if (critters[i]->GetX() < 0) {
                critters[i]->SetX(0);
                critters[i]->SetVelocity(Vector2{ -critters[i]->GetVelocity().x, critters[i]->GetVelocity().y });
            }
            if (critters[i]->GetX() > screenWidth) {
                critters[i]->SetX(screenWidth);
                critters[i]->SetVelocity(Vector2{ -critters[i]->GetVelocity().x, critters[i]->GetVelocity().y });
            }
            if (critters[i]->GetY() < 0) {
                critters[i]->SetY(0);
                critters[i]->SetVelocity(Vector2{ critters[i]->GetVelocity().x, -critters[i]->GetVelocity().y });
            }
            if (critters[i]->GetY() > screenHeight) {
                critters[i]->SetY(screenHeight);
                critters[i]->SetVelocity(Vector2{ critters[i]->GetVelocity().x, -critters[i]->GetVelocity().y });
            }

            // kill any critter touching the destroyer
            // simple circle-to-circle collision check
            float dist = Vector2Distance(critters[i]->GetPosition(), destroyer.GetPosition());
            
            if (dist < critters[i]->GetRadius() + destroyer.GetRadius())
            {
                critters.Destroy(i);
                // this would be the perfect time to put the critter into an object pool
            }
        }
                
        // check for critter-on-critter collisions
        for (int i = 0; i < CRITTER_COUNT; i++)
        {            
            for (int j = 0; j < CRITTER_COUNT; j++){
                if (i == j || critters[i]->IsDirty()) // note: the other critter (j) could be dirty - that's OK
                    continue;
                // check every critter against every other critter
                float dist = Vector2Distance(critters[i]->GetPosition(), critters[j]->GetPosition());
                if (dist < critters[i]->GetRadius() + critters[j]->GetRadius())
                {
                    // collision!
                    // do math to get critters bouncing
                    Vector2 normal = Vector2Normalize( Vector2Subtract(critters[j]->GetPosition(), critters[i]->GetPosition()));

                    // not even close to real physics, but fine for our needs
                    critters[i]->SetVelocity(Vector2Scale(normal, -MAX_VELOCITY));
                    // set the critter to *dirty* so we know not to process any more collisions on it
                    critters[i]->SetDirty();

                    // we still want to check for collisions in the case where 1 critter is dirty - so we need a check 
                    // to make sure the other critter is clean before we do the collision response
                    if (!critters[j]->IsDirty()) {
                        critters[j]->SetVelocity(Vector2Scale(normal, MAX_VELOCITY));
                        critters[j]->SetDirty();
                    }
                    break;
                }
            }
        }

        timer -= delta;
        if (timer <= 0)
        {
            timer = 1;

             //find any dead critters and spit them out (respawn)
            for (int i = 0; i < CRITTER_COUNT; i++)
            {
                if (critters.CritterExists(i) == false)
                {
                    Vector2 normal = Vector2Normalize(destroyer.GetVelocity());

                    // get a position behind the destroyer, and far enough away that the critter won't bump into it again
                    Vector2 pos = destroyer.GetPosition();
                    pos = Vector2Add(pos, Vector2Scale(normal, -50));
                    // its pretty ineficient to keep reloading textures. ...if only there was something else we could do
                    critters.Init(12, "critter", &textureTable);
                    break;
                }
            }
            nextSpawnPos = destroyer.GetPosition();
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // draw the critters
        for (int i = 0; i < critters.GetCritCount(); i++)
        {
            if (critters.CritterExists(i) == true) {
                critters.Draw(i);
            }
            
        }
        // draw the destroyer
        destroyer.Draw();

        DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    for (int i = 0; i < CRITTER_COUNT; i++)
    {
        critters.Destroy(i);
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}