#ifndef BASE
#define BASE
#include"Definidores.hpp"
class CarregaSDL{
public:
	SDL_Window* gWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	bool init() {
		//Initialization flag
		bool success = true;
		//Initialize SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
			success = false;
		} else {
			//Set texture filtering to linear
			if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
				printf("Warning: Linear texture filtering not enabled!");
			}
			//Create window
			gWindow = SDL_CreateWindow("TP2DGame - WAYPOINTS.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Largura_tela, Altura_tela, SDL_WINDOW_SHOWN);
			if (gWindow == NULL) {
				printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			} else {
				//Create vsynced renderer for window
				gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
				if (gRenderer == NULL) {
					printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
					success = false;
				} else {
					//Initialize renderer color
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
					//Initialize PNG loading
					int imgFlags = IMG_INIT_PNG;
					if (!(IMG_Init(imgFlags) & imgFlags)) {
						printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
						success = false;
					}
				}
			}
		}
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			return false;
		}
		if(TTF_Init()<0){
			printf("SDL_ttf could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			return false;
		}
		return success;
	}
	SDL_Renderer* GetRender() {
		return gRenderer;
	}
	~CarregaSDL(){
		SDL_DestroyRenderer(gRenderer);
		SDL_DestroyWindow(gWindow);
		gWindow = NULL;
		gRenderer = NULL;
		//Quit SDL subsystems
		IMG_Quit();
		SDL_Quit();
	}
};
class StrTextura {
	//Image
	SDL_Texture* textura;
	//Dimensions and position
public:
	bool loadTExtureFromFile(char * path, SDL_Renderer* gRenderer1) {
		//The final texture
		SDL_Texture* newTexture = NULL;
		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path);
		if (loadedSurface == NULL) {
			printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
		} else {
			//Color key image
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
			//Create texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface(gRenderer1, loadedSurface);
			if (newTexture == NULL) {
				printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
			}
			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}
		//Return success
		SetTextura(newTexture);
		return (GetTextura() != NULL);
	}
	SDL_Texture* GetTextura() {
		return textura;
	}
	void SetTextura(SDL_Texture* textura) {
		this->textura = textura;
	}
	~StrTextura(){
		SDL_DestroyTexture(textura);
	}
	//Dimensions and position
};
class StrPosition {
	int velX;
	int velY;
	SDL_Rect posicao;
public:
	int GetPosicaoX() {
		return posicao.x;
	}
	int GetPosicaoY() {
		return posicao.y;
	}
	int GetPosicaoW() {
		return posicao.w;
	}
	int GetPosicaoH() {
		return posicao.h;
	}
	SDL_Rect& GetPosicaoEndereco() {
		return posicao;
	}
	SDL_Rect GetPosicao() {
		return posicao;
	}
	void SetPosicao(SDL_Rect posicao) {
		this->posicao = posicao;
	}
	void SetPosicaoX(int x) {
		this->posicao.x = x;
	}
	void SetPosicaoY(int y) {
		this->posicao.y = y;
	}
	void SetPosicaoW(int w) {
		this->posicao.w = w;
	}
	void SetPosicaoH(int h) {
		this->posicao.h = h;
	}
	int GetVelX() {
		return velX;
	}
	void SetVelX(int velX) {
		this->velX = velX;
	}
	int GetVelY() {
		return velY;
	}
	void SetVelY(int velY) {
		this->velY = velY;
	}
};
class GameObject{
	int NumeroObjetos;
public:
	GameObject(){
		static int objetos=0;
		objetos++;
		NumeroObjetos=objetos;
	}
	int GetNumeroObjetos(){
		return NumeroObjetos;
	}
	StrPosition posicao;
	void TrataPosicao(){}
	void TrataObjeto(){}
	void Inicializa(){}
};
class TexturaControll{
public:
	StrTextura textura;
	bool loadMedia(char *path,SDL_Renderer* gRenderer1){
		if (!textura.loadTExtureFromFile(path, gRenderer1)) {
			printf("Failed to load arrow texture!\n");
			return false;
		}
		return true;
	}
};
class Texto {
private:
	char Pontuacao[100];
	char NVidas[100];
	SDL_Color fontColor;
	SDL_Color fontColor2;
	SDL_Surface *textSurface;
	SDL_Surface *textSurface2;
	SDL_Texture *texto;
	SDL_Texture *texto2;
public:
	int ponto;
	Texto(){
		ponto=0;
	}
	void SetPontos(int pontos){
		this->ponto = pontos;
	}
	bool MostraScore(SDL_Renderer *gRenderer1, int contagem) {
		TTF_Font *fonte = TTF_OpenFont("arial.ttf", 20);
		sprintf(Pontuacao,"%d",contagem);
		char txt[25];
		strcpy(txt, "Pontos: ");
		strcat(txt, Pontuacao);
		fontColor = {255,255,255,255};
		textSurface = TTF_RenderText_Blended(fonte, txt, fontColor);
		texto = SDL_CreateTextureFromSurface(gRenderer1, textSurface);
		SDL_Rect textoRect;
		textoRect.x = 0;
		textoRect.y = 0;
		textoRect.w = 100;
		textoRect.h = 100;
		SDL_QueryTexture(texto, NULL, NULL, &textoRect.w, &textoRect.h);
		SDL_RenderCopy(gRenderer1, texto, NULL, &textoRect);
		return true;
	};
	bool MostraVidas(SDL_Renderer *gRenderer1, int vida){
		TTF_Font *fonte2 = TTF_OpenFont("arial.ttf", 20);
		sprintf(NVidas,"%d",vida);
		char txt2[25];
		strcpy(txt2, "Vidas: ");
		strcat(txt2, NVidas);
		fontColor2 = {255,255,255,255};
		textSurface2 = TTF_RenderText_Blended(fonte2, txt2, fontColor2);
		texto2 = SDL_CreateTextureFromSurface(gRenderer1, textSurface2);
		SDL_Rect textoRect2;
		textoRect2.x = 0;
		textoRect2.y = 20;
		textoRect2.w = 100;
		textoRect2.h = 100;
		SDL_QueryTexture(texto2, NULL, NULL, &textoRect2.w, &textoRect2.h);
		SDL_RenderCopy(gRenderer1, texto2, NULL, &textoRect2);
		return true;
	}
	~Texto(){
		free(textSurface);
		free(textSurface2);
		free(texto);
		free(texto2);
	}
};

class MUSICA{
public:
	Mix_Chunk *Musica = NULL;
	bool loadMediaAudio(){
		return true;
	}
	~MUSICA(){
		Mix_FreeChunk( Musica );   
	}    
};
#endif
