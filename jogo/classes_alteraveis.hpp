#ifndef CLASSES_ALTERAVEIS
#define CLASSES_ALTERAVEIS
#include "Definidores.hpp"
//OBJETOS E TEXTURASS
//-----------------///-------------------
//---------------OBJETOS----------------
class BotaoMenuPrincipal: public GameObject{
public:
	void Inicializa(int x,int y, int w, int h){
		posicao.SetPosicaoX(x);
		posicao.SetPosicaoY(y);
		posicao.SetPosicaoW(w);	
		posicao.SetPosicaoH(h);	
	}
	void TrataPosicao(){}
	void TrataObjeto(){}
};
class FundoMenuPrincipal: public GameObject{
public:
	void Inicializa(int x,int y, int w, int h){
		posicao.SetPosicaoX(x);
		posicao.SetPosicaoY(y);
		posicao.SetPosicaoW(w);	
		posicao.SetPosicaoH(h);	
	}
	void TrataPosicao(){}
	void TrataObjeto(){}
};

class TelaMorte: public GameObject{
public:
	bool estado;
	void Inicializa(int x,int y, int w, int h){
		estado=0;
		posicao.SetPosicaoX(x);
		posicao.SetPosicaoY(y);
		posicao.SetPosicaoW(w);	
		posicao.SetPosicaoH(h);	
	}
	void TrataPosicao(){}
	void TrataObjeto(){}
};
class FundoTelaFimDjogo: public GameObject{
public:
	int estado;
	void Inicializa(int x,int y, int w, int h){
		estado=-1;
		posicao.SetPosicaoX(x);
		posicao.SetPosicaoY(y);
		posicao.SetPosicaoW(w);	
		posicao.SetPosicaoH(h);	
	}
	void TrataPosicao(){}
	void TrataObjeto(){}
};
class MenuPrincipal{
	bool estado;
public:
	bool tutorial;
	BotaoMenuPrincipal Botao[4];
	FundoMenuPrincipal Fundo;
	FundoMenuPrincipal FundoTutorial;
	MenuPrincipal(){
		estado=true;
		tutorial=false;
	}
	void TrataEventos(SDL_Event e){
		if(e.key.state==SDLK_SPACE){
			estado=true;
		}
	}
	int GetEstado(){
		return estado;
	}
	void SetEstado(int i){
		estado=i;
	}
	void TrataPosicao(){}
	bool TrataObjeto(SDL_Event e, int *CoeficienteMapa, bool *quit){
		if(estado==true){
			if (e.button.button == SDL_BUTTON_LEFT) {
				for(int i=0;i<4;i++){
					int xj=e.button.x;
					int yj=e.button.y;
					int xb=Botao[i].posicao.GetPosicaoX();
					int yb=Botao[i].posicao.GetPosicaoY();
					int wb=Botao[i].posicao.GetPosicaoW();
					int hb=Botao[i].posicao.GetPosicaoH();
					if(xj<=(xb+wb)&&xj>=xb&&yj>=yb&&yj<=(yb+hb)){
						if(i==3){*quit=true;}else{if(i!=2){*CoeficienteMapa=i;estado=false;return true;}else{tutorial=true;}}
					}
				}
			}
		}
		return false;
	}
};
class BlocoMapa:public GameObject{
	bool ponto;
public:
	
