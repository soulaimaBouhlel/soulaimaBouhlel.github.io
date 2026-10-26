#include <MLV/MLV_all.h>/* l'appel des biblio nécessaires pour travailler*/
#include <stdio.h>
#include<stdlib.h>
//*déclaration des variables*/
int main(int argc, char *argv[]){
	float yp=10.0;
	int width = 1280, height = 800, x=565, y=650, ys=500, xp=rand() % 1100+0, xs, b=0, f=0, a=1,r=0, score=0;  
	MLV_Image *image, *plane, *me, *sprite, *heart, *black, *game;
	MLV_create_window("game","play",width, height);/*création de la fenetre*/
	image= MLV_load_image("load.jpg");
	MLV_resize_image(image, 960,630);

	plane= MLV_load_image("plane.png");/*plane => ennemi*/
	MLV_resize_image(plane,150,150);
	me= MLV_load_image("met.png");/* me => joueur*/
	MLV_resize_image(me,120,120);

	sprite= MLV_load_image("sprite.png");/* sprite => arme*/
	MLV_resize_image(sprite,50,50);
	heart= MLV_load_image("heart.png");/* heart => vie*/
	MLV_resize_image(heart,50,50);
	black= MLV_load_image("black.jpg");/*j'ai utilisé  black(noir) pour effacer*/
	MLV_resize_image(black,50,50);
	game= MLV_load_image("game.jpg");/* afficher "game over"*/
	MLV_resize_image(game, 1280,800);
	while(1){
	MLV_clear_window( MLV_COLOR_BLACK );
	MLV_draw_text(1000,10,"ALWAYS PRESS {o} TO EXIT",MLV_COLOR_BLUE);/*toucher "o" pour quitter  */
	if(MLV_get_keyboard_state( MLV_KEYBOARD_SPACE) == MLV_PRESSED) {
		MLV_draw_image(image, 140, 0);/*l'initialisation de la partie*/
		MLV_actualise_window();	
		MLV_wait_seconds(1);
		while((a==1) || (r==1)){
			r=0;
			MLV_clear_window(MLV_COLOR_BLACK);
			
/*le joueur a 4 vies  et une dernière chance */		
			MLV_draw_image(plane,xp,yp);
			MLV_draw_image(heart,10,10);
			MLV_draw_image(heart,70,10);
			MLV_draw_image(heart,130,10);
			MLV_draw_image(heart,190,10);
		/*l'inctrémentation de la position de l'ennemi */	
			if ((yp>=10) && (yp<650)){
				yp+=0.5;
					
			}
			/*si l'ennemi traverse l'écran un autre apparait et le joueur perd une vie */	
			else{
				f++;
				MLV_draw_circle( xp, yp, 150, MLV_COLOR_BLACK );	
				
				yp=10;
				xp=rand() % 1100+0;
			}	
			/*presser le bouton droite et gauche pour se déplacer*/	
			MLV_draw_image(me,x,y);			
			if((MLV_get_keyboard_state( MLV_KEYBOARD_RIGHT) == MLV_PRESSED) && (x<1190)){
				x+=5;
			}
			if((MLV_get_keyboard_state( MLV_KEYBOARD_LEFT) == MLV_PRESSED) && (x>0)){
				x-=5;
			}	
			/* l'arme(sprite) est actionnée par la touche de l'espace du clavier*/
			xs=x;	
			if(MLV_get_keyboard_state( MLV_KEYBOARD_SPACE) == MLV_PRESSED) {
				 b=1;
			}	 
			if (b==1){	
				MLV_draw_image(sprite, xs-10, ys-50);
				MLV_draw_image(sprite, xs+85, ys-50);
				ys-=10;
				if (ys==0){
					ys=500;	
					b=0;				
				}
				else if  (((xs<=xp+300) && (xs>=xp-50) && (ys<=yp+150) && (ys>=yp-150))){
					score++;/* si le joueur tue un ennemi le score incrémente et un autre apparait*/
					MLV_draw_circle( x, yp, 150, MLV_COLOR_BLACK );	
					MLV_wait_seconds(0.5);
					yp=10;
					xp=rand() % 1200+0;
					b=0;
					
				}
						
			}
			/*si l'ennemi touche l'avion du joueur une vie est perdue et un autre ennemi apparait*/
			if ((xs<=xp+300) && (xs>=xp-50) && (y<=yp+150) && (y>=yp-150)){
				MLV_draw_circle( x, y, 300, MLV_COLOR_BLACK );	
				MLV_draw_circle( xp, yp, 150, MLV_COLOR_BLACK );	
				xp=rand() % 1100+0;
				yp=10;
				f+=1;
			}
			/* la disparition des vies perdues*/
			if (f==1) {
				MLV_draw_image(black,10,10);
				
			}	

			if (f==2) {
				MLV_draw_image(black,10,10);
				MLV_draw_image(black,70,10);
			}
			if (f==3) {
				MLV_draw_image(black,10,10);
				MLV_draw_image(black,70,10);
				MLV_draw_image(black,130,10);
			}
			if (f==4) {
				MLV_draw_image(black,10,10);
				MLV_draw_image(black,70,10);
				MLV_draw_image(black,130,10);
				MLV_draw_image(black,190,10);
			}			
			if (f==5){/* si le joueur perd ses 5 chances la parties est perdue */
				MLV_clear_window( MLV_COLOR_BLACK );	
				MLV_draw_image(game,0,0);/*GAME OVER*/
				MLV_draw_text(500,600," PRESS {R} TO REPLAY / PRESS {E} TO EXIT",MLV_COLOR_RED);/*la touche "r" pour réperter la partie sans avoir le besoin de faire une autre exécution et la touche "e" pour sortir */
				MLV_draw_text(500,450,"SCORE: ,%d ",score,MLV_COLOR_RED);/*affichage du score*/
				
				
				if (MLV_get_keyboard_state( MLV_KEYBOARD_r) == MLV_PRESSED){
				/*si la touche"r" est appuiée les condions initiales sont activées*/
					r=1;
					f=0;
				}	
				else if (MLV_get_keyboard_state( MLV_KEYBOARD_e) == MLV_PRESSED){
					MLV_free_window();
				}	
					
			}	
			MLV_draw_text(1000,10,"ALWAYS PRESS {o} TO EXIT",MLV_COLOR_BLUE);
			
			
			if (MLV_get_keyboard_state( MLV_KEYBOARD_o) == MLV_PRESSED) {
			/*on peut quitter le jeu à tout instant par la touche "o" du clavier*/
	 		break;
			
			}	
		
			MLV_actualise_window();
	 }
			
		
	}
	else if (MLV_get_keyboard_state( MLV_KEYBOARD_o) == MLV_PRESSED) {
	 	break;
	 }		
	else{	
		MLV_draw_text(520,600,"PRESS ON SPACE BUTTON", MLV_COLOR_PINK);
		/*il faut appuier sur la touche "espace" du clavier pour lancer le jeu*/
		}
		MLV_actualise_window();
	}
	
	MLV_free_window();
	return 0;
}


