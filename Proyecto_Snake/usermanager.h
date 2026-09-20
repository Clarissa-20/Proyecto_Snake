#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>

struct Usuario {
    std::string username;
    std::string password;
    int avatarId;
    int skinActual = 0;

    // progreso del juego
    int nivelActual = 1;
    bool completoJuego = false;
    std::string skinsCompradasStr = "0";
    int insignias = 0;
    int pedazosMapa = 0;
    int gemas = 1000;
    int puntosTotales = 0;

    // metodo auxiliar para verificar si ya compro una skin exactamente
    bool tieneSkin(int skinId) const {
        std::string idBuscado = "-" + std::to_string(skinId) + "-";
        std::string cadenaCompleta = "-" + skinsCompradasStr + "-";
        return cadenaCompleta.find(idBuscado) != std::string::npos;
    }
};

class UserManager {
private:
    static std::string obtenerRutaArchivo(const std::string &username);

public:
    static bool existeUsuario(const std::string &username);
    static bool registrarUsuario(const std::string &username, const std::string &password, int avatarId);
    static bool verificarCredenciales(const std::string &username, const std::string &password);
    static bool cargarDatosUsuario(const std::string &username, Usuario &outUsuario);
    static bool guardarProgresoUsuario(const Usuario &usuario);

    static std::string obtenerCarpetaUsuarios();

};

#endif // USERMANAGER_H