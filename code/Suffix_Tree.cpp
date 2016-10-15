#include <bits/stdc++.h>
#define END 1 << 30
#define RADIX 256
using namespace std;
struct Node {
    // represents the string [s, e)
    int s, e;
    Node *child[RADIX];
    Node *suffix;

    Node (int s, int e): s(s), e(e) {
        for (int i = 0; i < RADIX; i++)
            child[i] = nullptr;
        suffix = nullptr;
    }

    int getLength (int currentPos) {
        return min(currentPos + 1, e) - s;
    }
};
struct SuffixTree {
    string input;
    int len, currentPos, activeEdge, activeLength, remainder;
    bool firstNodeCreated;
    Node *root, *activeNode, *lastNodeCreated;

    SuffixTree (string input): input(input) {
        initialize();
    }

    void initialize () {
        len = input.size();
        root = new Node(0, 0);
        activeEdge = 0;
        activeLength = 0;
        remainder = 0;
        activeNode = root;
        currentPos = 0;
        lastNodeCreated = nullptr;
        firstNodeCreated = false;
    }

    void compute () {
        for (currentPos = 0; currentPos < len; currentPos++)
            addSuffix();
    }

    void addSuffixLink (Node* curr) {
        if (!firstNodeCreated)
            lastNodeCreated->suffix = curr;
        firstNodeCreated = false;
        lastNodeCreated = curr;
    }

    void addSuffix () {
        remainder++;
        firstNodeCreated = true;
        while (remainder > 0) {
            if (activeLength == 0)
                activeEdge = currentPos;
            if (activeNode->child[(int)input[activeEdge]] == nullptr) {
                activeNode->child[(int)input[activeEdge]] = new Node(currentPos, END);
                addSuffixLink(activeNode);
            } else {
                int nextLen = activeNode->child[(int)input[activeEdge]]->getLength(currentPos);
                if (activeLength >= nextLen) {
                    activeNode = activeNode->child[(int)input[activeEdge]];
                    activeEdge += nextLen;
                    activeLength -= nextLen;
                    continue;
                }

                if (input[activeNode->child[(int)input[activeEdge]]->s + activeLength] == input[currentPos]) {
                    activeLength++;
                    addSuffixLink(activeNode);
                    break;
                } else {
					Node* old = activeNode->child[(int)input[activeEdge]];
	                Node* split = new Node(old->s, old->s + activeLength);
	                activeNode->child[(int)input[activeEdge]] = split;
	                Node* leaf = new Node(currentPos, END);
	                split->child[(int)input[currentPos]] = leaf;
	                old->s += activeLength;
	                split->child[(int)input[old->s]] = old;
					addSuffixLink(split);
                }
            }
            remainder--;
            if (activeNode == root && activeLength > 0) {
                activeLength--;
                activeEdge = currentPos - remainder + 1;
            } else {
                if (activeNode->suffix != nullptr) {
                    activeNode = activeNode->suffix;
                } else {
                    activeNode = root;
                }
            }
        }
    }
    void printTree (Node* curr) {
		for (int i = 0; i < RADIX; i++) {
			if (curr->child[i] != nullptr) {
                cout << input.substr(curr->child[i]->s, curr->child[i]->e == END ? input.size() - curr->child[i]->s: curr->child[i]->e - curr->child[i]->s) << endl;
				printTree(curr->child[i]);
			}
		}
	}
};