	bool GetPonto() {
		return ponto;
	}
	void SetPonto(int p) {
		ponto = p;
	}
	void Inicializa(int x, int y, int w, int h, bool nponto){
		posicao.SetPosicaoX(x*w);
		posicao.SetPosicaoY(y*h);
		posicao.SetPosicaoW(w);
		posicao.SetPosicaoH(h);
		ponto=nponto;
	}
};
class PlayerObjeto:public GameObject{
	int direcao;

public:
	int vidas;
	PlayerObjeto(){
		direcao=0;
	}
	int GetDirecao() {
		return direcao;
	}
	void SetDirecao(int d) {
		direcao = d;
	}
	void Inicializa(int x, int y, int w, int h){
		posicao.SetPosicaoX(x);
		posicao.SetPosicaoY(y);
		posicao.SetPosicaoW(w);
		posicao.SetPosicaoH(h);
		posicao.SetVelX(0);
		posicao.SetVelY(0);
	}
	void TrataEventos(SDL_Event e){
		//Handle events on queue                
			//User requests quit
		if (!(e.key.state == SDL_PRESSED||e.type==SDL_KEYDOWN)){
			switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				posicao.SetVelX(0);
				break;
			case SDLK_RIGHT:
				posicao.SetVelX(0);
				break;  
			case SDLK_UP:
				posicao.SetVelY(0);
				break;
			case SDLK_DOWN:
				posicao.SetVelY(0);
				break;
			case SDLK_SPACE:
				posicao.SetVelY (0);
				posicao.SetVelX(0);
			}
		}else{
			if (e.key.state == SDL_PRESSED) {
				switch (e.key.keysym.sym) {
				case SDLK_LEFT:
					posicao.SetVelY(0);
					posicao.SetVelX(-1);
					direcao=3;
					break;
				case SDLK_RIGHT:
					posicao.SetVelY(0);
					posicao.SetVelX(1);
					direcao=1;
					break;  
				case SDLK_UP:
					posicao.SetVelX(0);
					posicao.SetVelY(-1);
					direcao=0;
					break;
				case SDLK_DOWN:
					posicao.SetVelX(0);
					posicao.SetVelY(1);
					direcao=2;
					break;
				case SDLK_SPACE:
					posicao.SetVelY (0);
					posicao.SetVelX(0);
					break;
				default:
					break;
				}
			}
		}
	}
	void TrataPosicao(int ok){
		
		posicao.SetPosicaoX(posicao.GetPosicaoX()+posicao.GetVelX()*ok);
		posicao.SetPosicaoY(posicao.GetPosicaoY()+posicao.GetVelY()*ok);
	}
};
class InimigoPosicao:public GameObject{
	int direcao;
	int layerX;
	int layerY;
public:
	InimigoPosicao(){
		direcao=0;
	}
	int GetDirecao() {
		return direcao;
	}
	void SetDirecao(int d) {
		direcao = d;
	}
	int GetLayerX() {
		return layerX;
	}
	void SetLayerX(int d) {
		layerX = d;
	}
	int GetLayerY() {
		return layerY;
	}
	void SetLayerY(int d) {
		layerY = d;
	}
	void Inicializa(int x, int y, int w, int h, int lX, int lY){
		posicao.SetPosicaoX(x);
		posicao.SetPosicaoY(y);
		posicao.SetPosicaoW(w);
		posicao.SetPosicaoH(h);
		posicao.SetVelX(0);
		posicao.SetVelY(0);
		layerX=lX;
		layerY=lY;
	}
};
class GerenteInimigo{
public:
	int GrauGiro;
	GerenteInimigo(){GrauGiro=0;}
	MatrizWaypoint WayPoints;
	InimigoPosicao *inimigo;// Alocação dinamica.
	~GerenteInimigo(){
		free(inimigo);
	}
};
class MAPA{
	int TamanhoMatrizY;
	int TamanhoMatrizX;
	bool **matriz;
public:
	BlocoMapa **MapaPosition;
	inicializa(char *path){
		int n,i,j, x=0,y=0, h=0,k=0;
		FILE *arq;
		if((arq=fopen(path,"r"))==NULL){
			printf("Nao foi possivel abrir o arquivo do mapa\n");
			exit(0);
		}
		while(!feof(arq)){
			fscanf(arq,"%d",&n);
			if(n==-10){
				y++;
				if(h==0){
					x=k;
					h++;
					k=0;
				}
			}else{
				k++;
			}
		}
		rewind(arq);
		TamanhoMatrizY=y;
		TamanhoMatrizX=x;
		matriz = (bool**)malloc(TamanhoMatrizY * sizeof(bool*)); 
		for ( i = 0; i < TamanhoMatrizY; i++){ 
			matriz[i] = (bool*) malloc(TamanhoMatrizX * sizeof(bool)); 
			for ( j = 0; j < TamanhoMatrizX; j++){ 
				fscanf(arq,"%d",&n);
				if(n==-10){
					fscanf(arq,"%d",&n);
				}
				matriz[i][j] = n; 
			}
		}
		MapaPosition = (BlocoMapa**) malloc(TamanhoMatrizY * sizeof(BlocoMapa*));
		for ( i = 0; i < TamanhoMatrizY; i++){ 
			MapaPosition[i] = (BlocoMapa*) malloc(TamanhoMatrizX * sizeof(BlocoMapa));
		}
		fclose(arq);
	}
	~MAPA(){
		free(matriz);
		free(MapaPosition);
	}
	int GetTamanhoY(){
		return TamanhoMatrizY;
	}
	int GetTamanhoX(){
		return TamanhoMatrizX;
	}
	int SetMatriz(int i, int j, int n){
		matriz[i][j]=n;
	}
	int GetMatriz(int i, int j){
		return matriz[i][j];
	}
};
class Objetos{
public:
	MAPA mapa[2];
	GerenteInimigo Inimigos[2];
	MenuPrincipal MenuPosicao;
	FundoTelaFimDjogo FimDeJogo;
	TelaMorte morte;
	PlayerObjeto jogador;
	Texto texto;
};


