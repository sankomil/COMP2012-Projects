//submit this file

#include "mall.h"

Mall::Mall(string name): name(name) {}

void Mall::mergeMall(Mall& another, string newName){

	shops.merge(another.shops);
	name=newName;
}

int calculate_hash(string name){
	int i=0;

	for(;name[i]!='\0';++i);


	int a[i];
	for(int x=0;x<i;++x){
		if(name[x]>='a' && name[x]<='z'){
			a[x]=name[x]-'a'+1;
		}
		else if(name[x]>='A' && name[x]<='Z'){
			a[x]=name[x]-'A'+1;
		}
	}

	int k=0;
	for(int x=0;x<i;++x){
		int b=1;
		for(int y=0;y<i-1-x;++y){
			b*=37;

		}
		k+=b*a[x];

	}

	return k;

}

bool Mall::buildShop(string name){

	int (*h)(string)=calculate_hash;
	Shop temp{name, 7, h, nullptr, Mode::LINEAR, 0.5};
	return shops.add(name,temp);

}

bool Mall::demolishShop(string name){

	return shops.remove(name);
}



Shop* Mall::getShop(string name){
	return shops.get(name);
}

