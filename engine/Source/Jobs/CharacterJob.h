#pragma once
#include "Job.h"
class Character;

class CharacterJob :
	public Job
{
public:
	CharacterJob(Character* c);
	void DoIt() override;
private:
	Character* m_character_;
};

