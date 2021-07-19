#pragma once
#include <iostream>
#include <string>

namespace NPatr{
	const int MAX_BITS_IN_ONE_CHAR = 5;

	struct TNode{
		int index, value;
		std::string key;
		TNode *left, *right;
		TNode()
			: index(0), value(0), key("") {}
		TNode(const std::string& keyIn, const int valIn, const int indexIn)
			: key(keyIn), value(valIn), index(indexIn),
				 left(this), right(nullptr) {}
	};

	class TPatr{
		private:
			TNode *root;
		public:
			TNode* Search(const std::string& searchKey,
					TNode *currentNode, int prevInd, 
					TNode *prevNode = nullptr) const;
			TNode* Search(const std::string& key, const int difference,
				TNode *currentNode, int prevInd,
				TNode *prevNode = nullptr) const;
			void Add(const std::string& key, const int value); // Throw
	};
}

/*
a -  1 00001
b -  2 00010
c -  3 00011
d -  4 00100
e -  5 00101
f -  6 00110
g -  7 00111
h -  8 01000
i -  9 01001
j - 10 01010
k - 11 01011
l - 12 01100
m - 13 01101
n - 14 01110
o - 15 01111
p - 16 10000
q - 17 10001
r - 18 10010
s - 19 10011
t - 20 10100
u - 21 10101
v - 22 10110
w - 23 10111
x - 24 11000
y - 25 11001
z - 26 11010
*/