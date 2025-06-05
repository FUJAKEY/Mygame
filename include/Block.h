#ifndef BLOCK_H
#define BLOCK_H

class Player;

class Block {
public:
    virtual ~Block() = default;
    virtual void onPlayerLand(Player* p, float verticalSpeed) {}
};

#endif // BLOCK_H
