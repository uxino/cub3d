//------------------------YouTube-3DSage----------------------------------------
//Full video: https://www.youtube.com/watch?v=gYRrGTC7GtA 
//WADS to move player.

#include <stdlib.h>

#include <math.h>
#include "cub3d.h"

//-----------------------------MAP----------------------------------------------
#define PI 3.14159265
#define mapX  8      //map width
#define mapY  8      //map height
#define mapS 64      //map cube size
int map[]=           //the map array. Edit to change level but keep the outer walls
{
 1,1,1,1,1,1,1,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,1,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1,	
};
float px,py,pdx,pdy,pa;

//------------------------PLAYER------------------------------------------------
float degToRad(int a) { return a*M_PI/180.0;}

int FixAng(int a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}

void DDA(t_data *data,int X0, int Y0, int X1, int Y1)
{ 
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 
  
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    float Xinc = dx / (float)steps; 
    float Yinc = dy / (float)steps; 
  
    float X = X0; 
    float Y = Y0; 
    for (int i = 0; i <= steps; i++)
	{ 
        mlx_pixel_put(data->g.mlx, data->g.win, X+20, Y+20, 0x00FF0000);
        X += Xinc; 
        Y += Yinc; 
    }
}
int	key_code(int keycode, t_data *data)
{
	if(keycode==0){ pa+=5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));} // left
	if(keycode==2){ pa-=5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));} // right
	if(keycode==13){ px+=pdx*5; py+=pdy*5;} // up
	if(keycode==1){ px-=pdx*5; py-=pdy*5;} // down
	return (0);
}

// void Buttons(unsigned char key,int x,int y)
// {
//  if(keycode==0){ pa+=5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));} // left
//  if(keycode==2){ pa-=5; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));} // right
//  if(keycode==13){ px+=pdx*5; py+=pdy*5;} // up
//  if(keycode==1){ px-=pdx*5; py-=pdy*5;} // down
//  glutPostRedisplay();
// }//---

void drawMap2D(t_data *data)
{
	int x, y, xo, yo;

	xo = 0;
	yo = 0;
	y = 0;
	while (y < mapY)
	{
		x = 0;
		while (x < mapX)
		{
			if (map[y * mapX + x] == 1)
				mlx_put_image_to_window(data->g.mlx, data->g.win, data->g.duvar, xo, yo);
			x++;
			xo += mapS;
		}
		y++;
		yo += mapS;
		xo = 0;
	}
}

int	close_game(void *param)
{
	param = NULL;
	exit(0);
	return (0);
}

//---------------------------Draw Rays and Walls--------------------------------
float distance(ax,ay,bx,by,ang){ return cos(degToRad(ang))*(bx-ax)-sin(degToRad(ang))*(by-ay);}

