#pragma once

class SceneManager;

class Scene
{
protected:
    SceneManager &sceneManager;

public:
    Scene(SceneManager &manager) : sceneManager(manager) {}
    virtual ~Scene() = default;

    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};