//-------------TEXTURAS-------------
class InimigoTextura:public TexturaControll{
public:
	bool loadMedia(char *path,SDL_Renderer* gRenderer1){
		if (!textura.loadTExtureFromFile(path, gRenderer1)) {
			printf("Nao foi possivel carregar textura do Inimigo!\n");
			return false;
		}
		return true;
	}
};
class TexturaBotao:public TexturaControll{
public:
	bool loadMedia(char *path,SDL_Renderer* gRenderer1){
		if (!textura.loadTExtureFromFile(path, gRenderer1)) {
			printf("Nao foi possivel carregar textura do Botao!\n");
			return false;
		}
		return true;
	}
};
class TexturaFundo:public TexturaControll{
public:
	bool loadMedia(char *path,SDL_Renderer* gRenderer1){
		if (!textura.loadTExtureFromFile(path, gRenderer1)) {
			printf("Nao foi possivel carregar textura do Fundo!\n");
			return false;
		}
		return true;
	}
};
class TexturaMenu{
public:
	TexturaBotao Botao[4];
	TexturaFundo Fundo;
	TexturaFundo FundoTutorial;
};
class MapaTextura:public TexturaControll{
public:
	bool loadMedia(char *path,SDL_Renderer* gRenderer1){
		if (!textura.loadTExtureFromFile(path, gRenderer1)) {
			printf("Nao foi possivel carregar textura do Mapa!\n");
			return false;
		}
		return true;
	}
};
class TelaFimDJogo:public TexturaControll{
public:
	bool loadMedia(char *path,SDL_Renderer* gRenderer1){
		if (!textura.loadTExtureFromFile(path, gRenderer1)) {
			printf("Nao foi possivel carregar textura de fim de jogo!\n");
			return false;
		}
		return true;
	}
};
class TelaDMorte:public TexturaControll{
public:
	bool loadMedia(char *path,SDL_Renderer* gRenderer1){
		if (!textura.loadTExtureFromFile(path, gRenderer1)) {
			printf("Nao foi possivel carregar textura de fim de morte!\n");
			return false;
		}
		return true;
	}
};
class PlayerTextura:public TexturaControll{
public:
	bool loadMedia(char *path,SDL_Renderer* gRenderer1){
		if (!textura.loadTExtureFromFile(path, gRenderer1)) {
			printf("Nao foi possivel carregar textura do player!\n");
			return false;
		}
		return true;
	}
};
class Texturas{
public:
	TexturaMenu MenuFoto;
	MapaTextura mapaTextura[3];
	PlayerTextura playertexture;
	InimigoTextura inimigotextura;
	TelaFimDJogo Telas[2];
	TelaDMorte morte;
};
//-----------------///-------------------

//--------------GERENCIADORES-------------
//-----------------///-------------------

