/*******************************************************************************************
*
*   raylib [core] example - Initialize 3d camera free
*
*   This example has been created using raylib 1.3 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2015 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "MD2.h"
#include "rImgui.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1200;
    const int screenHeight = 850;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

   // SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    CMD2Model model;
    model.LoadModel("/media/djoker/code/linux/cpp/raylib/rayprojects/raymd2/models/blade/Blade.md2");
  animState_t animation =  model.StartAnimation(STAND);





    Gui_Ini();

     float color[4]={1,0,1,1};

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera);          // Update camera

        if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
        //----------------------------------------------------------------------------------

        static float frame=0.002f;
        static int currentFrame=1;
        static int  nextFrame=2;


        model.UpdateAnimation(&animation,frame);


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground({0,0,45,0});
           // ClearBackground(RAYWHITE);

            BeginMode3D(camera);

              //  DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
              //DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
              rlPushMatrix();
              rlTranslatef(0,0,0);
             // model.renderLerp(currentFrame,nextFrame,{color[0]*255.0f,color[1]*255.0f,color[2]*255.0f,255});
              rlPopMatrix();

             rlPushMatrix();
              rlTranslatef(0,0,0);
              //model.renderLerp(frame,{color[0]*255.0f,color[1]*255.0f,color[2]*255.0f,255});
              model.RenderModel(&animation);
              rlPopMatrix();

                DrawGrid(10, 1.0f);

            EndMode3D();





             Gui_Begin();

             ImGui::Text("Blade animation %d", frame);
    if (ImGui::Button("Run"))
    {
     animation =  model.StartAnimation(RUN);
    }
    if (ImGui::Button("Idle"))
    {
     animation =  model.StartAnimation(STAND);
    }




//ImGui::SliderInt("frame", &frame, 0, 197);
ImGui::SliderFloat("frame", &frame, 0.001f, 1.0f);
ImGui::ColorEdit4("Model Color",color);
ImGui::SliderInt("frame", &currentFrame, 0, 196);
ImGui::SliderInt("nex", &nextFrame, 0, 196);
 ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

             Gui_End();

            DrawRectangle( 10, 10, 320, 133, Fade(SKYBLUE, 0.5f));
            DrawRectangleLines( 10, 10, 320, 133, BLUE);

            DrawText("Free camera default controls:", 20, 20, 10, BLACK);
            DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
            DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
            DrawText("- Alt + Mouse Wheel Pressed to Rotate", 40, 80, 10, DARKGRAY);
            DrawText("- Alt + Ctrl + Mouse Wheel Pressed for Smooth Zoom", 40, 100, 10, DARKGRAY);
            DrawText("- Z to zoom to (0, 0, 0)", 40, 120, 10, DARKGRAY);

            DrawText(FormatText("Frame %d ",animation.curr_frame), screenWidth-200, 100, 10, RED);
            DrawText(FormatText("Next %d ",animation.next_frame), screenWidth-200, 110, 10, RED);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    model.free();
    Gui_Free();
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
