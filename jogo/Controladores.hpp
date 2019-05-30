#ifndef CONTROLADORES
#define CONTROLADORES
#include"Definidores.hpp"
class TrataJogo{
public:
	CarregaSDL SDL;
	GerenciaMoveis Gerente;
	MUSICA musica;
	bool gameLoop() {
		bool quit = false;
		while (!quit) {
			SDL_RenderClear(SDL.GetRender());
			SDL_SetRenderDrawColor(SDL.GetRender(), 100, 100, 100, 0);
			Gerente.TrataEventosDeSaidaEEntrada(&quit,SDL.GetRender());
			Gerente.GerenteObjetos.TrataObjeto();
			Gerente.GerenteObjetos.TrataPosicao();
			Gerente.Renderiza(SDL.GetRender());
			SDL_RenderPresent(SDL.GetRender());
		}
	}
};
class GerenciaTudo {
private:
	TrataJogo jogo;
public:
	GerenciaTudo(){
		if (!jogo.SDL.init()) {
			printf("Failed to initialize!\n");
		} else {
			//Load media
			if (!jogo.Gerente.GerenteTexturas.loadMedia(jogo.SDL.GetRender())) {
				printf("Failed to load media!\n");
			} else {
				if(!jogo.musica.loadMediaAudio()){
					printf("Falhou em carregar a musica\n");
				}else{
					jogo.Gerente.GerenteObjetos.Inicializa();
					jogo.gameLoop();
				}
			}
		}
	}
};
#endif
