#pragma once

#include "GameWindow.h"
#include "Mesh.h"
#include "Renderable.h"
#include <ShaderProgram.h>
#include <memory>
#include <AssetManager.h>

class Scene
{
public:
	Scene(GameWindow* window);
	~Scene();

	bool init();
	void shutdown();
	void render(float dt);
	void update(float dt);
	GameWindow* getWindow();

	void onKey(Key key, Action action, Modifier modifier);
	void onMouseMove(MousePosition mouseposition);
	void onMouseButton(MouseButton button, Action action, Modifier modifier);
	void onMouseScroll(double xscroll, double yscroll);
	void onFrameBufferResize(int width, int height);

private:
	GameWindow* m_window;
	AssetManager m_assets;
    ShaderProgram* m_shader;
    Mesh* m_mesh;
    GLuint vaoID, vboID, iboID;
    OBJResult objResSphere;
    OBJResult objResGround;
    Renderable* renderableGround;
    Renderable* renderableSphere1;
    Renderable* renderableSphere2;
    Renderable* renderableSphere3;
    float dtSum;

};

