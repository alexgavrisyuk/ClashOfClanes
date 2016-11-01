#include "HUDLayer.h"
#include "GameScene.h"
#include "constants.h"
#include "ManagerComponent.h"
#include "HeroInputComponent.h"
#include "ManagerFactory.h"
#include "MachineFactory.h"
#include "WarriorFactory.h"

bool HUDLayer::init()
{
	if (!Layer::init())	
	{
		return false;
	}
	
	m_command = Command::NOTHING;

	LoadSpritesForMenu();

	return true;
}

void HUDLayer::LoadSpritesForMenu()
{
	Sprite* _spriteFactoryMachine = Sprite::create(CNT_PATH_TO_RESOURCES + "HUDLayer/Coal.png");
	_spriteFactoryMachine->setScale(GameScene::m_visibleSize.width / _spriteFactoryMachine->getContentSize().width / 8,
		GameScene::m_visibleSize.height / _spriteFactoryMachine->getContentSize().height / 8);
	_spriteFactoryMachine->setPosition(GameScene::m_visibleSize.width - _spriteFactoryMachine->getBoundingBox().size.width,
		GameScene::m_visibleSize.height / 2 - 50);
	m_rectFactoryMachine = _spriteFactoryMachine->getBoundingBox();
	this->addChild(_spriteFactoryMachine);

	Sprite* _spriteFactoryWarrior = Sprite::create(CNT_PATH_TO_RESOURCES + "HUDLayer/Ruby.png");
	_spriteFactoryWarrior->setScale(GameScene::m_visibleSize.width / _spriteFactoryWarrior->getContentSize().width / 8,
		GameScene::m_visibleSize.height / _spriteFactoryWarrior->getContentSize().height / 8);
	_spriteFactoryWarrior->setPosition(GameScene::m_visibleSize.width - _spriteFactoryWarrior->getBoundingBox().size.width,
		GameScene::m_visibleSize.height / 2 - 100);
	m_rectFactoryWarrior = _spriteFactoryWarrior->getBoundingBox();
	this->addChild(_spriteFactoryWarrior);
}

void HUDLayer::Update(ManagerComponent& i_manager)
{
	if ((m_locationTouch = i_manager.m_inputComponent->GetLocationTouch()) != Point::ZERO)
	{
		if (DetermineCommandForManagerFactory())
		{
			ExecuteCommandForManagerFactory(i_manager);
			i_manager.m_inputComponent->SetZeroLocation();
		}
	}
}

bool HUDLayer::DetermineCommandForManagerFactory()
{
	if (m_rectFactoryMachine.containsPoint(m_locationTouch))
	{
		m_command = Command::CREATE_FACTORY_MACHINE;
		return true;
	}
	else if (m_rectFactoryWarrior.containsPoint(m_locationTouch))
	{
		m_command = Command::CREATE_FACTORY_WARRIOR;
		return true;
	}
	return false;
}

void HUDLayer::ExecuteCommandForManagerFactory(ManagerComponent& i_manager)
{
	switch (m_command)
	{
		case Command::CREATE_FACTORY_MACHINE:
		{
			ManagerFactory::StateManagerFactory _state = ManagerFactory::StateManagerFactory::ADD_FACTORY_MACHINE;
			i_manager.m_managerFactory->SetState(_state);

			m_command = Command::NOTHING;

			break;
		}
		case Command::CREATE_FACTORY_WARRIOR:
		{
			ManagerFactory::StateManagerFactory _state = ManagerFactory::StateManagerFactory::ADD_FACTORY_WARRIOR;
			i_manager.m_managerFactory->SetState(_state);

			m_command = Command::NOTHING;

			break;
		}
	default:
		break;
	}
}

HUDLayer::~HUDLayer()
{

}

/*
	Tasks on today(01:11:2016)
	+ Hide menu;
	- automap;
*/