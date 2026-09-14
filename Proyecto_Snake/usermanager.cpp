#include "usermanager.h"
#include <fstream>
#include <sstream>

bool UserManager::existeUsuario(const std::string &username) {
    std::ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) return false;

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string userFile;
        if (std::getline(ss, userFile, ',')) {
            if (userFile == username) {
                archivo.close();
                return true;
            }
        }
    }
    archivo.close();
    return false;
}

bool UserManager::registrarUsuario(const std::string &username, const std::string &password, int avatarId) {
    if (existeUsuario(username)) {
        return false; //aqui, si el usuario ya existe, no se puede duplicar
    }

    std::ofstream archivo("usuarios.txt", std::ios::app);
    if (!archivo.is_open()) return false;

    //lo guardamos en formato plano separado por comas: usuario,contraseña,avatarId (para tener un orden)
    archivo << username << "," << password << "," << avatarId << "\n";
    archivo.close();
    return true;
}

bool UserManager::verificarCredenciales(const std::string &username, const std::string &password) {
    std::ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) return false;

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string userFile, passFile;
        if (std::getline(ss, userFile, ',') && std::getline(ss, passFile, ',')) {
            if (userFile == username && passFile == password) {
                archivo.close();
                return true;
            }
        }
    }
    archivo.close();
    return false;
}