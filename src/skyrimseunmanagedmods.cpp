#include "skyrimseunmanagedmods.h"


SkyrimSEUnmangedMods::SkyrimSEUnmangedMods(const GameGamebryo *game)
  : GamebryoUnmangedMods(game)
{}

SkyrimSEUnmangedMods::~SkyrimSEUnmangedMods()
{}

QStringList SkyrimSEUnmangedMods::secondaryFiles(const QString &modName) const {
  // file extension in SK is bsa
  QStringList archives;
  QDir dataDir = game()->dataDirectory();
  for (const QString &archiveName : dataDir.entryList({modName + "*.bsa"})) {
    archives.append(dataDir.absoluteFilePath(archiveName));
  }
  return archives;
}

QString SkyrimSEUnmangedMods::displayName(const QString &modName) const
{
  // unlike in earlier games, in fallout 4 the file name doesn't correspond to
  // the public name
  if (modName.compare("Dawnguard", Qt::CaseInsensitive) == 0) {
    return "Dawnguard";
  } else if (modName.compare("HearthFires", Qt::CaseInsensitive) == 0) {
    return "HearthFires";
  } else if (modName.compare("Dragonborn", Qt::CaseInsensitive) == 0) {
    return "Dragonborn";
  } else {
    return modName;
  }
}