class GerenciaObjetos{
	
public:
	Objetos objetos;
	int NumeroMapa;
	GerenciaObjetos(){
		NumeroMapa=0;
	};
	void ColisaoJogadorInimigo(){
		int xj=objetos.jogador.posicao.GetPosicaoX();
		int wj=objetos.jogador.posicao.GetPosicaoW();
		int yj=objetos.jogador.posicao.GetPosicaoY();
		int hj=objetos.jogador.posicao.GetPosicaoH();
		int xb;
		int wb;
		int yb;
		int hb;
		for(int i=0;i<objetos.Inimigos[NumeroMapa].WayPoints.GetNumeroInimigos();i++){
			xb=objetos.Inimigos[NumeroMapa].inimigo[i].posicao.GetPosicaoX();
			wb=objetos.Inimigos[NumeroMapa].inimigo[i].posicao.GetPosicaoW();
			yb=objetos.Inimigos[NumeroMapa].inimigo[i].posicao.GetPosicaoY();
			hb=objetos.Inimigos[NumeroMapa].inimigo[i].posicao.GetPosicaoH();
			if((xb+wb)>=xj&&xb<=(xj+wj)&&(yb)<=(yj+hj)&&(yb+hb)>=(yj)){
				objetos.Inimigos[0].WayPoints.Inicializa((char*)"Inf/waypoints.txt");
				objetos.Inimigos[1].WayPoints.Inicializa((char*)"Inf/waypoints2.txt");
				int w=objetos.mapa[NumeroMapa].MapaPosition[0][0].posicao.GetPosicaoW()/2-TamanhoJogadorX/2;
				int h=objetos.mapa[NumeroMapa].MapaPosition[0][0].posicao.GetPosicaoH()/2-TamanhoJogadorY/2;
				objetos.jogador.Inicializa(objetos.mapa[NumeroMapa].MapaPosition[1][4].posicao.GetPosicaoX()+w,objetos.mapa[NumeroMapa].MapaPosition[1][4].posicao.GetPosicaoY()+h,TamanhoJogadorX,TamanhoJogadorY);
				w=objetos.mapa[NumeroMapa].MapaPosition[0][0].posicao.GetPosicaoW()/2-TamanhoInimigoX/2;
				h=objetos.mapa[NumeroMapa].MapaPosition[0][0].posicao.GetPosicaoH()/2-TamanhoInimigoY/2;
				int o;
				for(int g=0;g<2;g++){
					o=objetos.Inimigos[g].WayPoints.GetNumeroInimigos();
					objetos.Inimigos[g].inimigo=(InimigoPosicao*)malloc(o*sizeof(InimigoPosicao));
					for(int i=0;i<objetos.Inimigos[g].WayPoints.GetNumeroInimigos();i++){
						objetos.Inimigos[g].inimigo[i].Inicializa(objetos.mapa[0].MapaPosition[objetos.Inimigos[g].WayPoints.Inicializador[i].GetX()][objetos.Inimigos[g].WayPoints.Inicializador[i].GetY()].posicao.GetPosicaoX()+w,objetos.mapa[0].MapaPosition[objetos.Inimigos[g].WayPoints.Inicializador[i].GetX()][objetos.Inimigos[g].WayPoints.Inicializador[i].GetY()].posicao.GetPosicaoY()+h,TamanhoInimigoX,TamanhoInimigoY, objetos.Inimigos[g].WayPoints.Inicializador[i].GetX(), objetos.Inimigos[g].WayPoints.Inicializador[i].GetY());
					}
					
				}
				objetos.jogador.vidas--;
				objetos.morte.estado=true;
				if(objetos.jogador.vidas==0){
					objetos.FimDeJogo.estado=0;
				}
			}
		}
	}
	void WaypointControll(int x,int y, int *way, int Tamanho,int p){
		int xb=objetos.Inimigos[NumeroMapa].inimigo[p].posicao.GetPosicaoX();
		int wb=objetos.Inimigos[NumeroMapa].inimigo[p].posicao.GetPosicaoW();
		int yb=objetos.Inimigos[NumeroMapa].inimigo[p].posicao.GetPosicaoY();
		int hb=objetos.Inimigos[NumeroMapa].inimigo[p].posicao.GetPosicaoH();
		
		int xw=objetos.mapa[NumeroMapa].MapaPosition[x][y].posicao.GetPosicaoX();
		int ww=objetos.mapa[NumeroMapa].MapaPosition[x][y].posicao.GetPosicaoW();
		int yw=objetos.mapa[NumeroMapa].MapaPosition[x][y].posicao.GetPosicaoY();
		int hw=objetos.mapa[NumeroMapa].MapaPosition[x][y].posicao.GetPosicaoH();
		
		if((xb+wb/2-TamanhoInimigoX/2)>=xw&&xb<=(xw+ww/2-TamanhoInimigoX/2)&&(yb)<=(yw+hw/2-TamanhoInimigoX/2)&&(yb+hb/2-TamanhoInimigoX/2)>=(yw)){
			objetos.Inimigos[NumeroMapa].inimigo[p].posicao.SetVelY(0);
			objetos.Inimigos[NumeroMapa].inimigo[p].posicao.SetVelX(0);
			objetos.Inimigos[NumeroMapa].inimigo[p].SetLayerX(x);
			objetos.Inimigos[NumeroMapa].inimigo[p].SetLayerY(y);
			if(*way==Tamanho){
				if(objetos.Inimigos[NumeroMapa].WayPoints.DirecaoWay[p].GetDirecao()==-1){
					objetos.Inimigos[NumeroMapa].WayPoints.DirecaoWay[p].SetCaminho(-1);
					(*way)--;
				}else{
					if(objetos.Inimigos[NumeroMapa].WayPoints.DirecaoWay[p].GetDirecao()==1){
						(*way)=0;
					}
				}
			}else{
				if(*way==0){
					objetos.Inimigos[NumeroMapa].WayPoints.DirecaoWay[p].SetCaminho(1);
				}
				if(objetos.Inimigos[NumeroMapa].WayPoints.DirecaoWay[p].GetCaminho()==1){
					(*way)++;
					
				}else{
					if(objetos.Inimigos[NumeroMapa].WayPoints.DirecaoWay[p].GetCaminho()==-1){
						(*way)--;
					}
				}
			}
		}else{
			if(objetos.Inimigos[NumeroMapa].inimigo[p].GetLayerX()==x){
				if(objetos.Inimigos[NumeroMapa].inimigo[p].GetLayerY()>y){
					objetos.Inimigos[NumeroMapa].inimigo[p].posicao.SetVelY(-1);
					objetos.Inimigos[NumeroMapa].inimigo[p].posicao.SetVelX(0);
				}else{
					objetos.Inimigos[NumeroMapa].inimigo[p].posicao.SetVelY(1);
					objetos.Inimigos[NumeroMapa].inimigo[p].posicao.SetVelX(0);
				}
			}
			if(objetos.Inimigos[NumeroMapa].inimigo[p].GetLayerY()==y){
				if(objetos.Inimigos[NumeroMapa].inimigo[p].GetLayerX()>x){
					objetos.Inimigos[NumeroMapa].inimigo[p].posicao.SetVelX(-1);
					objetos.Inimigos[NumeroMapa].inimigo[p].posicao.SetVelY(0);
				}else{
					objetos.Inimigos[NumeroMapa].inimigo[p].posicao.SetVelX(1);
					objetos.Inimigos[NumeroMapa].inimigo[p].posicao.SetVelY(0);
				}
			}
			objetos.Inimigos[NumeroMapa].inimigo[p].posicao.SetPosicaoX(objetos.Inimigos[NumeroMapa].inimigo[p].posicao.GetPosicaoX()+objetos.Inimigos[NumeroMapa].inimigo[p].posicao.GetVelX()*(VelocidadeInimigo-1));
			objetos.Inimigos[NumeroMapa].inimigo[p].posicao.SetPosicaoY(objetos.Inimigos[NumeroMapa].inimigo[p].posicao.GetPosicaoY()+objetos.Inimigos[NumeroMapa].inimigo[p].posicao.GetVelY()*(VelocidadeInimigo-1));
		}
		
	}
	void trataposicaoInimigo(){
		for(int i=0;i<objetos.Inimigos[NumeroMapa].WayPoints.GetNumeroInimigos();i++){
			WaypointControll(objetos.Inimigos[NumeroMapa].WayPoints.waypoint[i][objetos.Inimigos[NumeroMapa].WayPoints.LocalWaypoint[i]].GetX(),objetos.Inimigos[NumeroMapa].WayPoints.waypoint[i][objetos.Inimigos[NumeroMapa].WayPoints.LocalWaypoint[i]].GetY(),&objetos.Inimigos[NumeroMapa].WayPoints.LocalWaypoint[i],objetos.Inimigos[NumeroMapa].WayPoints.Tamanho[i],i);
		}
	}
	void trataposicaoJogador(){
		int xt;
		int yt;
		int wt;
		int ht;
		int ok=1;
		for(int p=0;p<VelocidadeJogador;p++){
			int xb=objetos.jogador.posicao.GetPosicaoX()+objetos.jogador.posicao.GetVelX();
			int yb=objetos.jogador.posicao.GetPosicaoY()+objetos.jogador.posicao.GetVelY();
			int wb=objetos.jogador.posicao.GetPosicaoW();
			int hb=objetos.jogador.posicao.GetPosicaoH();
			for(int i=0;i<objetos.mapa[NumeroMapa].GetTamanhoY();i++){
				for(int j=0;j<objetos.mapa[NumeroMapa].GetTamanhoX();j++){
					
					xt=objetos.mapa[NumeroMapa].MapaPosition[i][j].posicao.GetPosicaoX();
					yt=objetos.mapa[NumeroMapa].MapaPosition[i][j].posicao.GetPosicaoY();
					wt=objetos.mapa[NumeroMapa].MapaPosition[i][j].posicao.GetPosicaoW();
					ht=objetos.mapa[NumeroMapa].MapaPosition[i][j].posicao.GetPosicaoH();
					
					if((xb+wb)>=xt&&xb<=(xt+wt)&&(yb)<=(yt+ht)&&(yb+hb)>=(yt)){
						if(objetos.mapa[NumeroMapa].GetMatriz(i,j)==0){
							ok=0;
						}else{
							if((xb+wb-9)>xt&&xb<(xt+wt-9)&&(yb+9)<(yt+ht)&&(yb+hb-9)>(yt)){
								objetos.mapa[NumeroMapa].MapaPosition[i][j].SetPonto(false);
							}
						}
					}
				}
			}
			objetos.jogador.TrataPosicao(ok);
		}
	}
	void VerificaSeGahou(){
		for(int i=0;i<objetos.mapa[NumeroMapa].GetTamanhoY();i++){
			for(int j=0;j<objetos.mapa[NumeroMapa].GetTamanhoX();j++){
				if(objetos.mapa[NumeroMapa].MapaPosition[i][j].GetPonto()==true){
					return;
				}
			}
		}
		objetos.FimDeJogo.estado=1;
	}
	
