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
    //verifica si un nombre de usuario ya está registrado en el archivo
    static bool existeUsuario(const std::string &username);

    //registra un nuevo usuario al final del archivo usando fstream (append)
    static bool registrarUsuario(const std::string &username, const std::string &password, int avatarId);

    //valida las credenciales de acceso al hacer login
    static bool verificarCredenciales(const std::string &username, const std::string &password);
};

#endif // USERMANAGER_H