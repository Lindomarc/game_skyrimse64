#ifndef SKYRIMSEUNMANAGEDMODS_H
#define SKYRIMSEUNMANAGEDMODS_H


#include "gamebryounmanagedmods.h"
#include <gamegamebryo.h>


class SkyrimSEUnmangedMods : public GamebryoUnmangedMods {
public:
  SkyrimSEUnmangedMods(const GameGamebryo *game);
  ~SkyrimSEUnmangedMods();

  virtual QStringList secondaryFiles(const QString &modName) const override;
  virtual QString displayName(const QString &modName) const override;
};



#endif // SKYRIMSEUNMANAGEDMODS_H
