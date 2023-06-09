#include "SnakeGame.h"
static constexpr int ScreenWidth  = 800;
static constexpr int ScreenHeight = 600;
static constexpr int BlockSize = 10;
//BlockSize为10，则800×600的窗口将被划分为80×60的坐标


//判断位置x，y是否存在Block，是为wall预留的函数，现在没添加墙的逻辑，所以没用到
bool Block::IsBlock(unsigned int x,unsigned int y) const
{
	return (x == this->block_x && y == this->block_y);
}

unsigned int Block::GetBlockX() const
{
	return this->block_x;
}

unsigned int Block::GetBlockY() const
{
	return this->block_y;
}

unsigned int Block::GetBlockSize() const
{
	return this->block_size;
}

bool Block::BlockMoveUp()  //block块向上移动
{
	if (this->block_y > 0)  //block当前y大于0 才能向上移动，否则移动失败，返回false
	{
		this->block_y--;
		return true;
	}
	else
		return false;	
}

bool Block::BlockMoveDown()
{
	if (this->block_y < (ScreenHeight / this->block_size - 1))  
	{
		this->block_y++;
		return true;
	}
	else
		return false;
}

bool Block::BlockMoveLeft()
{
	if (this->block_x > 0)
	{
		this->block_x--;
		return true;
	}
	else
		return false;
}

bool Block::BlockMoveRight()
{
	if (this->block_x < (ScreenWidth / this->block_size - 1))
	{
		this->block_x++;
		return true;
	}
	else
		return false;
}

void Block::KeepGoing()   //根据之前的移动状态 移动Block
{
	switch (block_state)
	{
	case 1:
	{
		BlockMoveUp();
		break;
	}
	case 2:
	{
		BlockMoveDown();
		break;
	}
	case 3:
	{
		BlockMoveLeft();
		break;
	}
	case 4:
	{
		BlockMoveRight();
		break;
	}
	default:
	{
		break;
	}
	}
}


unsigned int Apple::GetAppleX()
{
	return this->apple_x;
}

unsigned int Apple::GetAppleY()
{
	return this->apple_y;
}

unsigned int Apple::GetAppleSize()
{
	return this->apple_size;
}

void Apple::RePlace()  //重新随机放置apple位置
{
	this->apple_x = rand() % (ScreenWidth / BlockSize);
	this->apple_y = rand() % (ScreenHeight / BlockSize);
}


bool Snack::IsSnackDie() const
{
	return this->snack_die;
}

bool Snack::IsSnackStop() const
{
	return (this->snack_state == 0);
}



void Snack::SnackMoveUp()
{
	if (snack_state == 2) //snack在向下移动时 不能向上移动
	{
		move_success = 0; //本次移动失败
		return;
	}
	Block temp_block = this->snack_q.front();  //将头部的block取出
	if (temp_block.BlockMoveUp())     //如果temp_block移动成功，则放在链表的头部，并记录snack移动状态
	{
		snack_q.push_front(temp_block);  
		move_success = 1;
		//snack_q.pop_back();
		snack_state = 1;
	}
	else
	{
		move_success = 0;
		snack_die = true;  //如果temp_block没有移动成功，则说明碰到了窗口边框，蛇die
	}
}

void Snack::SnackMoveDown()
{
	if (snack_state == 1)
	{
		move_success = 0; //本次移动失败
		return;
	}
	Block temp_block = this->snack_q.front();
	if (temp_block.BlockMoveDown())
	{
		snack_q.push_front(temp_block);
		move_success = 1;
		//snack_q.pop_back();
		snack_state = 2;
	}
	else
	{
		move_success = 0;
		snack_die = true;
	}
}

void Snack::SnackMoveLeft()
{
	if (snack_state == 4)
	{
		move_success = 0; //本次移动失败
		return;
	}
	Block temp_block = this->snack_q.front();
	if (temp_block.BlockMoveLeft())
	{
		snack_q.push_front(temp_block);
		move_success = 1;
		//snack_q.pop_back();
		snack_state = 3;
	}
	else
	{
		move_success = 0;
		snack_die = true;
	}
}

void Snack::SnackMoveRight()
{
	if (snack_state == 3)
	{
		move_success = 0; //本次移动失败
		return;
	}
	Block temp_block = this->snack_q.front();
	if (temp_block.BlockMoveRight())
	{
		snack_q.push_front(temp_block);
		move_success = 1;
		//snack_q.pop_back();
		snack_state = 4;
	}
	else
	{
		move_success = 0;
		snack_die = true;
	}
}

void Snack::SnackKeepMoving()  //保持前一个状态继续移动
{
	Block temp_block = this->snack_q.front();
	switch (snack_state)
	{
	case 1:
	{
		SnackMoveUp();
		break;
	}
	case 2:
	{
		SnackMoveDown();
		break;
	}
	case 3:
	{
		SnackMoveLeft();
		break;
	}
	case 4:
	{
		SnackMoveRight();
		break;
	}
	default:
		break;
	}
}

bool Snack::IsMoveSuccess() const
{
	return this->move_success;
}

void Snack::SnackGrow()  
{
	this->snack_len++;
}

void Snack::SnackTryEat(Apple& apple)
{
	if (IsSnackDie()) return;
	if (!IsMoveSuccess()) return;
	if (GetHeadX() == apple.GetAppleX() && GetHeadY() == apple.GetAppleY())
	{
		apple.RePlace(); 
		SnackGrow();
	}
	else //如果没吃到，就要把尾部的block移除
	{
			snack_q.pop_back();
	}
	
}
unsigned int Snack::GetHeadX()
{
	return snack_q.front().GetBlockX();
}

unsigned int Snack::GetHeadY()
{
	return snack_q.front().GetBlockY();
}

unsigned int Snack::GetSnackSize()
{
	return snack_q.front().GetBlockSize();
}

std::list<Block>::iterator Snack::GetHead()
{
	return this->snack_q.begin();
}

std::list<Block>::iterator Snack::GetEnd()
{
	return this->snack_q.end();
}

unsigned int Snack::GetLength()
{
	return this->snack_len;
}






