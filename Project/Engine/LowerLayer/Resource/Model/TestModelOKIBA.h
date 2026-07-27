#pragma once
#include "ModelContext.h"

class Model;


struct TestModelOKIBA
{
	TestModelOKIBA(ModelContext::ModelCreator* modelCreator_);

	Model* cube;
	Model* player;

};

