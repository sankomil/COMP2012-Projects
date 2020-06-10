//submit this file

#include "shop.h"


 Shop::Shop(string name, int m, int (*h)(string), int (*h2)(string), Mode mode, double loadLimit):name(name),profit(0){
	 inventory=new HashTable<string, Product>(m,*h,*h2,mode,loadLimit);
 }

 Shop::Shop(const Shop& another):name(another.name),profit(another.profit){
	 inventory=new HashTable<string, Product>(*another.inventory);
 }

 /*Shop::Shop(Shop&& another):name(another.name),profit(another.profit){

	 inventory=new HashTable<string, Product>(*another.inventory);
	 delete another.inventory;
	 another.name="moved";
 }*/

 Shop::Shop(Shop&& another)
     : name(another.name), profit(another.profit), inventory(another.inventory)
 {
     another.name = "moved";


     another.inventory = nullptr;
 }

 Shop::~Shop(){

	 delete inventory;
 }

 Shop& Shop::operator =(const Shop& another){
	 name=another.name;
	 profit=another.profit;
	 delete inventory;
	 inventory=new HashTable<string, Product>(*another.inventory);
	 return *this;
 }

bool Shop::addProduct(string name, int quantity, int price){


	Product* temp=inventory->get(name);
	if(temp!=nullptr){
		temp->add(quantity);
		return true;
	}
	else{
		temp=new Product(name,quantity,price);
		int check=inventory->add(name,temp);
		temp=nullptr;
		return (check==-1) ? false:true;
	}
}


bool Shop::sellProduct(string name,int quantity){

	Product* temp=inventory->get(name);
	if(temp!=nullptr){
		if(temp->take(quantity)){
			profit+=temp->getPrice()*quantity;
			if(temp->getQuantity()==0){
				inventory->remove(name);
			}
			return true;
		}
	}
	return false;
}



