//submit this file
//you do NOT need to include any header in this file
//just write your BST implementation here right away



template<typename T>
bool BST<T>::add(string key, T value){
	bool temp=true;
	if (isEmpty()){
		root = new BSTNode(key,value);
		temp=true;
	}
	else if (key < root->key){
		temp=root->left.add(key,value);
	}
	else if (key > root->key){
		temp=root->right.add(key,value);
	}
	else{temp=false;}
	return temp;
}

template<typename T>
bool BST<T>::isEmpty() const{return root==nullptr;}

template<typename T>
BST<T>::BST(const BST<T>& another){
	if (another.isEmpty()){
		return;
	}
	root = new BSTNode(*another.root); // Recursive

}

template<typename T>
bool BST<T>::remove(string key){		//need to figure out if working correctly and how to return bool


	if (isEmpty()){return false;} // Item is not found; do nothing

	if (key < root->key){return root->left.remove(key);} // Remove from the left subtree

	else if (key > root->key){return root->right.remove(key);} // Remove from the right subtree

	else if (root->left.root && root->right.root && root->key==key) // Found node has 2 children
	{
		root->key = root->right.findMin()->root->key; // operator= defined?
		root->value=root->right.findMin()->root->value;

		return root->right.remove(root->right.findMin()->root->key); // min is copied; can be deleted now
	}
	else if(root->key==key) // Found node has 0 or 1 child
	{
		BSTNode* deleting_node = root; // Save the root to delete first

		root = (root->left.isEmpty()) ? root->right.root : root->left.root;
		// Set subtrees to nullptr before removal due to recursive destructor

		deleting_node->left.root = deleting_node->right.root = nullptr;

		delete deleting_node;



		return true;
	}

	else {return false;}
}

template<typename T>
const BST<T>* BST<T>::findMin() const{
	if(isEmpty()){return nullptr;}
	 const BST<T>* temp=this;
	while(temp->root->left.root!=nullptr  ){
		temp=&temp->root->left;
	}
	return temp;
}


template<typename T>
void BST<T>::merge(BST<T>& another){



	BST<T> temp;
	//temp.root=root;
	temp.root=nullptr;
	//temp=*findMin();
	//remove(findMin()->root->key);

	while(!this->isEmpty()){
		temp.add(findMin()->root->key,findMin()->root->value);
		remove(findMin()->root->key);
	}

	//BST<T> temp2=another;


	while(!another.isEmpty()){
		temp.add(another.findMin()->root->key,another.findMin()->root->value);
		another.remove(another.findMin()->root->key);
	}

	this->root=temp.root;
	temp.root=nullptr;
}


template<typename T>
T* BST<T>::get(string key) const{

	if(isEmpty()){return nullptr;}

	if(root->key==key){return &root->value;}
	if(root->key>key){return root->left.get(key);}
	if(root->key<key){return root->right.get(key);}
	return nullptr;
}







