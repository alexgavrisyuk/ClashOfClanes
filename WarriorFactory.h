#ifndef __WARRIOR_FACTORY_H__
#define __WARRIOR_FACTORY_H__

#include "cocos2d.h"
#include "Factory.h"
#include "ManagerArmy.h"

USING_NS_CC;

class MapLayer;

class WarriorFactory : public Factory
{
public:

	enum StateFactoryWarrior
	{
		START_KNIGHT_BLACK,
		START_KNIGHT_BRONZE,
		START_KNIGHT_SILVER,
		WORKING,
		LISTEN,
		NOTHING
	};

	WarriorFactory();
	WarriorFactory(Point i_positionVisible, MapLayer& i_mapLayer);
	WarriorFactory(WarriorFactory& i_warriorFactory);

	~WarriorFactory();

	virtual void Update(ManagerComponent& i_manager);

	bool isComplete();

	StateFactoryWarrior& GetStateWarrior();

	void SetState(StateFactoryWarrior& i_stateWarrior);

	void LoadSprites();
	void LoadNameForSprites();
	void ShowMenu();
	void HideMenu();
	
	void LoadPositionWarrior();

	bool DetermineCommand();

private:
	std::chrono::time_point<std::chrono::system_clock> m_startSecond;
	int					m_timeForCompleteWarrior;
	StateFactoryWarrior m_stateWarrior;
	ManagerArmy::StateManagerArmy m_stateTypeAddWarrior;
	Vec2				m_locationTouch;
	Rect				m_rectFactoryOrigin;
	Rect				m_rectFactoryVisible;
	Rect				m_rectFactoryOriginWithVisible;

	std::vector<std::string>	m_vecNameForSprites;
	std::vector<Sprite*>		m_vecSpritesForFactoryWarrior;
	std::vector<Rect>			m_rectForSpritesWarrior;

	std::vector<Point>	m_vecPositionWarrior;
	int					m_numberWarriorComplete;
	Point				m_positionOrigin;
	Point				m_positionVisible;
	Point				m_positionOriginWithVisible;
};

#endif