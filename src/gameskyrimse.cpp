#include "gameSkyrimSE.h"

#include "skyrimsedataarchives.h"
#include "skyrimsescriptextender.h"
#include "skyrimsesavegameinfo.h"
#include "skyrimsegameplugins.h"
#include "skyrimseunmanagedmods.h"

#include <pluginsetting.h>
#include "iplugingame.h"
#include <executableinfo.h>
#include <gamebryolocalsavegames.h>
#include <gamebryogameplugins.h>
#include "versioninfo.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QObject>
#include <QString>
#include <QStringList>

#include <memory>

using namespace MOBase;

GameSkyrimSE::GameSkyrimSE()
{
}

bool GameSkyrimSE::init(IOrganizer *moInfo)
{
  if (!GameGamebryo::init(moInfo)) {
    return false;
  }

  registerFeature<ScriptExtender>(new SkyrimSEScriptExtender(this));
  registerFeature<DataArchives>(new SkyrimSEDataArchives());
  registerFeature<LocalSavegames>(new GamebryoLocalSavegames(myGamesPath(), "Skyrim.ini"));
  registerFeature<SaveGameInfo>(new SkyrimSESaveGameInfo(this));
  registerFeature<GamePlugins>(new SkyrimSEGamePlugins(moInfo));
  registerFeature<UnmanagedMods>(new SkyrimSEUnmangedMods(this));

  return true;
}

QString GameSkyrimSE::gameName() const
{
  return "Skyrim Special Edition";
}

QList<ExecutableInfo> GameSkyrimSE::executables() const
{
  return QList<ExecutableInfo>()
      << ExecutableInfo("SKSE64", findInGameFolder(feature<ScriptExtender>()->loaderName()))
      << ExecutableInfo("Skyrim Special Edition", findInGameFolder(binaryName()))
      << ExecutableInfo("Skyrim Special Edition Launcher", findInGameFolder(getLauncherName()))
      << ExecutableInfo("Creation Kit", findInGameFolder("CreationKit.exe"))
      << ExecutableInfo("LOOT", getLootPath())
         ;
}

QString GameSkyrimSE::name() const
{
  return "Skyrim Special Edition Support Plugin";
}

QString GameSkyrimSE::author() const
{
  return "Linzion";
}

QString GameSkyrimSE::description() const
{
  return tr("Adds support for the game Skyrim Special Edition.\n"
            "Splash by %1").arg("nekoyoubi");
}

MOBase::VersionInfo GameSkyrimSE::version() const
{
  return VersionInfo(0, 3, 0, VersionInfo::RELEASE_BETA);
}

bool GameSkyrimSE::isActive() const
{
  return qApp->property("managed_game").value<IPluginGame*>() == this;
}

QList<PluginSetting> GameSkyrimSE::settings() const
{
  return QList<PluginSetting>();
}

void GameSkyrimSE::initializeProfile(const QDir &path, ProfileSettings settings) const
{
  if (settings.testFlag(IPluginGame::MODS)) {
    copyToProfile(localAppFolder() + "/Skyrim Special Edition", path, "plugins.txt");
    copyToProfile(localAppFolder() + "/Skyrim Special Edition", path, "loadorder.txt");
  }

  if (settings.testFlag(IPluginGame::CONFIGURATION)) {
    if (settings.testFlag(IPluginGame::PREFER_DEFAULTS)
        || !QFileInfo(myGamesPath() + "/skyrim.ini").exists()) {
      copyToProfile(gameDirectory().absolutePath(), path, "skyrim_default.ini", "skyrim.ini");
    } else {
      copyToProfile(myGamesPath(), path, "skyrim.ini");
    }

    copyToProfile(myGamesPath(), path, "skyrimprefs.ini");
  }
}

QString GameSkyrimSE::savegameExtension() const
{
  return "fos";
}

QString GameSkyrimSE::steamAPPId() const
{
  return "489830";
}

QStringList GameSkyrimSE::primaryPlugins() const {
  return {"skyrim.esm", "update.esm" };
}

QStringList GameSkyrimSE::gameVariants() const
{
  return { "Regular" };
}

QString GameSkyrimSE::gameShortName() const
{
  return "SkyrimSE";
}

QStringList GameSkyrimSE::iniFiles() const
{
    return { "skyrim.ini", "skyrimprefs.ini" };
}

QStringList GameSkyrimSE::DLCPlugins() const
{
  return { "dawnguard.esm", "hearthfires.esm", "dragonborn.esm" };
}

IPluginGame::LoadOrderMechanism GameSkyrimSE::loadOrderMechanism() const
{
  return IPluginGame::LoadOrderMechanism::PluginsTxt;
}

int GameSkyrimSE::nexusModOrganizerID() const
{
  return 0; //...
}

int GameSkyrimSE::nexusGameID() const
{
  return 0;
}
