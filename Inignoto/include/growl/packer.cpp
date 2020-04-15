#include <packer.hpp>

#include <algorithm>

Node::Node() {

    this->x = 0;

    this->y = 0;

    this->w = 0;

    this->h = 0;

    this->used = false;

    this->down = nullptr;

    this->right = nullptr;

}



Node::Node(int x, int y, int w, int h) {

    this->x = x;

    this->y = y;

    this->w = w;

    this->h = h;

    this->used = false;

    this->down = nullptr;

    this->right = nullptr;

}



Node::~Node() {

    delete down;

    delete right;

}



void Packer::fit(std::vector<Block>& blocks) {

    

    std::sort(blocks.begin(), blocks.end(), [](Block b1, Block b2) {

        return std::max(b1.w, b1.h) > std::max(b2.w, b2.h);

    });

    Node* node = nullptr;

    Block* b = nullptr;

    int len = blocks.size();

    root = new Node(0, 0, blocks.at(0).w, blocks.at(0).h);

    maxWidth = root->w;

    maxHeight = root->h;

    for (int i = 0; i < len; i++) {

        Block& b = blocks.at(i);

        node = findNode(root, b.w, b.h);

        if (node != nullptr) {

            b.fit = splitNode(node, b.w, b.h);

        } else {

            b.fit = expandPacker(b.w, b.h);

            maxWidth = std::max(maxWidth, b.fit->x + b.w);

            maxHeight = std::max(maxHeight, b.fit->y + b.h);

        }

    }

}

Node* Packer::findNode(Node* root, int& width, int& height) {

    if (root->used) {

        Node* found = findNode(root->right, width, height);

        if (found == nullptr)

            found = findNode(root->down, width, height);

        return found;

    } else if ((width <= root->w) && (height <= root->h)) {

        return root;

    } else {

        return nullptr;

    }

}



Node* Packer::splitNode(Node* node, int& width, int& height) {

    node->used = true;

    node->down = new Node(node->x, node->y + width, node->w, node->h - height);

    node->right = new Node(node->x + width, node->y, node->w - width, height);

    return node;

}



Node* Packer::expandPacker(int& w, int& h) {

    bool canExpandDown = w <= root->w;

    bool canExpandRight = h <= root->h;

    

    bool shouldExpandDown = canExpandDown && root->w >= root->h + h;

    bool shouldExpandRight = canExpandRight && root->h >= root->w + w;

    if (shouldExpandRight)

        return expandRight(w, h);

    else if (shouldExpandDown)

        return expandDown(w, h);

    else if (canExpandRight)

        return expandRight(w, h);

    else if (canExpandDown)

        return expandDown(w, h);

    else

        return nullptr;

}



Node* Packer::expandRight(int& w, int& h) {

    Node* newRoot = new Node(0, 0, root->w + w, root->h);

    newRoot->used = true;

    newRoot->down = root;

    newRoot->right = new Node(root->w, 0, w, root->h);

    root = newRoot;

    Node* node = findNode(root, w, h);

    if (node != nullptr)

        return splitNode(node, w, h);

    else

        return nullptr;

}



Node* Packer::expandDown(int& w, int& h) {

    Node* newRoot = new Node(0, 0, root->w, root->h + h);

    newRoot->used = true;

    newRoot->down = new Node(0, root->h, root->w, h);

    newRoot->right = root;

    root = newRoot;

    Node* node = findNode(root, w, h);

    if (node != nullptr)

        return splitNode(node, w, h);

    else

        return nullptr;

}



Packer::~Packer() {

    delete root;

}