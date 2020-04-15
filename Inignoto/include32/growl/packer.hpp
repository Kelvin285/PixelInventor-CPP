#ifndef GAME_PACKER_H

#define GAME_PACKER_H



class Node {

public:

    bool used;

    int x, y, w, h;

    Node* right = nullptr;

    Node* down = nullptr;

    Node();

    Node(int, int, int, int);

    ~Node();

};

struct Block {

    int w, h;

    int id;

    Node *fit;

    Block(int _w, int _h): w(_w), h(_h), fit(nullptr), id(-1) { }

};

class Packer {

    int maxWidth;

    int maxHeight;

public:

    Node* root;

    ~Packer();

    void fit(std::vector<Block>&);

    Node* findNode(Node* root, int&, int&);

    Node* splitNode(Node*, int&, int&);

    Node* splitArea(Node*, int&, int&);

    Node* expandPacker(int&, int&);

    Node* expandDown(int&, int&);

    Node* expandRight(int&, int&);

    inline int getWidth() const {

        return maxWidth;

    }

    inline int getHeight() const {

        return maxHeight;

    }

};

#endif