#include "SnakeGame.h"
static constexpr int ScreenWidth  = 800;
static constexpr int ScreenHeight = 600;
static constexpr int BlockSize = 10;
//BlockSizeΪ10����800��600�Ĵ��ڽ�������Ϊ80��60������


//�ж�λ��x��y�Ƿ����Block����ΪwallԤ���ĺ���������û���ǽ���߼�������û�õ�
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

bool Block::BlockMoveUp()  //block�������ƶ�
{
	if (this->block_y > 0)  //block��ǰy����0 ���������ƶ��������ƶ�ʧ�ܣ�����false
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

void Block::KeepGoing()   //����֮ǰ���ƶ�״̬ �ƶ�Block
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

void Apple::RePlace()  //�����������appleλ��
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
	if (snack_state == 2) //snack�������ƶ�ʱ ���������ƶ�
	{
		move_success = 0; //�����ƶ�ʧ��
		return;
	}
	Block temp_block = this->snack_q.front();  //��ͷ����blockȡ��
	if (temp_block.BlockMoveUp())     //���temp_block�ƶ��ɹ�������������ͷ��������¼snack�ƶ�״̬
	{
		snack_q.push_front(temp_block);  
		move_success = 1;
		//snack_q.pop_back();
		snack_state = 1;
	}
	else
	{
		move_success = 0;
		snack_die = true;  //���temp_blockû���ƶ��ɹ�����˵�������˴��ڱ߿���die
	}
}

void Snack::SnackMoveDown()
{
	if (snack_state == 1)
	{
		move_success = 0; //�����ƶ�ʧ��
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
		move_success = 0; //�����ƶ�ʧ��
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
		move_success = 0; //�����ƶ�ʧ��
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

void Snack::SnackKeepMoving()  //����ǰһ��״̬�����ƶ�
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
	else //���û�Ե�����Ҫ��β����block�Ƴ�
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






