#include "WarriorFactory.h"
#include "ManagerComponent.h"
#include "HeroGraphicComponent.h"
#include "GameScene.h"
#include "GraphicComponent.h"
#include "ManagerArmy.h"
#include "HeroInputComponent.h"
#include "HUDLayer.h"
#include "MapLayer.h"

const int CNT_TIME_FOR_COMPLETE_KNIGHT_BLACK	= 10;
const int CNT_TIME_FOR_COMPLETE_KNIGHT_BRONZE	= 15;
const int CNT_TIME_FOR_COMPLETE_KNIGHT_SILVER	= 20;

const int INDEX_KNIGHT_BLACK	= 0;
const int INDEX_KNIGHT_BRONZE	= 1;
const int INDEX_KNIGHT_SILVER	= 2;

WarriorFactory::WarriorFactory()
{

}

WarriorFactory::WarriorFactory(Point i_positionVisible, MapLayer& i_mapLayer) : Factory(i_positionVisible, i_mapLayer, "Home/render4.png")
{
	m_stateWarrior	= StateFactoryWarrior::NOTHING;
	m_locationTouch = Point::ZERO;

	LoadNameForSprites();
	LoadSprites();
}
WarriorFactory::WarriorFactory(WarriorFactory& i_warriorFactory)
{

}

void WarriorFactory::LoadSprites()
{
	float _positionY = GameScene::m_visibleSize.height / 2;
	for (int i = 0; i < m_vecNameForSprites.size(); i++)
	{
		m_vecSpritesForFactoryWarrior.push_back(Sprite::create(m_vecNameForSprites[i]));
		m_vecSpritesForFactoryWarrior[i]->setScale(GameScene::m_visibleSize.width / m_vecSpritesForFactoryWarrior[i]->getContentSize().width / 15,
			GameScene::m_visibleSize.height / m_vecSpritesForFactoryWarrior[i]->getContentSize().height / 15);
		m_vecSpritesForFactoryWarrior[i]->setVisible(false);
		this->getParent()->addChild(m_vecSpritesForFactoryWarrior[i]);
	}
}

void WarriorFactory::LoadNameForSprites()
{
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Warrior/black_knight/attack_1.png");
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Warrior/bronze_knight/attack_1.png");
	m_vecNameForSprites.push_back(CNT_PATH_TO_RESOURCES + "Warrior/silver_knight/attack_1.png");
}

/*virtual*/ void WarriorFactory::Update(ManagerComponent& i_manager)
{
	switch (m_stateWarrior)
	{
		case StateFactoryWarrior::START_KNIGHT_BLACK:
		{
			if (i_manager.m_hero->CheckProductionKnightBlack())
			{
				m_timeForCompleteWarrior	= CNT_TIME_FOR_COMPLETE_KNIGHT_BLACK;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateWarrior				= StateFactoryWarrior::WORKING;
				m_stateTypeAddWarrior		= ManagerArmy::StateManagerArmy::ADD_KNIGHT_BLACK;
			}

			break;
		}
		case StateFactoryWarrior::START_KNIGHT_BRONZE:
		{
			if (i_manager.m_hero->CheckProductionKnightBronze())
			{
				m_timeForCompleteWarrior	= CNT_TIME_FOR_COMPLETE_KNIGHT_BRONZE;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateWarrior				= StateFactoryWarrior::WORKING;
				m_stateTypeAddWarrior		= ManagerArmy::StateManagerArmy::ADD_KNIGHT_BRONZE;
			}

			break;
		}
		case StateFactoryWarrior::START_KNIGHT_SILVER:
		{
			if (i_manager.m_hero->CheckProductionKnightSilver())
			{
				m_timeForCompleteWarrior	= CNT_TIME_FOR_COMPLETE_KNIGHT_SILVER;
				m_startSecond				= GraphicComponent::GetTime();
				m_stateWarrior				= StateFactoryWarrior::WORKING;
				m_stateTypeAddWarrior		= ManagerArmy::StateManagerArmy::ADD_KNIGHT_SILVER;
			}
			break;
		}
		case StateFactoryWarrior::WORKING:
		{
			if (isComplete())
			{
				m_stateWarrior = StateFactoryWarrior::LISTEN;
				i_manager.m_managerArmy->SetState(m_stateTypeAddWarrior);
				i_manager.m_managerArmy->SetPositionForWarrior(m_vecPositionWarrior[m_numberWarriorComplete]);
				++m_numberWarriorComplete;
			}
			break;
		}
		case StateFactoryWarrior::NOTHING:
		{
			Point m_positionMap = this->getParent()->getPosition();
			m_locationTouch		= i_manager.m_inputComponent->GetLocationTouch();
			Point _positionOrigin = this->getParent()->getPosition();
			_positionOrigin.x *= (-1);
			_positionOrigin.y *= (-1);
			m_locationTouch += _positionOrigin;
			if (m_rectFactoryOriginWithVisible.containsPoint(m_locationTouch) && m_locationTouch != Point::ZERO)
			{
				LoadPositionWarrior();
				ShowMenu();
				m_stateWarrior = StateFactoryWarrior::LISTEN;
				i_manager.m_inputComponent->SetZeroLocation();
			}	
			break;
		}
		case StateFactoryWarrior::LISTEN:
		{
			m_locationTouch = i_manager.m_inputComponent->GetLocationTouch();
			Point _positionOrigin = this->getParent()->getPosition();
			_positionOrigin.x *= (-1);
			_positionOrigin.y *= (-1);
			m_locationTouch += _positionOrigin;
			if (DetermineCommand())
			{
				i_manager.m_inputComponent->SetZeroLocation();
			}
			break;
		}
	default:
		break;
	}
}

bool WarriorFactory::DetermineCommand()
{
	if (m_rectForSpritesWarrior[INDEX_KNIGHT_BLACK].containsPoint(m_locationTouch))
	{
		m_stateWarrior = StateFactoryWarrior::START_KNIGHT_BLACK;
		return true;
	}
	else if (m_rectForSpritesWarrior[INDEX_KNIGHT_BRONZE].containsPoint(m_locationTouch))
	{
		m_stateWarrior = StateFactoryWarrior::START_KNIGHT_BRONZE;
		return true;
	}
	else if (m_rectForSpritesWarrior[INDEX_KNIGHT_SILVER].containsPoint(m_locationTouch))
	{
		m_stateWarrior = StateFactoryWarrior::START_KNIGHT_SILVER;
		return true;
	}
	return false;
}

using STATE_FACTORY = WarriorFactory::StateFactoryWarrior;
void WarriorFactory::SetState(STATE_FACTORY& i_stateWarrior)
{
	m_stateWarrior = i_stateWarrior;
}

WarriorFactory::StateFactoryWarrior& WarriorFactory::GetStateWarrior()
{
	return m_stateWarrior;
}

WarriorFactory::~WarriorFactory()
{

}