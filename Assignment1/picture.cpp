#include <iostream>
#include <fstream>
#include "picture.h"
#include "picture_pair.h"

const char SPACE = ' ';

using namespace std;

// Reads a char from ifstream
// Includes space but excludes newline
// Useful for reading character pictures
char get_ch(ifstream &in)
{
	char c = '\0';
	while (in >> noskipws >> c && c == '\n')
		;

	return c;
}

Picture::Picture(const Picture& p){
	this->height=p.height;
	this->width=p.width;
	this->pix=new char*[height];
	for(int x=0;x<height;++x){
		pix[x]=new char[width];
	}

	for(int x=0;x<height;++x){
		for(int y=0;y<width;++y){
			pix[x][y]=p.pix[x][y];
		}
	}
}

Picture::Picture(const Picture_Pair& pp){
	Picture* p0=pp.get_picture(0);
	Picture* p1=pp.get_picture(1);
	if(p0!=nullptr && p1!=nullptr){
		int longer_height=p0->height>p1->height?p0->height:p1->height;
		this->height=longer_height;
		this->width=p0->width+p1->width;
		this->pix=new char* [height];
		for(int x=0;x<height;++x){
			pix[x]=new char[width];
		}
		for(int x=0;x<height;++x){
			for(int y=0;y<width;++y){
				pix[x][y]=SPACE;
			}
		}
		int h0=p0->height;
		int w0=p0->width;
		int h1=p1->height;
		for(int x=0;x<h0;++x){
			for(int y=0;y<w0;++y){
				//if(p0->pix[x][y]!=SPACE){
					pix[x][y]=p0->pix[x][y];
				//}
				/*else if(p0->pix[x][y]==SPACE){
					pix[x][y]=SPACE;
				}*/
			}
		}
		for(int x=0;x<h1;++x){
			for(int y=w0,y1=0;y<width;++y,++y1){
				//if(p1->pix[x][y]!=SPACE){
					pix[x][y]=p1->pix[x][y1];
				//}
				/*else if(p1->pix[x][y]==SPACE){
					pix[x][y]=SPACE;
				}*/
			}
		}
	}
	else if((p0==nullptr && p1!=nullptr) || (p0!=nullptr && p1==nullptr)){
		if(p0==nullptr){
			this->height=p1->height;
			this->width=p1->width;
			this->pix=new char*[height];
			for(int x=0;x<height;++x){
				pix[x]=new char[width];
			}
			for(int x=0;x<height;++x){
				for(int y=0;y<width;++y){
					pix[x][y]=p1->pix[x][y];
				}
			}
		}
		else if(p1==nullptr){
			this->height=p0->height;
			this->width=p0->width;
			this->pix=new char*[height];
			for(int x=0;x<height;++x){
				pix[x]=new char[width];
			}
			for(int x=0;x<height;++x){
				for(int y=0;y<width;++y){
					pix[x][y]=p0->pix[x][y];
				}
			}
		}
	}
	else if(p0==nullptr && p1==nullptr){
		height=0;
		width=0;
		pix=nullptr;
	}

}

void Picture::frame(char symbol, int frame_length){
	if(frame_length>0 && pix!=nullptr){
		int frameheight=height + 2*frame_length;
		int framewidth=width + 2*frame_length;
		char**frame=new char* [frameheight];
		for(int x=0;x<frameheight;++x){
			frame[x]=new char[framewidth];
		}
		for(int x=0;x<frameheight;++x){
			for(int y=0;y<framewidth;++y){
				frame[x][y]=symbol;
			}
		}

		for(int x=0+frame_length;x<frame_length+height;++x){
			for(int y=0+frame_length;y<frame_length+width;++y){
				frame[x][y]=pix[x-frame_length][y-frame_length];
			}
		}
		for(int x=0;x<height;++x){
			delete [] pix[x];
		}
		delete[] pix;
		height=frameheight;
		width=framewidth;
		pix=frame;
	}
	else if(pix==nullptr){
		height=2*frame_length;
		width=2*frame_length;
		pix=new char*[height];
		for(int x=0;x<height;++x){
			pix[x]=new char[width];
		}
		for(int x=0;x<height;++x){
			for(int y=0;y<width;++y){
				pix[x][y]=symbol;
			}
		}
	}
}

void Picture::draw()const{
	if(pix!=nullptr){
		for(int x=0;x<height;++x){
			for(int y=0;y<width;++y){
				if(pix[x][y]!=SPACE){
					cout<<pix[x][y];
				}
				else if(pix[x][y]==SPACE){
					cout<<' ';
				}
			}
			cout<<endl;
		}
	}
}

Picture::Picture(const char* filename){
	ifstream ifs(filename);
	int height_a=0;
	int width_a=0;
	ifs>>height_a;
	ifs>>width_a;
	height=height_a;
	width=width_a;
		/*char waste=get_ch(ifs);
		int number=0;
		while(waste!=SPACE){
			number=10*number+(waste-48);
			waste=get_ch(ifs);
		}
		height=number;
		number=0;
		waste=get_ch(ifs);
		while(waste!=SPACE && waste<='9'){
			number=10*number+(waste-48);
			waste=get_ch(ifs);
		}
		width=number;*/
	pix=new char*[height];
	for(int x=0;x<height;++x){
		pix[x]=new char[width];
	}
	for(int x=0;x<height;++x){
		for(int y=0;y<width;++y){
			/*if(x==0 && y==0){
				pix[x][y]=waste;
			}*/
			//else{
			pix[x][y]=get_ch(ifs);
				//pix[x][y]=waste;
				//waste=get_ch(ifs);
			//}
		}
	}
}

Picture::~Picture(){
	for(int x=0;x<height && pix[x]!=nullptr;++x){
		delete [] pix[x];
		pix[x]=nullptr;
	}
	delete [] pix;
	pix=nullptr;
}
