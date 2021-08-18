#include <ByteCat.h>

#include "byteCat/render/Renderer.h"
#include "imgui/imgui.h"

#include "CameraControls.h"



#include "byteCat/lua/LuaScript.h"



using namespace BC;

class ExampleLayer : public Layer
{
private:
	std::shared_ptr<GameObject> object;
	std::shared_ptr<GameObject> camera;

public:
	ExampleLayer() : Layer("ExampleLayer")
	{		
		// std::shared_ptr<Shader> shader = Shaders::Create(ByteCatShader::Standard);
		// std::shared_ptr<Texture2D> texture = Texture2D::Create("TreeTexture.png");
		// shader->setTexture(texture);
		
		object = GameLayer::CreateGameObject("Tree", Transform({ 0, -5, -100 }, { 0, 0, 0 }, { 0.5, 0.5, 0.5 }));
		object->addComponent(new Material(Shaders::Create(ByteCatShader::Standard)));
		object->addComponent(new Sprite("kat.jpg"));
		//object->addComponent(new LuaComponent("LuaTestScript.lua"));
		
		camera = GameLayer::CreateGameObject("Camera", Transform({ 0, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 }));
		camera->addComponent(new PerspectiveCamera(70, 0.01f, 1000));
		camera->addComponent(new CameraControls);
		GameLayer::SetCamera(camera);
	}

	void onUpdate() override
	{
		object->transform.rotation.y += Application::GetDelta() * 10;
	}

	void onImGuiRender() override
	{
		ImGui::Begin("Test Window");
		ImGui::Text("Hello World");
		float v[2] = {0, 1};
		ImGui::SliderFloat2("Prachtige sliders", v, -10, 10);
		ImGui::End();
	}

	void onEvent(Event& event) override
	{
		
	}
};


int lua_testFunc(lua_State* vm)
{
	float a = (float)lua_tonumber(vm, 1);
	float b = (float)lua_tonumber(vm, 2);
	LOG_INFO("a: {0}, b: {1}", a, b);
	
	float c = a * b;
	lua_pushnumber(vm, c);
	return 1;
}


class Sandbox : public Application
{
public:
	// The init of your application
	Sandbox()
	{
		//pushLayer(new ExampleLayer());

		lua_State* vm = luaL_newstate();
		luaL_openlibs(vm);
		
		LuaScript script(vm, "res/LuaTestScript.lua");

		script.linkFunction("testFunc", lua_testFunc);
		
		auto func = script.getFunction<void>("test");
		std::function<void()> callback = func;
		callback();
		
		
		BC_DEBUG_BREAK;
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