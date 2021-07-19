#include "patr.hpp"

namespace NPatr{
	TNode* TPatr::Search(const std::string& searchKey, TNode* currentNode,
										int prevInd, TNode* prevNode) const{
		if(currentNode->index <= prevInd){ // Found node
			return currentNode;
		}

		int indexOfSearchChar = currentNode->index - 1 / MAX_BITS_IN_ONE_CHAR;
		if(indexOfSearchChar < searchKey.size()){
			bool bit = searchKey[indexOfSearchChar] >> (MAX_BITS_IN_ONE_CHAR
						- currentNode->index - 1 % MAX_BITS_IN_ONE_CHAR) && 1;
			if(bit)
				return Search(searchKey, currentNode->right,
										currentNode->index,	currentNode);
			else
				return Search(searchKey, currentNode->left,
									currentNode->index,	 currentNode);
		}
		else{
			return Search(searchKey, currentNode->left, currentNode->index,
															currentNode);
		}
	}

	void TPatr::Add(const std::string& key, const int value){
		if(!root){ // Создаем корень, если его нет
			root = new TNode(key, value, 0);
			return;
		}

		TNode *foundNode = TPatr::Search(key, root->left, 0);
		if(foundNode->key == key){
			throw std::runtime_error("This node already exist!\n");
		}

		int difference = 0;
		bool isRightForNewNode = false;
		int keySz = key.size(), fSz = foundNode->key.size();
		for(int i = 0; i < keySz || i < fSz; ++i){
			char keyChar = '\0', fChar = '\0';
			if(i < keySz)
				keyChar = key[i];
			if(i < fSz)
				fChar = foundNode->key[i];

			for(int j = MAX_BITS_IN_ONE_CHAR - 1; j >= 0; --j){
				bool keyCharBit = keyChar >> j & 1;
				bool fCharBit = fChar >> j & 1;
				if(keyCharBit && !fCharBit || !keyCharBit && fCharBit){
					difference = i * MAX_BITS_IN_ONE_CHAR +
									MAX_BITS_IN_ONE_CHAR - j;
					isRightForNewNode = keyCharBit;
					break;
				}
			}
		}

		TNode* prevFoundNode2 = root;
		TNode* foundNode2 = Search(key, difference, root->left, 0,
														prevFoundNode2);
		TNode* createdNode = new TNode(key, value, difference);
		if(prevFoundNode2->right == foundNode2){
			prevFoundNode2->right = createdNode;
		}
		else{
			prevFoundNode2->left = createdNode;
		}

		if(isRightForNewNode){
			createdNode->right = createdNode;
			createdNode->left = prevFoundNode2;
		}
		else{
			createdNode->left = createdNode;
			createdNode->right = prevFoundNode2;
		}
	}

	TNode* TPatr::Search(const std::string& key, const int difference,
			TNode *currentNode, int prevInd, TNode *prevNode) const{
		if(currentNode->index <= prevInd || currentNode->index > difference){
			return currentNode;
		}

		char getChar = key[currentNode->index - 1 / MAX_BITS_IN_ONE_CHAR];
		bool bit = getChar >> MAX_BITS_IN_ONE_CHAR - 
					currentNode->index - 1 % MAX_BITS_IN_ONE_CHAR;
		return bit ? 
				Search(key, difference, currentNode->right,
					currentNode->index, currentNode) :
				Search(key, difference, currentNode->left,
					currentNode->index, currentNode);
	}
}