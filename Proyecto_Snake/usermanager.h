#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>

struct Usuario {
    std::string username;
    std::string password;
    int avatarId;
};

class UserManager {
public:
    // Verifica si un nombre de usuario ya está registrado en el archivo
    static bool existeUsuario(const std::string &username);

    // Registra un nuevo usuario al final del archivo usando fstream (append)
    static bool registrarUsuario(const std::string &username, const std::string &password, int avatarId);

    // Valida las credenciales de acceso al hacer login
    static bool verificarCredenciales(const std::string &username, const std::string &password);
};

#endif // USERMANAGER_H