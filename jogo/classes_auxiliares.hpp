#ifndef CLASSES_AUXILIARES
#define CLASSES_AUXILIARES
#include"Definidores.hpp"
class PontoWaypoint{
	int x,y;
public:
	int GetX() {
		return x;
	}
	void SetX(int d) {
		x = d;
	}
	int GetY() {
		return y;
	}
	void SetY(int d) {
		y = d;
	}
};
class DirecaoWaypoint{
	int Caminho;
public:
	int DirecaoWay;
	DirecaoWaypoint(){
		DirecaoWay=1;
		Caminho=0;
	};
	int GetDirecao() {
		return DirecaoWay;
	}
	void SetDirecao(int d) {
		DirecaoWay = d;
	}
	int GetCaminho() {
		return Caminho;
	}
	void SetCaminho(int d) {
		Caminho = d;
	}
};
class MatrizWaypoint{
	int numero_inimigos;
public:
	int LocalWaypoint[QuantidadeWaypoints];
	int Tamanho[QuantidadeWaypoints];
	DirecaoWaypoint DirecaoWay[QuantidadeWaypoints];
	PontoWaypoint waypoint[Quantidadeinimigos][QuantidadeWaypoints];
	PontoWaypoint Inicializador[QuantidadeWaypoints];
	void Inicializa(char *path){
		for(int i=0;i<QuantidadeWaypoints;i++){
			LocalWaypoint[i]=0;
			DirecaoWay[i].DirecaoWay=1;
		}
		FILE *arq;int i=0,j=0,aux;
		if((arq=fopen(path,"r"))==NULL){
			printf("Nao foi possivel abrir o arquivo de texto de waypoints\n");
			exit(0);
		}numero_inimigos=0;
		while(!feof(arq)){
			if(i==0){
				fscanf(arq,"%d",&aux);
				DirecaoWay[j].DirecaoWay=aux;
				fscanf(arq,"%d",&aux);
				Inicializador[j].SetX(aux);
				fscanf(arq,"%d",&aux);
				Inicializador[j].SetY(aux);
				fscanf(arq,"%d",&aux);
				waypoint[j][i].SetX(aux);
				fscanf(arq,"%d",&aux);
				waypoint[j][i].SetY(aux);
				i++;
			}else{
				fscanf(arq,"%d",&aux);
				if(aux==-10){
					numero_inimigos++;
					i--;
					Tamanho[j]=i;
					i=0;
					j++;
				}else{
					waypoint[j][i].SetX(aux);
					fscanf(arq,"%d",&aux);
					waypoint[j][i].SetY(aux);
					i++;
				}
			}
		}
		fclose(arq);
	}
	int GetNumeroInimigos(){
		return numero_inimigos;
	}
	int GetTamanho(int i){
		return Tamanho[i];
	}
	int GetLocalWaypoint(int i){
		return LocalWaypoint[i];
	}
};
#endif
