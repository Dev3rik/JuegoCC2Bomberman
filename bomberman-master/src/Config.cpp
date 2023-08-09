

#include "Config.h"

void from_json(const nlohmann::json &j, VentanaConfig &wp) {
  j.at("title").get_to(wp.titulo);
  j.at("width").get_to(wp.ancho);
  j.at("height").get_to(wp.alto);
  j.at("frameLimit").get_to(wp.frameLimite);
  j.at("verticalSyncEnable").get_to(wp.verticalSyncEnable);
}

void from_json(const nlohmann::json &j, MapaConfig &map) {
  j.at("data").get_to(map.data);
  j.at("width").get_to(map.ancho);
  j.at("height").get_to(map.alto);
  j.at("tileSize").get_to(map.tileSize);
}

const std::vector<int> &MapaConfig::getData() const {
  return data;
}

unsigned int MapaConfig::getAncho() const {
  return ancho;
}

unsigned int MapaConfig::getAlto() const {
  return alto;
}

unsigned int MapaConfig::getTileSize() const {
  return tileSize;
}

void from_json(const nlohmann::json &j, Config &config) {
  j.at("window").get_to(config.ventanaConfig);
  j.at("map").get_to(config.mapa);
}

const VentanaConfig &Config::getVentanaConfig() const {
  return ventanaConfig;
}

const MapaConfig &Config::getMapa() const {
  return mapa;
}

Config Config::instancia{};

const Config &Config::getConfig() {
  return Config::instancia;
}

void Config::iniciar(nlohmann::json &j) {
  from_json(j, instancia);
}

Config::Config() {}

const std::string &VentanaConfig::getTitulo() const {
  return titulo;
}

unsigned int VentanaConfig::getAncho() const {
  return ancho;
}

unsigned int VentanaConfig::getAlto() const {
  return alto;
}

unsigned int VentanaConfig::getFrameLimite() const {
  return frameLimite;
}

bool VentanaConfig::esVerticalSyncEnable() const {
  return verticalSyncEnable;
}
