#include "usermanager.h"
#include <fstream>
#include <sstream>
#include <QDir>

//la carpeta global donde se almacenaran los archivos de cada usuario
static const std::string CARPETA_GLOBAL = "usuarios_data";

std::string UserManager::obtenerRutaArchivo(const std::string &username) {
    //para asegurar que la carpeta global exista
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
    nuevoUser.skinsCompradas = {0};
    nuevoUser.insignias = 0;
    nuevoUser.pedazosMapa = 0;
    nuevoUser.gemas = 0;
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
    //linea 1: credenciales y Avatar -> username,password,avatarId
    if (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::getline(ss, outUsuario.username, ',');
        std::getline(ss, outUsuario.password, ',');
        std::string temp;
        if (std::getline(ss, temp, ',')) outUsuario.avatarId = std::stoi(temp);
    }

    //linea 2: progreso del juego -> nivelActual,completoJuego,insignias,pedazosMapa,gemas,puntosTotales
    if (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string temp;
        if (std::getline(ss, temp, ',')) outUsuario.nivelActual = std::stoi(temp);
        if (std::getline(ss, temp, ',')) outUsuario.completoJuego = (temp == "1");
        if (std::getline(ss, temp, ',')) outUsuario.insignias = std::stoi(temp);
        if (std::getline(ss, temp, ',')) outUsuario.pedazosMapa = std::stoi(temp);
        if (std::getline(ss, temp, ',')) outUsuario.gemas = std::stoi(temp);
        if (std::getline(ss, temp, ',')) outUsuario.puntosTotales = std::stoi(temp);
    }

    //linea 3: skins compradas separadas por guiones o comas -> id1-id2-id3 y asi
    if (std::getline(archivo, linea)) {
        outUsuario.skinsCompradas.clear();
        std::stringstream ss(linea);
        std::string skinIdStr;
        while (std::getline(ss, skinIdStr, '-')) {
            if (!skinIdStr.empty()) {
                outUsuario.skinsCompradas.push_back(std::stoi(skinIdStr));
            }
        }
    }

    archivo.close();
    return true;
}

bool UserManager::guardarProgresoUsuario(const Usuario &usuario) {
    std::string ruta = obtenerRutaArchivo(usuario.username);
    std::ofstream archivo(ruta, std::ios::trunc); //sobrescribe con el estado más actualizado
    if (!archivo.is_open()) return false;

    //guardar credenciales y avatar
    archivo << usuario.username << "," << usuario.password << "," << usuario.avatarId << "\n";

    //guardando ek progreso
    archivo << usuario.nivelActual << ","
            << (usuario.completoJuego ? "1" : "0") << ","
            << usuario.insignias << ","
            << usuario.pedazosMapa << ","
            << usuario.gemas << ","
            << usuario.puntosTotales << "\n";

    //guardamos un vector de skins compradas separadas por un - (para terne orden)
    for (size_t i = 0; i < usuario.skinsCompradas.size(); ++i) {
        archivo << usuario.skinsCompradas[i];
        if (i + 1 < usuario.skinsCompradas.size()) {
            archivo << "-";
        }
    }
    archivo << "\n";

    archivo.close();
    return true;
}