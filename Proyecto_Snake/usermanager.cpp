#include "usermanager.h"
#include <fstream>
#include <QDir>

static const std::string CARPETA_GLOBAL = "usuarios_data";

//funcion auxiliar para extraer tokens CSV sin usar stringstream
static bool obtenerTokenCSV(const std::string &str, size_t &pos, std::string &token) {
    if (pos >= str.length()) return false;
    size_t nextPos = str.find(',', pos);
    if (nextPos == std::string::npos) {
        token = str.substr(pos);
        pos = str.length();
    } else {
        token = str.substr(pos, nextPos - pos);
        pos = nextPos + 1;
    }
    return true;
}

std::string UserManager::obtenerRutaArchivo(const std::string &username) {
    QDir().mkdir(QString::fromStdString(CARPETA_GLOBAL));
    return CARPETA_GLOBAL + "/" + username + ".txt";
}

bool UserManager::existeUsuario(const std::string &username) {
    std::string ruta = obtenerRutaArchivo(username);
    std::ifstream archivo(ruta);
    return archivo.is_open();
}

bool UserManager::registrarUsuario(const std::string &username, const std::string &password, int avatarId) {
    if (existeUsuario(username)) {
        return false;
    }

    Usuario nuevoUser;
    nuevoUser.username = username;
    nuevoUser.password = password;
    nuevoUser.avatarId = avatarId;
    nuevoUser.nivelActual = 1;
    nuevoUser.completoJuego = false;
    nuevoUser.skinsCompradasStr = "0";
    nuevoUser.insignias = 0;
    nuevoUser.pedazosMapa = 0;
    nuevoUser.gemas = 1000;
    nuevoUser.puntosTotales = 0;

    return guardarProgresoUsuario(nuevoUser);
}

bool UserManager::verificarCredenciales(const std::string &username, const std::string &password) {
    Usuario user;
    if (cargarDatosUsuario(username, user)) {
        return (user.password == password);
    }
    return false;
}

bool UserManager::cargarDatosUsuario(const std::string &username, Usuario &outUsuario) {
    std::string ruta = obtenerRutaArchivo(username);
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) return false;

    std::string linea;

    // linea 1: Credenciales, Avatar y Skin Actual -> username, password, avatarId, skinActual
    if (std::getline(archivo, linea)) {
        size_t pos = 0;
        std::string token;
        if (obtenerTokenCSV(linea, pos, token)) outUsuario.username = token;
        if (obtenerTokenCSV(linea, pos, token)) outUsuario.password = token;
        if (obtenerTokenCSV(linea, pos, token) && !token.empty()) {
            outUsuario.avatarId = std::stoi(token);
        } else {
            outUsuario.avatarId = 0;
        }

        // esto lee la skin actual si existe (compatible con archivos viejos y nuevos)
        if (obtenerTokenCSV(linea, pos, token) && !token.empty()) {
            outUsuario.skinActual = std::stoi(token);
        } else {
            outUsuario.skinActual = 0; // Valor por defecto si el archivo es antiguo
        }
    }

    // linea 2: Progreso del juego -> nivelActual, completoJuego, insignias, pedazosMapa, gemas, puntosTotales
    if (std::getline(archivo, linea)) {
        size_t pos = 0;
        std::string token;
        if (obtenerTokenCSV(linea, pos, token) && !token.empty()) outUsuario.nivelActual = std::stoi(token);
        if (obtenerTokenCSV(linea, pos, token)) outUsuario.completoJuego = (token == "1");
        if (obtenerTokenCSV(linea, pos, token) && !token.empty()) outUsuario.insignias = std::stoi(token);
        if (obtenerTokenCSV(linea, pos, token) && !token.empty()) outUsuario.pedazosMapa = std::stoi(token);
        if (obtenerTokenCSV(linea, pos, token) && !token.empty()) outUsuario.gemas = std::stoi(token);
        if (obtenerTokenCSV(linea, pos, token) && !token.empty()) outUsuario.puntosTotales = std::stoi(token);
    }

    // linea 3: Skins compradas como texto plano, ej: 0-1-3
    if (std::getline(archivo, linea)) {
        outUsuario.skinsCompradasStr = linea;
    }

    archivo.close();
    return true;
}

bool UserManager::guardarProgresoUsuario(const Usuario &usuario) {
    std::string ruta = obtenerRutaArchivo(usuario.username);
    std::ofstream archivo(ruta, std::ios::trunc);
    if (!archivo.is_open()) return false;

    // guardar credenciales, avatar y skinActual - linea 1
    archivo << usuario.username << ","
            << usuario.password << ","
            << usuario.avatarId << ","
            << usuario.skinActual << "\n";

    // guardar el progreso del juego - linea 2
    archivo << usuario.nivelActual << ","
            << (usuario.completoJuego ? "1" : "0") << ","
            << usuario.insignias << ","
            << usuario.pedazosMapa << ","
            << usuario.gemas << ","
            << usuario.puntosTotales << "\n";

    // guardar string de skins compradas directamente - linea 3
    archivo << usuario.skinsCompradasStr << "\n";

    archivo.close();
    return true;
}

std::string UserManager::obtenerCarpetaUsuarios()
{
    QDir().mkdir(QString::fromStdString(CARPETA_GLOBAL));
    return CARPETA_GLOBAL;
}