	int ContaPontos(){
		int pontos=0;
		for(int i=0;i<objetos.mapa[NumeroMapa].GetTamanhoY();i++){
			for(int j=0;j<objetos.mapa[NumeroMapa].GetTamanhoX();j++){
				if(objetos.mapa[NumeroMapa].MapaPosition[i][j].GetPonto()==false&&objetos.mapa[NumeroMapa].GetMatriz(i,j)==true){
					pontos++;
				}
			}
		}
		return pontos;
	}
	
	void TrataPosicao(){
		if(objetos.MenuPosicao.GetEstado()==false){
			trataposicaoJogador();
			trataposicaoInimigo();
			ColisaoJogadorInimigo();
			VerificaSeGahou();
			int pontos=ContaPontos();
		}else{
			objetos.MenuPosicao.TrataPosicao();
		}
	}
	void TrataObjeto(){}
	void Inicializa(){
		objetos.mapa[0].inicializa((char*)"Inf/matriz.txt");
		objetos.mapa[1].inicializa((char*)"Inf/matriz2.txt");
		for(int c=0;c<2;c++){
			for(int i=0;i<objetos.mapa[c].GetTamanhoY();i++){
				for(int j=0;j<objetos.mapa[c].GetTamanhoX();j++){
					if(objetos.mapa[c].GetMatriz(i,j)==0){
						objetos.mapa[c].MapaPosition[i][j].Inicializa(i,j,25,25,false);
					}else{
						objetos.mapa[c].MapaPosition[i][j].Inicializa(i,j,25,25,true);
					}
				}
			}
		}
		objetos.morte.Inicializa(0, 0, Largura_tela, Altura_tela);
		objetos.MenuPosicao.Botao[0].Inicializa(Largura_tela/2-200/2,Altura_tela/2-100/2-90, 200, 100);
		objetos.MenuPosicao.Botao[1].Inicializa(Largura_tela/2-200/2,Altura_tela/2+50-90, 200, 100);
		objetos.MenuPosicao.Botao[2].Inicializa(Largura_tela/2-200/2,Altura_tela/2+150-90, 200, 100);
		objetos.MenuPosicao.Botao[3].Inicializa(Largura_tela/2-200/2,Altura_tela/2+250-90, 200, 100);
		objetos.MenuPosicao.Fundo.Inicializa(0, 0, Largura_tela, Altura_tela);
		objetos.MenuPosicao.FundoTutorial.Inicializa(0, 0, Largura_tela, Altura_tela);
		objetos.FimDeJogo.Inicializa(0, 0, Largura_tela, Altura_tela);
		objetos.Inimigos[0].WayPoints.Inicializa((char*)"Inf/waypoints.txt");
		objetos.Inimigos[1].WayPoints.Inicializa((char*)"Inf/waypoints2.txt");
		int w=objetos.mapa[NumeroMapa].MapaPosition[0][0].posicao.GetPosicaoW()/2-TamanhoJogadorX/2;
		int h=objetos.mapa[NumeroMapa].MapaPosition[0][0].posicao.GetPosicaoH()/2-TamanhoJogadorY/2;
		objetos.jogador.Inicializa(objetos.mapa[NumeroMapa].MapaPosition[1][4].posicao.GetPosicaoX()+w,objetos.mapa[NumeroMapa].MapaPosition[1][4].posicao.GetPosicaoY()+h,TamanhoJogadorX,TamanhoJogadorY);
		objetos.jogador.vidas=4;
		w=objetos.mapa[NumeroMapa].MapaPosition[0][0].posicao.GetPosicaoW()/2-TamanhoInimigoX/2;
		h=objetos.mapa[NumeroMapa].MapaPosition[0][0].posicao.GetPosicaoH()/2-TamanhoInimigoY/2;
		int o;
		for(int g=0;g<2;g++){
			o=objetos.Inimigos[g].WayPoints.GetNumeroInimigos();
			objetos.Inimigos[g].inimigo=(InimigoPosicao*)malloc(o*sizeof(InimigoPosicao));
			for(int i=0;i<objetos.Inimigos[g].WayPoints.GetNumeroInimigos();i++){
				objetos.Inimigos[g].inimigo[i].Inicializa(objetos.mapa[0].MapaPosition[objetos.Inimigos[g].WayPoints.Inicializador[i].GetX()][objetos.Inimigos[g].WayPoints.Inicializador[i].GetY()].posicao.GetPosicaoX()+w,objetos.mapa[0].MapaPosition[objetos.Inimigos[g].WayPoints.Inicializador[i].GetX()][objetos.Inimigos[g].WayPoints.Inicializador[i].GetY()].posicao.GetPosicaoY()+h,TamanhoInimigoX,TamanhoInimigoY, objetos.Inimigos[g].WayPoints.Inicializador[i].GetX(), objetos.Inimigos[g].WayPoints.Inicializador[i].GetY());
			}
		}
	}
	
};
class GerenciaTexturas{
public:
	Texturas texturas;
	bool loadMedia(SDL_Renderer* gRenderer1){
		if(!texturas.MenuFoto.Fundo.loadMedia((char *)"imagens/fundo.PNG",gRenderer1)){
			return false;
		}
		if(!texturas.Telas[0].loadMedia((char *)"imagens/derrota.png",gRenderer1)){
			return false;
		}
		if(!texturas.morte.loadMedia((char *)"imagens/morte.png",gRenderer1)){
			return false;
		}
		if(!texturas.Telas[1].loadMedia((char *)"imagens/vitoria.png",gRenderer1)){
			return false;
		}
		if(!texturas.MenuFoto.FundoTutorial.loadMedia((char *)"imagens/tutorial.PNG",gRenderer1)){
			return false;
		}
		if(!texturas.MenuFoto.Botao[0].loadMedia((char *)"imagens/botao1.PNG",gRenderer1)){
			return false;
		}
		if(!texturas.MenuFoto.Botao[1].loadMedia((char *)"imagens/botao2.PNG",gRenderer1)){
			return false;
		}
		if(!texturas.MenuFoto.Botao[2].loadMedia((char *)"imagens/botao3.PNG",gRenderer1)){
			return false;
		}
		if(!texturas.MenuFoto.Botao[3].loadMedia((char *)"imagens/botao4.PNG",gRenderer1)){
			return false;
		}
		if(!texturas.mapaTextura[0].loadMedia((char *)"imagens/mapa1.png",gRenderer1)){
			return false;
		}
		if(!texturas.mapaTextura[1].loadMedia((char *)"imagens/moeda.png",gRenderer1)){
			return false;
		}if(!texturas.mapaTextura[2].loadMedia((char *)"imagens/mapa2.png",gRenderer1)){
			return false;
		}
		if(!texturas.playertexture.loadMedia((char *)"imagens/jogador.png",gRenderer1)){
			return false;
		}
		if(!texturas.inimigotextura.loadMedia((char *)"imagens/Estrela_Ninja.png",gRenderer1)){
			return false;
		}
		return true;
	}
};
//-----------------///-------------------
//----------------RENDERIZADOR----------------
//-----------------///-------------------
class GerenciaMoveis
{
public:
	GerenciaObjetos GerenteObjetos;
	GerenciaTexturas GerenteTexturas;
	

