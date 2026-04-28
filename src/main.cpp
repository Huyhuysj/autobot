#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/binding/GameObject.hpp>
#include <Geode/binding/PlayerObject.hpp>
#include <Geode/binding/LevelSettingsObject.hpp>

using namespace geode::prelude;

class AutoBot {
public:
    static AutoBot* get() {
        static AutoBot instance;
        return &instance;
    }

    bool isEnabled() {
        return Mod::get()->getSettingValue<bool>("enabled");
    }

    void update(PlayLayer* pl, float dt) {
        if (!isEnabled()) return;
        if (!pl->m_player1 || pl->m_player1->m_isDead || pl->m_isPaused) return;

        m_cooldown -= dt;
        if (m_cooldown > 0.0f) return;

        float playerX = pl->m_player1->getPositionX();
        float playerY = pl->m_player1->getPositionY();

        float speedFactor = 1.0f;
        if (pl->m_levelSettings) {
            speedFactor = pl->m_levelSettings->m_gameSpeed;
        }
        float threshold = 120.0f * speedFactor;

        float closestDist = threshold + 1.0f;
        GameObject* closestObj = nullptr;

        // Duyệt qua danh sách vật thể bằng CCARRAY_FOREACH chuẩn Cocos2d-x
        if (pl->m_objects) {
            CCObject* obj = nullptr;
            CCARRAY_FOREACH(pl->m_objects, obj) {
                auto go = static_cast<GameObject*>(obj);
                
                // Chỉ quan tâm đến gai (type 2) và lưỡi cưa (type 8)
                int objType = static_cast<int>(go->m_objectType);
                if (objType != 2 && objType != 8) continue;
                if (go->m_isTrigger || !go->isVisible()) continue;

                float objX = go->getPositionX();
                float objY = go->getPositionY();

                if (objX <= playerX) continue;
                float dist = objX - playerX;
                if (dist > threshold) continue;

                // Kiểm tra độ cao tương đối
                if (std::abs(objY - playerY) > 30.0f) continue;

                if (dist < closestDist) {
                    closestDist = dist;
                    closestObj = go;
                }
            }
        }

        if (closestObj) {
            if (m_lastTriggered != closestObj) {
                // Nhảy cho Player 1
                pl->pushButton(PlayerButton::Jump, false);
                pl->releaseButton(PlayerButton::Jump, false);
                m_lastTriggered = closestObj;
                m_cooldown = m_cooldownTime;
            }
        } else {
            m_lastTriggered = nullptr;
        }
    }

private:
    GameObject* m_lastTriggered = nullptr;
    float m_cooldown = 0.0f;
    const float m_cooldownTime = 0.2f;
};

class $modify(MyPlayLayer, PlayLayer) {
    struct Fields {
        AutoBot* bot;
    };

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects))
            return false;
        m_fields->bot = AutoBot::get();
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);
        if (m_fields->bot) {
            m_fields->bot->update(this, dt);
        }
    }
};
