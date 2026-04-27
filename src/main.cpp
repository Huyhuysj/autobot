#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/binding/GameObject.hpp>
#include <Geode/binding/PlayerObject.hpp>

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
        // ----- Kiểm tra điều kiện TẮT -----
        if (!isEnabled()) return;
        if (!pl->m_player1) return;
        if (pl->m_player1->m_isDead) return;
        if (pl->m_isPaused) return;

        m_cooldown -= dt;
        if (m_cooldown > 0.0f) return;

        PlayerObject* player = pl->m_player1;
        float playerX = player->getPositionX();
        float playerY = player->getPositionY();

        // Lấy tốc độ level (m_gameSpeed có sẵn trong LevelSettingsObject)
        float speedFactor = 1.0f;
        if (pl->m_levelSettings) {
            speedFactor = pl->m_levelSettings->m_gameSpeed;
        }
        float threshold = 120.0f * speedFactor;

        float closestDist = threshold + 1.0f;
        GameObject* closestObj = nullptr;

        CCObject* obj = nullptr;
        CCARRAY_FOREACH(pl->m_objects, obj) {
            auto go = static_cast<GameObject*>(obj);
            // Chỉ quan tâm đến spike (type 2) và sawblade (type 8)
            int objType = go->m_objectType;
            if (objType != 2 && objType != 8) continue;
            // Bỏ qua nếu là trigger hay không hiển thị
            if (go->m_isTrigger) continue;
            if (!go->isVisible()) continue;

            float objX = go->getPositionX();
            float objY = go->getPositionY();

            // Vật cản phải phía trước và trong tầm
            if (objX <= playerX) continue;
            float dist = objX - playerX;
            if (dist > threshold) continue;

            // Kiểm tra cùng hàng (chênh lệch Y không quá 30)
            if (std::abs(objY - playerY) > 30.0f) continue;

            if (dist < closestDist) {
                closestDist = dist;
                closestObj = go;
            }
        }

        if (closestObj) {
            // Chỉ nhảy mới khi chưa kích hoạt cho vật cản này
            if (m_lastTriggered != closestObj) {
                // pushButton(PlayerButton::Jump, false) -> nhảy cho player 1
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

class $modify(PlayLayer) {
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
