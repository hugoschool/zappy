# Implementation of a new graphical library

By default, the Zappy GUI uses the [Raylib](https://raylib.com/) graphical library.

However, if you wish to implement a different graphical library, here's how you should do it.

As an example, we're going to use the `SFML` graphical library.

First of all you would need to create a class that derives from `IGraphical` and implement all methods from it:

```cpp
class SFMLGraphical : public IGraphical {
    public:
        SFMLGraphical() = delete;
        SFMLGraphical(Map &map, GameplayEntitiesHolder& GEH);
        ~SFMLGraphical();

        void initWindow() override;
        void initCamera() override;
        bool run() override;
        void drawTiles() override;
        void drawParticles(PlayerInfo &) override;
        <...>
};
```

Next, you need to implement the `IModelHolder`:

```cpp
class SFMLModelHolder : IModelHolder {
    public:
        SFMLModelHolder();
        ~SFMLModelHolder();

        void initModels() override;
        void unloadModels() override;
        <...>
};
```

Then implementing the particles:

```cpp
class SFMLParticles : public IParticles {
    public:
        SFMLParticles();
        SFMLParticles(tileCoordinates, std::pair<int, int>);
        ~SFMLParticles();

        void update() override;
        void emit() override;
        int getTail() override;
        int getHead() override;
        <...>
};
```

Once that's done, you just need to change the currently in use graphical display in the `Zappy` class.

```cpp
_graphical(std::make_unique<zappy::SFMLGraphical>(_map, _geh))
```
