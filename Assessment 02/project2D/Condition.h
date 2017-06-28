#pragma once
#include <vector>
#include "State.h"

class Condition
{
public:
	virtual ~Condition() {}
	virtual bool test(Object* go) const = 0; };

class Transition final
{
public:
	Transition(Condition* condition, State* target) { m_condition = condition; m_state = target; }
	~Transition() { delete m_condition; }
	bool isConditionMet(Object* gameObject) const { return m_condition->test(gameObject); }
	State* getTargetState() const { return m_state; }

private:
	State* m_state; Condition* m_condition;
};