	void TrataEventosDeSaidaEEntrada(bool * quit, SDL_Renderer* gRenderer1) {
		//Event handler
		SDL_Event e;
		//Handle events on queue                
		SDL_PollEvent(&e);
			//User requests quit
			if (e.type == SDL_QUIT) {
				*quit = true;
			}else{
				GerenteObjetos.objetos.MenuPosicao.TrataEventos(e);
				if(GerenteObjetos.objetos.MenuPosicao.TrataObjeto(e, &GerenteObjetos.NumeroMapa,quit)){
					GerenteObjetos.Inicializa();
				}else{
					if(GerenteObjetos.objetos.MenuPosicao.tutorial==true){
						while (*quit!=true&&e.key.state!=SDLK_SPACE) {
							if (e.type == SDL_QUIT) {
								*quit = true;
							}
							SDL_PollEvent(&e);
							if(e.key.state==SDLK_SPACE){
								GerenteObjetos.objetos.MenuPosicao.tutorial=false;
							}
							SDL_RenderClear(gRenderer1);
							SDL_RenderCopyEx(gRenderer1, GerenteTexturas.texturas.MenuFoto.FundoTutorial.textura.GetTextura(), NULL, &(GerenteObjetos.objetos.MenuPosicao.FundoTutorial.posicao.GetPosicaoEndereco()), 0, NULL, SDL_FLIP_NONE);
							SDL_RenderPresent(gRenderer1);
						}
						
					}else{
						if(GerenteObjetos.objetos.morte.estado==true){
							while (*quit!=true&&e.key.state!=SDLK_SPACE) {
								if (e.type == SDL_QUIT) {
									*quit = true;
								}
								SDL_PollEvent(&e);
								if(e.key.state==SDLK_SPACE){
									GerenteObjetos.objetos.morte.estado=false;
								}
								SDL_RenderClear(gRenderer1);
								SDL_RenderCopyEx(gRenderer1, GerenteTexturas.texturas.morte.textura.GetTextura(), NULL, &(GerenteObjetos.objetos.morte.posicao.GetPosicaoEndereco()), 0, NULL, SDL_FLIP_NONE);
								SDL_RenderPresent(gRenderer1);
							}
						}
						if(GerenteObjetos.objetos.FimDeJogo.estado!=-1){
							while (*quit!=true&&e.key.state!=SDLK_SPACE) {
								if (e.type == SDL_QUIT) {
									*quit = true;
								}
								SDL_PollEvent(&e);
								if(e.key.state==SDLK_SPACE){
									GerenteObjetos.objetos.FimDeJogo.estado=-1;
									GerenteObjetos.Inicializa();
								}
								SDL_RenderClear(gRenderer1);
								SDL_RenderCopyEx(gRenderer1, GerenteTexturas.texturas.Telas[GerenteObjetos.objetos.FimDeJogo.estado].textura.GetTextura(), NULL, &(GerenteObjetos.objetos.FimDeJogo.posicao.GetPosicaoEndereco()), 0, NULL, SDL_FLIP_NONE);
								SDL_RenderPresent(gRenderer1);
							}
						}
					}
				}
				GerenteObjetos.objetos.jogador.TrataEventos(e);
			}
		
	}
	void Renderiza(SDL_Renderer* gRenderer1){
		
		
		//SDL_RenderCopyEx(gRenderer1, MenuFoto.textura.GetTextura(), NULL, &(MenuPosicao.posicao.GetPosicaoEndereco()), 0, NULL, SDL_FLIP_NONE);
		if(GerenteObjetos.objetos.MenuPosicao.GetEstado()==false){
			for(int i=0;i<GerenteObjetos.objetos.mapa[GerenteObjetos.NumeroMapa].GetTamanhoY();i++){
				for(int j=0;j<GerenteObjetos.objetos.mapa[GerenteObjetos.NumeroMapa].GetTamanhoX();j++){
						if(GerenteObjetos.objetos.mapa[GerenteObjetos.NumeroMapa].GetMatriz(i,j)==false){
							SDL_RenderCopyEx(gRenderer1, GerenteTexturas.texturas.mapaTextura[0].textura.GetTextura(), NULL, &(GerenteObjetos.objetos.mapa[GerenteObjetos.NumeroMapa].MapaPosition[i][j].posicao.GetPosicaoEndereco()), 0, NULL, SDL_FLIP_NONE);
						}else{
							if(GerenteObjetos.objetos.mapa[GerenteObjetos.NumeroMapa].MapaPosition[i][j].GetPonto()==true){
								SDL_RenderCopyEx(gRenderer1, GerenteTexturas.texturas.mapaTextura[1].textura.GetTextura(), NULL, &(GerenteObjetos.objetos.mapa[GerenteObjetos.NumeroMapa].MapaPosition[i][j].posicao.GetPosicaoEndereco()), 0, NULL, SDL_FLIP_NONE);
							}else{
								SDL_RenderCopyEx(gRenderer1, GerenteTexturas.texturas.mapaTextura[2].textura.GetTextura(), NULL, &(GerenteObjetos.objetos.mapa[GerenteObjetos.NumeroMapa].MapaPosition[i][j].posicao.GetPosicaoEndereco()), 0, NULL, SDL_FLIP_NONE);
							}
						}
					}
			}
			for(int i=0;i<GerenteObjetos.objetos.Inimigos[GerenteObjetos.NumeroMapa].WayPoints.GetNumeroInimigos();i++){
				SDL_RenderCopyEx(gRenderer1, GerenteTexturas.texturas.inimigotextura.textura.GetTextura(), NULL, &(GerenteObjetos.objetos.Inimigos[GerenteObjetos.NumeroMapa].inimigo[i].posicao.GetPosicaoEndereco()), GerenteObjetos.objetos.Inimigos[GerenteObjetos.NumeroMapa].GrauGiro, NULL, SDL_FLIP_HORIZONTAL);
			}
			GerenteObjetos.objetos.Inimigos[GerenteObjetos.NumeroMapa].GrauGiro+=12;
			if(GerenteObjetos.objetos.Inimigos[GerenteObjetos.NumeroMapa].GrauGiro>=360){GerenteObjetos.objetos.Inimigos[GerenteObjetos.NumeroMapa].GrauGiro=0;}
			SDL_RenderCopyEx(gRenderer1, GerenteTexturas.texturas.playertexture.textura.GetTextura(), NULL, &(GerenteObjetos.objetos.jogador.posicao.GetPosicaoEndereco()), 0, NULL, SDL_FLIP_NONE);
		}else{
			SDL_RenderCopyEx(gRenderer1, GerenteTexturas.texturas.MenuFoto.Fundo.textura.GetTextura(), NULL, &(GerenteObjetos.objetos.MenuPosicao.Fundo.posicao.GetPosicaoEndereco()), 0, NULL, SDL_FLIP_NONE);
			for(int i=0;i<4;i++){
				SDL_RenderCopyEx(gRenderer1, GerenteTexturas.texturas.MenuFoto.Botao[i].textura.GetTextura(), NULL, &(GerenteObjetos.objetos.MenuPosicao.Botao[i].posicao.GetPosicaoEndereco()), 0, NULL, SDL_FLIP_NONE);
			}
		}
		Objetos.texto.MostraVidas(gRenderer1,GerenteObjetos.objetos.jogador.vidas);
		Objetos.texto.MostraScore(gRenderer1,GerenteObjetos.ContaPontos());
		
	}
};
//-----------------///-------------------
#endif
