#ifndef BOMBERMAN_CONFIG_H
#define BOMBERMAN_CONFIG_H

#include <nlohmann/json.hpp>

#define RESOURCE_PATH(x)  "resource/" # x

class VentanaConfig;
class Config;

//void from_json(const nlohmann::json& j, VentanaConfig& wp);
void from_json(const nlohmann::json& j, Config& config);

class VentanaConfig {
private:
    std::string titulo;
    unsigned ancho;
    unsigned alto;
    unsigned frameLimite;


public:
    const std::string &getTitulo() const;
    unsigned int getAncho() const;
    unsigned int getAlto() const;
    unsigned int getFrameLimite() const;
    bool esVerticalSyncEnable() const;

    friend void from_json(const nlohmann::json& j, VentanaConfig &wp);
};

class MapaConfig {
private:
    std::vector<int> data;
    unsigned ancho;
    unsigned alto;
    unsigned tileSize;

public:
    unsigned int getAncho() const;
    unsigned int getAlto() const;
    unsigned int getTileSize() const;
    const std::vector<int> &getData() const;

    friend void from_json(const nlohmann::json& j, MapaConfig &map);
};

class Config {
private:
    VentanaConfig ventanaConfig;
    MapaConfig mapa;

    Config();
    Config(const Config&) = delete;
    Config(Config&&) = delete;

    static Config instancia;

public:
    static const Config& getConfig();
    static void iniciar(nlohmann::json& j);
    const VentanaConfig &getVentanaConfig() const;
    const MapaConfig &getMapa() const;

    friend void from_json(const nlohmann::json& j, Config &config);
};
#endif
