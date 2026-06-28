#include "RaylibParticles.hpp"
#include "IEntity.hpp"
#include <cstdlib>
#include <optional>
#include <cmath>

zappy::ParticlesData::ParticlesData(Vector3 displayCoords)
{
    _position = displayCoords;
    _position.y -= 0.4f;
    _alive = true;
    _lifetime = 0.0f;
    _radius = 0.1f;
    _color = raylib::Color::Pink();
    float speed = static_cast<float>(rand() % 3) / 5.0f;
    float direction = static_cast<float>(rand() % 360);
    _velocity = Vector3(speed * std::cosf(direction * DEG2RAD), 0.1, speed * std::sinf(direction * DEG2RAD));
}

zappy::ParticlesData::~ParticlesData()
{}

void zappy::ParticlesData::reset(Vector3 displayCoords)
{
    *this = ParticlesData(displayCoords);
}

zappy::RaylibParticles::RaylibParticles(): _emissionRate(-2), _dataArray(), _coords(tileCoordinates(0, 0)), _head(0), _tail(0)
{
    _displayCoords = Vector3(0, 0, 0);
    _dataArray.fill(std::nullopt);
}

zappy::RaylibParticles::RaylibParticles(zappy::tileCoordinates coords, std::pair<int, int> dimensions): _emissionRate(-2), _dataArray(), _coords(coords), _head(0), _tail(0)
{
    _displayCoords = Vector3(_coords.first - (dimensions.first / 2.0f) + 0.5f, 1.0f, _coords.second - (dimensions.second / 2.0f) + 0.5f);
    _dataArray.fill(std::nullopt);
}

zappy::RaylibParticles::~RaylibParticles()
{}

void zappy::RaylibParticles::emit()
{
    if ((_head + 1) % MAX_PARTICLES == _tail)
        return;
    _dataArray.at(_head) = ParticlesData(_displayCoords);
    _head = (_head + 1) % MAX_PARTICLES;
}

void zappy::RaylibParticles::update()
{
    if (_emissionRate < 0) {
        if (rand() % (-_emissionRate) == 0) {
            emit();
        }
    } else {
        for (int i = 0; i <= _emissionRate; i++) {
            emit();
        }
    }

    for (int i = _tail; i != _head; i = (i + 1) % MAX_PARTICLES) {
        std::optional<ParticlesData> &data = _dataArray.at(i);
        if (data.has_value()) {
            data.value()._lifetime += 1.0f/70.0f;
            data.value()._position.x += data.value()._velocity.x / 5.0f;
            data.value()._position.y += data.value()._velocity.y / 3.0f;
            data.value()._position.z += data.value()._velocity.z / 5.0f;
            data.value()._radius += 0.005f;
            data.value()._color.a -= 3;

            if (data.value()._lifetime > 1.0f) {
                data.value().reset(_displayCoords);
                data.value()._alive = false;
            }
        }
    }

    while (_tail != _head && _dataArray.at(_tail).has_value() && !_dataArray.at(_tail)-> _alive) {
        _dataArray.at(_tail).reset();
        _tail = (_tail + 1) % MAX_PARTICLES;
    }
}

int zappy::RaylibParticles::getTail()
{
    return _tail;
}

int zappy::RaylibParticles::getHead()
{
    return _head;
}

std::array<std::optional<zappy::ParticlesData>, MAX_PARTICLES> zappy::RaylibParticles::getDataArray()
{
    return _dataArray;
}
