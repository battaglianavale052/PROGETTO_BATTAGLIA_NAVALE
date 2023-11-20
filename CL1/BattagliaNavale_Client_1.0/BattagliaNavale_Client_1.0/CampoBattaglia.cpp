#include "CampoBattaglia.h"

bool CampoBattaglia::cellaCliccata[CampoBattaglia::GRID_ROWS][CampoBattaglia::GRID_COLS] = { false };

void CampoBattaglia::disegnaGriglia(SDL_Renderer* gRenderer, SDL_Texture* mareTexture) {
    for (int row = 0; row < GRID_ROWS; row++) {
        for (int col = 0; col < GRID_COLS; col++) {
            SDL_Rect cellRect = {
                col * CELL_SIZE + GRID_OFFSET_X,
                row * CELL_SIZE + GRID_OFFSET_Y,
                CELL_SIZE,
                CELL_SIZE
            };

            // Se la cella è stata cliccata, la disegna in rosso
            if (cellaCliccata[row][col]) {
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255); // Rosso
                SDL_RenderFillRect(gRenderer, &cellRect);
            }
            else {
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255); // Nero
                SDL_RenderCopy(gRenderer, mareTexture, NULL, &cellRect);
                SDL_RenderDrawRect(gRenderer, &cellRect);
            }
        }
    }
}
//-----------------------------------------------------------------------------------------
void CampoBattaglia::disegnaGrigliaVerde(SDL_Renderer* gRenderer, int row, int col, int red, int green, int blue)
{
    // Calcola il rettangolo per la cella
    SDL_Rect cellRect = {
        col * CELL_SIZE + GRID_OFFSET_X,
        row * CELL_SIZE + GRID_OFFSET_Y,
        CELL_SIZE,
        CELL_SIZE
    };

    //per fare in modo che non venga didisegnata di blu dopo
    cellaCliccata[row][col] = true;
    if (cellaCliccata[row][col]) {
        SDL_SetRenderDrawColor(gRenderer, red, green, blue, 255); // Rosso
        SDL_RenderFillRect(gRenderer, &cellRect);
    }
}

bool CampoBattaglia::gestisciInput(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.button == SDL_BUTTON_LEFT) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            // Verifica quale cella è stata cliccata
            int col = (mouseX - GRID_OFFSET_X) / CELL_SIZE;
            int row = (mouseY - GRID_OFFSET_Y) / CELL_SIZE;

            // Verifica che la cella sia all'interno della griglia
            if (col >= 0 && col < GRID_COLS && row >= 0 && row < GRID_ROWS) {
                // Cella cliccata, cambia lo stato
                cellaCliccata[row][col] = true;
                return true;
            }
        }
    }
    return false;
}

std::string  CampoBattaglia::ottieniCellaCliccata(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Calcola la riga e la colonna della cella cliccata
        int col = (mouseX - CampoBattaglia::GRID_OFFSET_X) / CampoBattaglia::CELL_SIZE;
        int row = (mouseY - CampoBattaglia::GRID_OFFSET_Y) / CampoBattaglia::CELL_SIZE;

        // Verifica che la cella sia all'interno della griglia
        if (col >= 0 && col < CampoBattaglia::GRID_COLS && row >= 0 && row < CampoBattaglia::GRID_ROWS) {
            // Restituisci la posizione della cella come stringa "riga;colonna"
            return std::to_string(row) + ";" + std::to_string(col);
        }
    }

    // Se non è stata cliccata alcuna cella, restituisci una stringa vuota
    return "";
}
