#include "ScriptMgr.h"
#include "Player.h"
#ifdef MOD_PLAYERBOTS
#include "Playerbots.h"
#endif
// FamWoW m22: playerbots keep stock behaviour (self-bot real players still count as players)
static bool FamM22IsBot(Player const* player)
{
    if (!player || !player->GetSession())
        return true;
#ifdef MOD_PLAYERBOTS
    PlayerbotAI* ai = GET_PLAYERBOT_AI(const_cast<Player*>(player));
    return ai != nullptr && !IsSelfBot(const_cast<Player*>(player));
#else
    return false;
#endif
}

namespace {
    constexpr uint32 WAND_ITEM_ID = 5235;

    class GivePlayerWandOnCreateScript final : public PlayerScript {
        public:
            GivePlayerWandOnCreateScript() : PlayerScript("StarterWandsScript") {

            }

            void OnPlayerFirstLogin(
                Player* player
            ) override {
                if (!FamM22IsBot(player) && player->HasSkill(SKILL_WANDS)) {
                    player->EquipNewItem(SLOT_RANGED, WAND_ITEM_ID, true);
                }
            }
    };
}

void MOD_STARTER_WANDS_INIT() {
    new GivePlayerWandOnCreateScript();
}
