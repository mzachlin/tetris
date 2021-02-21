#include <iostream>

#include <SDL2/SDL.h>          // Graphics libraries
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h> 

/* Functions */
void drawShape(SDL_Renderer* rend, SDL_Rect rect) {
    // Clear the screen 
    SDL_RenderClear(rend); 
    // Draw the rectangle
    SDL_SetRenderDrawColor(rend, 33, 163, 125, 170);
    // Draw the outline of the rectangle
    SDL_RenderDrawRect(rend, &rect);        
    // Fill the rectangle with a color               
    SDL_RenderFillRect(rend, &rect);                       
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderPresent(rend);
    
}

/* Main Execution */
int main() { 
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { 
        printf("error initializing SDL: %s\n", SDL_GetError()); 
    } 
    // Create game window
    int win_w = 900;
    int win_h = 700;
    SDL_Window* win = SDL_CreateWindow("TETRIS", 
                                       SDL_WINDOWPOS_CENTERED, 
                                       SDL_WINDOWPOS_CENTERED, 
                                       win_w, win_h, 0); 
    // Error check the window appearing
    if (!win) {  
        std::cout << "Failed to create window.\n";
        return -1;
    }
  
    // Trigger the program that controls graphics hardware and set flags 
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;    
  
    // Create a renderer to render our images 
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags); 
  
    // Create rectangle 
    SDL_Rect rect;       
    rect.w = 150; 
    rect.h = 150; 
    // Set initial x and y position
    rect.x = 250; 
    rect.y = 150; 
  
    
    int close = 0;    // Controls animation loop 
    int speed = 500;  // Animation speed

    // Draw initial rectangle
    drawShape(rend, rect);

    // Animation loop 
    while (!close) { 
        SDL_Event event; 
  
        // Events mangement 
        while (SDL_PollEvent(&event)) { 
            switch (event.type) { 
  
                case SDL_QUIT: 
                    // Handling of close button 
                    close = 1; 
                    break; 
  
                case SDL_KEYDOWN: 
                    // Keyboard API for key pressed 
                    switch (event.key.keysym.scancode) { 
                        case SDL_SCANCODE_W: 
                        case SDL_SCANCODE_UP: 
                            rect.y -= speed / 30; 
                            drawShape(rend, rect);
                            break; 
                        case SDL_SCANCODE_A: 
                        case SDL_SCANCODE_LEFT: 
                            rect.x -= speed / 30; 
                            drawShape(rend, rect);
                            break; 
                        case SDL_SCANCODE_S: 
                        case SDL_SCANCODE_DOWN: 
                            rect.y += speed / 30; 
                            drawShape(rend, rect);
                            break; 
                        case SDL_SCANCODE_D: 
                        case SDL_SCANCODE_RIGHT: 
                            rect.x += speed / 30; 
                            drawShape(rend, rect);
                            break; 
                    } 
            } 
        } 

        // Enforce right boundary 
        if (rect.x + rect.w > win_w) 
            rect.x = win_w - rect.w; 
  
        // Enforce left boundary 
        if (rect.x < 0) 
            rect.x = 0; 
  
        // Enforce bottom boundary 
        if (rect.y + rect.h > win_h) 
            rect.y = win_h - rect.h; 
  
        // Enforce upper boundary 
        if (rect.y < 0) 
            rect.y = 0; 
  
        // Calculate to 60 fps  
        SDL_Delay(1000 / 60);    // I'm not sure what the delay is for?
    } 

    // Destroy renderer 
    SDL_DestroyRenderer(rend); 
  
    // Destroy window 
    SDL_DestroyWindow(win); 

    return 0; 
} 

















