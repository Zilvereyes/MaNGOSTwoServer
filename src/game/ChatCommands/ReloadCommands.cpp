/**
 * MaNGOS is a full featured server for World of Warcraft, supporting
 * the following clients: 1.12.x, 2.4.3, 3.3.5a, 4.3.4a and 5.4.8
 *
 * Copyright (C) 2005-2022 MaNGOS <https://getmangos.eu>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * World of Warcraft, and all World of Warcraft or Warcraft art, images,
 * and lore are copyrighted by Blizzard Entertainment, Inc.
 */

#include "Chat.h"
#include "Language.h"
#include "SpellMgr.h"
#include "DisableMgr.h"
#include "World.h"
#include "MapManager.h"
#include "CreatureEventAIMgr.h"
#include "BattleGroundMgr.h"
#include "SkillExtraItems.h"
#include "SkillDiscovery.h"
#include "ItemEnchantmentMgr.h"
#include "CommandMgr.h"

/**********************************************************************
    CommandTable : reloadCommandTable
/***********************************************************************/

bool ChatHandler::HandleReloadAllSpellCommand(char* /*args*/)
{
    HandleReloadSkillDiscoveryTemplateCommand((char*)"a");
    HandleReloadSkillExtraItemTemplateCommand((char*)"a");
    HandleReloadSpellAreaCommand((char*)"a");
    HandleReloadSpellChainCommand((char*)"a");
    HandleReloadSpellElixirCommand((char*)"a");
    HandleReloadSpellLearnSpellCommand((char*)"a");
    HandleReloadSpellProcEventCommand((char*)"a");
    HandleReloadSpellBonusesCommand((char*)"a");
    HandleReloadSpellProcItemEnchantCommand((char*)"a");
    HandleReloadSpellScriptTargetCommand((char*)"a");
    HandleReloadSpellTargetPositionCommand((char*)"a");
    HandleReloadSpellThreatsCommand((char*)"a");
    HandleReloadSpellPetAurasCommand((char*)"a");
    return true;
}

// reload commands
bool ChatHandler::HandleReloadAllCommand(char* /*args*/)
{
    HandleReloadSkillFishingBaseLevelCommand((char*)"");

    HandleReloadAllAchievementCommand((char*)"");
    HandleReloadAllAreaCommand((char*)"");
    HandleReloadAutoBroadcastCommand((char*)"");
    HandleReloadAllEventAICommand((char*)"");
    HandleReloadAllLootCommand((char*)"");
    HandleReloadAllNpcCommand((char*)"");
    HandleReloadAllQuestCommand((char*)"");
    HandleReloadAllSpellCommand((char*)"");
    HandleReloadAllItemCommand((char*)"");
    HandleReloadAllGossipsCommand((char*)"");
    HandleReloadAllLocalesCommand((char*)"");

    HandleReloadMailLevelRewardCommand((char*)"");
    HandleReloadCommandCommand((char*)"");
    HandleReloadReservedNameCommand((char*)"");
    HandleReloadMangosStringCommand((char*)"");
    HandleReloadGameTeleCommand((char*)"");
    return true;
}

bool ChatHandler::HandleReloadAllAchievementCommand(char* /*args*/)
{
    HandleReloadAchievementCriteriaRequirementCommand((char*)"");
    HandleReloadAchievementRewardCommand((char*)"");
    return true;
}

bool ChatHandler::HandleReloadAllAreaCommand(char* /*args*/)
{
    // HandleReloadQuestAreaTriggersCommand((char*)""); -- reloaded in HandleReloadAllQuestCommand
    HandleReloadAreaTriggerTeleportCommand((char*)"");
    HandleReloadAreaTriggerTavernCommand((char*)"");
    HandleReloadGameGraveyardZoneCommand((char*)"");
    return true;
}

