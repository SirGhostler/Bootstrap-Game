#pragma once
#include <vector>
#include "GameState.h"
#include "Object.h"

class State
{
public:
	//virtual ~State() { for (auto t : m_transitions) delete t; }
	virtual void onEnter(Object* object) {}
	virtual void onExit(Object* object) {}
	virtual void onUpdate(Object* object, float dt) = 0;
	//void addTransition(Transition* transition) { m_transitions.push_back(transition); }
	State* getNextState(Object* gameObject)
	{
	//for (auto transition : m_transitions)
	//{
	//	if (transition->isConditionMet(gameObject)) return transition->getTargetState();
	//}
	// no state change
	return nullptr;
	}
protected:
	//std::vector<Transition*> m_transitions;
};