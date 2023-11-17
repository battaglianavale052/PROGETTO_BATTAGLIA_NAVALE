#include "NaviVettore.h"

void NaviVettore::riempiVettoreTestoNave(std::vector<std::string>& vet)
{
    vet.push_back("INSERIRE UNA PORTAEREI"); //7
    vet.push_back("INSERIRE UNA CORAZZATA"); //4
    vet.push_back("INSERIRE UNA SOTTOMARINO"); //3
    vet.push_back("INSERIRE UNA CORVETTA"); //2
    vet.push_back("INSERIRE UNA LANCIA"); //1
    vet.push_back("INSERIRE UNA LANCIA"); //1
}
void NaviVettore::riempiVettoreNaviTemporanee(std::vector<Nave> navi)
{
    for (int i = 0; i < 6; i++) {
        Nave n(0, 0);
        navi.push_back(n);  // Aggiungi un elemento a navi
    }
}

void NaviVettore::visualizzaVettore(std::vector<Nave>& navi, SDL_Renderer* gRenderer) {
    for (int i = 0; i < navi.size(); i++) {
        navi[i].render(gRenderer);
    }
    SDL_RenderPresent(gRenderer);
}