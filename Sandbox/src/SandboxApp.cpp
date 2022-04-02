#include <ByteCat.h>
#include "TestLayer.h"

using namespace BC;

class Sandbox : public Application
{
public:
	// The init of your application
	Sandbox()
	{
		pushLayer(new TestLayer());
	}

	// The end of your application
	~Sandbox() override
	{

	}
};

Application* BC::CreateApplication()
{
	return new Sandbox();
}