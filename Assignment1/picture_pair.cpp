#include "picture.h"
#include "picture_pair.h"

Picture_Pair::Picture_Pair(const Picture_Pair& pp){
	this->pp[0]=pp.get_picture(0);
	this->pp[1]=pp.get_picture(1);
}

Picture_Pair::Picture_Pair(Picture* p1, Picture* p2){
	this->pp[0]=p1;
	this->pp[1]=p2;
}

Picture* Picture_Pair::get_picture(int n) const {
	if(n==0 || n==1){
		return this->pp[n];
	}
	else{
		return nullptr;
	}
}

Picture_Pair::~Picture_Pair(){
	for(int x=0;x<2;++x){
		this->pp[x]=nullptr;
	}
}

void Picture_Pair::draw() const{
	if(pp[0]!=nullptr &&pp[1]!=nullptr){
		this->pp[0]->draw();
		this->pp[1]->draw();
	}
	else if(pp[0]==nullptr && pp[1]!=nullptr){
		this->pp[1]->draw();
	}
	else if(pp[1]==nullptr && pp[0]!=nullptr){
			this->pp[0]->draw();
	}
}