bool ChatHandler::HandleReloadAllLootCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Loot Tables...");
    LoadLootTables();
    SendGlobalSysMessage("DB tables `*_loot_template` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadAllNpcCommand(char* args)
{
    HandleReloadNpcTrainerCommand((char*)"a");
    HandleReloadNpcVendorCommand((char*)"a");
    HandleReloadPointsOfInterestCommand((char*)"a");
    HandleReloadSpellClickSpellsCommand((char*)"a");
    return true;
}

bool ChatHandler::HandleReloadAllQuestCommand(char* /*args*/)
{
    HandleReloadQuestAreaTriggersCommand((char*)"a");
    HandleReloadQuestPOICommand((char*)"a");
    HandleReloadQuestTemplateCommand((char*)"a");

    sLog.outString("Re-Loading Quests Relations...");
    sObjectMgr.LoadQuestRelations();
    SendGlobalSysMessage("DB tables `*_questrelation` and `*_involvedrelation` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadAllScriptsCommand(char* /*args*/)
{
    if (sScriptMgr.IsScriptScheduled())
    {
        PSendSysMessage("DB scripts used currently, please attempt reload later.");
        SetSentErrorMessage(true);
        return false;
    }

    sLog.outString("Re-Loading Scripts...");
    HandleReloadDBScriptsOnCreatureDeathCommand((char*)"a");
    HandleReloadDBScriptsOnGoUseCommand((char*)"a");
    HandleReloadDBScriptsOnGossipCommand((char*)"a");
    HandleReloadDBScriptsOnEventCommand((char*)"a");
    HandleReloadDBScriptsOnQuestEndCommand((char*)"a");
    HandleReloadDBScriptsOnQuestStartCommand((char*)"a");
    HandleReloadDBScriptsOnSpellCommand((char*)"a");
    SendGlobalSysMessage("DB tables `*_scripts` reloaded.");
    HandleReloadDbScriptStringCommand((char*)"a");
    return true;
}

bool ChatHandler::HandleReloadAllEventAICommand(char* /*args*/)
{
    HandleReloadEventAITextsCommand((char*)"a");
    HandleReloadEventAISummonsCommand((char*)"a");
    HandleReloadEventAIScriptsCommand((char*)"a");
    return true;
}

bool ChatHandler::HandleReloadAllGossipsCommand(char* args)
{
    if (*args != 'a')                                       // already reload from all_scripts
    {
        HandleReloadDBScriptsOnGossipCommand((char*)"a");
    }
    HandleReloadGossipMenuCommand((char*)"a");
    HandleReloadPointsOfInterestCommand((char*)"a");
    return true;
}

bool ChatHandler::HandleReloadAllItemCommand(char* /*args*/)
{
    HandleReloadPageTextsCommand((char*)"a");
    HandleReloadItemConvertCommand((char*)"a");
    HandleReloadItemEnchantementsCommand((char*)"a");
    HandleReloadItemRequiredTragetCommand((char*)"a");
    return true;
}

bool ChatHandler::HandleReloadAllLocalesCommand(char* /*args*/)
{
    HandleReloadLocalesAchievementRewardCommand((char*)"a");
    HandleReloadLocalesCreatureCommand((char*)"a");
    HandleReloadLocalesGameobjectCommand((char*)"a");
    HandleReloadLocalesGossipMenuOptionCommand((char*)"a");
    HandleReloadLocalesItemCommand((char*)"a");
    HandleReloadLocalesNpcTextCommand((char*)"a");
    HandleReloadLocalesPageTextCommand((char*)"a");
    HandleReloadLocalesPointsOfInterestCommand((char*)"a");
    HandleReloadLocalesQuestCommand((char*)"a");
    HandleReloadLocalesCommandHelpCommand((char*)"a");
    return true;
}

bool ChatHandler::HandleReloadConfigCommand(char* /*args*/)
{
    sLog.outString("Re-Loading config settings...");
    sWorld.LoadConfigSettings(true);
    sMapMgr.InitializeVisibilityDistanceInfo();
    SendGlobalSysMessage("World config settings reloaded.");
    return true;
}

bool ChatHandler::HandleReloadAchievementCriteriaRequirementCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Additional Achievement Criteria Requirements Data...");
    sAchievementMgr.LoadAchievementCriteriaRequirements();
    SendGlobalSysMessage("DB table `achievement_criteria_requirement` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadAchievementRewardCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Achievement Reward Data...");
    sAchievementMgr.LoadRewards();
    SendGlobalSysMessage("DB table `achievement_reward` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadAreaTriggerTavernCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Tavern Area Triggers...");
    sObjectMgr.LoadTavernAreaTriggers();
    SendGlobalSysMessage("DB table `areatrigger_tavern` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadAreaTriggerTeleportCommand(char* /*args*/)
{
    sLog.outString("Re-Loading AreaTrigger teleport definitions...");
    sObjectMgr.LoadAreaTriggerTeleports();
    SendGlobalSysMessage("DB table `areatrigger_teleport` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadAutoBroadcastCommand(char* /*args*/)
{
    sLog.outString("Re-Loading broadcast strings...");
    sWorld.LoadBroadcastStrings();
    SendGlobalSysMessage("Broadcast strings reloaded.");
    return true;
}

bool ChatHandler::HandleReloadCommandCommand(char* /*args*/)
{
    load_command_table = true;
    SendGlobalSysMessage("DB table `command` will be reloaded at next chat command use.");
    return true;
}

bool ChatHandler::HandleReloadCreatureQuestRelationsCommand(char* /*args*/)
{
    sLog.outString("Loading Quests Relations... (`creature_questrelation`)");
    sObjectMgr.LoadCreatureQuestRelations();
    SendGlobalSysMessage("DB table `creature_questrelation` (creature quest givers) reloaded.");
    return true;
}

bool ChatHandler::HandleReloadCreatureQuestInvRelationsCommand(char* /*args*/)
{
    sLog.outString("Loading Quests Relations... (`creature_involvedrelation`)");
    sObjectMgr.LoadCreatureInvolvedRelations();
    SendGlobalSysMessage("DB table `creature_involvedrelation` (creature quest takers) reloaded.");
    return true;
}

bool ChatHandler::HandleReloadConditionsCommand(char* /*args*/)
{
    sLog.outString("Re-Loading `conditions`... ");
    sObjectMgr.LoadConditions();
    SendGlobalSysMessage("DB table `conditions` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadCreaturesStatsCommand(char* /*args*/)
{
    sLog.outString("Re-Loading stats data...");
    sObjectMgr.LoadCreatureClassLvlStats();
    SendGlobalSysMessage("DB table `creature_template_classlevelstats` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadGossipMenuCommand(char* /*args*/)
{
    sObjectMgr.LoadGossipMenus();
    SendGlobalSysMessage("DB tables `gossip_menu` and `gossip_menu_option` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadGOQuestRelationsCommand(char* /*args*/)
{
    sLog.outString("Loading Quests Relations... (`gameobject_questrelation`)");
    sObjectMgr.LoadGameobjectQuestRelations();
    SendGlobalSysMessage("DB table `gameobject_questrelation` (gameobject quest givers) reloaded.");
    return true;
}

bool ChatHandler::HandleReloadGOQuestInvRelationsCommand(char* /*args*/)
{
    sLog.outString("Loading Quests Relations... (`gameobject_involvedrelation`)");
    sObjectMgr.LoadGameobjectInvolvedRelations();
    SendGlobalSysMessage("DB table `gameobject_involvedrelation` (gameobject quest takers) reloaded.");
    return true;
}

bool ChatHandler::HandleReloadQuestAreaTriggersCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Quest Area Triggers...");
    sObjectMgr.LoadQuestAreaTriggers();
    SendGlobalSysMessage("DB table `areatrigger_involvedrelation` (quest area triggers) reloaded.");
    return true;
}

bool ChatHandler::HandleReloadQuestTemplateCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Quest Templates...");
    sObjectMgr.LoadQuests();
    SendGlobalSysMessage("DB table `quest_template` (quest definitions) reloaded.");

    /// dependent also from `gameobject` but this table not reloaded anyway
    sLog.outString("Re-Loading GameObjects for quests...");
    sObjectMgr.LoadGameObjectForQuests();
    SendGlobalSysMessage("Data GameObjects for quests reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLootTemplatesCreatureCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Loot Tables... (`creature_loot_template`)");
    LoadLootTemplates_Creature();
    LootTemplates_Creature.CheckLootRefs();
    SendGlobalSysMessage("DB table `creature_loot_template` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLootTemplatesDisenchantCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Loot Tables... (`disenchant_loot_template`)");
    LoadLootTemplates_Disenchant();
    LootTemplates_Disenchant.CheckLootRefs();
    SendGlobalSysMessage("DB table `disenchant_loot_template` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLootTemplatesFishingCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Loot Tables... (`fishing_loot_template`)");
    LoadLootTemplates_Fishing();
    LootTemplates_Fishing.CheckLootRefs();
    SendGlobalSysMessage("DB table `fishing_loot_template` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLootTemplatesGameobjectCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Loot Tables... (`gameobject_loot_template`)");
    LoadLootTemplates_Gameobject();
    LootTemplates_Gameobject.CheckLootRefs();
    SendGlobalSysMessage("DB table `gameobject_loot_template` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLootTemplatesItemCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Loot Tables... (`item_loot_template`)");
    LoadLootTemplates_Item();
    LootTemplates_Item.CheckLootRefs();
    SendGlobalSysMessage("DB table `item_loot_template` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLootTemplatesMillingCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Loot Tables... (`milling_loot_template`)");
    LoadLootTemplates_Milling();
    LootTemplates_Milling.CheckLootRefs();
    SendGlobalSysMessage("DB table `milling_loot_template` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLootTemplatesPickpocketingCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Loot Tables... (`pickpocketing_loot_template`)");
    LoadLootTemplates_Pickpocketing();
    LootTemplates_Pickpocketing.CheckLootRefs();
    SendGlobalSysMessage("DB table `pickpocketing_loot_template` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLootTemplatesProspectingCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Loot Tables... (`prospecting_loot_template`)");
    LoadLootTemplates_Prospecting();
    LootTemplates_Prospecting.CheckLootRefs();
    SendGlobalSysMessage("DB table `prospecting_loot_template` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLootTemplatesMailCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Loot Tables... (`mail_loot_template`)");
    LoadLootTemplates_Mail();
    LootTemplates_Mail.CheckLootRefs();
    SendGlobalSysMessage("DB table `mail_loot_template` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLootTemplatesReferenceCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Loot Tables... (`reference_loot_template`)");
    LoadLootTemplates_Reference();
    SendGlobalSysMessage("DB table `reference_loot_template` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLootTemplatesSkinningCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Loot Tables... (`skinning_loot_template`)");
    LoadLootTemplates_Skinning();
    LootTemplates_Skinning.CheckLootRefs();
    SendGlobalSysMessage("DB table `skinning_loot_template` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLootTemplatesSpellCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Loot Tables... (`spell_loot_template`)");
    LoadLootTemplates_Spell();
    LootTemplates_Spell.CheckLootRefs();
    SendGlobalSysMessage("DB table `spell_loot_template` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadMangosStringCommand(char* /*args*/)
{
    sLog.outString("Re-Loading mangos_string Table!");
    sObjectMgr.LoadMangosStrings();
    SendGlobalSysMessage("DB table `mangos_string` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadNpcTextCommand(char* /*args*/)
{
    sLog.outString("Re-Loading `npc_text` Table!");
    sObjectMgr.LoadGossipText();
    SendGlobalSysMessage("DB table `npc_text` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadNpcTrainerCommand(char* /*args*/)
{
    sLog.outString("Re-Loading `npc_trainer_template` Table!");
    sObjectMgr.LoadTrainerTemplates();
    SendGlobalSysMessage("DB table `npc_trainer_template` reloaded.");

    sLog.outString("Re-Loading `npc_trainer` Table!");
    sObjectMgr.LoadTrainers();
    SendGlobalSysMessage("DB table `npc_trainer` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadNpcVendorCommand(char* /*args*/)
{
    // not safe reload vendor template tables independent...
    sLog.outString("Re-Loading `npc_vendor_template` Table!");
    sObjectMgr.LoadVendorTemplates();
    SendGlobalSysMessage("DB table `npc_vendor_template` reloaded.");

    sLog.outString("Re-Loading `npc_vendor` Table!");
    sObjectMgr.LoadVendors();
    SendGlobalSysMessage("DB table `npc_vendor` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadPointsOfInterestCommand(char* /*args*/)
{
    sLog.outString("Re-Loading `points_of_interest` Table!");
    sObjectMgr.LoadPointsOfInterest();
    SendGlobalSysMessage("DB table `points_of_interest` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadQuestPOICommand(char* /*args*/)
{
    sLog.outString("Re-Loading `quest_poi` and `quest_poi_points` Tables!");
    sObjectMgr.LoadQuestPOI();
    SendGlobalSysMessage("DB Table `quest_poi` and `quest_poi_points` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadSpellClickSpellsCommand(char* /*args*/)
{
    sLog.outString("Re-Loading `npc_spellclick_spells` Table!");
    sObjectMgr.LoadNPCSpellClickSpells();
    SendGlobalSysMessage("DB table `npc_spellclick_spells` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadReservedNameCommand(char* /*args*/)
{
    sLog.outString("Loading ReservedNames... (`reserved_name`)");
    sObjectMgr.LoadReservedPlayersNames();
    SendGlobalSysMessage("DB table `reserved_name` (player reserved names) reloaded.");
    return true;
}

bool ChatHandler::HandleReloadReputationRewardRateCommand(char* /*args*/)
{
    sLog.outString("Re-Loading `reputation_reward_rate` Table!");
    sObjectMgr.LoadReputationRewardRate();
    SendGlobalSysMessage("DB table `reputation_reward_rate` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadReputationSpilloverTemplateCommand(char* /*args*/)
{
    sLog.outString("Re-Loading `reputation_spillover_template` Table!");
    sObjectMgr.LoadReputationSpilloverTemplate();
    SendGlobalSysMessage("DB table `reputation_spillover_template` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadSkillDiscoveryTemplateCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Skill Discovery Table...");
    LoadSkillDiscoveryTable();
    SendGlobalSysMessage("DB table `skill_discovery_template` (recipes discovered at crafting) reloaded.");
    return true;
}

bool ChatHandler::HandleReloadSkillExtraItemTemplateCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Skill Extra Item Table...");
    LoadSkillExtraItemTable();
    SendGlobalSysMessage("DB table `skill_extra_item_template` (extra item creation when crafting) reloaded.");
    return true;
}

bool ChatHandler::HandleReloadScriptBindingCommand(char* /*args*/)
{
    sLog.outString("Trying to re-load `script_binding` Table!");
    if (sScriptMgr.ReloadScriptBinding())
    {
        SendGlobalSysMessage("DB table `script_binding` reloaded.");
    }
    else
    {
        SendSysMessage("DENIED: DB table `script_binding` is reloadable only in Debug build.");
    }
    return true;
}

bool ChatHandler::HandleReloadSkillFishingBaseLevelCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Skill Fishing base level requirements...");
    sObjectMgr.LoadFishingBaseSkillLevel();
    SendGlobalSysMessage("DB table `skill_fishing_base_level` (fishing base level for zone/subzone) reloaded.");
    return true;
}

bool ChatHandler::HandleReloadSpellAreaCommand(char* /*args*/)
{
    sLog.outString("Re-Loading SpellArea Data...");
    sSpellMgr.LoadSpellAreas();
    SendGlobalSysMessage("DB table `spell_area` (spell dependences from area/quest/auras state) reloaded.");
    return true;
}

bool ChatHandler::HandleReloadSpellBonusesCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Spell Bonus Data...");
    sSpellMgr.LoadSpellBonuses();
    SendGlobalSysMessage("DB table `spell_bonus_data` (spell damage/healing coefficients) reloaded.");
    return true;
}

bool ChatHandler::HandleReloadSpellChainCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Spell Chain Data... ");
    sSpellMgr.LoadSpellChains();
    SendGlobalSysMessage("DB table `spell_chain` (spell ranks) reloaded.");
    return true;
}

bool ChatHandler::HandleReloadSpellElixirCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Spell Elixir types...");
    sSpellMgr.LoadSpellElixirs();
    SendGlobalSysMessage("DB table `spell_elixir` (spell elixir types) reloaded.");
    return true;
}

bool ChatHandler::HandleReloadSpellLearnSpellCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Spell Learn Spells...");
    sSpellMgr.LoadSpellLearnSpells();
    SendGlobalSysMessage("DB table `spell_learn_spell` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadSpellProcEventCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Spell Proc Event conditions...");
    sSpellMgr.LoadSpellProcEvents();
    SendGlobalSysMessage("DB table `spell_proc_event` (spell proc trigger requirements) reloaded.");
    return true;
}

bool ChatHandler::HandleReloadSpellProcItemEnchantCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Spell Proc Item Enchant...");
    sSpellMgr.LoadSpellProcItemEnchant();
    SendGlobalSysMessage("DB table `spell_proc_item_enchant` (item enchantment ppm) reloaded.");
    return true;
}

bool ChatHandler::HandleReloadSpellScriptTargetCommand(char* /*args*/)
{
    sLog.outString("Re-Loading SpellsScriptTarget...");
    sSpellMgr.LoadSpellScriptTarget();
    SendGlobalSysMessage("DB table `spell_script_target` (spell targets selection in case specific creature/GO requirements) reloaded.");
    return true;
}

bool ChatHandler::HandleReloadSpellTargetPositionCommand(char* /*args*/)
{
    sLog.outString("Re-Loading spell target destination coordinates...");
    sSpellMgr.LoadSpellTargetPositions();
    SendGlobalSysMessage("DB table `spell_target_position` (destination coordinates for spell targets) reloaded.");
    return true;
}

bool ChatHandler::HandleReloadSpellThreatsCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Aggro Spells Definitions...");
    sSpellMgr.LoadSpellThreats();
    SendGlobalSysMessage("DB table `spell_threat` (spell aggro definitions) reloaded.");
    return true;
}

bool ChatHandler::HandleReloadSpellPetAurasCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Spell pet auras...");
    sSpellMgr.LoadSpellPetAuras();
    SendGlobalSysMessage("DB table `spell_pet_auras` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadPageTextsCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Page Texts...");
    sObjectMgr.LoadPageTexts();
    SendGlobalSysMessage("DB table `page_texts` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadItemEnchantementsCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Item Random Enchantments Table...");
    LoadRandomEnchantmentsTable();
    SendGlobalSysMessage("DB table `item_enchantment_template` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadItemConvertCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Item Converts Table...");
    sObjectMgr.LoadItemConverts();
    SendGlobalSysMessage("DB table `item_convert` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadItemRequiredTragetCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Item Required Targets Table...");
    sObjectMgr.LoadItemRequiredTarget();
    SendGlobalSysMessage("DB table `item_required_target` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadBattleEventCommand(char* /*args*/)
{
    sLog.outString("Re-Loading BattleGround Eventindexes...");
    sBattleGroundMgr.LoadBattleEventIndexes();
    SendGlobalSysMessage("DB table `gameobject_battleground` and `creature_battleground` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadEventAITextsCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Texts from `creature_ai_texts`...");
    sEventAIMgr.LoadCreatureEventAI_Texts(true);
    SendGlobalSysMessage("DB table `creature_ai_texts` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadEventAISummonsCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Summons from `creature_ai_summons`...");
    sEventAIMgr.LoadCreatureEventAI_Summons(true);
    SendGlobalSysMessage("DB table `creature_ai_summons` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadEventAIScriptsCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Scripts from `creature_ai_scripts`...");
    sEventAIMgr.LoadCreatureEventAI_Scripts();
    SendGlobalSysMessage("DB table `creature_ai_scripts` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadDbScriptStringCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Script strings from `db_script_string`...");
    sScriptMgr.LoadDbScriptStrings();
    SendGlobalSysMessage("DB table `db_script_string` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadDBScriptsOnGossipCommand(char* args)
{
    if (sScriptMgr.IsScriptScheduled())
    {
        SendSysMessage("DB scripts used currently, please attempt reload later.");
        SetSentErrorMessage(true);
        return false;
    }

    if (*args != 'a')
    {
        sLog.outString("Re-Loading Scripts from `db_scripts [type = DBS_ON_GOSSIP]`...");
    }

    sScriptMgr.LoadDbScripts(DBS_ON_GOSSIP);

    if (*args != 'a')
    {
        SendGlobalSysMessage("DB table `db_scripts [type = DBS_ON_GOSSIP]` reloaded.");
    }

    return true;
}

bool ChatHandler::HandleReloadDBScriptsOnSpellCommand(char* args)
{
    if (sScriptMgr.IsScriptScheduled())
    {
        SendSysMessage("DB scripts used currently, please attempt reload later.");
        SetSentErrorMessage(true);
        return false;
    }

    if (*args != 'a')
    {
        sLog.outString("Re-Loading Scripts from `db_scripts [type = DBS_ON_SPELL]`...");
    }

    sScriptMgr.LoadDbScripts(DBS_ON_SPELL);

    if (*args != 'a')
    {
        SendGlobalSysMessage("DB table `db_scripts [type = DBS_ON_SPELL]` reloaded.");
    }

    return true;
}

bool ChatHandler::HandleReloadDBScriptsOnQuestStartCommand(char* args)
{
    if (sScriptMgr.IsScriptScheduled())
    {
        SendSysMessage("DB scripts used currently, please attempt reload later.");
        SetSentErrorMessage(true);
        return false;
    }

    if (*args != 'a')
    {
        sLog.outString("Re-Loading Scripts from `db_scripts [type = DBS_ON_QUEST_START]`...");
    }

    sScriptMgr.LoadDbScripts(DBS_ON_QUEST_START);

    if (*args != 'a')
    {
        SendGlobalSysMessage("DB table `db_scripts [type = DBS_ON_QUEST_START]` reloaded.");
    }

    return true;
}

bool ChatHandler::HandleReloadDBScriptsOnQuestEndCommand(char* args)
{
    if (sScriptMgr.IsScriptScheduled())
    {
        SendSysMessage("DB scripts used currently, please attempt reload later.");
        SetSentErrorMessage(true);
        return false;
    }

    if (*args != 'a')
    {
        sLog.outString("Re-Loading Scripts from `db_scripts [type = DBS_ON_QUEST_END]`...");
    }

    sScriptMgr.LoadDbScripts(DBS_ON_QUEST_END);

    if (*args != 'a')
    {
        SendGlobalSysMessage("DB table `db_scripts [type = DBS_ON_QUEST_END]` reloaded.");
    }

    return true;
}

bool ChatHandler::HandleReloadDBScriptsOnEventCommand(char* args)
{
    if (sScriptMgr.IsScriptScheduled())
    {
        SendSysMessage("DB scripts used currently, please attempt reload later.");
        SetSentErrorMessage(true);
        return false;
    }

    if (*args != 'a')
    {
        sLog.outString("Re-Loading Scripts from `db_scripts [type = DBS_ON_EVENT]`...");
    }

    sScriptMgr.LoadDbScripts(DBS_ON_EVENT);

    if (*args != 'a')
    {
        SendGlobalSysMessage("DB table `db_scripts [type = DBS_ON_EVENT]` reloaded.");
    }

    return true;
}

bool ChatHandler::HandleReloadDBScriptsOnGoUseCommand(char* args)
{
    if (sScriptMgr.IsScriptScheduled())
    {
        SendSysMessage("DB scripts used currently, please attempt reload later.");
        SetSentErrorMessage(true);
        return false;
    }

    if (*args != 'a')
    {
        sLog.outString("Re-Loading Scripts from `db_scripts [type = DBS_ON_GO[_TEMPLATE]_USE]`...");
    }

    sScriptMgr.LoadDbScripts(DBS_ON_GO_USE);
    sScriptMgr.LoadDbScripts(DBS_ON_GOT_USE);

    if (*args != 'a')
    {
        SendGlobalSysMessage("DB table `db_scripts [type = DBS_ON_GO[_TEMPLATE]_USE]` reloaded.");
    }

    return true;
}

bool ChatHandler::HandleReloadDBScriptsOnCreatureDeathCommand(char* args)
{
    if (sScriptMgr.IsScriptScheduled())
    {
        SendSysMessage("DB scripts used currently, please attempt reload later.");
        SetSentErrorMessage(true);
        return false;
    }

    if (*args != 'a')
    {
        sLog.outString("Re-Loading Scripts from `db_scripts [type = DBS_ON_CREATURE_DEATH]`...");
    }

    sScriptMgr.LoadDbScripts(DBS_ON_CREATURE_DEATH);

    if (*args != 'a')
    {
        SendGlobalSysMessage("DB table `db_scripts [type = DBS_ON_CREATURE_DEATH]` reloaded.");
    }

    return true;
}

bool ChatHandler::HandleReloadGameGraveyardZoneCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Graveyard-zone links...");
    sObjectMgr.LoadGraveyardZones();
    SendGlobalSysMessage("DB table `game_graveyard_zone` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadGameTeleCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Game Tele coordinates...");
    sObjectMgr.LoadGameTele();
    SendGlobalSysMessage("DB table `game_tele` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLocalesAchievementRewardCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Locales Achievement Reward Data...");
    sAchievementMgr.LoadRewardLocales();
    SendGlobalSysMessage("DB table `locales_achievement_reward` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLocalesCreatureCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Locales Creature ...");
    sObjectMgr.LoadCreatureLocales();
    SendGlobalSysMessage("DB table `locales_creature` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLocalesGameobjectCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Locales Gameobject ... ");
    sObjectMgr.LoadGameObjectLocales();
    SendGlobalSysMessage("DB table `locales_gameobject` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLocalesGossipMenuOptionCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Locales Gossip Menu Option ... ");
    sObjectMgr.LoadGossipMenuItemsLocales();
    SendGlobalSysMessage("DB table `locales_gossip_menu_option` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLocalesItemCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Locales Item ... ");
    sObjectMgr.LoadItemLocales();
    SendGlobalSysMessage("DB table `locales_item` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLocalesNpcTextCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Locales NPC Text ... ");
    sObjectMgr.LoadGossipTextLocales();
    SendGlobalSysMessage("DB table `locales_npc_text` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLocalesCommandHelpCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Locales Command Help ... ");
    sCommandMgr.LoadCommandHelpLocale();
    //SendGlobalSysMessage("DB table `locales_command` reloaded.", SEC_MODERATOR);
    SendGlobalSysMessage("DB table `locales_command` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLocalesPageTextCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Locales Page Text ... ");
    sObjectMgr.LoadPageTextLocales();
    SendGlobalSysMessage("DB table `locales_page_text` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLocalesPointsOfInterestCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Locales Points Of Interest ... ");
    sObjectMgr.LoadPointOfInterestLocales();
    SendGlobalSysMessage("DB table `locales_points_of_interest` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadLocalesQuestCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Locales Quest ... ");
    sObjectMgr.LoadQuestLocales();
    SendGlobalSysMessage("DB table `locales_quest` reloaded.");
    return true;
}

bool ChatHandler::HandleReloadMailLevelRewardCommand(char* /*args*/)
{
    sLog.outString("Re-Loading Player level dependent mail rewards...");
    sObjectMgr.LoadMailLevelRewards();
    SendGlobalSysMessage("DB table `mail_level_reward` reloaded.");
    return true;
}



bool ChatHandler::HandleReloadDisablesCommand(char * /*args*/)
{
    sLog.outString("Re-loading Disables...");
    DisableMgr::LoadDisables();
    DisableMgr::CheckQuestDisables();
    SendGlobalSysMessage("DB table `disables` reloaded.");
    return true;
}