void drawRays2D(t_data *data)
{
	int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH;

	ra=FixAng(pa+30);
	for(r=0;r<60;r++)
	{
        // Vertical
		dof=0; side=0; disV=100000;
        
		float Tan=tan(degToRad(ra));
		if(cos(degToRad(ra))> 0.001){ rx=(((int)px>>6)<<6)+64;      ry=(px-rx)*Tan+py; xo= 64; yo=-xo*Tan;}//looking left
  		else if(cos(degToRad(ra))<-0.001){ rx=(((int)px>>6)<<6) -0.0001; ry=(px-rx)*Tan+py; xo=-64; yo=-xo*Tan;}//looking right
  		else { rx=px; ry=py; dof=8;}
		while(dof<8) 
		{ 
		    mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                     
		    if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disV=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
		    else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
		}

        // Horizontal
		vx=rx; vy=ry;
		dof=0; disH=100000;
  		Tan=1.0/Tan;
  		if(sin(degToRad(ra))> 0.001){ ry=(((int)py>>6)<<6) -0.0001; rx=(py-ry)*Tan+px; yo=-64; xo=-yo*Tan;}//looking up 
  		else if(sin(degToRad(ra))<-0.001){ ry=(((int)py>>6)<<6)+64;      rx=(py-ry)*Tan+px; yo= 64; xo=-yo*Tan;}//looking down
  		else{ rx=px; ry=py; dof=8;}

 	 	while(dof<8) 
 	 	{ 
 	 	    mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                          
 	 	    if(mp>0 && mp<mapX*mapY && map[mp]==1){ dof=8; disH=cos(degToRad(ra))*(rx-px)-sin(degToRad(ra))*(ry-py);}//hit         
 	 	    else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
 	 	}
		if(disV<disH){ rx=vx; ry=vy; disH=disV;}
  		int ca=FixAng(pa-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye 
  		int lineH = (mapS*320)/(disH); if(lineH>320){ lineH=320;}                     //line height and limit
  		int lineOff = 160 - (lineH>>1);


        // kare ile duvar arası çizgi
		for (int i = 0; i < 8; i++)
		{
			mlx_pixel_put(data->g.mlx, data->g.win, px, py, 0x00FF0000);
			mlx_pixel_put(data->g.mlx, data->g.win, px + 1, py - 1, 0x00FF0000);
			mlx_pixel_put(data->g.mlx, data->g.win, px - 1, py + 1, 0x00FF0000);
			mlx_pixel_put(data->g.mlx, data->g.win, px - 1, py - 1, 0x00FF0000);
			mlx_pixel_put(data->g.mlx, data->g.win, px + 1, py + 1, 0x00FF0000);

			mlx_pixel_put(data->g.mlx, data->g.win, rx, ry, 0x00FF0000);
			mlx_pixel_put(data->g.mlx, data->g.win, rx + 1, ry - 1, 0x00FF0000);
			mlx_pixel_put(data->g.mlx, data->g.win, rx - 1, ry + 1, 0x00FF0000);
			mlx_pixel_put(data->g.mlx, data->g.win, rx - 1, ry - 1, 0x00FF0000);
			mlx_pixel_put(data->g.mlx, data->g.win, rx + 1, ry + 1, 0x00FF0000);
		}
		// DDA(data, xo, yo, px, py);
        // Duvarların çizimi
        // for (int i = 0; i < 16; i++)
		// {
        //     printf("lineOff: %d\n", lineOff);
        //     printf("di: %d\n", disH);
		// 	mlx_pixel_put(data->g.mlx, data->g.win, r*8 + 530, lineOff, 0x00FF0000);
		// 	mlx_pixel_put(data->g.mlx, data->g.win, r*8 + 530, lineOff+lineH, 0x00FF0000);
		// }
		ra=FixAng(ra-1);
	}
}

//  if(disV<disH){ rx=vx; ry=vy; disH=disV; glColor3f(0,0.6,0);}                  //horizontal hit first
//   glLineWidth(2); glBegin(GL_LINES); glVertex2i(px,py); glVertex2i(rx,ry); glEnd();//draw 2D ray
    
//   int ca=FixAng(pa-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye 
//   int lineH = (mapS*320)/(disH); if(lineH>320){ lineH=320;}                     //line height and limit
//   int lineOff = 160 - (lineH>>1);                                               //line offset
  
//   glLineWidth(8);glBegin(GL_LINES);glVertex2i(r*8+530,lineOff);glVertex2i(r*8+530,lineOff+lineH);glEnd();//draw vertical wall  

//   ra=FixAng(ra-1);  

int draw_player(t_data *data)
{
	mlx_clear_window(data->g.mlx, data->g.win);
	mlx_put_image_to_window(data->g.mlx, data->g.win, data->g.kare,px,py);
	// drawMap2D(data);
	drawRays2D(data);
	mlx_do_sync(data->g.mlx);
	return (1);
}

void	mlx_define(t_data *data)
{
	int	x;
	int	y;
	data->g.mlx = mlx_init();
	data->g.win = mlx_new_window(data->g.mlx, 64*16, 64*8, "ELMA.TXT");
	data->g.sky = mlx_xpm_file_to_image(data->g.mlx, "textures/sky_eagle.xpm", &x,&y);
	data->g.floor = mlx_xpm_file_to_image(data->g.mlx, "textures/floor_wood.xpm", &x,&y);
	data->g.north_wall = mlx_xpm_file_to_image(data->g.mlx, "textures/north_pillar.xpm", &x,&y);
	data->g.east_wall = mlx_xpm_file_to_image(data->g.mlx, "textures/east_greystone.xpm",&x,&y);
	data->g.west_wall = mlx_xpm_file_to_image(data->g.mlx, "textures/west_mossy.xpm", &x, &y);
	data->g.south_wall = mlx_xpm_file_to_image(data->g.mlx, "textures/south_bluestone.xpm", &x, &y);
	data->g.kare = mlx_xpm_file_to_image(data->g.mlx, "textures/kare.xpm", &x, &y);
	data->g.duvar = mlx_xpm_file_to_image(data->g.mlx, "textures/duvar.xpm", &x, &y);
	px=150; py=400; pa=90;
	mlx_hook(data->g.win, 2, 1L << 0, key_code, data);
	mlx_loop_hook(data->g.mlx, draw_player, data);
	mlx_hook(data->g.win, 17, 0L, close_game, NULL);		
	mlx_loop(data->g.mlx);
}


void	ft_init(t_data *data, char *address)
{
	data->file_width = 0;
	data->file_height = 0;
	data->map_height = 0;
	data->win_width = 0;
	data->win_height = 0;
	data->map_location = 0;
	data->ch->planeX = 0;
	data->ch->planeY = 0.66;
	data->ch->time = 0;
	data->ch->oldTime = 0;
	get_all_map_size(data, address);
	data->all_map = ft_calloc(data->file_height + 1, sizeof(char *));
	data->map = malloc(sizeof(char *) * (data->file_height + 1));
	data->redirect = malloc(sizeof(char *) * (data->file_height + 1));
	get_all_map(data, address);
	set_redirects(data);
	ft_getmap(data, data->map_location - 1);
	ft_checkmap(data);
	ft_checkdirect(data);
}

int main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (0);
	data = malloc(sizeof(t_data));
	data->ch = malloc(sizeof(t_ch));
	if (!data)
		return (0);
	ft_init(data, argv[1]);
	mlx_define(data);
	return (0);
}
















































