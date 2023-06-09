#pragma once
#include<utility>
#include<list>
#include<vector>
#include"Graphics.h"
//Block对象用于定义一个像素块
class Block
{
public:
	Block() {
		block_x = 0;
		block_y = 0;
		block_state = 0;
	};
	Block(unsigned int x, unsigned int y) {
		block_x = x;
		block_y = y;
		block_state = 0;
	}
	Block(const Block& block_in)
	{
		this->block_x = block_in.block_x;
		this->block_y = block_in.block_y;
		this->block_state = 0;
	}
	Block& operator=(const Block& block_in)
	{
		this->block_x = block_in.block_x;
		this->block_y = block_in.block_y;
		this->block_state = 0;
	}
	unsigned int GetBlockX() const;  
	unsigned int GetBlockY() const;
	unsigned int GetBlockSize() const;
	bool BlockMoveUp();
	bool BlockMoveDown();
	bool BlockMoveLeft();
	bool BlockMoveRight();
	void KeepGoing();
	bool IsBlock(unsigned int x,unsigned int y) const;

private:
	unsigned int block_x;
	unsigned int block_y;
	static constexpr unsigned int block_size = 10u; //一个像素块高度和宽度为10
	unsigned int block_state;//记录Block的状态 静止/MoveUp/MoveDown/MoveLeft/MoveRight
};


class Apple
{
public:
	Apple()
	{
		apple_x = rand() % 10;
		apple_y = rand() % 20;
	}
	Apple(const Apple&) = delete;
	Apple& operator=(const Apple&) = delete;
	unsigned int GetAppleX();
	unsigned int GetAppleY();
	unsigned int GetAppleSize();
	void RePlace();
private:
	unsigned int apple_x;
	unsigned int apple_y;
	static constexpr unsigned int apple_size = 10u; //一个像素块高度和宽度为10
};


class Snack   //蛇对象
{
public:
	Snack() {
		Block block(0, 0);
		snack_q.push_back(block);
		
	}
	Snack(unsigned int start_x, unsigned int start_y) {
		Block block(start_x, start_y);
		snack_q.push_back(block);
	}
	
	Snack(const Snack&) = delete;
	Snack& operator=(const Snack&) = delete;

	bool IsSnackDie()      const;
	bool IsSnackStop()     const;
	bool IsMoveSuccess()   const;

	void SnackMoveUp();
	void SnackMoveDown();
	void SnackMoveLeft();
	void SnackMoveRight();
	void SnackKeepMoving();
	
	void SnackGrow();
	void SnackTryEat(Apple& apple);
	unsigned int GetHeadX();
	unsigned int GetHeadY();
	unsigned int GetSnackSize();
	unsigned int GetLength();
	std::list<Block>::iterator GetHead();
	std::list<Block>::iterator GetEnd();

private:
	std::list<Block> snack_q; //蛇对象的身体由一个block链表组成
	unsigned int snack_len = 1;
	bool snack_die = false;
	int snack_state = 0;
	bool move_success = false; //判断是否移动成功
	
};

//class Wall 
//{
//public:
//	Wall();
//	Wall(unsigned int start_x, unsigned int end);
//	bool IsWall(unsigned int x, unsigned int y);
//
//private:
//	std::vector<Block> vec_wall;
//};




