#ifndef SKYRIMSEGAMEPLUGINS_H
#define SKYRIMSEGAMEPLUGINS_H


#include <gamebryogameplugins.h>
#include <iplugingame.h>
#include <imoinfo.h>
#include <map>


class SkyrimSEGamePlugins : public GamebryoGamePlugins
{
public:
  SkyrimSEGamePlugins(MOBase::IOrganizer *organizer);

protected:
  virtual void writePluginList(const MOBase::IPluginList *pluginList,
                               const QString &filePath) override;
  virtual bool readPluginList(MOBase::IPluginList *pluginList,
                              const QString &filePath,
                              bool useLoadOrder) override;

private:
  std::map<QString, QByteArray> m_LastSaveHash;
};

#endif // SKYRIMSEGAMEPLUGINS_H