// void	mlx_define(t_data *data)
// {
// 	int	x;
// 	int	y;
// 	data->g.mlx = mlx_init();
// 	data->g.win = mlx_new_window(data->g.mlx, 1024, 510, "ELMA.TXT");
// 	data->g.sky = mlx_xpm_file_to_image(data->g.mlx, "textures/sky_eagle.xpm", &x,&y);
// 	data->g.floor = mlx_xpm_file_to_image(data->g.mlx, "textures/floor_wood.xpm", &x,&y);
// 	data->g.north_wall = mlx_xpm_file_to_image(data->g.mlx, "textures/north_pillar.xpm", &x,&y);
// 	data->g.east_wall = mlx_xpm_file_to_image(data->g.mlx, "textures/east_greystone.xpm",&x,&y);
// 	data->g.west_wall = mlx_xpm_file_to_image(data->g.mlx, "textures/west_mossy.xpm", &x, &y);
// 	data->g.south_wall = mlx_xpm_file_to_image(data->g.mlx, "textures/south_bluestone.xpm", &x, &y);
// 	data->g.kare = mlx_xpm_file_to_image(data->g.mlx, "textures/kare.xpm", &x, &y);
// 	data->g.duvar = mlx_xpm_file_to_image(data->g.mlx, "textures/duvar.xpm", &x, &y);
// 	px=150; py=400; pa=90;
// 	mlx_hook(data->g.win, 2, 1L << 0, key_code, data);
// 	mlx_loop_hook(data->g.mlx, draw_player, data);
// 	mlx_hook(data->g.win, 17, 0L, close_game, NULL);		
// 	mlx_loop(data->g.mlx);
// }

// void	ft_init(t_data *data, char *address)
// {
// 	data->file_width = 0;
// 	data->file_height = 0;
// 	data->map_height = 0;
// 	data->win_width = 0;
// 	data->win_height = 0;
// 	data->map_location = 0;
// 	data->ch->planeX = 0;
// 	data->ch->planeY = 0.66;
// 	data->ch->time = 0;
// 	data->ch->oldTime = 0;
// 	get_all_map_size(data, address);
// 	data->all_map = ft_calloc(data->file_height + 1, sizeof(char *));
// 	data->map = malloc(sizeof(char *) * (data->file_height + 1));
// 	data->redirect = malloc(sizeof(char *) * (data->file_height + 1));
// 	get_all_map(data, address);
// 	set_redirects(data);
// 	ft_getmap(data, data->map_location - 1);
// 	ft_checkmap(data);
// 	ft_checkdirect(data);
// }

// int main(int argc, char **argv)
// {
// 	t_data	*data;

// 	if (argc != 2)
//         ft_error("Invalid arguman!", -1, -1);
// 	data = malloc(sizeof(t_data));
// 	data->ch = malloc(sizeof(t_ch));
// 	if (!data)
// 		return (0);
// 	ft_init(data, argv[1]);
// 	mlx_define(data);
// 	return (0);
// }