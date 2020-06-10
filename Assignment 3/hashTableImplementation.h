//submit this file
//you do NOT need to include any header in this file
//just write your HashTable implementation here right away



template <typename K, typename T>
HashTable<K,T>::HashTable(int m, int (*h)(K), int (*h2)(K), Mode mode, double loadLimit): m(m),mode(mode),h(h),h2(h2), count(0),loadLimit(loadLimit){
	table=new Cell[m];
	for(int x=0;x<m;++x){
		table[x].status=CellStatus::EMPTY;
		table[x].data=nullptr;
	}
}

template <typename K,typename T>
HashTable<K,T>::HashTable(const HashTable& another):m(another.m),mode(another.mode),h(another.h),h2(another.h2),count(another.count),loadLimit(another.loadLimit){
	table=new Cell[m];
	for(int x=0;x<m;++x){
		table[x].key=another.table[x].key;
		if(another.table[x].data==nullptr){table[x].data=nullptr;}
		else{table[x].data=new T(*another.table[x].data);}
		table[x].status=another.table[x].status;
	}
}

template <typename K,typename T>
HashTable<K,T>::~HashTable(){
	for(int x=0;x<m  ;++x){
		if(table[x].status==CellStatus::ACTIVE){

			delete table[x].data;
		}
	}
	delete[] table;
}

template <typename K,typename T>
HashTable<K,T>& HashTable<K,T>::operator=(const HashTable& another){

	mode=another.mode;
	h=another.h;
	h2=another.h2;
	loadLimit=another.loadLimit;
	count=another.count;
	for(int x=0;x<m;++x){
		if(table[x].status!=CellStatus::EMPTY){delete table[x].data;}
	}
	delete[] table;
	table=nullptr;
	m=another.m;
	table=new Cell[m];
	for(int x=0;x<m;++x){
		table[x].key=another.table[x].key;
		if(another.table[x].status==CellStatus::EMPTY){table[x].data=nullptr;}
		else{
			table[x].data=new T(*another.table[x].data);

		}

		table[x].status=another.table[x].status;
	}
	return *this;
}



template <typename K,typename T>
int HashTable<K,T>::add(K key, T* data){  	//check if all the parameters have been fulfilled

	int che=0;
	for(int x=0;x<m;++x){
		if(table[x].status!=CellStatus::EMPTY){
			++che;
		}
	}

	if(che+1>=loadLimit*m){
		Cell* temp=new Cell[2*m];
		for(int x=0;x<2*m;++x){
			temp[x].status=CellStatus::EMPTY;
		}
		for(int x=0;x<m;++x){
			if(table[x].status==CellStatus::ACTIVE){
				int place=h(table[x].key) % (2*m);
				if(temp[place].status!=CellStatus::ACTIVE){
					temp[place].key=table[x].key;
					temp[place].data=table[x].data;
					temp[place].status=CellStatus::ACTIVE;
				}
				else{
					switch(mode){
					case Mode::LINEAR:
						for(int y=1;y<2*m;++y){
							place=(h(table[x].key)+y) % (2*m);
							if(temp[place].status==CellStatus::EMPTY){
								temp[place].key=table[x].key;
								temp[place].data=table[x].data;
								temp[place].status=CellStatus::ACTIVE;
								break;
							}
						}
						break;

					case Mode::QUADRATIC:
						for(int y=1;y<2*m;++y){
							place=(h(table[x].key)+(y*y)) % (2*m);
							if(temp[place].status==CellStatus::EMPTY){
								temp[place].key=table[x].key;
								temp[place].data=table[x].data;
								temp[place].status=CellStatus::ACTIVE;
								break;
							}
						}
						break;

					case Mode::DOUBLE:
						for(int y=1;y<2*m;++y){
							place=(h(table[x].key)+y*h2(table[x].key)) % (2*m);
							if(temp[place].status==CellStatus::EMPTY){
								temp[place].key=table[x].key;
								temp[place].data=table[x].data;
								temp[place].status=CellStatus::ACTIVE;
								break;
							}
						}
						break;
					}
				}
			}
		}
		m*=2;

		delete[] table;
		table=temp;
		temp=nullptr;
	}

	int coll=0;
	int place=h(key) % m;
	if(table[place].status==CellStatus::EMPTY){
		table[place].key=key;
		table[place].data=data;
		table[place].status=CellStatus::ACTIVE;
		++count;
		return 0;
	}

	else{
		coll=1;
		switch(mode){
		case Mode::LINEAR:
			for(int x=1;x<m,coll<m;++x){
				place=(h(key)+x)%m;
				if(table[place].status==CellStatus::EMPTY){
					table[place].key=key;
					table[place].data=data;
					table[place].status=CellStatus::ACTIVE;
					break;
				}
				else{++coll;}
			}
			break;

		case Mode::QUADRATIC:
			for(int x=1;x<m,coll<m;++x){
				place=(h(key)+(x*x))%m;
				if(table[place].status==CellStatus::EMPTY){
					table[place].key=key;
					table[place].data=data;
					table[place].status=CellStatus::ACTIVE;
					break;
				}
				else{++coll;}
			}
			break;

		case Mode::DOUBLE:
			for(int x=1;x<m,coll<m;++x){
				place=(h(key) + x*h2(key)) % m;
				if(table[place].status==CellStatus::EMPTY){
					table[place].key=key;
					table[place].data=data;
					table[place].status=CellStatus::ACTIVE;
					break;
				}
				else{++coll;}
			}
			break;
		}
		if(coll<m){++count;return coll;}
		else{return -1;}
	}

}

template<typename K,typename T>
bool HashTable<K,T>::remove(K key){
	int i=-1;
	int x=0;
	for(;x<m;++x){
		if(table[x].key==key && table[x].status==CellStatus::ACTIVE){
			++i;
			break;
		}
	}
	if(i!=-1){
		table[x].status=CellStatus::DELETED;
		--count;
		delete table[x].data;
		return true;
	}
	else{return false;}
}

template<typename K,typename T>
T* HashTable<K,T>::get(K key) const{

	T* ret=nullptr;
	for(int x=0;x<m;++x){
		if(table[x].key==key && table[x].status==CellStatus::ACTIVE){
			ret=table[x].data;
			break;
		}
	}
	return ret;
}



















